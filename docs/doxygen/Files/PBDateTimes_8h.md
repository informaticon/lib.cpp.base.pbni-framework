---
title: src/PBDateTimes.h

---

# src/PBDateTimes.h



## Namespaces

| Name           |
| -------------- |
| **[Inf](/docs/doxygen/Namespaces/namespaceInf.md)**  |

## Classes

|                | Name           |
| -------------- | -------------- |
| class | **[Inf::PBTime](/docs/doxygen/Classes/classInf_1_1PBTime.md)**  |
| class | **[Inf::PBDate](/docs/doxygen/Classes/classInf_1_1PBDate.md)**  |
| class | **[Inf::PBDateTime](/docs/doxygen/Classes/classInf_1_1PBDateTime.md)**  |




## Source code

```cpp
#pragma once

#include <tuple>

#include <pbext.h>

#include "PBString.h"
#include "AcquiredValue.h"


namespace Inf
{
    class PBTime {
    public:
        PBTime(IPB_Session* session, pbtime time);
        PBTime(IPB_Session* session, pbint hours, pbint minutes, pbdouble seconds);

        std::tuple<pbint, pbint, pbdouble> GetTime() const;
        void SetTime(pbint hours, pbint minutes, pbdouble seconds);

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
        pbtime m_Time;
        std::shared_ptr<Helper::AcquiredValue> m_AcquiredValue;

        PBTime(IPB_Session* session, IPB_Value* value, bool acquire);
    };


    class PBDate {
    public:
        PBDate(IPB_Session* session, pbdate date);
        PBDate(IPB_Session* session, pbint years, pbint months, pbint days);

        std::tuple<pbint, pbint, pbint> GetDate() const;
        void SetDate(pbint years, pbint months, pbint days);

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
        pbdate m_Date;
        std::shared_ptr<Helper::AcquiredValue> m_AcquiredValue;

        PBDate(IPB_Session* session, IPB_Value* value, bool acquire);
    };


    class PBDateTime {
    public:
        PBDateTime(IPB_Session* session, pbdatetime datetime);
        PBDateTime(IPB_Session* session, pbint years, pbint months, pbint days, pbint hours, pbint minutes, pbdouble seconds);

        std::tuple<pbint, pbint, pbint, pbint, pbint, pbdouble> GetDateTime() const;
        void SetDateTime(pbint years, pbint months, pbint days, pbint hours, pbint minutes, pbdouble seconds);

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
        pbdatetime m_DateTime;
        std::shared_ptr<Helper::AcquiredValue> m_AcquiredValue;

        PBDateTime(IPB_Session* session, IPB_Value* value, bool acquire);
    };
}
```


-------------------------------

Updated on 2022-09-16 at 11:32:55 +0200
