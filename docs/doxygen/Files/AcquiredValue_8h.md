---
title: src/AcquiredValue.h

---

# src/AcquiredValue.h



## Namespaces

| Name           |
| -------------- |
| **[Inf](/docs/doxygen/Namespaces/namespaceInf.md)**  |




## Source code

```cpp
#pragma once

#include <memory>

#include <pbext.h>


namespace Inf::Helper
{
    struct AcquiredValue
    {
        AcquiredValue(IPB_Session* session, IPB_Value* value)
            : Session(session), Value(Session->AcquireValue(value))
        { }

        ~AcquiredValue()
        {
            Session->ReleaseValue(Value);
        }

        IPB_Session* Session;
        IPB_Value* Value;
    };
}
```


-------------------------------

Updated on 2022-09-15 at 20:34:45 +0200
