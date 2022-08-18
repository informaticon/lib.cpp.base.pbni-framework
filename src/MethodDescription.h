#pragma once

#include <string>

#include <pbext.h>

#include "Framework.h"
#include "PBTypes.h"


/**
 * This Macro is just there for convenienve.
 * Use it to register a Method to an already registered Class.
 * Make sure that the Class was already registered in the same file.
 * Don't use this inside a header File.
 *
 * \param func					Just the plain name of the function (not in a string)
 * \param name					A WString containing the Name to be used by PowerBuilder
 * \param ...argument_names		WStrings containing the Argument names to be used by PowerBuilder
 */
#define INF_REGISTER_FUNC(func, name, ...) static Inf::MethodDescription func##_desc(s_PBNI_ClassName, name, &Inf_PBNI_Class::func  __VA_OPT__(,) __VA_ARGS__)

namespace Inf
{
	/**
	 * This Class is there to be extended from, so that different MethodDescription Templates can all be put in one Type.
	 */
	class IMethodDescription {
	public:
		/**
		 * This is the method called by PBNI_Class::Invoke. Calls the Class Method.
		 * This will check whether the Argument Types are correct, gather the Arguments, call the Method, set References and ReturnValue
		 * 
		 * \param object	Will be used as this
		 * \param session	Current session
		 * \param ci		Arguments for Method and returned Value
		 * \return			PBX_SUCCESS, always
		 * 
		 * \throw Inf::PBNI_IncorrectArgumentsException		If the wrong Arguments were provided
		 * \throw Inf::PBNI_PowerBuilderException			If a PowerBuilder function didnt return PBX_SUCCESS
		 */
		virtual PBXRESULT Invoke(PBNI_Class* object, IPB_Session* session, PBCallInfo* ci) = 0;

		/**
		 * Returns the definition, that was built during constructing.
		 * 
		 * \return Description
		 */
		std::wstring GetDescription() {
			return m_Description;
		}
	protected:
		std::wstring m_Description;

		/**
		 * This Function is there so parameter unpacking can be done with a tuple, it just calls SetValue if Arg is a reference.
		 * 
		 * \param session	Current Session
		 * \param value		The Value to set the reference of
		 * \param arg		The [reference] argument
		 * 
		 * \tparam	The type of the [ref] argument
		 */
		template <typename Arg>
		inline static void SetReference(IPB_Session* session, IPB_Value* value, const Arg& arg) {
			if constexpr (std::is_reference_v<Arg>)
			{
				PBXRESULT res = Type<std::remove_reference_t<Arg>>::SetValue(session, value, arg);
				if (res != PBX_SUCCESS)
					throw PBNI_PowerBuilderException(L"IPB_Value::Set<Type> for " + Type<std::remove_reference_t<Arg>>::GetPBName(L""), res);
			}
		}
	};

	/**
	 * This is the derived class, it needs to be Templated to be able to store the Function Pointer.
	 */
	template <typename Cls, typename Ret, typename... Args>
		requires (std::is_base_of_v<PBNI_Class, Cls> && !std::is_pointer_v<Ret> && !std::is_reference_v<Ret> && (!std::is_pointer_v<Args> && ...))
	class MethodDescription : public IMethodDescription
	{
	public:
		/**
		 * This will craete the Description and register itself to the ClassDescription.
		 * 
		 * \param pc_class_name		The name of the already registerd Class
		 * \param pb_method_name	The Name that PowerBuilder will use
		 * \param method			The Function Pointer
		 * \param ...arg_names		The Names of the arguments
		 */
		template <typename... ArgNames>
			requires (sizeof...(Args) == sizeof...(ArgNames))
		MethodDescription(std::wstring pc_class_name, std::wstring pb_method_name, Ret (Cls::* method)(Args...), ArgNames... arg_names)
			: m_Method(method)
		{
			// Description building
			if constexpr (std::is_void_v<Ret>)
			{
				m_Description = std::wstring(L"subroutine ") + pb_method_name + L"(";
			}
			else
			{
				m_Description = std::wstring(L"function ") + Type<Ret>::GetPBName(L"") + L" " + pb_method_name + L"(";
			}

			if constexpr (sizeof...(Args) > 0)
			{
				// Parameter pack loop
				([&] {
					if constexpr (std::is_reference_v<Args>)
					{
						m_Description += L"ref " + Type<std::remove_reference_t<Args>>::GetPBName(std::wstring(L" ") + arg_names) + L", ";
					}
					else
					{
						m_Description += Type<Args>::GetPBName(std::wstring(L" ") + arg_names) + L", ";
					}
				}(), ...);

				m_Description.resize(m_Description.size() - 2);
			}
			m_Description += L") throws u_exf_ex";

			// Register
			PBNI_Framework::GetInstance().RegisterPBMethod(pc_class_name, this);
		}

		/**
		 * This is the method called by PBNI_Class::Invoke. Calls the Class Method.
		 * This will check whether the Argument Types are correct, gather the Arguments, call the Method, set References and ReturnValue
		 *
		 * \param object	Will be used as this
		 * \param session	Current session
		 * \param ci		Arguments for Method and returned Value
		 * \return			PBX_SUCCESS, always
		 *
		 * \throw Inf::PBNI_IncorrectArgumentsException		If the wrong Arguments were provided
		 * \throw Inf::PBNI_PowerBuilderException			If a PowerBuilder function didnt return PBX_SUCCESS
		 */
		PBXRESULT Invoke(PBNI_Class* object, IPB_Session* session, PBCallInfo* ci) override
		{
			// Argument Checking
			if (ci->pArgs->GetCount() != sizeof...(Args))
				throw PBNI_IncorrectArgumentsException(object->PB_NAME, m_Description);

			pbint i = 0;
			([&] {
				IPB_Value* value = ci->pArgs->GetAt(i);
				if (!Type<std::remove_reference_t<Args>>::Assert(session, value) || std::is_reference_v<Args> != (value->IsByRef() != 0))
					throw PBNI_IncorrectArgumentsException(object->PB_NAME, m_Description, i);
			
				i++;
				}(), ...);

			// Gathering arguments
			i = 0;
			std::tuple<Cls*, std::remove_reference_t<Args>...> args{ static_cast<Cls*>(object), Type<std::remove_reference_t<Args>>::FromArgument(session, ci->pArgs->GetAt(i++), false)... };

			if constexpr (std::is_void_v<Ret>)
			{
				std::apply(m_Method, args);
			}
			else
			{
				PBXRESULT res = Type<Ret>::Return(session, ci, std::apply(m_Method, args));

				if (res != PBX_SUCCESS)
					throw PBNI_PowerBuilderException(L"IPB_Value::Set<Type> for " + Type<Ret>::GetPBName(L""), res);
			}

			// Applying references, ignore first argument (Cls* object);
			std::apply([&](Cls* _, auto... values)
				{
					pbint i = 0;
					// For some reason this doesnt work with IIFEs, so we use function instead
					(IMethodDescription::SetReference<Args>(session, ci->pArgs->GetAt(i++), values), ...);
				}, args);

			return PBX_SUCCESS;
		}

	private:
		Ret (Cls::* m_Method)(Args...);
	};
}
