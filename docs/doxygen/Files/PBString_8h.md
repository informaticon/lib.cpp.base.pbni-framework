---
title: src/PBString.h

---

# src/PBString.h



## Namespaces

| Name           |
| -------------- |
| **[Inf](/docs/doxygen/Namespaces/namespaceInf.md)**  |

## Classes

|                | Name           |
| -------------- | -------------- |
| class | **[Inf::PBString](/docs/doxygen/Classes/classInf_1_1PBString.md)**  |




## Source code

```cpp
#pragma once

#include <string>

#include <pbext.h>

#include "AcquiredValue.h"


namespace Inf
{

    namespace Helper
    {
        template<size_t N>
        struct FixedString
        {
            constexpr FixedString(wchar_t const (&s)[N])
            {
                std::copy_n(s, N, this->data);
            }

            constexpr std::strong_ordering operator<=>(FixedString const&) const = default;

            wchar_t data[N];
        };
    }

    class PBString
    {
    public:
        PBString(IPB_Session* session, pbstring pb_string);
        PBString(IPB_Session* session, const std::string& str);
        PBString(IPB_Session* session, const std::wstring& wstr);

        std::string GetString() const;
        std::wstring GetWString() const;
        void SetString(const std::string& str);
        void SetWString(const std::wstring& wstr);

        pblong Size() const;

        bool IsNull() const;
        void SetToNull();
    private:
        template <typename T>
        friend struct Type;
        template <typename PBT, pblong... dims>
            requires (sizeof...(dims) <= 3 && !std::is_reference_v<PBT> && !std::is_pointer_v<PBT>)
        friend class PBArray;
        template <Helper::FixedString class_id, pbgroup_type group_type>
        friend class PBObject;

        IPB_Session* m_Session;
        pbstring m_String;
        std::shared_ptr<Helper::AcquiredValue> m_AcquiredValue;

        PBString(IPB_Session* session, IPB_Value* value, bool acquire);
    };


    template <typename ToStr, typename... FromStr> ToStr ConvertString(FromStr... str) = delete;

    template<> std::wstring ConvertString<>(const char* str, size_t size);
    template<> std::wstring ConvertString<>(const char* str);
    template<> std::wstring ConvertString<>(const std::string str);
    template<> std::string ConvertString<>(const wchar_t* wstr, size_t size);
    template<> std::string ConvertString<>(const wchar_t* wstr);
    template<> std::string ConvertString<>(const std::wstring wstr);
}
```


-------------------------------

Updated on 2022-09-15 at 20:34:45 +0200
