#include "PBAny.h"

#include "PBObjects.h"


Inf::PBAny::PBAny(IPB_Session* session, IPB_Value* value, bool acquire)
    : m_Session(session)
{
    if (value->IsObject())
    {
        m_Class = value->GetClass();
        m_Type = AnyType::Object;
    }
    else
        m_Type = (AnyType) value->GetType();

    if (value->IsArray())
    {
        m_IsArray = true;

        if (!value->IsNull())
            m_Value = Helper::PBValue(session, value).Get<PBArray<PBAny>>(acquire);

        return;
    }


    if (value->IsNull())
        return;

    if (value->IsObject())
    {
        m_Value = DynPBObject(session, value->GetObject());
        return;
    }

    switch (m_Type)
    {
        case Type<PBByte    >::PBType: m_Value = Helper::PBValue(session, value).Get<PBByte    >(acquire); break;
        case Type<PBBoolean >::PBType: m_Value = Helper::PBValue(session, value).Get<PBBoolean >(acquire); break;
        case Type<PBChar    >::PBType: m_Value = Helper::PBValue(session, value).Get<PBChar    >(acquire); break;
        case Type<PBInt     >::PBType: m_Value = Helper::PBValue(session, value).Get<PBInt     >(acquire); break;
        case Type<PBUint    >::PBType: m_Value = Helper::PBValue(session, value).Get<PBUint    >(acquire); break;
        case Type<PBLong    >::PBType: m_Value = Helper::PBValue(session, value).Get<PBLong    >(acquire); break;
        case Type<PBUlong   >::PBType: m_Value = Helper::PBValue(session, value).Get<PBUlong   >(acquire); break;
        case Type<PBLongLong>::PBType: m_Value = Helper::PBValue(session, value).Get<PBLongLong>(acquire); break;
        case Type<PBReal    >::PBType: m_Value = Helper::PBValue(session, value).Get<PBReal    >(acquire); break;
        case Type<PBDouble  >::PBType: m_Value = Helper::PBValue(session, value).Get<PBDouble  >(acquire); break;
        case Type<PBDecimal >::PBType: m_Value = Helper::PBValue(session, value).Get<PBDecimal >(acquire); break;
        case Type<PBTime    >::PBType: m_Value = Helper::PBValue(session, value).Get<PBTime    >(acquire); break;
        case Type<PBDate    >::PBType: m_Value = Helper::PBValue(session, value).Get<PBDate    >(acquire); break;
        case Type<PBDateTime>::PBType: m_Value = Helper::PBValue(session, value).Get<PBDateTime>(acquire); break;
        case Type<PBString  >::PBType: m_Value = Helper::PBValue(session, value).Get<PBString  >(acquire); break;
        case Type<PBBlob    >::PBType: m_Value = Helper::PBValue(session, value).Get<PBBlob    >(acquire); break;
    }
}

PBXRESULT Inf::PBAny::ToValue(IPB_Value* value) const
{
    if (IsNull())
        return value->SetToNull();

    // Because IPB_Values often crash when you try to change their types,
    // we need to create a new IPB_Value and then set the old one to it.
    // The only way to create new IPB_Values is using this workaround
    pbclass sysFuncClass = m_Session->FindClass(m_Session->GetSystemGroup(), L"SystemFunctions");
    pbmethodID mid = m_Session->GetMethodID(sysFuncClass, L"classname", PBRT_FUNCTION, L"");
    PBCallInfo ci;
    m_Session->InitCallInfo(sysFuncClass, mid, &ci);

    if (m_IsArray)
    {
        pbarray arr = std::any_cast<PBArray<PBAny>>(m_Value);
        m_Session->AddArrayArgument(&ci, arr);
    }

    else
    {
        switch (m_Type)
        {
            case Type<PBByte    >::PBType: m_Session->AddByteArgument    (&ci, std::any_cast<PBByte    >(m_Value)); break;
            case Type<PBBoolean >::PBType: m_Session->AddBoolArgument    (&ci, std::any_cast<PBBoolean >(m_Value)); break;
            case Type<PBChar    >::PBType: m_Session->AddCharArgument    (&ci, std::any_cast<PBChar    >(m_Value)); break;
            case Type<PBInt     >::PBType: m_Session->AddIntArgument     (&ci, std::any_cast<PBInt     >(m_Value)); break;
            case Type<PBUint    >::PBType: m_Session->AddUintArgument    (&ci, std::any_cast<PBUint    >(m_Value)); break;
            case Type<PBLong    >::PBType: m_Session->AddLongArgument    (&ci, std::any_cast<PBLong    >(m_Value)); break;
            case Type<PBUlong   >::PBType: m_Session->AddUlongArgument   (&ci, std::any_cast<PBUlong   >(m_Value)); break;
            case Type<PBLongLong>::PBType: m_Session->AddLongLongArgument(&ci, std::any_cast<PBLongLong>(m_Value)); break;
            case Type<PBReal    >::PBType: m_Session->AddRealArgument    (&ci, std::any_cast<PBReal    >(m_Value)); break;
            case Type<PBDouble  >::PBType: m_Session->AddDoubleArgument  (&ci, std::any_cast<PBDouble  >(m_Value)); break;
            case Type<PBDecimal >::PBType: m_Session->AddDecArgument     (&ci, std::any_cast<PBDecimal >(m_Value)); break;
            case Type<PBTime    >::PBType: m_Session->AddTimeArgument    (&ci, std::any_cast<PBTime    >(m_Value)); break;
            case Type<PBDate    >::PBType: m_Session->AddDateArgument    (&ci, std::any_cast<PBDate    >(m_Value)); break;
            case Type<PBDateTime>::PBType: m_Session->AddDateTimeArgument(&ci, std::any_cast<PBDateTime>(m_Value)); break;
            case Type<PBString  >::PBType: m_Session->AddPBStringArgument(&ci, std::any_cast<PBString  >(m_Value)); break;
            case Type<PBBlob    >::PBType: m_Session->AddBlobArgument    (&ci, std::any_cast<PBBlob    >(m_Value)); break;

            case AnyType::Object: m_Session->AddObjectArgument(&ci, std::any_cast<DynPBObject>(m_Value)); break;
        }
    }

    m_Session->SetValue(value, ci.pArgs->GetAt(1));
    m_Session->FreeCallInfo(&ci);

    return PBX_OK;
}
