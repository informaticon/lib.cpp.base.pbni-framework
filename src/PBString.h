#pragma once

#include <string>

#include "AcquiredValue.h"
#include "Helper.h"


namespace Inf
{

    /**
     * This is a simple Wrapper to be able to get/set an std::string or std::wstring from/to a pbstring.
     * This Class doesnt store any Data of the String.
     */
    class PBString
    {
    public:
        enum StringEncoding : UINT
        {
            ANSI = CP_ACP,
            UTF8 = CP_UTF8
        };

        /**
         * Creates a Wrapper to an already existing pb_string.
         * Will be Null if pbstring is 0.
         *
         * \param session       Current Session
         * \param pb_string     The existing pb_string or 0
         */
        PBString(IPB_Session* session, pbstring pb_string);
        /**
         * Creates a new pbstring, converts the String to unicode and copies it.
         *
         * \param session   Current Session
         * \param str       String to copy
         */
        PBString(IPB_Session* session, const std::string& str, StringEncoding encoding = UTF8);
        PBString(IPB_Session* session, const std::string_view& str, StringEncoding encoding = UTF8);
        PBString(IPB_Session* session, const char* str, StringEncoding encoding = UTF8);
        /**
         * Creates a new pbstring and writes the WString to it.
         *
         * \param session   Current Session
         * \param wstr      WString to copy
         */
        PBString(IPB_Session* session, const std::wstring& wstr);

        /**
         * Reads the String and converts it to an Ansi String.
         *
         * \return  Ansi String
         *
         * \throw PBNI_NullPointerException     If String is Null
         */
        std::string GetString(StringEncoding encoding = UTF8) const;
        /**
         * Gets the String from Poerbuilder.
         *
         * \return  Unicode String
         *
         * \throw PBNI_NullPointerException     If String is Null
         */
        std::wstring GetWString() const;
        /**
         * Converts and copies the String to PowerBuilder.
         *
         * \param str   The String to copy
         */
        void SetString(const std::string& str, StringEncoding encoding = UTF8);
        /**
         * Copies the WString to PowerBuilder.
         *
         * \param wstr  The WString to copy
         */
        void SetWString(const std::wstring& wstr);

        /**
         * Gets the Size from PowerBuilder.
         *
         * \return  The size in bytes without Terminator.
         *
         * \throw PBNI_NullPointerException     If String is Null
         */
        pblong Size() const;

        /**
         * Checks whether the pbstring is Null.
         */
        bool IsNull() const;
        /**
         * Sets the pbstring to Null.
         */
        void SetToNull();

        /**
         * Retrieve the private PB Reference
         */
        operator pbstring() const
        {
            return m_String;
        }

    private:
        friend Helper::PBValue;

        IPB_Session* m_Session;
        pbstring m_String;
        std::shared_ptr<Helper::AcquiredValue> m_AcquiredValue;

        PBString(IPB_Session* session, IPB_Value* value, bool acquire);
    };


    /**
     * These functions return true if the wide string is losslessly convertible to Ansi.
     */
    bool StringConvertibleToANSI(const wchar_t* wstr, size_t size);
    bool StringConvertibleToANSI(const wchar_t* wstr);
    bool StringConvertibleToANSI(const std::wstring& wstr);

    /**
     * These functions convert a String from Ansi to Unicode or back.
     * They use Window's MultiByteToWideChar and WideCharToMultiByte functions (stringapiset.h).
     * Characters that cant be converted to ANSI will be replaced with using the default system character ('?').
     *
     * \tparam ToStr    The Type to be converted to
     */
    template<typename ToStr, typename... FromStr>
    ToStr ConvertString(const FromStr&... str) = delete;

    // clang-format off
    template<> std::wstring ConvertString<>(const char* const& str, const size_t& size, const PBString::StringEncoding& encoding);
    template<> std::wstring ConvertString<>(const char* const& str, const PBString::StringEncoding& encoding);
    template<> std::wstring ConvertString<>(const std::string_view& str, const PBString::StringEncoding& encoding);
    template<> std::wstring ConvertString<>(const std::string& str, const PBString::StringEncoding& encoding);
    template<> std::string  ConvertString<>(const wchar_t* const& wstr, const size_t& size, const PBString::StringEncoding& encoding);
    template<> std::string  ConvertString<>(const wchar_t* const& wstr, const PBString::StringEncoding& encoding);
    template<> std::string  ConvertString<>(const std::wstring& wstr, const PBString::StringEncoding& encoding);

    template<> inline std::wstring ConvertString<>(const char* const& str, const size_t& size)     { return ConvertString<std::wstring>(str, size, PBString::UTF8); }
    template<> inline std::wstring ConvertString<>(const char* const& str)                         { return ConvertString<std::wstring>(str, PBString::UTF8); }
    template<> inline std::wstring ConvertString<>(const std::string_view& str)                    { return ConvertString<std::wstring>(str, PBString::UTF8); }
    template<> inline std::wstring ConvertString<>(const std::string& str)                         { return ConvertString<std::wstring>(str, PBString::UTF8); }
    template<> inline std::string  ConvertString<>(const wchar_t* const& wstr, const size_t& size) { return ConvertString<std::string >(wstr, size, PBString::UTF8); }
    template<> inline std::string  ConvertString<>(const wchar_t* const& wstr)                     { return ConvertString<std::string >(wstr, PBString::UTF8); }
    template<> inline std::string  ConvertString<>(const std::wstring& wstr)                       { return ConvertString<std::string >(wstr, PBString::UTF8); }
    // clang-format on
}  // namespace Inf