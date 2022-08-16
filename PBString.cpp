#include "PBString.h"

#include <stringapiset.h>

#include "Errors.h"


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
		throw Inf::PBNI_NullPointerException(L"PBString");

	LPCTSTR c_str = m_Session->GetString(m_String);
	pblong size = m_Session->GetStringLength(m_String);

	std::wstring wstr(c_str, size);
	m_Session->ReleaseString(c_str);

	return wstr;
}

std::string Inf::PBString::GetString() const
{
	if (IsNull())
		throw Inf::PBNI_NullPointerException(L"PBString");

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
	if (IsNull())
		throw Inf::PBNI_NullPointerException(L"PBString");

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

Inf::PBString::PBString(IPB_Session* session, IPB_Value* value, bool acquire)
	: m_Session(session)
{
	if (value->IsNull())
	{
		m_String = 0;
	}
	else
	{
		if (acquire)
		{
			m_AcquiredValue = std::make_shared<Helper::AcquiredValue>(session, value);
			m_String = m_AcquiredValue->Value->GetString();
		}
		else
		{
			m_String = value->GetString();
		}
	}
}


template<> std::wstring Inf::ConvertString(const char* str, size_t size)
{
	if (size == 0)
	{
		return L"";
	}
	std::wstring wstr(size, 0);

	MultiByteToWideChar(CP_ACP, 0, str, size, wstr.data(), size);
	return wstr;
}

template<> std::wstring Inf::ConvertString(const char* str)
{
	size_t size = MultiByteToWideChar(CP_ACP, 0, str, -1, nullptr, 0);
	return ConvertString<std::wstring>(str, size - 1);;
}

template<> std::wstring Inf::ConvertString(const std::string str)
{
	return ConvertString<std::wstring>(str.c_str(), str.size());
}

template<> std::string Inf::ConvertString(const wchar_t* wstr, size_t size)
{
	if (size == 0)
	{
		return "";
	}

	std::string str(size, 0);

	WideCharToMultiByte(CP_ACP, 0, wstr, size, str.data(), size, 0, FALSE);
	return str;
}

template<> std::string Inf::ConvertString(const wchar_t* wstr)
{
	size_t size = WideCharToMultiByte(CP_ACP, 0, wstr, -1, nullptr, 0, 0, FALSE);
	return ConvertString<std::string>(wstr, size - 1);
}

template<> std::string Inf::ConvertString(const std::wstring wstr)
{
	return ConvertString<std::string>(wstr.c_str(), wstr.size());
}