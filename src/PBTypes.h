#pragma once

#include <windows.h>

#include "PBNumbers.h"
#include "PBDateTimes.h"
#include "PBString.h"
#include "PBBlob.h"


namespace Inf
{
	/**
	 * This is the Genereic Type struct, each PBType implements the Fields it needs.
	 * You can Access any one of the Functions using e.g. Type<T>::PBSignature.
	 * 
	 * \tparam T	The related Type
	 */
	template <typename T>
	struct Type {
		// This Field is used to build a Method Signature, if you want to invoke a PowerBuilder Function from C++.
		static constexpr wchar_t PBSignature = L' ';
		// This Field is used to check for correct IPB_Value Types.
		static constexpr pbvalue_type PBType = pbvalue_notype;

		/**
		 * This Function is used to generate the Description of a Method, it needs to take in the name of the argument so we can add [] at the end of arrays.
		 * This wont add any spaces between the type and argument_name.
		 *
		 * \param argument_name		The name to put between type and []
		 * \return					The combined string
		 */
		static inline std::wstring GetPBName(std::wstring argument_name) = delete;
	};

/// \cond typetemplates
	/**
	 * We dont want to be used as Argument, only implement whats allowed.
	 */
	using PBVoid = void;
	template <>
	struct Type<PBVoid> {
		static constexpr wchar_t PBSignature = L'Q';
	};

	/**
	 * Complex Types start with Decimal
	 */

#pragma region Any
	template<> constexpr wchar_t Type<PBAny>::PBSignature = L'A';
	template<> constexpr pbvalue_type Type<PBAny>::PBType = pbvalue_any;
	template<> inline std::wstring Type<PBAny>::GetPBName(std::wstring argument_name) { return L"any" + argument_name; }
#pragma endregion

#pragma region Bytelike
	template<> constexpr wchar_t Type<PBByte>::PBSignature = L'E';
	template<> constexpr pbvalue_type Type<PBByte>::PBType = pbvalue_byte;
	template<> inline std::wstring Type<PBByte>::GetPBName(std::wstring argument_name) { return L"byte" + argument_name; }

	template<> constexpr wchar_t Type<PBBoolean>::PBSignature = L'B';
	template<> constexpr pbvalue_type Type<PBBoolean>::PBType = pbvalue_boolean;
	template<> inline std::wstring Type<PBBoolean>::GetPBName(std::wstring argument_name) { return L"boolean" + argument_name; }

	template<> constexpr wchar_t Type<PBChar>::PBSignature = L'H';
	template<> constexpr pbvalue_type Type<PBChar>::PBType = pbvalue_char;
	template<> inline std::wstring Type<PBChar>::GetPBName(std::wstring argument_name) { return L"char" + argument_name; }
#pragma endregion

#pragma region Integer_Numbers
	template<> constexpr wchar_t Type<PBInt>::PBSignature = L'I';
	template<> constexpr pbvalue_type Type<PBInt>::PBType = pbvalue_int;
	template<> inline std::wstring Type<PBInt>::GetPBName(std::wstring argument_name) { return L"int" + argument_name; }

	template<> constexpr wchar_t Type<PBUint>::PBSignature = L'N';
	template<> constexpr pbvalue_type Type<PBUint>::PBType = pbvalue_uint;
	template<> inline std::wstring Type<PBUint>::GetPBName(std::wstring argument_name) { return L"uint" + argument_name; }

	template<> constexpr wchar_t Type<PBLong>::PBSignature = L'L';
	template<> constexpr pbvalue_type Type<PBLong>::PBType = pbvalue_long;
	template<> inline std::wstring Type<PBLong>::GetPBName(std::wstring argument_name) { return L"long" + argument_name; }

	template<> constexpr wchar_t Type<PBUlong>::PBSignature = L'U';
	template<> constexpr pbvalue_type Type<PBUlong>::PBType = pbvalue_ulong;
	template<> inline std::wstring Type<PBUlong>::GetPBName(std::wstring argument_name) { return L"ulong" + argument_name; }

	template<> constexpr wchar_t Type<PBLongLong>::PBSignature = L'K';
	template<> constexpr pbvalue_type Type<PBLongLong>::PBType = pbvalue_longlong;
	template<> inline std::wstring Type<PBLongLong>::GetPBName(std::wstring argument_name) { return L"longlong" + argument_name; }
#pragma endregion

#pragma region Floating_Point_Numbers
	template<> constexpr wchar_t Type<PBReal>::PBSignature = L'F';
	template<> constexpr pbvalue_type Type<PBReal>::PBType = pbvalue_real;
	template<> inline std::wstring Type<PBReal>::GetPBName(std::wstring argument_name) { return L"real" + argument_name; }

	template<> constexpr wchar_t Type<PBDouble>::PBSignature = L'D';
	template<> constexpr pbvalue_type Type<PBDouble>::PBType = pbvalue_double;
	template<> inline std::wstring Type<PBDouble>::GetPBName(std::wstring argument_name) { return L"double" + argument_name; }

	template<> constexpr wchar_t Type<PBDecimal>::PBSignature = L'M';
	template<> constexpr pbvalue_type Type<PBDecimal>::PBType = pbvalue_dec;
	template<> inline std::wstring Type<PBDecimal>::GetPBName(std::wstring argument_name) { return L"dec" + argument_name; }
#pragma endregion

#pragma region Date_Times
	template<> constexpr wchar_t Type<PBTime>::PBSignature = L'T';
	template<> constexpr pbvalue_type Type<PBTime>::PBType = pbvalue_time;
	template<> inline std::wstring Type<PBTime>::GetPBName(std::wstring argument_name) { return L"time" + argument_name; }

	template<> constexpr wchar_t Type<PBDate>::PBSignature = L'Y';
	template<> constexpr pbvalue_type Type<PBDate>::PBType = pbvalue_date;
	template<> inline std::wstring Type<PBDate>::GetPBName(std::wstring argument_name) { return L"date" + argument_name; }

	template<> constexpr wchar_t Type<PBDateTime>::PBSignature = L'W';
	template<> constexpr pbvalue_type Type<PBDateTime>::PBType = pbvalue_datetime;
	template<> inline std::wstring Type<PBDateTime>::GetPBName(std::wstring argument_name) { return L"datetime" + argument_name; }
#pragma endregion

#pragma region Variable_Sized
	template<> constexpr wchar_t Type<PBString>::PBSignature = L'S';
	template<> constexpr pbvalue_type Type<PBString>::PBType = pbvalue_string;
	template<> inline std::wstring Type<PBString>::GetPBName(std::wstring argument_name) { return L"string" + argument_name; }

	template<> constexpr wchar_t Type<PBBlob>::PBSignature = L'O';
	template<> constexpr pbvalue_type Type<PBBlob>::PBType = pbvalue_blob;
	template<> inline std::wstring Type<PBBlob>::GetPBName(std::wstring argument_name) { return L"blob" + argument_name; }

	/**
	 * For Types that have their own template types (PBObject<>, PBArray<>) we cant partially specialize the static Functions.
	 * Instead we have to create our own Struct, which can be partially specialized
	 */
	template <typename T, pblong... dims>
	struct Type<PBArray<T, dims...>> // <- Partial specialization
	{
		static inline std::wstring PBSignature = std::wstring(1, Type<T>::PBSignature) + L"[]";
		static inline std::wstring GetPBName(std::wstring argument_name)
		{
			if constexpr (sizeof...(dims) == 0)
			{
				return Type<T>::GetPBName(argument_name) + L"[]";
			}
			else
			{
				std::wstring dimensions = ((std::to_wstring(dims) + L", ") + ...);
				dimensions.resize(dimensions.size() - 2);
				return Type<T>::GetPBName(argument_name) + L"[" + dimensions + L"]";
			}
		}
	};


	template <Helper::FixedString class_id, pbgroup_type group_type>
	class PBObject;

	template <typename Item, pblong... dims>
		requires (sizeof...(dims) <= 3 && !std::is_reference_v<Item> && !std::is_pointer_v<Item>)
	class PBArray;

	template <Helper::FixedString class_id, pbgroup_type group_type, pblong... dims>
	struct Type<PBArray<PBObject<class_id, group_type>, dims...>>
	{
		static inline std::wstring PBSignature = Type<PBObject<class_id, group_type>>::PBSignature + L"[]";
		static inline std::wstring GetPBName(std::wstring argument_name)
		{
			if constexpr (sizeof...(dims) == 0)
			{
				return Type<PBObject<class_id, group_type>>::GetPBName(argument_name) + L"[]";
			}
			else
			{
				std::wstring dimensions = ((std::to_wstring(dims) + L", ") + ...);
				dimensions.resize(dimensions.size() - 2);
				return Type<PBObject<class_id, group_type>>::GetPBName(argument_name) + L"[" + dimensions + L"]";
			}
		}
	};


	template <Helper::FixedString class_id, pbgroup_type group_type>
	struct Type<PBObject<class_id, group_type>>
	{
		static inline std::wstring PBSignature = std::wstring(L"C") + PBObject<class_id, group_type>::ClassName() + L".";
		static inline std::wstring GetPBName(std::wstring argument_name) { return std::wstring(class_id.data) + argument_name; }
	};
#pragma endregion
/// \endcond
}