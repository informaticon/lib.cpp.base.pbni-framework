#pragma once

#include <string>
#include <unordered_map>

#include <pbext.h>


namespace Inf
{
	class IClassDescription;
	class IMethodDescription;

	/**
	 * PBNI_Class is the Base Class for all Classes that you want to be used inside PowerBuilder.
	 * You just need to extend this Class and override GetPBName().
	 */
	class PBNI_Class : public IPBX_NonVisualObject
	{
	public:
		const std::wstring PB_NAME;

		/**
		* 
		* 
		* \param session		Current Session
		* \param pbobj			The PowerBuilder object representing this
		* \param pb_class_name	The name of the class in powerbuilder
		*/
		PBNI_Class(IPB_Session* session, pbobject pbobj, std::wstring pb_class_name);
		virtual ~PBNI_Class() {};

		/**
		 * This Method will be called by PowerBuilder once it no longer needs this Object, don't use it.
		 * Put your cleanup Code inside the Destructor.
		 */
		void Destroy() override { delete this; }

		/**
		 * This Method will be called when PowerBuilder wants to call a Method to this specific Object.
		 * 
		 * \param session	The PowerBuilder session that is used to get Arguments and create Objects
		 * \param obj		This is the PowerBuilder reference to this
		 * \param mid		This is the ID of the Method that gets called, it is in the Order of the Description
		 * \param ci		These are the Arguments and return Value
		 * \return			Returns PBX_SUCCESS if the Method exists, otherwise PBX_E_INVALID_METHOD_ID
		 */
		PBXRESULT Invoke(IPB_Session* session, pbobject obj, pbmethodID  mid, PBCallInfo* ci) override;
	
	protected:
		IPB_Session* m_Session;
		pbobject m_PBObject;
	};

	/**
	 * This is a Singleton class, whose purpose is holding and creating/invoking all Class and Method Descriptions.
	 */
	class PBNI_Framework
	{
	public:
		/**
		 * This method is just called from dllmain.cpp::PBX_CreateNonVisualObject.
		 * It tries to find the Class from the Class name and create a new Object.
		 * 
		 * \param pb_class_name		Name of the Class in PowerBuilder
		 * \param session			Current session
		 * \param pbobj				The PowerBuilder reference to the to be created Object
		 * \return					The Created Class or nullptr, if no class was found
		 */
		PBNI_Class* CreateClass(std::wstring pb_class_name, IPB_Session* session, pbobject pbobj);

		/**
		 * This method is just there to be called from dllmain.cpp::PBX_GetDescription.
		 * It loops through the registered Classes and gathers all Method Descriptions, then returns the entire thing.
		 * 
		 * \return	The Description as Unicode
		 */
		const std::wstring& GetDescription();
		/**
		 * This method is just used in PBNI_Class::Invoke.
		 * It tries to find the invoked method.
		 * 
		 * \param pb_class_name		The Name of PowerBuilder Class
		 * \param method_id			The ID of the Method, in order of registration
		 * \return					A pointer to the Method's Description
		 */
		IMethodDescription* GetClassMethod(std::wstring pb_class_name, pbmethodID method_id);

		/**
		 * Static function to get the singleton instance of PBNI_Framework.
		 * 
		 * \return 
		 */
		static PBNI_Framework& GetInstance()
		{
			static PBNI_Framework instance;
			return instance;
		}
		PBNI_Framework(PBNI_Framework const&) = delete;
		void operator=(PBNI_Framework const&) = delete;

	private:
		template <typename Cls>
			requires (std::is_base_of_v<PBNI_Class, Cls>)
		friend class ClassDescription;

		template <typename Cls, typename Ret, typename... Args>
			requires (std::is_base_of_v<PBNI_Class, Cls> && !std::is_pointer_v<Ret> && !std::is_reference_v<Ret> && (!std::is_pointer_v<Args> && ...))
		friend class MethodDescription;


		PBNI_Framework() {}

		/**
		 * Only used in PBNI_Framework::GetDescription to initialize a static variable.
		 * 
		 * \return The created Description
		 */
		std::wstring GenerateDescription();
		
		/**
		 * This is the Method that is called by every ClassDescription when it gets constructed.
		 * It will add a Pointer to the ClassDescription to a map.
		 * The ClassDescription should have a Lifetime as long as the dll.
		 * You should not call this Method by yourself.
		 * 
		 * \param pb_class_name		The Name that will be used by PowerBuilder
		 * \param class_desciption	The Pointer to be registered
		 */
		void RegisterPBClass(std::wstring pb_class_name, IClassDescription* class_desciption);

		/**
		 * This is the Method that is called by every MethodDescription when it gets constructed.
		 * It will get the ClassDescription of pb_class_name and register itself to it.
		 * The MethodDescriptio should have a Lifetime as long as the dll.
		 * You should not call this Method by yourself.
		 *
		 * \param pb_class_name		The Name of the already registered Class
		 * \param class_desciption	The Pointer to be registered
		 */
		void RegisterPBMethod(std::wstring pb_class_name, IMethodDescription* method_description);


		std::unordered_map<std::wstring, IClassDescription*> m_Classes;
		std::wstring m_Description;
	};
};
