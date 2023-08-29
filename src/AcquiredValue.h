#pragma once

#include <memory>

#include <pbext.h>


namespace Inf::Helper
{
    /**
     * This struct is used to hold a PowerBuilder Value.
     * If you dont hold Acquire the Value, the data within it will be Freed once the CallbackInfo gets freed.
     * So if you want to keep the Value, you need to Acquire it.
     * This is only useful with complex types, such as DateTimes, Blob, Strings, Arrays and Objects
     */
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