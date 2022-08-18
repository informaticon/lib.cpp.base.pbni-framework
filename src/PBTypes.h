#pragma once

#include <windows.h>

#include "PBObjects.h"


namespace Inf
{
	/**
	 * This is the Genereic Type struct, each PBType implements the Fields it needs.
	 * You can Access any one of the Functions using e.g. Type<T>::PBSignature.
	 */
	template <typename T>
	struct Type {
		// This Field is used to build a Method Signature, if you want to invoke a PowerBuilder Function from C++.
		static constexpr wchar_t PBSignature = L' ';
		// This Field is used to check for correct IPB_Value Types.
		static constexpr pbvalue_type PBType = pbvalue_notype;

		/**
		 * This Function returns whether the IPB_Value can be used to retrieve the specified type.
		 *
		 * \param session	Current Session
		 * \param pb_value	The Value to check
		 * \return			true if its okay to convert, false otherwise.
		 */
		static inline bool Assert(IPB_Session* session, IPB_Value* pb_value) { return pb_value->GetType() == PBType; };

		/**
		 * This Function is used to generate the Description of a Method, it needs to take in the name of the argument so we can add [] at the end of arrays.
		 * This wont add any spaces between the type and argument_name.
		 *
		 * \param argument_name		The name to put between type and []
		 * \return					The combined string
		 */
		static inline std::wstring GetPBName(std::wstring argument_name) = delete;

		/**
		 * This Function Retrieves the specified Type from an IPB_Value.
		 *
		 * \param session	Current Session
		 * \param pb_value	The value to get retrieve the Type from
		 * \param acquire	Whether or not to take ownership of the type, only relevant for complex types. The Type will free itself
		 * \return			The returned Type
		 */
		static inline T FromArgument(IPB_Session* session, IPB_Value* pb_value, bool acquire) = delete;

		/**
		 * This sets a value to a specified Type.
		 *
		 * \param session	Current Session
		 * \param pb_value	Value to set
		 * \param t			Type to set Value to
		 */
		static inline PBXRESULT SetValue(IPB_Session* session, IPB_Value* pb_value, const T& t) = delete;

		/**
		 * Basically the same as SetValue.
		 * Currently only used so that PBArray can delete this function.
		 *
		 * \param session	Current Session
		 * \param ci		The Callback info to set the returnValue of
		 * \param t			Type to set returnValue to
		 */
		static inline PBXRESULT Return(IPB_Session* session, PBCallInfo* ci, const T& t) { return SetValue(session, ci->returnValue, t); }
	};

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
#pragma region Bytelike
	template<> constexpr wchar_t Type<PBByte>::PBSignature = L'E';
	template<> constexpr pbvalue_type Type<PBByte>::PBType = pbvalue_byte;
	template<> inline std::wstring Type<PBByte>::GetPBName(std::wstring argument_name) { return L"byte" + argument_name; }
	template<> inline PBByte Type<PBByte>::FromArgument(IPB_Session* session, IPB_Value* pb_value, bool acquire) { return pb_value->IsNull() ? PBByte() : PBByte(pb_value->GetByte()); }
	template<> inline PBXRESULT Type<PBByte>::SetValue(IPB_Session* session, IPB_Value* pb_value, const PBByte& value) { return value.IsNull() ? pb_value->SetToNull() : pb_value->SetByte(value); }

	template<> constexpr wchar_t Type<PBBoolean>::PBSignature = L'B';
	template<> constexpr pbvalue_type Type<PBBoolean>::PBType = pbvalue_boolean;
	template<> inline std::wstring Type<PBBoolean>::GetPBName(std::wstring argument_name) { return L"boolean" + argument_name; }
	template<> inline PBBoolean Type<PBBoolean>::FromArgument(IPB_Session* session, IPB_Value* pb_value, bool acquire) { return pb_value->IsNull() ? PBBoolean() : PBBoolean(pb_value->GetBool()); }
	template<> inline PBXRESULT Type<PBBoolean>::SetValue(IPB_Session* session, IPB_Value* pb_value, const PBBoolean& value) { return value.IsNull() ? pb_value->SetToNull() : pb_value->SetBool(value); }

	template<> constexpr wchar_t Type<PBChar>::PBSignature = L'H';
	template<> constexpr pbvalue_type Type<PBChar>::PBType = pbvalue_char;
	template<> inline std::wstring Type<PBChar>::GetPBName(std::wstring argument_name) { return L"char" + argument_name; }
	template<> inline PBChar Type<PBChar>::FromArgument(IPB_Session* session, IPB_Value* pb_value, bool acquire) { return pb_value->IsNull() ? PBChar() : PBChar(pb_value->GetChar()); }
	template<> inline PBXRESULT Type<PBChar>::SetValue(IPB_Session* session, IPB_Value* pb_value, const PBChar& value) { return value.IsNull() ? pb_value->SetToNull() : pb_value->SetChar(value); }
#pragma endregion

#pragma region Integer_Numbers
	template<> constexpr wchar_t Type<PBInt>::PBSignature = L'I';
	template<> constexpr pbvalue_type Type<PBInt>::PBType = pbvalue_int;
	template<> inline std::wstring Type<PBInt>::GetPBName(std::wstring argument_name) { return L"int" + argument_name; }
	template<> inline PBInt Type<PBInt>::FromArgument(IPB_Session* session, IPB_Value* pb_value, bool acquire) { return pb_value->IsNull() ? PBInt() : PBInt(pb_value->GetInt()); }
	template<> inline PBXRESULT Type<PBInt>::SetValue(IPB_Session* session, IPB_Value* pb_value, const PBInt& value) { return value.IsNull() ? pb_value->SetToNull() : pb_value->SetInt(value); }

	template<> constexpr wchar_t Type<PBUint>::PBSignature = L'N';
	template<> constexpr pbvalue_type Type<PBUint>::PBType = pbvalue_uint;
	template<> inline std::wstring Type<PBUint>::GetPBName(std::wstring argument_name) { return L"uint" + argument_name; }
	template<> inline PBUint Type<PBUint>::FromArgument(IPB_Session* session, IPB_Value* pb_value, bool acquire) { return pb_value->IsNull() ? PBUint() : PBUint(pb_value->GetUint()); }
	template<> inline PBXRESULT Type<PBUint>::SetValue(IPB_Session* session, IPB_Value* pb_value, const PBUint& value) { return value.IsNull() ? pb_value->SetToNull() : pb_value->SetUint(value); }

	template<> constexpr wchar_t Type<PBLong>::PBSignature = L'L';
	template<> constexpr pbvalue_type Type<PBLong>::PBType = pbvalue_long;
	template<> inline std::wstring Type<PBLong>::GetPBName(std::wstring argument_name) { return L"long" + argument_name; }
	template<> inline PBLong Type<PBLong>::FromArgument(IPB_Session* session, IPB_Value* pb_value, bool acquire) { return pb_value->IsNull() ? PBLong() : PBLong(pb_value->GetLong()); }
	template<> inline PBXRESULT Type<PBLong>::SetValue(IPB_Session* session, IPB_Value* pb_value, const PBLong& value) { return value.IsNull() ? pb_value->SetToNull() : pb_value->SetLong(value); }

	template<> constexpr wchar_t Type<PBUlong>::PBSignature = L'U';
	template<> constexpr pbvalue_type Type<PBUlong>::PBType = pbvalue_ulong;
	template<> inline std::wstring Type<PBUlong>::GetPBName(std::wstring argument_name) { return L"ulong" + argument_name; }
	template<> inline PBUlong Type<PBUlong>::FromArgument(IPB_Session* session, IPB_Value* pb_value, bool acquire) { return pb_value->IsNull() ? PBUlong() : PBUlong(pb_value->GetUlong()); }
	template<> inline PBXRESULT Type<PBUlong>::SetValue(IPB_Session* session, IPB_Value* pb_value, const PBUlong& value) { return value.IsNull() ? pb_value->SetToNull() : pb_value->SetUlong(value); }

	template<> constexpr wchar_t Type<PBLongLong>::PBSignature = L'K';
	template<> constexpr pbvalue_type Type<PBLongLong>::PBType = pbvalue_longlong;
	template<> inline std::wstring Type<PBLongLong>::GetPBName(std::wstring argument_name) { return L"longlong" + argument_name; }
	template<> inline PBLongLong Type<PBLongLong>::FromArgument(IPB_Session* session, IPB_Value* pb_value, bool acquire) { return pb_value->IsNull() ? PBLongLong() : PBLongLong(pb_value->GetLongLong()); }
	template<> inline PBXRESULT Type<PBLongLong>::SetValue(IPB_Session* session, IPB_Value* pb_value, const PBLongLong& value) { return value.IsNull() ? pb_value->SetToNull() : pb_value->SetLongLong(value); }
#pragma endregion

#pragma region Floating_Point_Numbers
	template<> constexpr wchar_t Type<PBReal>::PBSignature = L'F';
	template<> constexpr pbvalue_type Type<PBReal>::PBType = pbvalue_real;
	template<> inline std::wstring Type<PBReal>::GetPBName(std::wstring argument_name) { return L"real" + argument_name; }
	template<> inline PBReal Type<PBReal>::FromArgument(IPB_Session* session, IPB_Value* pb_value, bool acquire) { return pb_value->IsNull() ? PBReal() : PBReal(pb_value->GetReal()); }
	template<> inline PBXRESULT Type<PBReal>::SetValue(IPB_Session* session, IPB_Value* pb_value, const PBReal& value) { return value.IsNull() ? pb_value->SetToNull() : pb_value->SetReal(value); }

	template<> constexpr wchar_t Type<PBDouble>::PBSignature = L'D';
	template<> constexpr pbvalue_type Type<PBDouble>::PBType = pbvalue_double;
	template<> inline std::wstring Type<PBDouble>::GetPBName(std::wstring argument_name) { return L"double" + argument_name; }
	template<> inline PBDouble Type<PBDouble>::FromArgument(IPB_Session* session, IPB_Value* pb_value, bool acquire) { return pb_value->IsNull() ? PBDouble() : PBDouble(pb_value->GetDouble()); }
	template<> inline PBXRESULT Type<PBDouble>::SetValue(IPB_Session* session, IPB_Value* pb_value, const PBDouble& value) { return value.IsNull() ? pb_value->SetToNull() : pb_value->SetDouble(value); }

	template<> constexpr wchar_t Type<PBDecimal>::PBSignature = L'M';
	template<> constexpr pbvalue_type Type<PBDecimal>::PBType = pbvalue_dec;
	template<> inline std::wstring Type<PBDecimal>::GetPBName(std::wstring argument_name) { return L"dec" + argument_name; }
	template<> inline PBDecimal Type<PBDecimal>::FromArgument(IPB_Session* session, IPB_Value* pb_value, bool acquire) { return { session, pb_value, acquire }; }
	template<> inline PBXRESULT Type<PBDecimal>::SetValue(IPB_Session* session, IPB_Value* pb_value, const PBDecimal& value) { return value.IsNull() ? pb_value->SetToNull() : pb_value->SetDecimal(value.m_Decimal); }
#pragma endregion

#pragma region Date_Times
	template<> constexpr wchar_t Type<PBTime>::PBSignature = L'T';
	template<> constexpr pbvalue_type Type<PBTime>::PBType = pbvalue_time;
	template<> inline std::wstring Type<PBTime>::GetPBName(std::wstring argument_name) { return L"time" + argument_name; }
	template<> inline PBTime Type<PBTime>::FromArgument(IPB_Session* session, IPB_Value* pb_value, bool acquire) { return { session, pb_value, acquire }; }
	template<> inline PBXRESULT Type<PBTime>::SetValue(IPB_Session* session, IPB_Value* pb_value, const PBTime& value) { return value.IsNull() ? pb_value->SetToNull() : pb_value->SetTime(value.m_Time); }

	template<> constexpr wchar_t Type<PBDate>::PBSignature = L'Y';
	template<> constexpr pbvalue_type Type<PBDate>::PBType = pbvalue_date;
	template<> inline std::wstring Type<PBDate>::GetPBName(std::wstring argument_name) { return L"date" + argument_name; }
	template<> inline PBDate Type<PBDate>::FromArgument(IPB_Session* session, IPB_Value* pb_value, bool acquire) { return { session, pb_value, acquire }; }
	template<> inline PBXRESULT Type<PBDate>::SetValue(IPB_Session* session, IPB_Value* pb_value, const PBDate& value) { return value.IsNull() ? pb_value->SetToNull() : pb_value->SetDate(value.m_Date); }

	template<> constexpr wchar_t Type<PBDateTime>::PBSignature = L'W';
	template<> constexpr pbvalue_type Type<PBDateTime>::PBType = pbvalue_datetime;
	template<> inline std::wstring Type<PBDateTime>::GetPBName(std::wstring argument_name) { return L"datetime" + argument_name; }
	template<> inline PBDateTime Type<PBDateTime>::FromArgument(IPB_Session* session, IPB_Value* pb_value, bool acquire) { return { session, pb_value, acquire }; }
	template<> inline PBXRESULT Type<PBDateTime>::SetValue(IPB_Session* session, IPB_Value* pb_value, const PBDateTime& value) { return value.IsNull() ? pb_value->SetToNull() : pb_value->SetDateTime(value.m_DateTime); }
#pragma endregion

#pragma region Variable_Sized
	template<> constexpr wchar_t Type<PBString>::PBSignature = L'S';
	template<> constexpr pbvalue_type Type<PBString>::PBType = pbvalue_string;
	template<> inline std::wstring Type<PBString>::GetPBName(std::wstring argument_name) { return L"string" + argument_name; }
	template<> inline PBString Type<PBString>::FromArgument(IPB_Session* session, IPB_Value* pb_value, bool acquire) { return { session, pb_value, acquire }; }
	template<> inline PBXRESULT Type<PBString>::SetValue(IPB_Session* session, IPB_Value* pb_value, const PBString& value) { return value.IsNull() ? pb_value->SetToNull() : pb_value->SetPBString(value.m_String); }

	template<> constexpr wchar_t Type<PBBlob>::PBSignature = L'O';
	template<> constexpr pbvalue_type Type<PBBlob>::PBType = pbvalue_blob;
	template<> inline std::wstring Type<PBBlob>::GetPBName(std::wstring argument_name) { return L"blob" + argument_name; }
	template<> inline PBBlob Type<PBBlob>::FromArgument(IPB_Session* session, IPB_Value* pb_value, bool acquire) { return { session, pb_value, acquire }; }
	template<> inline PBXRESULT Type<PBBlob>::SetValue(IPB_Session* session, IPB_Value* pb_value, const PBBlob& value) { return value.IsNull() ? pb_value->SetToNull() : pb_value->SetBlob(value.m_Blob); }

	/**
	 * For Types that have their own template types (PBObject<>, PBArray<>) we cant partially specialize the static Functions.
	 * Instead we have to create our own Struct, which can be partially specialized
	 */
	template <typename T, pblong... dims>
	struct Type<PBArray<T, dims...>> // <- Partial specialization
	{
		static inline std::wstring PBSignature = std::wstring(1, Type<T>::PBSignature) + L"[]";
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
		static inline PBArray<T, dims...> FromArgument(IPB_Session* session, IPB_Value* pb_value, bool acquire) { return { session, pb_value, acquire }; }
		static inline PBXRESULT SetValue(IPB_Session* session, IPB_Value* pb_value, const PBArray<T, dims...>& value) { return value.IsNull() ? pb_value->SetToNull() : pb_value->SetArray(value.m_Array); }
	};

	template <Helper::FixedString class_id, pbgroup_type group_type, pblong... dims>
	struct Type<PBArray<PBObject<class_id, group_type>, dims...>>
	{
		static inline std::wstring PBSignature = Type<PBObject<class_id, group_type>>::PBSignature + L"[]";
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
				return Type<PBObject<class_id, group_type>>::GetPBName(argument_name) + L"[]";
			}
			else
			{
				std::wstring dimensions = ((std::to_wstring(dims) + L", ") + ...);
				dimensions.resize(dimensions.size() - 2);
				return Type<PBObject<class_id, group_type>>::GetPBName(argument_name) + L"[" + dimensions + L"]";
			}
		}
		static inline PBArray<PBObject<class_id, group_type>, dims...> FromArgument(IPB_Session* session, IPB_Value* pb_value, bool acquire) { return { session, pb_value, acquire }; }
		static inline PBXRESULT SetValue(IPB_Session* session, IPB_Value* pb_value, const PBArray<PBObject<class_id, group_type>, dims...>& value) { return value.IsNull() ? pb_value->SetToNull() : pb_value->SetArray(value.m_Array); }
	};


	template <Helper::FixedString class_id, pbgroup_type group_type>
	struct Type<PBObject<class_id, group_type>>
	{
		static inline std::wstring PBSignature = std::wstring(L"C") + PBObject<class_id, group_type>::ClassName() + L".";
		static inline bool Assert(IPB_Session* session, IPB_Value* pb_value) { return pb_value->IsObject(); }
		static inline std::wstring GetPBName(std::wstring argument_name) { return std::wstring(class_id.data) + argument_name; }
		static inline PBObject<class_id, group_type> FromArgument(IPB_Session* session, IPB_Value* pb_value, bool acquire) { return { session, pb_value->IsNull() ? 0 : pb_value->GetObject() }; }
		static inline PBXRESULT SetValue(IPB_Session* session, IPB_Value* pb_value, const PBObject<class_id, group_type>& value) { return value.IsNull() ? pb_value->SetToNull() : pb_value->SetObject(value.m_Object); }
		static inline PBXRESULT Return(IPB_Session* session, PBCallInfo* ci, const PBObject<class_id, group_type>& value) { return SetValue(session, ci->returnValue, value); }
	};
#pragma endregion
}