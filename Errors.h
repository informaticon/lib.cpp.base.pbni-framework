#pragma once

#include <exception>
#include <boost/stacktrace.hpp>
#include <map>

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

}