#include "Framework.h"

#include "ClassDescription.h"


Inf::PBNI_Class::PBNI_Class(IPB_Session* session, pbobject pbobj, std::wstring pb_class_name)
	: m_Session(session), m_PBObject(pbobj), PB_NAME(pb_class_name)
{ }

PBXRESULT Inf::PBNI_Class::Invoke(IPB_Session* session, pbobject obj, pbmethodID mid, PBCallInfo* ci)
{
	try
	{
		if (Inf::IMethodDescription* method = PBNI_Framework::GetInstance().GetClassMethod(PB_NAME, mid))
		{
			m_Session = session;
			return method->Invoke(this, session, ci);
		}
		
		return PBX_E_INVALID_METHOD_ID;
	}
	catch (const Inf::PBNI_Exception& ex)
	{
		auto& key_value_store = ex.GetKeyValues();

		Inf::PBObject<L"u_exf_ex_pbni"> pbni_exception(m_Session);
		auto pbni_error_data = pbni_exception.Invoke<Inf::PBObject<L"u_exf_error_data">>(L"of_init", PBRT_FUNCTION, Inf::PBString(m_Session, key_value_store.at(L"Error")));

		for (auto& [key, value] : key_value_store)
		{
			pbni_error_data.InvokeSig(L"of_push", PBRT_FUNCTION, L"Cu_exf_error_data.SA", Inf::PBString(m_Session, key), Inf::PBString(m_Session, value));
		}

		m_Session->ThrowException(pbni_exception);

		return PBX_SUCCESS; // Need to return success otherwise it will throw system error
	}
	catch (const std::exception& err)
	{
		Inf::PBObject<L"u_exf_ex_pbni"> pbni_exception(session);

		const char* err_msg = err.what();
		auto pbni_error_data = pbni_exception.Invoke<Inf::PBObject<L"u_exf_error_data">>(L"of_init", PBRT_FUNCTION, Inf::PBString(session, err_msg));
		pbni_error_data.InvokeSig(L"of_push", PBRT_FUNCTION, L"Cu_exf_error_data.SA", Inf::PBString(m_Session, L"Error"), Inf::PBString(m_Session, err_msg));

		session->ThrowException(pbni_exception);

		return PBX_SUCCESS; // Need to return success otherwise it will throw system error
	}
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
