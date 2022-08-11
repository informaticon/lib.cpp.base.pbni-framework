#pragma once

#include <string>

#include <pbext.h>

#include "Framework.h"
#include "PBTypes.h"


#define INF_REGISTER_FUNC(func, ...) static Inf::MethodDescription func##_desc(s_PBNI_ClassName, L""#func, &Inf_PBNI_Class::func  __VA_OPT__(,) __VA_ARGS__)

namespace Inf
{
	class IMethodDescription {
	public:
		virtual PBXRESULT Invoke(PBNI_Class* object, IPB_Session* session, PBCallInfo* ci) = 0;

		std::wstring GetDescription() {
			return m_Description;
		}
	protected:
		std::wstring m_Description;

		template <typename Arg>
		inline static void FreeArgument(IPB_Session* session, IPB_Value* value, const Arg arg) {
			if constexpr (std::is_reference_v<Arg>)
			{
				Inf::Type<std::remove_reference_t<Arg>>::SetValue(session, value, arg);
			}
		}
	};

	template <typename Cls, typename Ret, typename... Args>
		requires (std::is_base_of_v<PBNI_Class, Cls> && !std::is_pointer_v<Ret> && !std::is_reference_v<Ret> && (!std::is_pointer_v<Args> && ...))
	class MethodDescription : public IMethodDescription
	{
	public:
		template <typename... ArgNames>
			requires (sizeof...(Args) == sizeof...(ArgNames))
		MethodDescription(std::wstring pc_class_name, std::wstring pb_method_name, Ret(Cls::* method)(Args...), ArgNames... arg_names)
			: m_Method(method)
		{
			// Description building
			if constexpr (std::is_void_v<Ret>)
			{
				m_Description = std::wstring(L"subroutine ") + pb_method_name + L"(";
			}
			else
			{
				m_Description = std::wstring(L"function ") + Inf::Type<Ret>::GetPBName(L"") + L" " + pb_method_name + L"(";
			}

			if constexpr (sizeof...(Args) > 0)
			{
				([&] {
					if constexpr (std::is_reference_v<Args>)
					{
						m_Description += L"ref " + Inf::Type<std::remove_reference_t<Args>>::GetPBName(std::wstring(L" ") + arg_names) + L", ";
					}
					else
					{
						m_Description += Inf::Type<Args>::GetPBName(std::wstring(L" ") + arg_names) + L", ";
					}
					}(), ...);

				m_Description.resize(m_Description.size() - 2);
			}
			m_Description += L")";

			PBNI_Framework::GetInstance().RegisterPBMethod(pc_class_name, this);
		}

		PBXRESULT Invoke(PBNI_Class* object, IPB_Session* session, PBCallInfo* ci) override
		{
			// Argument Checking
			if (ci->pArgs->GetCount() != sizeof...(Args))
				throw Inf::u_exf_pbni(L"Malformed PBNI description, Method invoked with wrong number of arguments (" + m_Description + L")");

			pbint i = 0;
			([&] {
				IPB_Value* value = ci->pArgs->GetAt(i);
				if (!Type<std::remove_reference_t<Args>>::Assert(session, value) || std::is_reference_v<Args> != (value->IsByRef() != 0))
				{
					throw Inf::u_exf_pbni(std::wstring(L"Malformed PBNI description, Method invoked with wrong arguments type (Argument position "\
						+ std::to_wstring(i) + L" in method " + m_Description + L")"));
				}
				i++;
				}(), ...);

			// Gathering arguments
			i = 0;
			std::tuple<Cls*, std::remove_reference_t<Args>...> args{ static_cast<Cls*>(object), Inf::Type<std::remove_reference_t<Args>>::FromArgument(session, ci->pArgs->GetAt(i++))... };

			if constexpr (std::is_void_v<Ret>)
			{
				std::apply(m_Method, args);
			}
			else
			{
				Inf::Type<Ret>::Return(session, ci, std::apply(m_Method, args));
			}

			// Applying references, ignore first argument (Cls* object);
			std::apply([&](Cls* _, auto... values)
				{
					pbint i = 0;
					// For some reason this doestn work with IIFEs, so we use function instead
					(IMethodDescription::FreeArgument<Args>(session, ci->pArgs->GetAt(i++), values), ...);
				}, args);

			return PBX_SUCCESS;
		}

	private:
		Ret(Cls::* m_Method)(Args...);
	};
}
