#pragma once

#include <string>

#include <pbext.h>


namespace Inf
{
	template <typename PBT, pblong... dims>
		requires (sizeof...(dims) <= 3 && !std::is_reference_v<PBT> && !std::is_pointer_v<PBT>)
	class PBArray;

	template <typename T>
	class Type;


	class PBString
	{
	public:
		PBString(IPB_Session* session, pbstring pb_string);
		PBString(IPB_Session* session, const std::string& str);
		PBString(IPB_Session* session, const std::wstring& str);

		std::string GetString() const;
		std::wstring GetWString() const;
		void SetString(const std::string& str);
		void SetWString(const std::wstring& str);

		pblong Size() const;

		bool IsNull() const;
		void SetToNull();
	private:
		friend class Type<PBString>;
		friend class PBArray<PBString>;

		IPB_Session* m_Session;
		pbstring m_String;
	};
}
