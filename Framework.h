#pragma once

#include <string>
#include <unordered_map>

#include <pbext.h>


namespace Inf
{
	class IClassDescription;
	class IMethodDescription;


	class PBNI_Class : public IPBX_NonVisualObject
	{
	public:
		PBNI_Class() : m_Session(nullptr) {};
		virtual ~PBNI_Class() {};
		virtual inline std::wstring GetPBName() = 0;

		void Destroy() override { delete this; }
		PBXRESULT Invoke(IPB_Session* session, pbobject obj, pbmethodID  mid, PBCallInfo* ci) override;
	
	protected:
		IPB_Session* m_Session;
	};


	class PBNI_Framework
	{
	public:

		void RegisterPBNI_Class(std::wstring pb_class_name, IClassDescription* class_desciption);
		void RegisterPBMethod(std::wstring pb_class_name, IMethodDescription* method_description);

		PBNI_Class* CreateClass(std::wstring pb_class_name, IPB_Session* session);

		const std::wstring& GetDescription();
		IMethodDescription* GetClassMethod(std::wstring pb_class_name, unsigned int method_id);

		// Singleton functions
		static PBNI_Framework& GetInstance()
		{
			static PBNI_Framework instance;
			return instance;
		}
		PBNI_Framework(PBNI_Framework const&) = delete;
		void operator=(PBNI_Framework const&) = delete;

	private:
		PBNI_Framework() {}

		std::unordered_map<std::wstring, IClassDescription*> m_Classes;
		std::wstring m_Description;
	};
};
