#include "PBTypes.h"

namespace Inf
{
    // clang-format off
#pragma region Bytelike
	template<> constexpr wchar_t Type<PBByte>::PBSignature = L'E';
	template<> constexpr pbvalue_type Type<PBByte>::PBType = pbvalue_byte;

	template<> constexpr wchar_t Type<PBBoolean>::PBSignature = L'B';
	template<> constexpr pbvalue_type Type<PBBoolean>::PBType = pbvalue_boolean;

	template<> constexpr wchar_t Type<PBChar>::PBSignature = L'H';
	template<> constexpr pbvalue_type Type<PBChar>::PBType = pbvalue_char;
#pragma endregion

#pragma region Integer_Numbers
	template<> constexpr wchar_t Type<PBInt>::PBSignature = L'I';
	template<> constexpr pbvalue_type Type<PBInt>::PBType = pbvalue_int;

	template<> constexpr wchar_t Type<PBUint>::PBSignature = L'N';
	template<> constexpr pbvalue_type Type<PBUint>::PBType = pbvalue_uint;

	template<> constexpr wchar_t Type<PBLong>::PBSignature = L'L';
	template<> constexpr pbvalue_type Type<PBLong>::PBType = pbvalue_long;

	template<> constexpr wchar_t Type<PBUlong>::PBSignature = L'U';
	template<> constexpr pbvalue_type Type<PBUlong>::PBType = pbvalue_ulong;

	template<> constexpr wchar_t Type<PBLongLong>::PBSignature = L'K';
	template<> constexpr pbvalue_type Type<PBLongLong>::PBType = pbvalue_longlong;
#pragma endregion

#pragma region Floating_Point_Numbers
	template<> constexpr wchar_t Type<PBReal>::PBSignature = L'F';
	template<> constexpr pbvalue_type Type<PBReal>::PBType = pbvalue_real;

	template<> constexpr wchar_t Type<PBDouble>::PBSignature = L'D';
	template<> constexpr pbvalue_type Type<PBDouble>::PBType = pbvalue_double;

	template<> constexpr wchar_t Type<PBDecimal>::PBSignature = L'M';
	template<> constexpr pbvalue_type Type<PBDecimal>::PBType = pbvalue_dec;
#pragma endregion

#pragma region Date_Times
	template<> constexpr wchar_t Type<PBTime>::PBSignature = L'T';
	template<> constexpr pbvalue_type Type<PBTime>::PBType = pbvalue_time;

	template<> constexpr wchar_t Type<PBDate>::PBSignature = L'Y';
	template<> constexpr pbvalue_type Type<PBDate>::PBType = pbvalue_date;

	template<> constexpr wchar_t Type<PBDateTime>::PBSignature = L'W';
	template<> constexpr pbvalue_type Type<PBDateTime>::PBType = pbvalue_datetime;
#pragma endregion

#pragma region Variable_Sized
	template<> constexpr wchar_t Type<PBString>::PBSignature = L'S';
	template<> constexpr pbvalue_type Type<PBString>::PBType = pbvalue_string;

	template<> constexpr wchar_t Type<PBBlob>::PBSignature = L'O';
	template<> constexpr pbvalue_type Type<PBBlob>::PBType = pbvalue_blob;
#pragma endregion
    // clang-format on
}  // namespace Inf
