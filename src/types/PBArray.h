#pragma once

#include "../Strings.h"
#include "PBNumbers.h"
#include "PBDateTimes.h"
#include "PBString.h"
#include "PBBlob.h"


namespace Inf
{
	template <Helper::FixedString cls_name, pbgroup_type group_type>
	class PBObject;


	template <typename PBT, pblong... dims>
		requires (sizeof...(dims) <= 3 && !std::is_reference_v<PBT> && !std::is_pointer_v<PBT>)
	class PBArray
	{
	public:
		PBArray(IPB_Session* session)
			: m_Session(session)
		{
			if constexpr (sizeof...(dims) == 0)
			{
				m_Array = m_Session->NewUnboundedSimpleArray(Type<PBT>::PBType);
			}
			else
			{
				PBArrayInfo::ArrayBound bounds[] = { { 1, dims }... };
				m_Array = m_Session->NewBoundedSimpleArray(Type<PBT>::PBType, sizeof...(dims), bounds);
			}
		}

		PBArray(IPB_Session* session, pbarray arr)
			: m_Session(session), m_Array(arr)
		{
			if (!IsNull())
				m_ArrayInfo = std::shared_ptr<PBArrayInfo>(m_Session->GetArrayInfo(arr), [=](PBArrayInfo* info) { m_Session->ReleaseArrayInfo(info); });
		}

		// Unbounded arrays
		inline void Set(pblong pos, const PBT t)
			requires (sizeof...(dims) == 0)
		{
			AssertInside(pos, false);

			SetImpl<PBT>(&pos, t);
		}

		inline void SetItemToNull(pblong pos)
			requires (sizeof...(dims) == 0)
		{
			// No need to check upper bound
			AssertInside(pos, false);

			m_Session->SetArrayItemToNull(m_Array, &pos);
		}

		inline PBT Get(pblong pos)
			requires (sizeof...(dims) == 0)
		{
			AssertInside(pos);

			return GetImpl<PBT>(&pos);
		}


		// Bounded arrays
		inline void Set(std::array<pblong, sizeof...(dims)> pos, const PBT t)
			requires (sizeof...(dims) != 0)
		{
			AssertInside(pos);

			SetImpl<PBT>(pos.data(), t);
		}

		inline void SetItemToNull(std::array<pblong, sizeof...(dims)> pos)
			requires (sizeof...(dims) != 0)
		{
			AssertInside(pos);

			m_Session->SetArrayItemToNull(m_Array, pos.data());
		}

		inline PBT Get(std::array<pblong, sizeof...(dims)> pos)
			requires (sizeof...(dims) != 0)
		{
			AssertInside(pos);

			return GetImpl<PBT>(pos.data());
		}


		pblong Size()
		{
			return m_Session->GetArrayLength(m_Array);
		}

		std::array<std::array<pblong, 2>, sizeof...(dims)>  Bounds() const
			requires (sizeof...(dims) != 0)
		{
			std::array<std::array<pblong, 2>, sizeof...(dims)> bounds;

			for (uint8_t i = 0; i < sizeof...(dims); i++)
				bounds[i] = { m_ArrayInfo->bounds[i].lowerBound, m_ArrayInfo->bounds[i].upperBound };

			return bounds;
		}

		bool IsNull() const
		{
			return !m_Array;
		}

		void SetToNull()
		{
			m_Array = 0;
		}
	private:
		friend class Type<PBArray>;

		IPB_Session* m_Session;
		pbarray m_Array;
		std::shared_ptr<PBArrayInfo> m_ArrayInfo;


		void AssertInside(std::array<pblong, sizeof...(dims)> pos)
			requires (sizeof...(dims) != 0)
		{
			if (IsNull())
				throw Inf::u_exf_pbni(L"Tried to access a field in a bounded " + Type<PBT>::GetPBName(L" array of value Null"));

			for (uint8_t i = 0; i < sizeof...(dims); i++)
			{
				if (m_ArrayInfo->bounds[i].lowerBound > pos[i] || pos[i] > m_ArrayInfo->bounds[i].upperBound)
					throw Inf::u_exf_pbni(L"Accesssing an index out of bounds in a bounded " + Type<PBT>::GetPBName(L" array (") + std::to_wstring(pos[i]) + L" != [" + std::to_wstring(m_ArrayInfo->bounds[i].lowerBound) + L" to " + std::to_wstring(m_ArrayInfo->bounds[i].upperBound) + L"] for dimension " + std::to_wstring(i) + L")");
			}
		}

		void AssertInside(pblong pos, bool check_upper_bound = true)
			requires (sizeof...(dims) == 0)
		{
			if (IsNull())
				throw Inf::u_exf_pbni(L"Tried to access a field in an unbounded " + Type<PBT>::GetPBName(L" array of value Null"));

			if (1 > pos || (check_upper_bound && pos < Size()))
				throw Inf::u_exf_pbni(L"Accesssing an out of bounds in an unbounded " + Type<PBT>::GetPBName(L" array (") + std::to_wstring(pos) + L" >= " + std::to_wstring(Size()) + L")");
		}


		template <typename T>
		inline void SetImpl(pblong* dim, const T t) = delete;
		template <typename T>
		inline T GetImpl(pblong* dim) const = delete;

		// Array template definitinos
		template<> inline void SetImpl<PBByte>		(pblong* dim, const PBByte t)		{ if (t.IsNull()) m_Session->SetArrayItemToNull(m_Array, dim); else m_Session->SetByteArrayItem(m_Array, dim, t); }
		template<> inline void SetImpl<PBBoolean>	(pblong* dim, const PBBoolean t)	{ if (t.IsNull()) m_Session->SetArrayItemToNull(m_Array, dim); else m_Session->SetCharArrayItem(m_Array, dim, t); }
		template<> inline void SetImpl<PBChar>		(pblong* dim, const PBChar t)		{ if (t.IsNull()) m_Session->SetArrayItemToNull(m_Array, dim); else m_Session->SetCharArrayItem(m_Array, dim, t); }
		template<> inline void SetImpl<PBInt>		(pblong* dim, const PBInt t)		{ if (t.IsNull()) m_Session->SetArrayItemToNull(m_Array, dim); else m_Session->SetIntArrayItem(m_Array, dim, t); }
		template<> inline void SetImpl<PBUint>		(pblong* dim, const PBUint t)		{ if (t.IsNull()) m_Session->SetArrayItemToNull(m_Array, dim); else m_Session->SetUintArrayItem(m_Array, dim, t); }
		template<> inline void SetImpl<PBLong>		(pblong* dim, const PBLong t)		{ if (t.IsNull()) m_Session->SetArrayItemToNull(m_Array, dim); else m_Session->SetLongArrayItem(m_Array, dim, t); }
		template<> inline void SetImpl<PBUlong>		(pblong* dim, const PBUlong t)		{ if (t.IsNull()) m_Session->SetArrayItemToNull(m_Array, dim); else m_Session->SetUlongArrayItem(m_Array, dim, t); }
		template<> inline void SetImpl<PBLongLong>	(pblong* dim, const PBLongLong t)	{ if (t.IsNull()) m_Session->SetArrayItemToNull(m_Array, dim); else m_Session->SetLongLongArrayItem(m_Array, dim, t); }
		template<> inline void SetImpl<PBReal>		(pblong* dim, const PBReal t)		{ if (t.IsNull()) m_Session->SetArrayItemToNull(m_Array, dim); else m_Session->SetRealArrayItem(m_Array, dim, t); }
		template<> inline void SetImpl<PBDouble>	(pblong* dim, const PBDouble t)		{ if (t.IsNull()) m_Session->SetArrayItemToNull(m_Array, dim); else m_Session->SetDoubleArrayItem(m_Array, dim, t); }
		template<> inline void SetImpl<PBDecimal>	(pblong* dim, const PBDecimal t)
		{
			if (t.IsNull())
			{
				m_Session->SetArrayItemToNull(m_Array, dim);
			}
			else
			{
				std::wstring dec_repr = ConvertString<std::wstring>(t.t.str());

				pbdec pb_dec = m_Session->NewDecimal();
				m_Session->SetDecimal(pb_dec, dec_repr.c_str());

				m_Session->SetDecArrayItem(m_Array, dim, pb_dec);
			}
		}
		template<> inline void SetImpl<PBTime>		(pblong* dim, const PBTime t)		{ if (t.IsNull()) m_Session->SetArrayItemToNull(m_Array, dim); else m_Session->SetTimeArrayItem(m_Array, dim, t.m_Time); }
		template<> inline void SetImpl<PBDate>		(pblong* dim, const PBDate t)		{ if (t.IsNull()) m_Session->SetArrayItemToNull(m_Array, dim); else m_Session->SetDateArrayItem(m_Array, dim, t.m_Date); }
		template<> inline void SetImpl<PBDateTime>	(pblong* dim, const PBDateTime t)	{ if (t.IsNull()) m_Session->SetArrayItemToNull(m_Array, dim); else m_Session->SetDateTimeArrayItem(m_Array, dim, t.m_DateTime); }
		template<> inline void SetImpl<PBString>	(pblong* dim, const PBString t)		{ if (t.IsNull()) m_Session->SetArrayItemToNull(m_Array, dim); else m_Session->SetPBStringArrayItem(m_Array, dim, t.m_String); }
		template<> inline void SetImpl<PBBlob>		(pblong* dim, const PBBlob t)		{ if (t.IsNull()) m_Session->SetArrayItemToNull(m_Array, dim); else m_Session->SetBlobArrayItem(m_Array, dim, t.m_Blob); }

		template<> inline PBByte		GetImpl<PBByte>		(pblong* dim) const	{ pbboolean is_null = false; pbbyte pb_byte			= m_Session->GetByteArrayItem(m_Array, dim, is_null);		return is_null ? PBByte() : PBByte(pb_byte); }
		template<> inline PBBoolean		GetImpl<PBBoolean>	(pblong* dim) const	{ pbboolean is_null = false; pbboolean pb_boolean	= m_Session->GetCharArrayItem(m_Array, dim, is_null);		return is_null ? PBBoolean() : PBBoolean(pb_boolean); }
		template<> inline PBChar		GetImpl<PBChar>		(pblong* dim) const	{ pbboolean is_null = false; pbchar pb_char			= m_Session->GetCharArrayItem(m_Array, dim, is_null);		return is_null ? PBChar() : PBChar(pb_char); }
		template<> inline PBInt			GetImpl<PBInt>		(pblong* dim) const	{ pbboolean is_null = false; pbint pb_int			= m_Session->GetIntArrayItem(m_Array, dim, is_null);		return is_null ? PBInt() : PBInt(pb_int); }
		template<> inline PBUint		GetImpl<PBUint>		(pblong* dim) const	{ pbboolean is_null = false; pbuint pb_uint			= m_Session->GetUintArrayItem(m_Array, dim, is_null);		return is_null ? PBUint() : PBUint(pb_uint); }
		template<> inline PBLong		GetImpl<PBLong>		(pblong* dim) const	{ pbboolean is_null = false; pblong pb_long			= m_Session->GetLongArrayItem(m_Array, dim, is_null);		return is_null ? PBLong() : PBLong(pb_long); }
		template<> inline PBUlong		GetImpl<PBUlong>	(pblong* dim) const	{ pbboolean is_null = false; pbulong pb_ulong		= m_Session->GetUlongArrayItem(m_Array, dim, is_null);		return is_null ? PBUlong() : PBUlong(pb_ulong); }
		template<> inline PBLongLong	GetImpl<PBLongLong>	(pblong* dim) const	{ pbboolean is_null = false; pblonglong pb_longlong	= m_Session->GetLongLongArrayItem(m_Array, dim, is_null);	return is_null ? PBLongLong() : PBLongLong(pb_longlong); }
		template<> inline PBReal		GetImpl<PBReal>		(pblong* dim) const	{ pbboolean is_null = false; pbreal pb_real			= m_Session->GetRealArrayItem(m_Array, dim, is_null);		return is_null ? PBReal() : PBReal(pb_real); }
		template<> inline PBDouble		GetImpl<PBDouble>	(pblong* dim) const	{ pbboolean is_null = false; pbdouble pb_double		= m_Session->GetDoubleArrayItem(m_Array, dim, is_null);		return is_null ? PBDouble() : PBDouble(pb_double); }
		template<> inline PBDecimal		GetImpl<PBDecimal>	(pblong* dim) const
		{
			pbboolean is_null = false;

			LPCTSTR dec_repr = m_Session->GetDecimalString(m_Session->GetDecArrayItem(m_Array, dim, is_null));

			PBDecimal dec;
			if (!is_null)
				dec = Helper::PBDecimalImpl(ConvertString<std::string>(dec_repr));

			m_Session->ReleaseDecimalString(dec_repr);

			return dec;
		}
		template<> inline PBTime		GetImpl<PBTime>		(pblong* dim) const	{ pbboolean is_null = false; pbtime pb_time			= m_Session->GetTimeArrayItem(m_Array, dim, is_null);		return { m_Session, is_null ? 0 : pb_time }; }
		template<> inline PBDate		GetImpl<PBDate>		(pblong* dim) const	{ pbboolean is_null = false; pbdate pb_date			= m_Session->GetDateArrayItem(m_Array, dim, is_null);		return { m_Session, is_null ? 0 : pb_date }; }
		template<> inline PBDateTime	GetImpl<PBDateTime>	(pblong* dim) const	{ pbboolean is_null = false; pbdatetime pb_datetime	= m_Session->GetDateTimeArrayItem(m_Array, dim, is_null);	return { m_Session, is_null ? 0 : pb_datetime }; }
		template<> inline PBString		GetImpl<PBString>	(pblong* dim) const	{ pbboolean is_null = false; pbstring pb_string		= m_Session->GetStringArrayItem(m_Array, dim, is_null);		return { m_Session, is_null ? 0 : pb_string }; }
		template<> inline PBBlob		GetImpl<PBBlob>		(pblong* dim) const	{ pbboolean is_null = false; pbblob pb_blob			= m_Session->GetBlobArrayItem(m_Array, dim, is_null);		return { m_Session, is_null ? 0 : pb_blob }; }
};

	template <Helper::FixedString cls_name, pbgroup_type group_type, pblong... dims>
	class PBArray<PBObject<cls_name, group_type>, dims...>
	{
	public:
		PBArray(IPB_Session* session)
			: m_Session(session)
		{
			auto [group, cls] = PBObject<cls_name, group_type>::ExtractPBGroupClass(m_Session);

			if constexpr (sizeof...(dims) == 0)
			{
				m_Array = m_Session->NewUnboundedObjectArray(cls);
			}
			else
			{
				PBArrayInfo::ArrayBound bounds[] = { { 1, dims }... };
				m_Array = m_Session->NewBoundedObjectArray(cls, sizeof...(dims), bounds);
			}
		}

		PBArray(IPB_Session* session, pbarray arr)
			: m_Session(session), m_Array(arr)
		{
			if (!IsNull())
				m_ArrayInfo = std::shared_ptr<PBArrayInfo>(m_Session->GetArrayInfo(arr), [=](PBArrayInfo* info) { m_Session->ReleaseArrayInfo(info); });
		}

		// Unbounded arrays
		inline void Set(pblong pos, const PBObject<cls_name, group_type>& t)
			requires (sizeof...(dims) == 0)
		{
			// No need to check upper bound
			AssertInside(pos, false);

			m_Session->SetObjectArrayItem(m_Array, &pos, t.m_Object);
		}

		inline void SetItemToNull(pblong pos)
			requires (sizeof...(dims) == 0)
		{
			// No need to check upper bound
			AssertInside(pos, false);

			m_Session->SetArrayItemToNull(m_Array, &pos);
		}

		inline PBObject<cls_name, group_type> Get(pblong pos)
			requires (sizeof...(dims) == 0)
		{
			AssertInside(pos);

			pbboolean is_null;
			pbobject obj = m_Session->GetObjectArrayItem(m_Array, &pos, is_null);
			return { m_Session, is_null ? 0 : obj };
		}


		// Bounded arrays
		inline void Set(std::array<pblong, sizeof...(dims)> pos, const PBObject<cls_name, group_type>& t)
			requires (sizeof...(dims) != 0)
		{
			AssertInside(pos);

			m_Session->SetObjectArrayItem(m_Array, pos.data(), t.m_Object);
		}

		void SetItemToNull(std::array<pblong, sizeof...(dims)> pos)
			requires (sizeof...(dims) != 0)
		{
			AssertInside(pos);

			m_Session->SetArrayItemToNull(m_Array, pos.data());
		}

		inline PBObject<cls_name, group_type> Get(std::array<pblong, sizeof...(dims)> pos)
			requires (sizeof...(dims) != 0)
		{
			AssertInside(pos);

			return m_Session->GetObjectArrayItem(m_Array, pos.data());
		}


		PBNI_Class GetClass() const
		{
			return m_Session->FindClass(m_ArrayInfo->itemGroup, cls_name.data);
		}

		pblong Size() const
		{
			return m_Session->GetArrayLength(m_Array);
		}

		std::array<std::array<pblong, 2>, sizeof...(dims)>  Bounds() const
			requires (sizeof...(dims) != 0)
		{
			std::array<std::array<pblong, 2>, sizeof...(dims)> bounds;

			for (uint8_t i = 0; i < sizeof...(dims); i++)
				bounds[i] = { m_ArrayInfo->bounds[i].lowerBound, m_ArrayInfo->bounds[i].upperBound };

			return bounds;
		}

		bool IsNull() const
		{
			return !m_Array;
		}

		void SetToNull()
		{
			m_Array = 0;
		}
	private:
		friend class Type<PBArray>;

		IPB_Session* m_Session;
		pbarray m_Array;
		std::shared_ptr<PBArrayInfo> m_ArrayInfo;

		void AssertInside(std::array<pblong, sizeof...(dims)> pos)
			requires (sizeof...(dims) != 0)
		{
			if (IsNull())
				throw Inf::u_exf_pbni(L"Tried to access a field in a bounded object array of value Null");

			for (uint8_t i = 0; i < sizeof...(dims); i++)
			{
				if (m_ArrayInfo->bounds[i].lowerBound > pos[i] || pos[i] > m_ArrayInfo->bounds[i].upperBound)
					throw Inf::u_exf_pbni(std::wstring(L"Accesssing an index out of bounds in a bounded object array (") + std::to_wstring(pos[i]) + L"!= [" + std::to_wstring(m_ArrayInfo->bounds[i].lowerBound) + L" to " + std::to_wstring(m_ArrayInfo->bounds[i].upperBound) + L"] for dimension " + std::to_wstring(i) + L")");
			}
		}

		void AssertInside(pblong pos, bool check_upper_bound = true)
			requires (sizeof...(dims) == 0)
		{
			if (IsNull())
				throw Inf::u_exf_pbni(L"Tried to access a field in an unbounded object array of value Null");

			if (1 > pos || (check_upper_bound && pos > Size()))
				throw Inf::u_exf_pbni(L"Accesssing an out of bounds in an unbounded object array (" + std::to_wstring(pos) + L" >= " + std::to_wstring(Size()) + L")");
		}
	};

}
