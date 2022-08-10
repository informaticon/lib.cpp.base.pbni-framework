#include "PBDateTimes.h"


Inf::PBTime::PBTime(IPB_Session* session, pbtime time)
	: m_Session(session), m_Time(time)
{ }

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


Inf::PBDate::PBDate(IPB_Session* session, pbdate date)
	: m_Session(session), m_Date(date)
{ }

std::tuple<pbint, pbint, pbint> Inf::PBDate::GetDate() const
{
	pbint years, months, days;

	m_Session->SplitDate(m_Date, &years, &months, &days);

	return { years, months, days };
}

void Inf::PBDate::SetDate(pbint y, pbint m, pbint d)
{
	if (IsNull())
		m_Date = m_Session->NewDate();

	m_Session->SetDate(m_Date, y, m, d);
}

bool Inf::PBDate::IsNull() const
{
	return m_Date == 0;
}

void Inf::PBDate::SetToNull()
{
	m_Date = 0;
}


Inf::PBDateTime::PBDateTime(IPB_Session* session, pbdatetime datetime)
	: m_Session(session), m_DateTime(datetime)
{ }

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