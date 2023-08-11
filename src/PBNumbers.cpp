#include "PBNumbers.h"

#include "Errors.h"


Inf::PBDecimal::PBDecimal(IPB_Session* session, pbdec dec)
    : m_Session(session), m_Decimal(dec)
{ }

Inf::PBDecimal::PBDecimal(IPB_Session* session, const Inf::Helper::PBDecimalImpl& value)
    : m_Session(session), m_Decimal(session->NewDecimal())
{
    SetDecimal(value);
}

void Inf::PBDecimal::SetDecimal(const Inf::Helper::PBDecimalImpl& value)
{
    if (IsNull())
        m_Decimal = m_Session->NewDecimal();

    PBXRESULT res = m_Session->SetDecimal(m_Decimal, Inf::ConvertString<std::wstring>(value.str()).c_str());
    if (res != PBX_SUCCESS)
        throw Inf::PBNI_PowerBuilderException(L"IPB_Session::SetDecimal", res);
}

Inf::Helper::PBDecimalImpl Inf::PBDecimal::GetDecimal() const
{
    if (IsNull())
        throw Inf::PBNI_NullPointerException(L"PBDecimal");

    auto dec_repr = m_Session->GetDecimalString(m_Decimal);
    std::string repr = Inf::ConvertString<std::string>(dec_repr);

    m_Session->ReleaseDecimalString(dec_repr);

    return Inf::Helper::PBDecimalImpl(repr);
}


bool Inf::PBDecimal::IsNull() const
{
    return !m_Decimal;
}

void Inf::PBDecimal::SetToNull()
{
    m_Decimal = 0;
}

Inf::PBDecimal::PBDecimal(IPB_Session* session, IPB_Value* value, bool acquire)
    : m_Session(session)
{
    if (value->IsNull())
    {
        m_Decimal = 0;
    }
    else
    {
        if (acquire)
        {
            m_AcquiredValue = std::make_shared<Helper::AcquiredValue>(session, value);
            m_Decimal = m_AcquiredValue->Value->GetDecimal();
        }
        else
        {
            m_Decimal = value->GetDecimal();
        }
    }
}
