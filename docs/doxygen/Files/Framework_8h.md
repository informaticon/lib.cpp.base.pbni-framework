---
title: src/Framework.h

---

# src/Framework.h



## Namespaces

| Name           |
| -------------- |
| **[Inf](/docs/doxygen/Namespaces/namespaceInf.md)**  |

## Classes

|                | Name           |
| -------------- | -------------- |
| class | **[Inf::PBNI_Class](/docs/doxygen/Classes/classInf_1_1PBNI__Class.md)**  |
| class | **[Inf::PBNI_Framework](/docs/doxygen/Classes/classInf_1_1PBNI__Framework.md)**  |




## Source code

```cpp
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
        const std::wstring PB_NAME;

        PBNI_Class(IPB_Session* session, pbobject pbobj, std::wstring pb_class_name);
        virtual ~PBNI_Class() {};

        void Destroy() override { delete this; }

        PBXRESULT Invoke(IPB_Session* session, pbobject obj, pbmethodID  mid, PBCallInfo* ci) override;
    
    protected:
        IPB_Session* m_Session;
        pbobject m_PBObject;
    };

    class PBNI_Framework
    {
    public:
        PBNI_Class* CreateClass(std::wstring pb_class_name, IPB_Session* session, pbobject pbobj);

        const std::wstring& GetDescription();
        IMethodDescription* GetClassMethod(std::wstring pb_class_name, pbmethodID method_id);

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

        std::wstring GenerateDescription();
        
        void RegisterPBClass(std::wstring pb_class_name, IClassDescription* class_desciption);

        void RegisterPBMethod(std::wstring pb_class_name, IMethodDescription* method_description);


        std::unordered_map<std::wstring, IClassDescription*> m_Classes;
        std::wstring m_Description;
    };
};
```


-------------------------------

Updated on 2022-09-15 at 20:34:45 +0200
