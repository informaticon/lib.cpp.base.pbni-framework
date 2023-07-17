#include "PBString.h"

#include <cwchar>

#include "Errors.h"


Inf::PBString::PBString(IPB_Session* session, pbstring pb_string)
	: m_Session(session), m_String(pb_string)
{ }

Inf::PBString::PBString(IPB_Session* session, const std::string& str, StringEncoding encoding)
	: m_Session(session)
{
	std::wstring wstr = Inf::ConvertString<std::wstring>(str, encoding);
	m_String = m_Session->NewString(wstr.c_str());
}

Inf::PBString::PBString(IPB_Session* session, const std::string_view& str, StringEncoding encoding)
	: m_Session(session)
{
	std::wstring wstr = Inf::ConvertString<std::wstring>(str, encoding);
	m_String = m_Session->NewString(wstr.c_str());
}

Inf::PBString::PBString(IPB_Session* session, const char* str, StringEncoding encoding)
	: m_Session(session)
{
	std::wstring wstr = Inf::ConvertString<std::wstring>(str, encoding);
	m_String = m_Session->NewString(wstr.c_str());
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

std::string Inf::PBString::GetString(StringEncoding encoding) const
{
	if (IsNull())
		throw Inf::PBNI_NullPointerException(L"PBString");

	LPCTSTR c_str = m_Session->GetString(m_String);
	pblong size = m_Session->GetStringLength(m_String);

	std::string str = Inf::ConvertString<std::string>(c_str, (size_t) size, encoding);
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

void Inf::PBString::SetString(const std::string& str, StringEncoding encoding)
{
	std::wstring wstr = Inf::ConvertString<std::wstring>(str, encoding);
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


bool Inf::StringConvertibleToANSI(const wchar_t* wstr, size_t size)
{
	BOOL conversionFailed = FALSE;
	WideCharToMultiByte(PBString::ANSI , 0, wstr, size, NULL, 0, 0, &conversionFailed);

	return !conversionFailed;
}

bool Inf::StringConvertibleToANSI(const wchar_t* wstr)
{
	return StringConvertibleToANSI(wstr, wcslen(wstr));
}

bool Inf::StringConvertibleToANSI(const std::wstring& wstr)
{
	return StringConvertibleToANSI(wstr.data(), wstr.size());
}


template<> std::wstring Inf::ConvertString(const char* str, size_t size, PBString::StringEncoding encoding)
{
	if (size == 0)
		return L"";

	int newSize = MultiByteToWideChar(encoding, 0, str, size, NULL, 0);

	std::wstring wstr(newSize, 0);

	MultiByteToWideChar(encoding, 0, str, size, wstr.data(), newSize);
	return wstr;
}

template<> std::wstring Inf::ConvertString(const char* str, PBString::StringEncoding encoding)
{
	return ConvertString<std::wstring>(str, strlen(str), encoding);
}

template<> std::wstring Inf::ConvertString(const std::string_view str, PBString::StringEncoding encoding)
{
	return ConvertString<std::wstring>(str.data(), str.size(), encoding);
}

template<> std::wstring Inf::ConvertString(const std::string str, PBString::StringEncoding encoding)
{
	return ConvertString<std::wstring>(str.data(), str.size(), encoding);
}

template<> std::string Inf::ConvertString(const wchar_t* wstr, size_t size, PBString::StringEncoding encoding)
{
	if (size == 0)
		return "";

	int newSize = WideCharToMultiByte(encoding, 0, wstr, size, NULL, 0, 0, NULL);

	std::string str(newSize, 0);

	WideCharToMultiByte(encoding, 0, wstr, size, str.data(), newSize, 0, NULL);
	return str;
}

template<> std::string Inf::ConvertString(const wchar_t* wstr, PBString::StringEncoding encoding)
{
	return ConvertString<std::string>(wstr, wcslen(wstr), encoding);
}

template<> std::string Inf::ConvertString(const std::wstring wstr, PBString::StringEncoding encoding)
{
	return ConvertString<std::string>(wstr.data(), wstr.size(), encoding);
}

template<> std::wstring Inf::ConvertString<>(const char* str, size_t size) { return ConvertString<std::wstring>(str, size, PBString::ANSI); };
template<> std::wstring Inf::ConvertString<>(const char* str) { return ConvertString<std::wstring>(str, PBString::ANSI); };
template<> std::wstring Inf::ConvertString<>(const std::string_view str) { return ConvertString<std::wstring>(str, PBString::ANSI); };
template<> std::wstring Inf::ConvertString<>(const std::string str) { return ConvertString<std::wstring>(str, PBString::ANSI); };
template<> std::string Inf::ConvertString<>(const wchar_t* wstr, size_t size) { return ConvertString<std::string>(wstr, size, PBString::ANSI); };
template<> std::string Inf::ConvertString<>(const wchar_t* wstr) { return ConvertString<std::string>(wstr, PBString::ANSI); };
template<> std::string Inf::ConvertString<>(const std::wstring wstr) { return ConvertString<std::string>(wstr, PBString::ANSI); };
