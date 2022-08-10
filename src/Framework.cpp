#include "Framework.h"

#include "ClassDescription.h"
#include "Strings.h"


PBXRESULT Inf::PBNI_Class::Invoke(IPB_Session* session, pbobject obj, pbmethodID mid, PBCallInfo* ci)
{
	if (Inf::IMethodDescription* method = PBNI_Framework::GetInstance().GetClassMethod(GetPBName(), mid))
	{
		try
		{
			m_Session = session;
			return method->Invoke(this, session, ci);
		}
		//catch (const Inf::u_exf_pbni& err)
		//{
		//	// TODO figure out groups
		//	pbgroup err_group = session->FindGroup(L"u_exf_pbni", pbgroup_userobject);
		//	pbclass err_class = session->FindClass(err_group, L"u_exf_pbni");
		//	pbobject ex = session->NewObject(err_class);
		//	pbmethodID mid = session->GetMethodID(err_class, L"of_push", PBRT_FUNCTION, L"QS");

		//	PBCallInfo ci;
		//	session->InitCallInfo(err_class, mid, &ci);

		//	std::wstring err_msg = err.err_msg();
		//	ci.pArgs->GetAt(0)->SetString(L"Error");
		//	ci.pArgs->GetAt(1)->SetString(err_msg.c_str());
		//	session->InvokeObjectFunction(ex, mid, &ci);

		//	std::wstring strace = err.err_msg();
		//	ci.pArgs->GetAt(0)->SetString(L"Stacktrace");
		//	ci.pArgs->GetAt(1)->SetString(strace.c_str());
		//	session->InvokeObjectFunction(ex, mid, &ci);

		//	session->ThrowException(ex);

		//	session->FreeCallInfo(&ci);

		//	return PBX_SUCCESS;
		//}
		catch (const std::exception& err)
		{
			pbgroup err_group = session->FindGroup(L"u_tse_ex", pbgroup_userobject);
			pbclass err_class = session->FindClass(err_group, L"u_tse_ex");
			pbobject ex = session->NewObject(err_class);
			pbmethodID mid = session->GetMethodID(err_class, L"setmessage", PBRT_FUNCTION, L"QS"); // TODO What is QS?

			PBCallInfo ci;
			session->InitCallInfo(err_class, mid, &ci);

			std::wstring str = ConvertString<std::wstring>(err.what());
			ci.pArgs->GetAt(0)->SetString(str.c_str());

			session->InvokeObjectFunction(ex, mid, &ci);
			session->ThrowException(ex);

			session->FreeCallInfo(&ci);

			return PBX_SUCCESS; // TODO does success need to be returned?
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

Inf::PBNI_Class* Inf::PBNI_Framework::CreateClass(std::wstring pb_class_name)
{
	if (m_Classes.find(pb_class_name) == m_Classes.end())
	{
		return nullptr;
	}
	return m_Classes[pb_class_name]->Create();
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
