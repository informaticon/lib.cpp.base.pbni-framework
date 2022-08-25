---
title: src/AcquiredValue.h

---

# src/AcquiredValue.h



## Namespaces

| Name           |
| -------------- |
| **[Inf](/doxygen/Namespaces/namespace_inf/)**  |




## Source code

```cpp
#pragma once

#include <memory>

#include <pbext.h>


namespace Inf::Helper
{
    struct AcquiredValue
    {
        IPB_Session* Session;
        IPB_Value* Value;
        bool Acquired;
        AcquiredValue(IPB_Session* session, IPB_Value* value, bool acquire = true)
            : Session(session), Value(nullptr), Acquired(acquire)
        {
            if (acquire)
                Acquire();
        }

        ~AcquiredValue()
        {
            Release();
        }

        void Acquire()
        {
            if (!Acquired)
                Value = Session->AcquireValue(Value);
        
            Acquired = true;
        }

        void Release()
        {
            if (Acquired)
                Session->ReleaseValue(Value);

            Acquired = false;
        }


    };
}
```


-------------------------------

Updated on 2022-08-25 at 16:29:24 +0200
