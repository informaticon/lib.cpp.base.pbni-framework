---
title: src/ClassDescription.h

---

# src/ClassDescription.h



## Namespaces

| Name           |
| -------------- |
| **[Inf](/docs/doxygen/Namespaces/namespaceInf.md)**  |

## Classes

|                | Name           |
| -------------- | -------------- |
| class | **[Inf::IClassDescription](/docs/doxygen/Classes/classInf_1_1IClassDescription.md)**  |

## Defines

|                | Name           |
| -------------- | -------------- |
|  | **[INF_REGISTER_CLASS](/docs/doxygen/Files/ClassDescription_8h.md#define-inf-register-class)**(cls, name)  |




## Macros Documentation

### define INF_REGISTER_CLASS

```cpp
#define INF_REGISTER_CLASS(
    cls,
    name
)
typedef cls Inf_PBNI_Class; static std::wstring s_PBNI_ClassName = name; static Inf::ClassDescription<cls> class_description(name)
```


**Parameters**: 

  * **cls** The Class Type to use 
  * **name** A WString containing the Name to be used by PowerBuilder (Must be the same as GetPBName) 


This Macro is just there for convenienve. Use it to register a Class to the PBNI Franework. Make sure that every function you register to this class is in the same File. Don't use this inside a header File.


## Source code

```cpp
#pragma once

#include <vector>

#include "MethodDescription.h"

#define INF_REGISTER_CLASS(cls, name) typedef cls Inf_PBNI_Class; static std::wstring s_PBNI_ClassName = name; static Inf::ClassDescription<cls> class_description(name)

namespace Inf
{
    class IClassDescription
    {
    public:
        virtual PBNI_Class* Create(IPB_Session* session, pbobject pbobj, std::wstring pb_class_name) const = 0;

        IMethodDescription* GetMethod(pbmethodID method_id) const
        {
            return method_id < m_Methods.size() ? m_Methods[method_id] : nullptr;
        }

        std::wstring GetDescription() const
        {
            std::wstring builder = L"class " + m_PBName + L" from nonvisualobject\n";
            for (IMethodDescription* method : m_Methods)
            {
                builder += method->GetDescription() + L"\n";
            }
            builder += L"end class\n";

            return builder;
        }


    protected:
        friend PBNI_Framework;

        std::wstring m_PBName;
        std::vector<IMethodDescription*> m_Methods;

        void AddMethod(IMethodDescription* method_description)
        {
            m_Methods.push_back(method_description);
        };
    };

    template <typename Cls>
        requires (std::is_base_of_v<PBNI_Class, Cls>)
    class ClassDescription : public IClassDescription
    {
    public:
        ClassDescription(std::wstring pb_name)
        {
            m_PBName = pb_name;
            PBNI_Framework::GetInstance().RegisterPBClass(pb_name, this);
        };

        PBNI_Class* Create(IPB_Session* session, pbobject pbobj, std::wstring pb_class_name) const override
        {
            return static_cast<PBNI_Class*>(new Cls(session, pbobj, pb_class_name));
        }
    };
};
```


-------------------------------

Updated on 2022-09-16 at 11:32:55 +0200
