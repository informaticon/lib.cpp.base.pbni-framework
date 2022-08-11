#pragma once

#include <windows.h>

#include "PBObjects.h"


namespace Inf
{
	template <typename T>
	struct Type {
		static constexpr wchar_t PBSignature = L' ';
		static constexpr pbvalue_type PBType = pbvalue_notype;
		static inline bool Assert(IPB_Session* session, IPB_Value* pb_value) { return pb_value->GetType() == PBType; };
		static inline std::wstring GetPBName(std::wstring argument_name) = delete;
		static inline T FromArgument(IPB_Session* session, IPB_Value* argument) = delete;
		static inline void SetValue(IPB_Session* session, IPB_Value* pb_value, T t) = delete;
		static inline void Return(IPB_Session* session, PBCallInfo* ci, const T t) { SetValue(session, ci->returnValue, t); }
	};

	using PBVoid = void;
	template <>
	struct Type<PBVoid> {
		static constexpr wchar_t PBSignature = L'Q';
	};

	// Bytelike
	template<> constexpr wchar_t Type<PBByte>::PBSignature = L'E';
	template<> constexpr pbvalue_type Type<PBByte>::PBType = pbvalue_byte;
	template<> inline std::wstring Type<PBByte>::GetPBName(std::wstring argument_name) { return L"byte" + argument_name; }
	template<> inline PBByte Type<PBByte>::FromArgument(IPB_Session* session, IPB_Value* argument) { return argument->IsNull() ? PBByte() : PBByte(argument->GetByte()); }
	template<> inline void Type<PBByte>::SetValue(IPB_Session* session, IPB_Value* pb_value, const PBByte value) { if (value.IsNull()) pb_value->SetToNull(); else pb_value->SetByte(value); }

	template<> constexpr wchar_t Type<PBBoolean>::PBSignature = L'B';
	template<> constexpr pbvalue_type Type<PBBoolean>::PBType = pbvalue_boolean;
	template<> inline std::wstring Type<PBBoolean>::GetPBName(std::wstring argument_name) { return L"boolean" + argument_name; }
	template<> inline PBBoolean Type<PBBoolean>::FromArgument(IPB_Session* session, IPB_Value* argument) { return argument->IsNull() ? PBBoolean() : PBBoolean(argument->GetBool()); }
	template<> inline void Type<PBBoolean>::SetValue(IPB_Session* session, IPB_Value* pb_value, const PBBoolean value) { if (value.IsNull()) pb_value->SetToNull(); else pb_value->SetBool(value); }

	template<> constexpr wchar_t Type<PBChar>::PBSignature = L'H';
	template<> constexpr pbvalue_type Type<PBChar>::PBType = pbvalue_char;
	template<> inline std::wstring Type<PBChar>::GetPBName(std::wstring argument_name) { return L"char" + argument_name; }
	template<> inline PBChar Type<PBChar>::FromArgument(IPB_Session* session, IPB_Value* argument) { return argument->IsNull() ? PBChar() : PBChar(argument->GetChar()); }
	template<> inline void Type<PBChar>::SetValue(IPB_Session* session, IPB_Value* pb_value, const PBChar value) { if (value.IsNull()) pb_value->SetToNull(); else pb_value->SetChar(value); }


	// Integer numbers
	template<> constexpr wchar_t Type<PBInt>::PBSignature = L'I';
	template<> constexpr pbvalue_type Type<PBInt>::PBType = pbvalue_int;
	template<> inline std::wstring Type<PBInt>::GetPBName(std::wstring argument_name) { return L"int" + argument_name; }
	template<> inline PBInt Type<PBInt>::FromArgument(IPB_Session* session, IPB_Value* argument) { return argument->IsNull() ? PBInt() : PBInt(argument->GetInt()); }
	template<> inline void Type<PBInt>::SetValue(IPB_Session* session, IPB_Value* pb_value, const PBInt value) { if (value.IsNull()) pb_value->SetToNull(); else pb_value->SetInt(value); }

	template<> constexpr wchar_t Type<PBUint>::PBSignature = L'N';
	template<> constexpr pbvalue_type Type<PBUint>::PBType = pbvalue_uint;
	template<> inline std::wstring Type<PBUint>::GetPBName(std::wstring argument_name) { return L"uint" + argument_name; }
	template<> inline PBUint Type<PBUint>::FromArgument(IPB_Session* session, IPB_Value* argument) { return argument->IsNull() ? PBUint() : PBUint(argument->GetUint()); }
	template<> inline void Type<PBUint>::SetValue(IPB_Session* session, IPB_Value* pb_value, const PBUint value) { if (value.IsNull()) pb_value->SetToNull(); else pb_value->SetUint(value); }

	template<> constexpr wchar_t Type<PBLong>::PBSignature = L'L';
	template<> constexpr pbvalue_type Type<PBLong>::PBType = pbvalue_long;
	template<> inline std::wstring Type<PBLong>::GetPBName(std::wstring argument_name) { return L"long" + argument_name; }
	template<> inline PBLong Type<PBLong>::FromArgument(IPB_Session* session, IPB_Value* argument) { return argument->IsNull() ? PBLong() : PBLong(argument->GetLong()); }
	template<> inline void Type<PBLong>::SetValue(IPB_Session* session, IPB_Value* pb_value, const PBLong value) { if (value.IsNull()) pb_value->SetToNull(); else pb_value->SetLong(value); }

	template<> constexpr wchar_t Type<PBUlong>::PBSignature = L'U';
	template<> constexpr pbvalue_type Type<PBUlong>::PBType = pbvalue_ulong;
	template<> inline std::wstring Type<PBUlong>::GetPBName(std::wstring argument_name) { return L"ulong" + argument_name; }
	template<> inline PBUlong Type<PBUlong>::FromArgument(IPB_Session* session, IPB_Value* argument) { return argument->IsNull() ? PBUlong() : PBUlong(argument->GetUlong()); }
	template<> inline void Type<PBUlong>::SetValue(IPB_Session* session, IPB_Value* pb_value, const PBUlong value) { if (value.IsNull()) pb_value->SetToNull(); else pb_value->SetUlong(value); }

	template<> constexpr wchar_t Type<PBLongLong>::PBSignature = L'K';
	template<> constexpr pbvalue_type Type<PBLongLong>::PBType = pbvalue_longlong;
	template<> inline std::wstring Type<PBLongLong>::GetPBName(std::wstring argument_name) { return L"longlong" + argument_name; }
	template<> inline PBLongLong Type<PBLongLong>::FromArgument(IPB_Session* session, IPB_Value* argument) { return argument->IsNull() ? PBLongLong() : PBLongLong(argument->GetLongLong()); }
	template<> inline void Type<PBLongLong>::SetValue(IPB_Session* session, IPB_Value* pb_value, const PBLongLong value) { if (value.IsNull()) pb_value->SetToNull(); else pb_value->SetLongLong(value); }


	// Floating point numbers
	template<> constexpr wchar_t Type<PBReal>::PBSignature = L'F';
	template<> constexpr pbvalue_type Type<PBReal>::PBType = pbvalue_real;
	template<> inline std::wstring Type<PBReal>::GetPBName(std::wstring argument_name) { return L"real" + argument_name; }
	template<> inline PBReal Type<PBReal>::FromArgument(IPB_Session* session, IPB_Value* argument) { return argument->IsNull() ? PBReal() : PBReal(argument->GetReal()); }
	template<> inline void Type<PBReal>::SetValue(IPB_Session* session, IPB_Value* pb_value, const PBReal value) { if (value.IsNull()) pb_value->SetToNull(); else pb_value->SetReal(value); }

	template<> constexpr wchar_t Type<PBDouble>::PBSignature = L'D';
	template<> constexpr pbvalue_type Type<PBDouble>::PBType = pbvalue_double;
	template<> inline std::wstring Type<PBDouble>::GetPBName(std::wstring argument_name) { return L"double" + argument_name; }
	template<> inline PBDouble Type<PBDouble>::FromArgument(IPB_Session* session, IPB_Value* argument) { return argument->IsNull() ? PBDouble() : PBDouble(argument->GetDouble()); }
	template<> inline void Type<PBDouble>::SetValue(IPB_Session* session, IPB_Value* pb_value, const PBDouble value) { if (value.IsNull()) pb_value->SetToNull(); else pb_value->SetDouble(value); }

	// Complex types start here
	template<> constexpr wchar_t Type<PBDecimal>::PBSignature = L'M';
	template<> constexpr pbvalue_type Type<PBDecimal>::PBType = pbvalue_dec;
	template<> inline std::wstring Type<PBDecimal>::GetPBName(std::wstring argument_name) { return L"dec" + argument_name; }
	template<> inline PBDecimal Type<PBDecimal>::FromArgument(IPB_Session* session, IPB_Value* argument)
	{
		if (argument->IsNull())
			return {};

		LPCTSTR dec_repr = session->GetDecimalString(argument->GetDecimal());

		PBDecimal dec = Helper::PBDecimalImpl(ConvertString<std::string>(dec_repr));

		session->ReleaseDecimalString(dec_repr);

		return dec;
	}
	template<> inline void Type<PBDecimal>::SetValue(IPB_Session* session, IPB_Value* pb_value, const PBDecimal value)
	{
		if (value.IsNull())
		{
			pb_value->SetToNull();
		}
		else
		{
			std::wstring dec_repr = ConvertString<std::wstring>(value.t.str());

			pbdec pb_dec = session->NewDecimal();
			session->SetDecimal(pb_dec, dec_repr.c_str());

			pb_value->SetDecimal(pb_dec);
		}
	}


	// Dates and Times
	template<> constexpr wchar_t Type<PBTime>::PBSignature = L'T';
	template<> constexpr pbvalue_type Type<PBTime>::PBType = pbvalue_time;
	template<> inline std::wstring Type<PBTime>::GetPBName(std::wstring argument_name) { return L"time" + argument_name; }
	template<> inline PBTime Type<PBTime>::FromArgument(IPB_Session* session, IPB_Value* argument) { return { session, argument->IsNull() ? 0 : argument->GetTime() }; }
	template<> inline void Type<PBTime>::SetValue(IPB_Session* session, IPB_Value* pb_value, const PBTime value) { if (value.IsNull()) pb_value->SetToNull(); else pb_value->SetTime(value.m_Time); }

	template<> constexpr wchar_t Type<PBDate>::PBSignature = L'Y';
	template<> constexpr pbvalue_type Type<PBDate>::PBType = pbvalue_date;
	template<> inline std::wstring Type<PBDate>::GetPBName(std::wstring argument_name) { return L"date" + argument_name; }
	template<> inline PBDate Type<PBDate>::FromArgument(IPB_Session* session, IPB_Value* argument) { return { session, argument->IsNull() ? 0 : argument->GetDate() }; }
	template<> inline void Type<PBDate>::SetValue(IPB_Session* session, IPB_Value* pb_value, const PBDate value) { if (value.IsNull()) pb_value->SetToNull(); else pb_value->SetDate(value.m_Date); }

	template<> constexpr wchar_t Type<PBDateTime>::PBSignature = L'W';
	template<> constexpr pbvalue_type Type<PBDateTime>::PBType = pbvalue_datetime;
	template<> inline std::wstring Type<PBDateTime>::GetPBName(std::wstring argument_name) { return L"datetime" + argument_name; }
	template<> inline PBDateTime Type<PBDateTime>::FromArgument(IPB_Session* session, IPB_Value* argument) { return { session, argument->IsNull() ? 0 : argument->GetDateTime() }; }
	template<> inline void Type<PBDateTime>::SetValue(IPB_Session* session, IPB_Value* pb_value, const PBDateTime value) { if (value.IsNull()) pb_value->SetToNull(); else pb_value->SetDateTime(value.m_DateTime); }


	// Variable sized
	template<> constexpr wchar_t Type<PBString>::PBSignature = L'S';
	template<> constexpr pbvalue_type Type<PBString>::PBType = pbvalue_string;
	template<> inline std::wstring Type<PBString>::GetPBName(std::wstring argument_name) { return L"string" + argument_name; }
	template<> inline PBString Type<PBString>::FromArgument(IPB_Session* session, IPB_Value* argument) { return { session, argument->IsNull() ? 0 : argument->GetString() }; }
	template<> inline void Type<PBString>::SetValue(IPB_Session* session, IPB_Value* pb_value, const PBString value) { if (value.IsNull()) pb_value->SetToNull(); else pb_value->SetPBString(value.m_String); }

	template<> constexpr wchar_t Type<PBBlob>::PBSignature = L'O';
	template<> constexpr pbvalue_type Type<PBBlob>::PBType = pbvalue_blob;
	template<> inline std::wstring Type<PBBlob>::GetPBName(std::wstring argument_name) { return L"blob" + argument_name; }
	template<> inline PBBlob Type<PBBlob>::FromArgument(IPB_Session* session, IPB_Value* argument) { return { session, argument->IsNull() ? 0 : argument->GetBlob() }; }
	template<> inline void Type<PBBlob>::SetValue(IPB_Session* session, IPB_Value* pb_value, const PBBlob value) { pb_value->SetBlob(value.m_Blob); }


	// Need to be classes because functions cant be partially specialized
	template <typename T, pblong... dims>
	struct Type<PBArray<T, dims...>>
	{
		static std::wstring PBSignature;
		static inline bool Assert(IPB_Session* session, IPB_Value* pb_value)
		{
			if (!pb_value->IsArray())
				return false;
			if (pb_value->IsNull())
				return true;

			PBArrayInfo* info = session->GetArrayInfo(pb_value->GetArray());

			bool is_correct;
			if constexpr (sizeof...(dims) == 0)
			{
				is_correct = info->arrayType == info->UnboundedArray && info->valueType == Type<T>::PBType;
			}
			else
			{
				uint8_t i = 0;
				is_correct = \
					info->arrayType == info->BoundedArray && \
					info->valueType == Type<T>::PBType && \
					info->numDimensions == sizeof...(dims) && \
					((info->bounds[i].upperBound - info->bounds[i++].lowerBound == dims - 1) && ...);
			}

			session->ReleaseArrayInfo(info);
			return is_correct;
		}
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
		static inline PBArray<T, dims...> FromArgument(IPB_Session* session, IPB_Value* argument) { return { session, argument->IsNull() ? 0 : argument->GetArray() }; }
		static inline void SetValue(IPB_Session* session, IPB_Value* pb_value, const PBArray<T, dims...> value) { pb_value->SetArray(value.m_Array); }
		static inline void Return(IPB_Session* session, PBCallInfo* ci, const PBArray<T, dims...> value) = delete;
	};
	template <typename T, pblong... dims>
	std::wstring Type<PBArray<T, dims...>>::PBSignature = std::wstring(1, Type<T>::PBSignature) + L"[]";

	template <Helper::FixedString cls_name, pbgroup_type group_type, pblong... dims>
	struct Type<PBArray<PBObject<cls_name, group_type>, dims...>>
	{
		static std::wstring PBSignature;
		static inline bool Assert(IPB_Session* session, IPB_Value* pb_value)
		{
			if (!pb_value->IsArray())
				return false;
			if (pb_value->IsNull())
				return true;

			PBArrayInfo* info = session->GetArrayInfo(pb_value->GetArray());

			bool is_correct;
			if constexpr (sizeof...(dims) == 0)
			{
				is_correct = info->arrayType == info->UnboundedArray && info->itemGroup != 0;
			}
			else
			{
				uint8_t i = 0;
				is_correct = \
					info->arrayType == info->BoundedArray && \
					info->itemGroup != 0 && \
					info->numDimensions == sizeof...(dims) && \
					((info->bounds[i].upperBound - info->bounds[i++].lowerBound == dims - 1) && ...);
			}

			session->ReleaseArrayInfo(info);
			return is_correct;
		}
		static inline std::wstring GetPBName(std::wstring argument_name)
		{
			if constexpr (sizeof...(dims) == 0)
			{
				return Type<PBObject<cls_name, group_type>>::GetPBName(argument_name) + L"[]";
			}
			else
			{
				std::wstring dimensions = ((std::to_wstring(dims) + L", ") + ...);
				dimensions.resize(dimensions.size() - 2);
				return Type<PBObject<cls_name, group_type>>::GetPBName(argument_name) + L"[" + dimensions + L"]";
			}
		}
		static inline PBArray<PBObject<cls_name, group_type>, dims...> FromArgument(IPB_Session* session, IPB_Value* argument) { return { session, argument->IsNull() ? 0 : argument->GetArray() }; }
		static inline void SetValue(IPB_Session* session, IPB_Value* pb_value, const PBArray<PBObject<cls_name, group_type>, dims...> value) { pb_value->SetArray(value.m_Array); }
		static inline void Return(IPB_Session* session, PBCallInfo* ci, const PBArray<PBObject<cls_name, group_type>, dims...> value) = delete;
	};
	template <Helper::FixedString cls_name, pbgroup_type group_type, pblong... dims>
	std::wstring Type<PBArray<PBObject<cls_name, group_type>, dims...>>::PBSignature = Type<PBObject<cls_name, group_type>>::PBSignature + L"[]";


	// User Object
	template <Helper::FixedString cls_name, pbgroup_type group_type>
	struct Type<PBObject<cls_name, group_type>>
	{
		static std::wstring PBSignature;
		static inline bool Assert(IPB_Session* session, IPB_Value* pb_value) { return pb_value->IsObject(); }
		static inline std::wstring GetPBName(std::wstring argument_name) { return std::wstring(cls_name.data) + argument_name; }
		static inline PBObject<cls_name, group_type> FromArgument(IPB_Session* session, IPB_Value* argument) { return { session, argument->IsNull() ? 0 : argument->GetObject() }; }
		static inline void SetValue(IPB_Session* session, IPB_Value* pb_value, const PBObject<cls_name, group_type> value) { pb_value->SetObject(value.m_Object); }
		static inline void Return(IPB_Session* session, PBCallInfo* ci, const PBObject<cls_name, group_type> value) { ci->returnClass = value.m_Class; SetValue(session, ci->returnValue, value); }
	};
	template <Helper::FixedString cls_name, pbgroup_type group_type>
	std::wstring Type<PBObject<cls_name, group_type>>::PBSignature = std::wstring(L"C") + PBObject<cls_name, group_type>::ClassName() + L".";
}