#include "PBAny.h"


Inf::PBAny::PBAny(IPB_Session* session, IPB_Value* value, bool acquire)
    : m_Session(session)
{
    if (!value || value->IsNull())
    {
        m_Type = AnyType::Null;
        return;
    }

    if (value->IsObject())
    {
        m_Class = value->GetClass();
        m_Type = AnyType::Object;
    }
    else
        m_Type = (AnyType)value->GetType();

    if (value->IsArray())
    {
        m_IsArray = true;

        m_Value = PBArray<PBAny>(session, value, acquire);
        return;
    }

    if (value->IsObject())
    {
        m_Value = PBObject<L"">(session, value->GetObject());
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

    Helper::PBValue pbValue(m_Session, value);
    if (m_IsArray)
        return pbValue.Set(std::any_cast<PBArray<PBAny>>(m_Value));

    switch (m_Type)
    {
        case Type<PBByte    >::PBType: return pbValue.Set(std::any_cast<PBByte>(m_Value));
        case Type<PBBoolean >::PBType: return pbValue.Set(std::any_cast<PBBoolean>(m_Value));
        case Type<PBChar    >::PBType: return pbValue.Set(std::any_cast<PBChar>(m_Value));
        case Type<PBInt     >::PBType: return pbValue.Set(std::any_cast<PBInt>(m_Value));
        case Type<PBUint    >::PBType: return pbValue.Set(std::any_cast<PBUint>(m_Value));
        case Type<PBLong    >::PBType: return pbValue.Set(std::any_cast<PBLong>(m_Value));
        case Type<PBUlong   >::PBType: return pbValue.Set(std::any_cast<PBUlong>(m_Value));
        case Type<PBLongLong>::PBType: return pbValue.Set(std::any_cast<PBLongLong>(m_Value));
        case Type<PBReal    >::PBType: return pbValue.Set(std::any_cast<PBReal>(m_Value));
        case Type<PBDouble  >::PBType: return pbValue.Set(std::any_cast<PBDouble>(m_Value));
        case Type<PBDecimal >::PBType: return pbValue.Set(std::any_cast<PBDecimal>(m_Value));
        case Type<PBTime    >::PBType: return pbValue.Set(std::any_cast<PBTime>(m_Value));
        case Type<PBDate    >::PBType: return pbValue.Set(std::any_cast<PBDate>(m_Value));
        case Type<PBDateTime>::PBType: return pbValue.Set(std::any_cast<PBDateTime>(m_Value));
        case Type<PBString  >::PBType: return pbValue.Set(std::any_cast<PBString>(m_Value));
        case Type<PBBlob    >::PBType: return pbValue.Set(std::any_cast<PBBlob>(m_Value));

        case AnyType::Object: return pbValue.Set(std::any_cast<PBObject<L"">>(m_Value));
    }

    return PBX_E_NO_SUCH_CLASS;
}