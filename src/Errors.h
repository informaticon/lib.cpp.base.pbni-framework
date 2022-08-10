#pragma once

#include <exception>
#include <boost/stacktrace.hpp>

#include "Strings.h"


namespace Inf
{
	class u_exf_pbni : public std::exception
	{
	public:
		u_exf_pbni(std::wstring info)
			: m_Info(info)
		{ }

		virtual const char* what() const override
		{
			m_What = ConvertString<std::string>(err_msg() + L"\n" + stack_trace());
			return m_What.c_str();
		}

		virtual std::wstring err_msg() const
		{
			return m_Info;
		}

		virtual std::wstring stack_trace() const
		{
			return ConvertString<std::wstring>(boost::stacktrace::to_string(m_Stacktrace));
		}

	private:
		mutable std::string m_What;
		boost::stacktrace::stacktrace m_Stacktrace;
		std::wstring m_Info;
	};

}