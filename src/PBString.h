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
        PBString(IPB_Session* session, const std::string& str, StringEncoding encoding = ANSI);
        PBString(IPB_Session* session, const std::string_view& str, StringEncoding encoding = ANSI);
        PBString(IPB_Session* session, const char* str, StringEncoding encoding = ANSI);
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
        std::string GetString(StringEncoding encoding = ANSI) const;
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
        void SetString(const std::string& str, StringEncoding encoding = ANSI);
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
        operator pbstring() const {
            return m_String;
        }
    private:
        friend class Helper::PBValue;
        friend class PBAny;
        template <typename PBT, pblong... dims>
            requires (sizeof...(dims) <= 3 && !std::is_reference_v<PBT> && !std::is_pointer_v<PBT>)
        friend class PBArray;
        template <Helper::FixedString class_id, pbgroup_type group_type>
        friend class PBObject;

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
    template <typename ToStr, typename... FromStr> ToStr ConvertString(FromStr... str) = delete;

    // TODO Stop uneccessary copying from happening
    template<> std::wstring ConvertString<>(const char* str, size_t size, PBString::StringEncoding encoding);
    template<> std::wstring ConvertString<>(const char* str, PBString::StringEncoding encoding);
    template<> std::wstring ConvertString<>(const std::string_view str, PBString::StringEncoding encoding);
    template<> std::wstring ConvertString<>(const std::string str, PBString::StringEncoding encoding);
    template<> std::string ConvertString<>(const wchar_t* wstr, size_t size, PBString::StringEncoding encoding);
    template<> std::string ConvertString<>(const wchar_t* wstr, PBString::StringEncoding encoding);
    template<> std::string ConvertString<>(const std::wstring wstr, PBString::StringEncoding encoding);

    template<> std::wstring ConvertString<>(const char* str, size_t size);
    template<> std::wstring ConvertString<>(const char* str);
    template<> std::wstring ConvertString<>(const std::string_view str);
    template<> std::wstring ConvertString<>(const std::string str);
    template<> std::string ConvertString<>(const wchar_t* wstr, size_t size);
    template<> std::string ConvertString<>(const wchar_t* wstr);
    template<> std::string ConvertString<>(const std::wstring wstr);
}
