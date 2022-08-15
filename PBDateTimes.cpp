#include "PBDateTimes.h"


Inf::PBTime::PBTime(IPB_Session* session, pbtime time)
	: m_Session(session), m_Time(time)
{ }

Inf::PBTime::PBTime(IPB_Session* session, pbint hours, pbint minutes, pbdouble seconds)
	: m_Session(session), m_Time(0)
{
	SetTime(hours, minutes, seconds);
}

std::tuple<pbint, pbint, pbdouble> Inf::PBTime::GetTime() const
{
	pbint hours, minutes;
	pbdouble seconds;

	m_Session->SplitTime(m_Time, &hours, &minutes, &seconds);

	return { hours, minutes, seconds };
}

void Inf::PBTime::SetTime(pbint hours, pbint minutes, pbdouble seconds)
{
	if (IsNull())
		m_Time = m_Session->NewTime();

	m_Session->SetTime(m_Time, hours, minutes, seconds);
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

Inf::PBDate::PBDate(IPB_Session * session, pbint years, pbint months, pbint days)
	: m_Session(session), m_Date(0)
{
	SetDate(years, months, days);
}

std::tuple<pbint, pbint, pbint> Inf::PBDate::GetDate() const
{
	pbint years, months, days;

	m_Session->SplitDate(m_Date, &years, &months, &days);

	return { years, months, days };
}

void Inf::PBDate::SetDate(pbint years, pbint months, pbint days)
{
	if (IsNull())
		m_Date = m_Session->NewDate();

	m_Session->SetDate(m_Date, years, months, days);
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


Inf::PBDateTime::PBDateTime(IPB_Session* session, pbint years, pbint months, pbint days, pbint hours, pbint minutes, pbdouble seconds)
	: m_Session(session), m_DateTime(0)
{
	SetDateTime(years, months, days, hours, minutes, seconds);
}

std::tuple<pbint, pbint, pbint, pbint, pbint, pbdouble> Inf::PBDateTime::GetDateTime() const
{
	pbint years, months, days, hours, minutes;
	pbdouble seconds;

	m_Session->SplitDateTime(m_DateTime, &years, &months, &days, &hours, &minutes, &seconds);

	return { years, months, days, hours, minutes, seconds };
}

void Inf::PBDateTime::SetDateTime(pbint years, pbint months, pbint days, pbint hours, pbint minutes, pbdouble seconds)
{
	if (IsNull())
		m_DateTime = m_Session->NewDateTime();

	m_Session->SetDateTime(m_DateTime, years, months, days, hours, minutes, seconds);
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
