#pragma once

#include <string>

// Windows API
#include <stringapiset.h>

namespace Inf
{
	template <typename ToStr, typename... FromStr> ToStr ConvertString(FromStr... str) = delete;

	// See Documentation at https://docs.microsoft.com/en-us/windows/win32/api/stringapiset/nf-stringapiset-widechartomultibyte and https://docs.microsoft.com/en-us/windows/win32/api/stringapiset/nf-stringapiset-multibytetowidechar
	template<> inline std::wstring ConvertString(const char* str, size_t size)
	{
		if (size == 0)
		{
			return L"";
		}
		std::wstring wstr(size, 0);

		MultiByteToWideChar(CP_ACP, 0, str, size, wstr.data(), size);
		return wstr;
	}
	template<> inline std::wstring ConvertString(const char* str)
	{
		size_t size = MultiByteToWideChar(CP_ACP, 0, str, -1, nullptr, 0);
		return ConvertString<std::wstring>(str, size - 1);;
	}
	template<> inline std::wstring ConvertString(const std::string str)
	{
		return ConvertString<std::wstring>(str.c_str(), str.size());
	}
	template<> inline std::string ConvertString(const wchar_t* wstr, size_t size)
	{
		if (size == 0)
		{
			return "";
		}

		std::string str(size, 0);

		WideCharToMultiByte(CP_ACP, 0, wstr, size, str.data(), size, 0, FALSE);
		return str;
	}
	template<> inline std::string ConvertString(const wchar_t* wstr)
	{
		size_t size = WideCharToMultiByte(CP_ACP, 0, wstr, -1, nullptr, 0, 0, FALSE);
		return ConvertString<std::string>(wstr, size - 1);
	}
	template<> inline std::string ConvertString(const std::wstring wstr)
	{
		return ConvertString<std::string>(wstr.c_str(), wstr.size());
	}

	namespace Helper
	{
		// Use this to be able to pass const chars as template parameters
		// https://www.quora.com/How-do-you-pass-a-string-literal-as-a-parameter-to-a-C-template-class
		// this probably wont be needed in C++23
		template<size_t N>
		struct FixedString
		{
			constexpr FixedString(wchar_t const (&s)[N])
			{
				std::copy_n(s, N, this->data);
			}

			constexpr std::strong_ordering operator<=>(FixedString const&) const = default;

			wchar_t data[N];
		};
	}
}