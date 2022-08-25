---
title: src/PBBlob.h

---

# src/PBBlob.h



## Namespaces

| Name           |
| -------------- |
| **[Inf](/doxygen/Namespaces/namespace_inf/)**  |

## Classes

|                | Name           |
| -------------- | -------------- |
| class | **[Inf::PBBlob](/doxygen/Classes/class_inf_1_1_p_b_blob/)**  |




## Source code

```cpp
#pragma once

#include <type_traits>
#include <stdint.h>

#include <pbext.h>

#include "PBString.h"


namespace Inf
{
    class PBBlob
    {
    public:
        PBBlob(IPB_Session* session, pbblob blob);
        PBBlob(IPB_Session* session, pbbyte* data, pblong size);

        void SetData(pbbyte* data, pblong size);
        pbbyte* GetData() const;
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

        pbblob m_Blob;
        IPB_Session* m_Session;
        std::shared_ptr<Helper::AcquiredValue> m_AcquiredValue;

        PBBlob(IPB_Session* session, IPB_Value* value, bool acquire);
    };
}
```


-------------------------------

Updated on 2022-08-25 at 16:29:24 +0200
