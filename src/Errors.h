#pragma once

#include <exception>
#include <boost/stacktrace.hpp>
#include <map>
#include <array>

#include "PBString.h"


namespace Inf
{
	/**
	 * Use this class to throw Verbose Exceptions that can be handled by PowerBuilder.
	 * This class automatically generates a StackTrace.
	 */
	class PBNI_Exception : public std::exception
	{
	public:
		PBNI_Exception(std::wstring err_msg)
			: PBNI_Exception({ { L"Error", err_msg } })
		{}

		PBNI_Exception(std::map<std::wstring, std::wstring> key_values)
			: m_KeyValueStore(key_values)
		{
			boost::stacktrace::stacktrace st;
			m_KeyValueStore.insert({ L"Stacktrace", ConvertString<std::wstring>(boost::stacktrace::to_string(st)) });
		}

		/**
		 * This method is just there so the exception is compatible with std::exception.
		 * 
		 * \return The First error
		 */
		virtual const char* what() const override
		{
			m_What = ConvertString<std::string>( (*m_KeyValueStore.begin()).second );
			return m_What.c_str();
		}

		/**
		 * Method to retrieve the pushed KeyValues.
		 * 
		 * \return KeyValues
		 */
		virtual const std::map<std::wstring, std::wstring>& GetKeyValues() const
		{
			return m_KeyValueStore;
		}

		/**
		 * Push a KeyValue to an already existing error.
		 * 
		 * \param key		Key To add
		 * \param value		Value to add as key
		 */
		virtual void Push(std::wstring key, std::wstring value)
		{
			m_KeyValueStore.insert({ key, value });
		}
	private:
		mutable std::string m_What;
		std::map<std::wstring, std::wstring> m_KeyValueStore;
	};

	/**
	 * This Exception is thrown by PBArray when someone tried to access a value outside of the arrays bounds.
	 */
	class PBNI_IndexOutOfBoundsException : public PBNI_Exception
	{
	public:
		PBNI_IndexOutOfBoundsException(pblong pos, pblong size)
			: PBNI_Exception({
					{ L"Error", L"Accesssing an index out of bounds in an Unounded PBArray" },
					{ L"Position", std::to_wstring(pos) },
					{ L"Bounds", L"1 to " + std::to_wstring(size) }
				})
		{ }

		template <int N>
		PBNI_IndexOutOfBoundsException(std::array<pblong, N> pos, std::array<std::pair<pblong, pblong>, N> bounds, pbbyte dim)
			: PBNI_Exception({
					{ L"Error", L"Accesssing an index out of bounds in a Bounded PBArray" },
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
			: PBNI_Exception({
					{ L"Error", L"Tried to access a PowerBuilder value that is Null" },
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
			: PBNI_Exception({
					{ L"Error", L"Tried to acces an Invalid Field" },
					{ L"Type", type },
					{ L"Field", field },
					{ L"Field Type", field_type }
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
			: PBNI_Exception({
					{ L"Error", L"Tried to call a PowerBuilder Method with wrong Arguments" },
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
			: PBNI_Exception({
					{ L"Error", L"Failed to call PowerBuilder Method" },
					{ L"Method", method_name },
					{ L"Result", std::to_wstring(res) }
				})
		{ }
	};
}