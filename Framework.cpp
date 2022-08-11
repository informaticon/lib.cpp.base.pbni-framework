#include "Framework.h"

#include "ClassDescription.h"


PBXRESULT Inf::PBNI_Class::Invoke(IPB_Session* session, pbobject obj, pbmethodID mid, PBCallInfo* ci)
{
	if (Inf::IMethodDescription* method = PBNI_Framework::GetInstance().GetClassMethod(GetPBName(), mid))
	{
		try
		{
			m_Session = session;
			return method->Invoke(this, session, ci);
		}
		//catch (const Inf::u_exf_pbni& err) TODO
		//{
		//	Inf::PBObject<L"u_exf_pbni"> pb_err(session);
		//	pb_err.Invoke(L"of_push", PBRT_FUNCTION, Inf::PBString(session, L"Error"), Inf::PBString(session, err.err_msg()));
		//	pb_err.Invoke(L"of_push", PBRT_FUNCTION, Inf::PBString(session, L"Stacktrace"), Inf::PBString(session, err.stack_trace()));
		//	// ...

		//	session->ThrowException(pb_err);

		//	return PBX_SUCCESS; // Need to return success otherwise it will throw system error
		//}
		catch (const std::exception& err)
		{
			Inf::PBObject<L"u_tse_ex"> pb_err(session);
			pb_err.Invoke(L"setmessage", PBRT_FUNCTION, Inf::PBString(session, err.what()));
			session->ThrowException(pb_err);

			return PBX_SUCCESS; // Need to return success otherwise it will throw system error
		}
	}

	return PBX_E_INVALID_METHOD_ID;
};


void Inf::PBNI_Framework::RegisterPBNI_Class(std::wstring pb_name, Inf::IClassDescription* class_desciption)
{
	m_Classes[pb_name] = class_desciption;
}

void Inf::PBNI_Framework::RegisterPBMethod(std::wstring pb_class_name, Inf::IMethodDescription* method)
{
	m_Classes[pb_class_name]->AddMethod(method);
}

Inf::PBNI_Class* Inf::PBNI_Framework::CreateClass(std::wstring pb_class_name, IPB_Session* session)
{
	if (m_Classes.find(pb_class_name) == m_Classes.end())
	{
		return nullptr;
	}
	return m_Classes[pb_class_name]->Create(session);
}

const std::wstring& Inf::PBNI_Framework::GetDescription()
{
	if (m_Description.empty())
	{
		for (auto& [class_name, class_description] : m_Classes)
		{
			m_Description += class_description->GetDescription();
		}
	}

	return m_Description;
}

Inf::IMethodDescription* Inf::PBNI_Framework::GetClassMethod(std::wstring pb_class_name, unsigned int method_id)
{
	if (m_Classes.find(pb_class_name) == m_Classes.end())
	{
		return nullptr;
	}
	return m_Classes[pb_class_name]->GetMethod(method_id);
}
