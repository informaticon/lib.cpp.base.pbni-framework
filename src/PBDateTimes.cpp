#include "PBDateTimes.h"

#include "Errors.h"

static time_t mkgmtime(struct tm* tm)
{
    // TODO use gmtime or something else?
#if defined(_WIN32)
    return _mkgmtime(tm);
#elif defined(linux)
    return timegm(tm);
#endif
}

Inf::PBTime::PBTime(IPB_Session* session, pbtime time)
    : m_Session(session), m_Time(time)
{ }

Inf::PBTime::PBTime(IPB_Session* session, pbint hours, pbint minutes, pbdouble seconds)
    : m_Session(session), m_Time(0)
{
    SetTime(hours, minutes, seconds);
}

std::chrono::time_point<std::chrono::system_clock> Inf::PBTime::GetChrono() const
{
    auto [hour, min, sec] = GetTime();
    std::tm tm = {
        .tm_min = min,
        .tm_hour = hour,
        .tm_mday = 1,
        .tm_year = 1970 - 1900  // because .tm_year is years since 1900, and mkgmtime wants atleast 1970
    };

    // Doing some weird stuff because we want subsecond precission
    return std::chrono::system_clock::from_time_t(mkgmtime(&tm)) +
           std::chrono::microseconds(static_cast<std::chrono::microseconds::rep>(sec * std::micro::den));
}

std::tuple<pbint, pbint, pbdouble> Inf::PBTime::GetTime() const
{
    if (IsNull())
        throw Inf::PBNI_NullPointerException(L"PBTime");

    pbint hours, minutes;
    pbdouble seconds;

    PBXRESULT res = m_Session->SplitTime(m_Time, &hours, &minutes, &seconds);
    if (res != PBX_SUCCESS)
        throw Inf::PBNI_PowerBuilderException(L"IPB_Session::SplitTime", res);

    return { hours, minutes, seconds };
}

void Inf::PBTime::SetTime(pbint hours, pbint minutes, pbdouble seconds)
{
    if (IsNull())
        m_Time = m_Session->NewTime();

    PBXRESULT res = m_Session->SetTime(m_Time, hours, minutes, seconds);
    if (res != PBX_SUCCESS)
        throw Inf::PBNI_PowerBuilderException(L"IPB_Session::SetTime", res);
}

bool Inf::PBTime::IsNull() const
{
    return m_Time == 0;
}

void Inf::PBTime::SetToNull()
{
    m_Time = 0;
}

Inf::PBTime::PBTime(IPB_Session* session, IPB_Value* value, bool acquire)
    : m_Session(session)
{
    if (value->IsNull())
    {
        m_Time = 0;
    }
    else
    {
        if (acquire)
        {
            m_AcquiredValue = std::make_shared<Helper::AcquiredValue>(session, value);
            m_Time = m_AcquiredValue->Value->GetTime();
        }
        else
        {
            m_Time = value->GetTime();
        }
    }
}


Inf::PBDate::PBDate(IPB_Session* session, pbdate date)
    : m_Session(session), m_Date(date)
{ }

Inf::PBDate::PBDate(IPB_Session* session, pbint years, pbint months, pbint days)
    : m_Session(session), m_Date(0)
{
    SetDate(years, months, days);
}

std::chrono::time_point<std::chrono::system_clock> Inf::PBDate::GetChrono() const
{
    auto [year, mon, day] = GetDate();
    std::tm tm = {
        .tm_mday = day,
        .tm_mon = mon - 1,
        .tm_year = year - 1900,
    };

    // Doing some weird stuff because we want subsecond precission
    return std::chrono::system_clock::from_time_t(mkgmtime(&tm));
}

std::tuple<pbint, pbint, pbint> Inf::PBDate::GetDate() const
{
    if (IsNull())
        throw Inf::PBNI_NullPointerException(L"PBDate");

    pbint years, months, days;

    PBXRESULT res = m_Session->SplitDate(m_Date, &years, &months, &days);
    if (res != PBX_SUCCESS)
        throw Inf::PBNI_PowerBuilderException(L"IPB_Session::SplitDate", res);

    return { years, months, days };
}

void Inf::PBDate::SetDate(pbint years, pbint months, pbint days)
{
    if (IsNull())
        m_Date = m_Session->NewDate();

    PBXRESULT res = m_Session->SetDate(m_Date, years, months, days);
    if (res != PBX_SUCCESS)
        throw Inf::PBNI_PowerBuilderException(L"IPB_Session::SetDate", res);
}

bool Inf::PBDate::IsNull() const
{
    return m_Date == 0;
}

void Inf::PBDate::SetToNull()
{
    m_Date = 0;
}

Inf::PBDate::PBDate(IPB_Session* session, IPB_Value* value, bool acquire)
    : m_Session(session)
{
    if (value->IsNull())
    {
        m_Date = 0;
    }
    else
    {
        if (acquire)
        {
            m_AcquiredValue = std::make_shared<Helper::AcquiredValue>(session, value);
            m_Date = m_AcquiredValue->Value->GetDate();
        }
        else
        {
            m_Date = value->GetDate();
        }
    }
}


Inf::PBDateTime::PBDateTime(IPB_Session* session, pbdatetime datetime)
    : m_Session(session), m_DateTime(datetime)
{ }


Inf::PBDateTime::PBDateTime(
    IPB_Session* session,
    pbint years,
    pbint months,
    pbint days,
    pbint hours,
    pbint minutes,
    pbdouble seconds
)
    : m_Session(session), m_DateTime(0)
{
    SetDateTime(years, months, days, hours, minutes, seconds);
}

std::chrono::time_point<std::chrono::system_clock> Inf::PBDateTime::GetChrono() const
{
    auto [year, mon, day, hour, min, sec] = GetDateTime();
    std::tm tm = {
        .tm_min = min,
        .tm_hour = hour,
        .tm_mday = day,
        .tm_mon = mon - 1,
        .tm_year = year - 1900,
    };

    // Doing some weird stuff because we want subsecond precission

    return std::chrono::system_clock::from_time_t(mkgmtime(&tm)) +
           std::chrono::microseconds(static_cast<std::chrono::microseconds::rep>(sec * std::micro::den));
}

std::tuple<pbint, pbint, pbint, pbint, pbint, pbdouble> Inf::PBDateTime::GetDateTime() const
{
    if (IsNull())
        throw Inf::PBNI_NullPointerException(L"PBDateTime");

    pbint years, months, days, hours, minutes;
    pbdouble seconds;

    PBXRESULT res = m_Session->SplitDateTime(m_DateTime, &years, &months, &days, &hours, &minutes, &seconds);
    if (res != PBX_SUCCESS)
        throw Inf::PBNI_PowerBuilderException(L"IPB_Session::SplitDateTime", res);

    return { years, months, days, hours, minutes, seconds };
}

void Inf::PBDateTime::SetDateTime(pbint years, pbint months, pbint days, pbint hours, pbint minutes, pbdouble seconds)
{
    if (IsNull())
        m_DateTime = m_Session->NewDateTime();

    PBXRESULT res = m_Session->SetDateTime(m_DateTime, years, months, days, hours, minutes, seconds);
    if (res != PBX_SUCCESS)
        throw Inf::PBNI_PowerBuilderException(L"IPB_Session::SetDateTime", res);
}

bool Inf::PBDateTime::IsNull() const
{
    return m_DateTime == 0;
}

void Inf::PBDateTime::SetToNull()
{
    m_DateTime = 0;
}

Inf::PBDateTime::PBDateTime(IPB_Session* session, IPB_Value* value, bool acquire)
    : m_Session(session)
{
    if (value->IsNull())
    {
        m_DateTime = 0;
    }
    else
    {
        if (acquire)
        {
            m_AcquiredValue = std::make_shared<Helper::AcquiredValue>(session, value);
            m_DateTime = m_AcquiredValue->Value->GetDateTime();
        }
        else
        {
            m_DateTime = value->GetDateTime();
        }
    }
}
