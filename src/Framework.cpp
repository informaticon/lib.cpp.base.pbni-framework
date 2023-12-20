#include "Framework.h"

#include <fstream>

#include "ClassDescription.h"


Inf::PBObject<L"u_exf_ex"> Inf::ConvertException(IPB_Session* session, const std::exception& ex)
{
    PBObject<L"u_exf_ex_pbni"> pbException(session);

    const PBNI_Exception* pbniEx = dynamic_cast<const PBNI_Exception*>(&ex);
    if (pbniEx)
    {
        auto& keyValueStore = pbniEx->GetKeyValues();
        auto pbErrorData = pbException.Call<PBObject<L"u_exf_error_data">>(L"of_init", PBString(session, pbniEx->GetMessage()));

        for (auto& [key, value] : keyValueStore)
        {
            pbErrorData.InvokeSig(L"of_push", PBRT_FUNCTION, L"Cu_exf_error_data.SA", PBString(session, key), PBString(session, value));
        }

        const std::wstring nestAs = pbniEx->GetNestAs();
        if (!nestAs.empty())
        {
            auto nestedException = pbException.Call<PBObject<L"u_exf_ex">>(L"of_nest", PBString(session, nestAs));
            if (!nestedException.IsNull())
                return nestedException;

            return ConvertException(session, PBNI_Exception(L"Tried to Nest an exception as an invalid Type", {{ L"Type", nestAs }}));
        }
    }
    else
    {
        const char* err_msg = ex.what();
        pbException
            .Call<PBObject<L"u_exf_error_data">>(L"of_init", PBString(session, err_msg))
            .InvokeSig(L"of_push", PBRT_FUNCTION, L"Cu_exf_error_data.SA", PBString(session, L"Error"), PBString(session, err_msg));
    }

    return { session, pbException };
}

Inf::PBNI_Class::PBNI_Class(IPB_Session* session, pbobject pbobj, std::wstring pb_class_name)
    : m_Session(session), m_PBObject(pbobj), m_PBName(pb_class_name)
{ }

PBXRESULT Inf::PBNI_Class::Invoke(IPB_Session* session, pbobject obj, pbmethodID mid, PBCallInfo* ci)
{
    try
    {
        if (Inf::IMethodDescription* method = PBNI_Framework::GetInstance().GetClassMethod(m_PBName, mid))
        {
            m_Session = session;
            return method->Invoke(this, session, ci);
        }
        
        return PBX_E_INVALID_METHOD_ID;
    }
    catch (const PBNI_ExceptionThrown&)
    {
        // Exception already known to powerbuilder, this is just a quick exit
    }
    catch (const std::exception& ex)
    {
        try
        {
            m_Session->ThrowException(ConvertException(m_Session, ex));
        }
        catch (const PBNI_ExceptionThrown&)
        { }
        catch (const std::exception& ex2)
        {
#ifndef NDEBUG
            // Last ditch effort

            const auto logError = [](std::wofstream& log, const std::exception& e)
            {
                const PBNI_Exception* pbniEx = dynamic_cast<const PBNI_Exception*>(&e);
                if (pbniEx)
                {
                    log << L"  PBNI Exception:\n";
                    for (const auto& [key, value] : pbniEx->GetKeyValues())
                    {
                        log << L"    " << key << L": " << value << '\n';
                    }
                }
                else
                    log << L"  " << e.what() << L'\n';
            };


            std::wofstream log("pbni.log", std::fstream::app);
            log << "Errored:\n";
            logError(log, ex2);

            log << "While trying to catch:\n";
            logError(log, ex);
#endif
            throw;
        }
    }
    
    // Need to return success even after ThrowException otherwise it will throw system error
    return PBX_SUCCESS;
};


Inf::PBNI_Class* Inf::PBNI_Framework::CreateClass(std::wstring pb_class_name, IPB_Session* session, pbobject pbobj)
{
    auto cls = m_Classes.find(pb_class_name);

    if ( cls == m_Classes.end())
    {
        return nullptr;
    }
    return cls->second->Create(session, pbobj, pb_class_name);
}

const std::wstring& Inf::PBNI_Framework::GetDescription()
{
    static std::wstring s_Description = GenerateDescription();

    return s_Description;
}

Inf::IMethodDescription* Inf::PBNI_Framework::GetClassMethod(std::wstring pb_class_name, pbmethodID method_id)
{
    auto cls = m_Classes.find(pb_class_name);

    if (cls == m_Classes.end())
    {
        return nullptr;
    }
    return cls->second->GetMethod(method_id);
}


std::wstring Inf::PBNI_Framework::GenerateDescription()
{
    std::wstring description;

    for (auto& [class_name, class_description] : m_Classes)
    {
        m_Description += class_description->GetDescription();
    }

    return m_Description;
}

void Inf::PBNI_Framework::RegisterPBClass(std::wstring pb_name, Inf::IClassDescription* class_desciption)
{
    m_Classes[pb_name] = class_desciption;
}

void Inf::PBNI_Framework::RegisterPBMethod(std::wstring pb_class_name, Inf::IMethodDescription* method)
{
    auto cls = m_Classes.find(pb_class_name);

    if (cls == m_Classes.end())
    {
        std::wstring msg = L"Adding a MethodDescription to a Class that hasnt been Registered yet (" + pb_class_name + L"::" + method->GetDescription() + L")";
        MessageBoxW(NULL, msg.c_str(), L"[PBNI Warning]", MB_OK);
    }
    else
    {
        cls->second->AddMethod(method);
    }
}

