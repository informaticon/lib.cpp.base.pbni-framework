---
title: src/MethodDescription.h

---

# src/MethodDescription.h



## Namespaces

| Name           |
| -------------- |
| **[Inf](/docs/doxygen/Namespaces/namespaceInf.md)**  |

## Classes

|                | Name           |
| -------------- | -------------- |
| class | **[Inf::IMethodDescription](/docs/doxygen/Classes/classInf_1_1IMethodDescription.md)**  |

## Defines

|                | Name           |
| -------------- | -------------- |
|  | **[INF_REGISTER_FUNC](/docs/doxygen/Files/MethodDescription_8h.md#define-inf-register-func)**(func, name, ...)  |




## Macros Documentation

### define INF_REGISTER_FUNC

```cpp
#define INF_REGISTER_FUNC(
    func,
    name,
    ...
)
static Inf::MethodDescription func##_desc(s_PBNI_ClassName, name, &Inf_PBNI_Class::func  __VA_OPT__(,) __VA_ARGS__)
```


**Parameters**: 

  * **func** Just the plain name of the function (not in a string) 
  * **name** A WString containing the Name to be used by PowerBuilder 
  * **...argument_names** WStrings containing the Argument names to be used by PowerBuilder 


This Macro is just there for convenienve. Use it to register a Method to an already registered Class. Make sure that the Class was already registered in the same file. Don't use this inside a header File.


## Source code

```cpp
#pragma once

#include <string>

#include <pbext.h>

#include "Framework.h"
#include "PBTypes.h"


#define INF_REGISTER_FUNC(func, name, ...) static Inf::MethodDescription func##_desc(s_PBNI_ClassName, name, &Inf_PBNI_Class::func  __VA_OPT__(,) __VA_ARGS__)

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
        inline static void SetReference(IPB_Session* session, IPB_Value* value, const Arg& arg) {
            if constexpr (std::is_reference_v<Arg>)
            {
                PBXRESULT res = Type<std::remove_reference_t<Arg>>::SetValue(session, value, arg);
                if (res != PBX_SUCCESS)
                    throw PBNI_PowerBuilderException(L"IPB_Value::Set<Type> for " + Type<std::remove_reference_t<Arg>>::GetPBName(L""), res);
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
```


-------------------------------

Updated on 2022-09-15 at 20:34:45 +0200
