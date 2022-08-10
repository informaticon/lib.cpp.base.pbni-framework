#include "PBString.h"

#include "../Strings.h"
#include "../Errors.h"


Inf::PBString::PBString(IPB_Session* session, pbstring pb_string)
	: m_Session(session), m_String(pb_string)
{ }

Inf::PBString::PBString(IPB_Session* session, const std::string& str)
	: m_Session(session)
{
	m_String = m_Session->NewString(Inf::ConvertString<std::wstring>(str).c_str());
}

Inf::PBString::PBString(IPB_Session* session, const std::wstring& str)
	: m_Session(session)
{
	m_String = m_Session->NewString(str.c_str());
}

std::wstring Inf::PBString::GetWString() const
{
	if (IsNull())
	{
		throw Inf::u_exf_pbni(L"Tried to access a WString of value Null");
	}

	// GetStringLength returns length without terminator, std::wstring doesnt need null terminator
	LPCTSTR c_str = m_Session->GetString(m_String);
	pblong size = m_Session->GetStringLength(m_String);

	std::wstring wstr(c_str, size);
	m_Session->ReleaseString(c_str);

	return wstr;
}

std::string Inf::PBString::GetString() const
{
	if (IsNull())
	{
		throw Inf::u_exf_pbni(L"Tried to access a String of value Null");
	}

	// GetStringLength returns length without terminator, std::wstring doesnt need null terminator
	LPCTSTR c_str = m_Session->GetString(m_String);
	pblong size = m_Session->GetStringLength(m_String);

	std::string str = Inf::ConvertString<std::string>(c_str, (size_t)size);
	m_Session->ReleaseString(c_str);

	return str;
}

void Inf::PBString::SetWString(const std::wstring& wstr)
{
	if (IsNull())
	{
		m_String = m_Session->NewString(wstr.c_str());
	}
	else
	{
		m_Session->SetString(m_String, wstr.c_str());
	}
}

void Inf::PBString::SetString(const std::string& str)
{
	std::wstring wstr = Inf::ConvertString<std::wstring>(str);
	if (IsNull())
	{
		m_String = m_Session->NewString(wstr.c_str());
	}
	else
	{
		m_Session->SetString(m_String, wstr.c_str());
	}
}

pblong Inf::PBString::Size() const
{
	return m_Session->GetStringLength(m_String);
}

bool Inf::PBString::IsNull() const
{
	return !m_String;
}

void Inf::PBString::SetToNull()
{
	m_String = 0;
}
