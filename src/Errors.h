#pragma once

#include <exception>
#include <boost/stacktrace.hpp>
#include <map>
#include <array>

#include "PBString.h"


namespace Inf
{
    /**
     * Used by PBObject::Invoke if the invoked PowerBuilder function throws an Exception
     */
    class PBNI_ExceptionThrown : public std::exception { };

    /**
     * Use this class to throw Verbose Exceptions that can be handled by PowerBuilder.
     * This class automatically generates a StackTrace.
     */
    class PBNI_Exception : public std::exception
    {
    public:
        PBNI_Exception(const std::wstring& message)
            : PBNI_Exception(message, {})
        { }

        PBNI_Exception(const std::wstring& message, const std::map<std::wstring, std::wstring>& keyValues)
            : m_Message(message), m_KeyValueStore(keyValues)
        {
            #if NDEBUG
                m_KeyValueStore.insert({ L"Stacktrace", L"Use the debug library to get Stacktraces from C++"});
            #else
                boost::stacktrace::stacktrace st;
                m_KeyValueStore.insert({ L"Stacktrace", ConvertString<std::wstring>(boost::stacktrace::to_string(st)) });
            #endif
        }

        /**
         * This method is just there so the exception is compatible with std::exception.
         * 
         * \return The First error
         */
        const char* what() const noexcept override
        {
            m_What = ConvertString<std::string>(m_Message);
            return m_What.c_str();
        }

        /**
         * Method to retrieve the pushed KeyValues.
         * 
         * \return KeyValues
         */
        const std::map<std::wstring, std::wstring>& GetKeyValues() const
        {
            return m_KeyValueStore;
        }

        /**
         * Method to retrieve the pushed KeyValues.
         * 
         * \return KeyValues
         */
        const std::wstring& GetMessage() const
        {
            return m_Message;
        }

        /**
         * Method to retrieve the Type to nest as.
         * 
         * \return Type or empty string
         */
        const std::wstring& GetNestAs() const
        {
            return m_NestedType;
        }

        /**
         * Push a KeyValue to an already existing error.
         * 
         * \param key       Key To add
         * \param value     Value to add as key
         */
        PBNI_Exception& Push(std::wstring key, std::wstring value)
        {
            m_KeyValueStore.insert({ key, value });
            return *this;
        }

        /**
         * Nests the `u_exf_ex` in a new exception with type exceptionType. 
         * 
         * \param exceptionType The Type of the new exception
         */
        PBNI_Exception& NestAs(std::wstring exceptionType)
        {
            m_NestedType = exceptionType;
            return *this;
        }
    private:
        mutable std::string m_What;

        std::wstring m_Message;
        std::map<std::wstring, std::wstring> m_KeyValueStore;
        std::wstring m_NestedType;
    };

    /**
     * This Exception is thrown by PBArray when someone tried to access a value outside of the arrays bounds.
     */
    class PBNI_IndexOutOfBoundsException : public PBNI_Exception
    {
    public:
        PBNI_IndexOutOfBoundsException(pblong pos, pblong size)
            : PBNI_Exception(L"Accesssing an index out of bounds in an Unbounded PBArray", {
                    { L"Position", std::to_wstring(pos) },
                    { L"Bounds", L"1 to " + std::to_wstring(size) }
                })
        { }

        template <int N>
        PBNI_IndexOutOfBoundsException(std::array<pblong, N> pos, std::array<std::pair<pblong, pblong>, N> bounds, pbbyte dim)
            : PBNI_Exception(L"Accesssing an index out of bounds in a Bounded PBArray", {
                    { L"Dimension", std::to_wstring(dim) }
                })
        {
            std::wstring pos_str;
            for (pblong i : pos)
            {
                pos_str += std::to_wstring(i) + L", ";
            }
            pos_str.resize(pos_str.size() - 2);
            Push(L"Positions", pos_str);

            std::wstring bounds_str;
            for (auto [upper, lower] : bounds)
            {
                bounds_str += std::to_wstring(lower) + L" to " + std::to_wstring(upper) + L", ";
            }
            bounds_str.resize(bounds_str.size() - 2);
            Push(L"Bounds", bounds_str);
        }
    };

    /**
     * This Exception can be thrown anywhere, because all PowerBuilder types can be null, always check using IsNull.
     */
    class PBNI_NullPointerException : public PBNI_Exception
    {
    public:
        PBNI_NullPointerException(std::wstring type)
            : PBNI_Exception(L"Tried to access a PowerBuilder value that is Null", {
                    { L"Type", type }
                })
        { }
    };

    /**
     * This Exception gets thrown if you try to access a field of an Object, that doesn't exist.
     */
    class PBNI_InvalidFieldException : public PBNI_Exception
    {
    public:
        PBNI_InvalidFieldException(std::wstring type, std::wstring field, std::wstring field_type)
            : PBNI_Exception(L"Tried to acces an Invalid Field", {
                    { L"Type", type },
                    { L"Field", field },
                    { L"Field Type", field_type }
                })
        { }
    };

    /**
     * This Exception gets thrown if you try to read an Enum that doesn't exist
     */
    class PBNI_InvalidEnumException : public PBNI_Exception
    {
    public:
        PBNI_InvalidEnumException(std::wstring type, std::wstring value)
            : PBNI_Exception(L"Tried to acces an Invalid Enum", {
                    { L"Type", type },
                    { L"Value", value }
                })
        { }

        PBNI_InvalidEnumException(std::wstring type, pblong value)
            : PBNI_Exception(L"Tried to acces an Invalid Enum", {
                    { L"Type", type },
                    { L"Value ID", std::to_wstring(value) }
                })
        { }
    };

    /**
     * This exception gets thrown, when PowerBuilder invokes a function inside the Framework,
     * but it doesnt give the right Arguments. Or when you try to Invoke a PowerBuilder function
     * and dont give the right Arguments.
     */
    class PBNI_IncorrectArgumentsException : public PBNI_Exception
    {
    public:
        PBNI_IncorrectArgumentsException(std::wstring class_name, std::wstring method_name)
            : PBNI_Exception(L"Tried to call a PowerBuilder Method with wrong Arguments", {
                    { L"Class", class_name },
                    { L"Method", method_name }
                })
        { }

        PBNI_IncorrectArgumentsException(std::wstring class_name, std::wstring method_name, pbint argument_number)
            : PBNI_IncorrectArgumentsException(class_name, method_name)
        {
            Push(L"Argument Number", std::to_wstring(argument_number));
        }
    };

    /**
     * This exception gets thrown if any PBNI Function that gets called doesn't return PBX_SUCCESS.
     */
    class PBNI_PowerBuilderException : public PBNI_Exception
    {
    public:
        PBNI_PowerBuilderException(std::wstring method_name, PBXRESULT res)
            : PBNI_Exception(L"Failed to call PowerBuilder Method", {
                    { L"Method", method_name },
                    { L"Result", std::to_wstring(res) }
                })
        { }
    };
}