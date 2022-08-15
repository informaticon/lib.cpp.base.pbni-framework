#pragma once

#include "PBNumbers.h"
#include "PBDateTimes.h"
#include "PBString.h"
#include "PBBlob.h"


namespace Inf
{
	template <Helper::FixedString class_id, pbgroup_type group_type>
	class PBObject;

	/**
	 * Wrapper for simple Arrays.
	 * 
	 * \tparam PBT Type of the Array Items
	 * \tparam dims... The Bounds of the Bounded Array, Unbounded Array if empty
	 */
	template <typename PBT, pblong... dims>
		requires (sizeof...(dims) <= 3 && !std::is_reference_v<PBT> && !std::is_pointer_v<PBT>)
	class PBArray
	{
	public:
		/**
		 * Creates a Wrapper to an existing pbarray.
		 * Null if arr is 0
		 * 
		 * \param session	Current session
		 * \param arr		pbarray or 0
		 */
		PBArray(IPB_Session* session, pbarray arr)
			: m_Session(session), m_Array(arr)
		{
			if (!IsNull())
				m_ArrayInfo = std::shared_ptr<PBArrayInfo>(m_Session->GetArrayInfo(m_Array), [=](PBArrayInfo* info) { m_Session->ReleaseArrayInfo(info); });
		}
		
		/**
		 * Creates a new Bounded or Unbounded Array.
		 * 
		 * \param session	Current Session
		 */
		PBArray(IPB_Session* session)
			: m_Session(session)
		{
			if constexpr (sizeof...(dims) == 0)
			{
				m_Array = m_Session->NewUnboundedSimpleArray(Type<PBT>::PBType);
			}
			else
			{
				PBArrayInfo::ArrayBound bounds[] = { { dims, 1 }... };
				m_Array = m_Session->NewBoundedSimpleArray(Type<PBT>::PBType, sizeof...(dims), bounds);
			}

			m_ArrayInfo = std::shared_ptr<PBArrayInfo>(m_Session->GetArrayInfo(m_Array), [=](PBArrayInfo* info) { m_Session->ReleaseArrayInfo(info); });
		}


	#pragma region UnboundedSimpleArray_Functions
		/**
		 * Sets an Item in an Unbounded Array.
		 * Copies if PBT is string or blob.
		 * 
		 * \param pos	The Position
		 * \param t		The Value to set from
		 */
		void Set(pblong pos, const PBT t)
			requires (sizeof...(dims) == 0)
		{
			AssertInside(pos, false);

			if (t.IsNull())
			{
				m_Session->SetArrayItemToNull(m_Array, &pos);
			}
			else
			{
				PBXRESULT res = SetImpl<PBT>(&pos, t);

				if (res != PBX_OK)
				{
					throw Inf::PBNI_Exception({
						{ L"Error", L"Failed to set an Item in an Unbounded Array"},
						{ L"Position", std::to_wstring(pos)},
						{ L"Result", std::to_wstring(res)}
					});
				}
			}
		}

		/**
		 * Sets an Item in an Unbounded Array To Null.
		 *
		 * \param pos	The Position
		 */
		void SetItemToNull(pblong pos)
			requires (sizeof...(dims) == 0)
		{
			// No need to check upper bound
			AssertInside(pos, false);

			m_Session->SetArrayItemToNull(m_Array, &pos);
		}

		/**
		 * Retrieves an Item in an Unbounded Array.
		 * If PBT is complex, it will return a reference.
		 * 
		 * \param pos	The Position
		 * \return		The Value
		 */
		PBT Get(pblong pos)
			requires (sizeof...(dims) == 0)
		{
			AssertInside(pos);

			return GetImpl<PBT>(&pos);
		}

		/**
		 * Checks wheter an Item in an Unbounded Array is Null.
		 * 
		 * \param pos	The Position
		 * \return		Is Null
		 */
		bool IsItemNull(pblong pos)
			requires (sizeof...(dims) == 0)
		{
			// No need to check upper bound
			AssertInside(pos, false);

			return m_Session->IsArrayItemNull(&pos);
		}
	#pragma endregion

	#pragma region BoundedSimpleArray_Functions
		/**
		 * Sets an Item in a Bounded Array.
		 * Copies if PBT is string or blob.
		 *
		 * \param pos	Array of Positions
		 * \param t		The Value to set from
		 */
		void Set(std::array<pblong, sizeof...(dims)> pos, const PBT t)
			requires (sizeof...(dims) != 0)
		{
			AssertInside(pos);

			if (t.IsNull())
			{
				m_Session->SetArrayItemToNull(m_Array, pos.data());
			}
			else
			{
				PBXRESULT res = SetImpl<PBT>(&pos, t);
			
				if (res != PBX_OK)
				{
					std::wstring pos_str;
					for (pblong i : pos)
					{
						pos_str += std::to_wstring(i) + L", ";
					}
					pos_str.resize(pos_str.size() - 2);

					std::wstring dims_str = ((L"1 to " + std::to_wstring(dims) + L", ") + ...);
					dims_str.resize(dims_str.size() - 2);

					throw Inf::PBNI_Exception({
						{ L"Error", L"Failed to set an Item to Null in a Bounded Array"},
						{ L"Position", pos_str},
						{ L"Bounds", dims_str},
						{ L"Result", std::to_wstring(res)}
					});
				}
			}
		}

		/**
		 * Sets an Item in a Bounded Array To Null.
		 *
		 * \param pos	Array of Positions
		 */
		void SetItemToNull(std::array<pblong, sizeof...(dims)> pos)
			requires (sizeof...(dims) != 0)
		{
			AssertInside(pos);

			PBXRESULT res = m_Session->SetArrayItemToNull(m_Array, pos.data());

			if (res != PBX_OK)
			{
				std::wstring pos_str;
				for (pblong i : pos)
				{
					pos_str += std::to_wstring(i) + ", ";
				}
				pos_str.resize(pos_str.size() - 2);

				std::wstring dims_str = ((L"1 to " + std::to_wstring(dims) + ", ") + ...);
				dims_str.resize(dims_str.size() - 2);

				throw Inf::PBNI_Exception({
					{ L"Error", L"Failed to set an Item to Null in a Bounded Array"},
					{ L"Position", pos_str},
					{ L"Bounds", dims_str},
					{ L"Result", std::to_wstring(res)}
					});
			}
		}

		/**
		 * Retrieves an Item in a Bounded Array.
		 * If PBT is complex, it will return a reference.
		 *
		 * \param pos	Array of Positions
		 * \return		The Value
		 */
		PBT Get(std::array<pblong, sizeof...(dims)> pos)
			requires (sizeof...(dims) != 0)
		{
			AssertInside(pos);

			return GetImpl<PBT>(pos.data());
		}

		/**
		 * Checks wheter an Item in a Bounded Array is Null.
		 *
		 * \param pos	Array of Positions
		 * \return		Is Null
		 */
		bool IsItemNull(std::array<pblong, sizeof...(dims)> pos)
			requires (sizeof...(dims) != 0)
		{
			AssertInside(pos);

			return m_Session->IsArrayItemNull(pos);
		}
	#pragma endregion


		/**
		 * Retrieves the Length of the Array from PowerBuilder.
		 * 
		 * \return	The Size
		 */
		pblong Size()
		{
			return m_Session->GetArrayLength(m_Array);
		}

		/**
		 * Gets the Bounds of a Bounded Array From PowerBuilder.
		 * 
		 * \return	An Array of Bounds
		 */
		std::array<std::array<pblong, 2>, sizeof...(dims)> Bounds() const
			requires (sizeof...(dims) != 0)
		{
			std::array<std::array<pblong, 2>, sizeof...(dims)> bounds;

			for (uint8_t i = 0; i < sizeof...(dims); i++)
				bounds[i] = { m_ArrayInfo->bounds[i].lowerBound, m_ArrayInfo->bounds[i].upperBound };

			return bounds;
		}

		/**
		 * Check wether the pbarray is null.
		 * 
		 * \return	Is Null
		 */
		bool IsNull() const
		{
			return !m_Array;
		}

		/**
		 * Sets the pbarray to Null.
		 */
		void SetToNull()
		{
			m_Array = 0;
		}
	private:
		friend Type<PBArray>;

		IPB_Session* m_Session;
		pbarray m_Array;
		std::shared_ptr<PBArrayInfo> m_ArrayInfo;
		std::shared_ptr<Helper::AcquiredValue> m_AcquiredValue;

		PBArray(IPB_Session* session, IPB_Value* value, bool acquire)
			: m_Session(session)
		{
			if (value->IsNull())
			{
				m_Array = 0;
			}
			else
			{
				if (acquire)
				{
					m_AcquiredValue = std::make_shared<Helper::AcquiredValue>(session, value);
					m_Array = m_AcquiredValue->Value->GetArray();
				}
				else
				{
					m_Array = value->GetArray();
				}
			}
		}

		/**
		 * Asserts whether a position is inside a bounded Array.
		 * 
		 * \param pos	Array of Positions
		 * 
		 * \throw	Inf::PBNI_Exception if out of bounds.
		 */
		void AssertInside(std::array<pblong, sizeof...(dims)> pos)
			requires (sizeof...(dims) != 0)
		{
			if (IsNull())
				throw Inf::PBNI_Exception(L"Tried to access a field in a bounded " + Type<PBT>::GetPBName(L" array of value Null"));

			for (uint8_t i = 0; i < sizeof...(dims); i++)
			{
				if (m_ArrayInfo->bounds[i].lowerBound > pos[i] || pos[i] > m_ArrayInfo->bounds[i].upperBound)
					throw Inf::PBNI_Exception(L"Accesssing an index out of bounds in a bounded " + Type<PBT>::GetPBName(L" array (") + std::to_wstring(pos[i]) + L" != [" + std::to_wstring(m_ArrayInfo->bounds[i].lowerBound) + L" to " + std::to_wstring(m_ArrayInfo->bounds[i].upperBound) + L"] for dimension " + std::to_wstring(i) + L")");
			}
		}

		/**
		 * Asserts whether a position is inside an Unbounded Array.
		 * 
		 * \param pos					The Position
		 * \param check_upper_bound		Whether to Check if the Position is too big
		 * 
		 * \throw	Inf::PBNI_Exception if out of bounds.
		 */
		void AssertInside(pblong pos, bool check_upper_bound = true)
			requires (sizeof...(dims) == 0)
		{
			if (IsNull())
				throw Inf::PBNI_Exception(L"Tried to access a field in an unbounded " + Type<PBT>::GetPBName(L" array of value Null"));

			if (1 > pos || (check_upper_bound && pos < Size()))
				throw Inf::PBNI_Exception(L"Accesssing an out of bounds in an unbounded " + Type<PBT>::GetPBName(L" array (") + std::to_wstring(pos) + L" >= " + std::to_wstring(Size()) + L")");
		}


		template <typename T>
		inline PBXRESULT SetImpl(pblong* dim, const T t) = delete;
		template <typename T>
		inline T GetImpl(pblong* dim) const = delete;

		// Array template definitinos
		template<> inline PBXRESULT SetImpl<PBByte>		(pblong* dim, const PBByte t)		{ return m_Session->SetByteArrayItem(m_Array, dim, t); }
		template<> inline PBXRESULT SetImpl<PBBoolean>	(pblong* dim, const PBBoolean t)	{ return m_Session->SetCharArrayItem(m_Array, dim, t); }
		template<> inline PBXRESULT SetImpl<PBChar>		(pblong* dim, const PBChar t)		{ return m_Session->SetCharArrayItem(m_Array, dim, t); }
		template<> inline PBXRESULT SetImpl<PBInt>		(pblong* dim, const PBInt t)		{ return m_Session->SetIntArrayItem(m_Array, dim, t); }
		template<> inline PBXRESULT SetImpl<PBUint>		(pblong* dim, const PBUint t)		{ return m_Session->SetUintArrayItem(m_Array, dim, t); }
		template<> inline PBXRESULT SetImpl<PBLong>		(pblong* dim, const PBLong t)		{ return m_Session->SetLongArrayItem(m_Array, dim, t); }
		template<> inline PBXRESULT SetImpl<PBUlong>	(pblong* dim, const PBUlong t)		{ return m_Session->SetUlongArrayItem(m_Array, dim, t); }
		template<> inline PBXRESULT SetImpl<PBLongLong>	(pblong* dim, const PBLongLong t)	{ return m_Session->SetLongLongArrayItem(m_Array, dim, t); }
		template<> inline PBXRESULT SetImpl<PBReal>		(pblong* dim, const PBReal t)		{ return m_Session->SetRealArrayItem(m_Array, dim, t); }
		template<> inline PBXRESULT SetImpl<PBDouble>	(pblong* dim, const PBDouble t)		{ return m_Session->SetDoubleArrayItem(m_Array, dim, t); }
		template<> inline PBXRESULT SetImpl<PBDecimal>	(pblong* dim, const PBDecimal t)
		{
			std::wstring dec_repr = ConvertString<std::wstring>(t.t.str());

			pbdec pb_dec = m_Session->NewDecimal();
			m_Session->SetDecimal(pb_dec, dec_repr.c_str());

			return m_Session->SetDecArrayItem(m_Array, dim, pb_dec);
		}
		template<> inline PBXRESULT SetImpl<PBTime>		(pblong* dim, const PBTime t)		{ return m_Session->SetTimeArrayItem(m_Array, dim, t.m_Time); }
		template<> inline PBXRESULT SetImpl<PBDate>		(pblong* dim, const PBDate t)		{ return m_Session->SetDateArrayItem(m_Array, dim, t.m_Date); }
		template<> inline PBXRESULT SetImpl<PBDateTime>	(pblong* dim, const PBDateTime t)	{ return m_Session->SetDateTimeArrayItem(m_Array, dim, t.m_DateTime); }
		template<> inline PBXRESULT SetImpl<PBString>	(pblong* dim, const PBString t)		{ return m_Session->SetPBStringArrayItem(m_Array, dim, t.m_String); }
		template<> inline PBXRESULT SetImpl<PBBlob>		(pblong* dim, const PBBlob t)		{ return m_Session->SetBlobArrayItem(m_Array, dim, t.m_Blob); }

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



	/**
	 * Wrapper for Object Arrays.
	 * ObjectArrays need their own class, because there is no partial specialization for functions.
	 * 
	 * \tparam class_id		The ID of the Group and Class, split with '.', or just the Class
	 * \tparam group_type	The Group Type used by PowerBuilder (struct, userobject, ...)
	 * \tparam dims...		The Bounds of the Bounded Array, Unbounded Array if empty
	 */
	template <Helper::FixedString class_id, pbgroup_type group_type, pblong... dims>
	class PBArray<PBObject<class_id, group_type>, dims...>
	{
	public:
		/**
		 * Creates a Wrapper to an existing pbarray.
		 * Null if arr is 0
		 * 
		 * \param session	Current session
		 * \param arr		pbarray or 0
		 */
		PBArray(IPB_Session* session, pbarray arr)
			: m_Session(session), m_Array(arr)
		{
			if (!IsNull())
				m_ArrayInfo = std::shared_ptr<PBArrayInfo>(m_Session->GetArrayInfo(m_Array), [=](PBArrayInfo* info) { m_Session->ReleaseArrayInfo(info); });
		}

		/**
		 * Creates a new Bounded or Unbounded Array.
		 *
		 * \param session	Current Session
		 */
		PBArray(IPB_Session* session)
			: m_Session(session)
		{
			pbclass cls = PBObject<class_id, group_type>::PBClass(session);

			if constexpr (sizeof...(dims) == 0)
			{
				m_Array = m_Session->NewUnboundedObjectArray(cls);
			}
			else
			{
				PBArrayInfo::ArrayBound bounds[] = { { dims, 1 }... };
				m_Array = m_Session->NewBoundedObjectArray(cls, sizeof...(dims), bounds);
			}
		
			m_ArrayInfo = std::shared_ptr<PBArrayInfo>(m_Session->GetArrayInfo(m_Array), [=](PBArrayInfo* info) { m_Session->ReleaseArrayInfo(info); });
		}


	#pragma region UnboundedObjectArray_Functions
		/**
		 * Sets an Item in an Unbounded Array.
		 * Copies if PBT is string or blob.
		 *
		 * \param pos	The Position
		 * \param t		The Value to set from
		 */
		inline void Set(pblong pos, const PBObject<class_id, group_type>& t)
			requires (sizeof...(dims) == 0)
		{
			// No need to check upper bound
			AssertInside(pos, false);

			if (t.IsNull())
			{
				m_Session->SetArrayItemToNull(m_Array, &pos);
			}
			else
			{
				PBXRESULT res = m_Session->SetObjectArrayItem(m_Array, &pos, t.m_Object);

				if (res != PBX_OK)
				{
					throw Inf::PBNI_Exception({
						{ L"Error", L"Failed to set an Object in an Unbounded Array"},
						{ L"Class", class_id.data },
						{ L"Position", std::to_wstring(pos)},
						{ L"Result", std::to_wstring(res)}
					});
				}
			}
		}

		/**
		 * Sets an Item in an Unbounded Array To Null.
		 *
		 * \param pos	The Position
		 */
		inline void SetItemToNull(pblong pos)
			requires (sizeof...(dims) == 0)
		{
			// No need to check upper bound
			AssertInside(pos, false);

			PBXRESULT res = m_Session->SetArrayItemToNull(m_Array, &pos);

			if (res != PBX_OK)
			{
				throw Inf::PBNI_Exception({
					{ L"Error", L"Failed to set an Object to Null in an Unbounded Array"},
					{ L"Class", class_id.data },
					{ L"Position", std::to_wstring(pos)},
					{ L"Result", std::to_wstring(res)}
				});
			}
		}

		/**
		 * Retrieves an Item in an Unbounded Array.
		 * If PBT is complex, it will return a reference.
		 *
		 * \param pos	The Position
		 * \return		The Value
		 */
		inline PBObject<class_id, group_type> Get(pblong pos)
			requires (sizeof...(dims) == 0)
		{
			AssertInside(pos);

			pbboolean is_null;
			pbobject obj = m_Session->GetObjectArrayItem(m_Array, &pos, is_null);
			return { m_Session, is_null ? 0 : obj };
		}

		/**
		 * Checks wheter an Item in an Unbounded Array is Null.
		 * 
		 * \param pos	The Position
		 * \return		Is Null
		 */
		bool IsItemNull(pblong pos)
			requires (sizeof...(dims) == 0)
		{
			// No need to check upper bound
			AssertInside(pos, false);

			return m_Session->IsArrayItemNull(&pos);
		}
	#pragma endregion


	#pragma region BoundedObjectArray_Functions
		/**
		 * Sets an Item in a Bounded Array.
		 * Copies if PBT is string or blob.
		 *
		 * \param pos	Array of Positions
		 * \param t		The Value to set from
		 */
		inline void Set(std::array<pblong, sizeof...(dims)> pos, const PBObject<class_id, group_type>& t)
			requires (sizeof...(dims) != 0)
		{
			AssertInside(pos);

			if (t.IsNull())
			{
				m_Session->SetArrayItemToNull(m_Array, pos.data());
			}
			else
			{
				PBXRESULT res = m_Session->SetObjectArrayItem(m_Array, pos.data(), t.m_Object);

				if (res != PBX_OK)
				{
					std::wstring pos_str;
					for (pblong i : pos)
					{
						pos_str += std::to_wstring(i) + L", ";
					}
					pos_str.resize(pos_str.size() - 2);

					std::wstring dims_str = ((L"1 to " + std::to_wstring(dims) + L", ") + ...);
					dims_str.resize(dims_str.size() - 2);

					throw Inf::PBNI_Exception({
						{ L"Error", L"Failed to set an Object in a Bounded Array"},
						{ L"Class", class_id.data },
						{ L"Position", pos_str},
						{ L"Bounds", dims_str},
						{ L"Result", std::to_wstring(res)},
						});
				}
			}
		}


		/**
		 * Sets an Item in a Bounded Array To Null.
		 *
		 * \param pos	Array of Positions
		 */
		void SetItemToNull(std::array<pblong, sizeof...(dims)> pos)
			requires (sizeof...(dims) != 0)
		{
			AssertInside(pos);

			PBXRESULT res = m_Session->SetArrayItemToNull(m_Array, pos.data());

			if (res != PBX_OK)
			{
				std::wstring pos_str;
				for (pblong i : pos)
				{
					pos_str += std::to_wstring(i) + L", ";
				}
				pos_str.resize(pos_str.size() - 2);

				std::wstring dims_str = ((L"1 to " + std::to_wstring(dims) + L", ") + ...);
				dims_str.resize(dims_str.size() - 2);

				throw Inf::PBNI_Exception({
					{ L"Error", L"Failed to set an Object to Null in a Bounded Array"},
					{ L"Class", class_id.data },
					{ L"Position", pos_str},
					{ L"Bounds", dims_str},
					{ L"Result", std::to_wstring(res)}
				});
			}
		}

		/**
		 * Retrieves an Item in a Bounded Array.
		 * If PBT is complex, it will return a reference.
		 *
		 * \param pos	Array of Positions
		 * \return		The Value
		 */
		inline PBObject<class_id, group_type> Get(std::array<pblong, sizeof...(dims)> pos)
			requires (sizeof...(dims) != 0)
		{
			AssertInside(pos);

			pbboolean is_null;
			pbobject obj = m_Session->GetObjectArrayItem(m_Array, pos.data(), is_null);
			return { m_Session, is_null ? 0 : obj };
		}

		/**
		 * Checks wheter an Item in a Bounded Array is Null.
		 *
		 * \param pos	Array of Positions
		 * \return		Is Null
		 */
		bool IsItemNull(std::array<pblong, sizeof...(dims)> pos)
			requires (sizeof...(dims) != 0)
		{
			AssertInside(pos);

			return m_Session->IsArrayItemNull(pos);
		}
	#pragma endregion


		/**
		 * Retrieves the Length of the Array from PowerBuilder.
		 *
		 * \return	The Size
		 */
		pblong Size() const
		{
			return m_Session->GetArrayLength(m_Array);
		}

		/**
		 * Gets the Bounds of a Bounded Array From PowerBuilder.
		 *
		 * \return	An Array of Bounds
		 */
		std::array<std::array<pblong, 2>, sizeof...(dims)>  Bounds() const
			requires (sizeof...(dims) != 0)
		{
			std::array<std::array<pblong, 2>, sizeof...(dims)> bounds;

			for (uint8_t i = 0; i < sizeof...(dims); i++)
				bounds[i] = { m_ArrayInfo->bounds[i].lowerBound, m_ArrayInfo->bounds[i].upperBound };

			return bounds;
		}

		/**
		 * Check wether the pbarray is null.
		 *
		 * \return	Is Null
		 */
		bool IsNull() const
		{
			return !m_Array;
		}

		/**
		 * Sets the pbarray to Null.
		 */
		void SetToNull()
		{
			m_Array = 0;
		}
	private:
		friend Type<PBArray>;

		IPB_Session* m_Session;
		pbarray m_Array;
		std::shared_ptr<PBArrayInfo> m_ArrayInfo;
		std::shared_ptr<Helper::AcquiredValue> m_AcquiredValue;

		PBArray(IPB_Session* session, IPB_Value* value, bool acquire)
			: m_Session(session)
		{
			if (value->IsNull())
			{
				m_Array = 0;
			}
			else
			{
				if (acquire)
				{
					m_AcquiredValue = std::make_shared<Helper::AcquiredValue>(session, value);
					m_Array = m_AcquiredValue->Value->GetArray();
				}
				else
				{
					m_Array = value->GetArray();
				}
			}
		}

		/**
		 * Asserts whether a position is inside a bounded Array.
		 *
		 * \param pos	Array of Positions
		 *
		 * \throw	Inf::PBNI_Exception if out of bounds.
		 */
		void AssertInside(std::array<pblong, sizeof...(dims)> pos)
			requires (sizeof...(dims) != 0)
		{
			if (IsNull())
				throw Inf::PBNI_Exception(L"Tried to access a field in a bounded object array of value Null");

			for (uint8_t i = 0; i < sizeof...(dims); i++)
			{
				if (m_ArrayInfo->bounds[i].lowerBound > pos[i] || pos[i] > m_ArrayInfo->bounds[i].upperBound)
					throw Inf::PBNI_Exception(std::wstring(L"Accesssing an index out of bounds in a bounded object array (") + std::to_wstring(pos[i]) + L"!= [" + std::to_wstring(m_ArrayInfo->bounds[i].lowerBound) + L" to " + std::to_wstring(m_ArrayInfo->bounds[i].upperBound) + L"] for dimension " + std::to_wstring(i) + L")");
			}
		}

		/**
		 * Asserts whether a position is inside an Unbounded Array.
		 *
		 * \param pos					The Position
		 * \param check_upper_bound		Whether to Check if the Position is too big
		 *
		 * \throw	Inf::PBNI_Exception if out of bounds.
		 */
		void AssertInside(pblong pos, bool check_upper_bound = true)
			requires (sizeof...(dims) == 0)
		{
			if (IsNull())
				throw Inf::PBNI_Exception(L"Tried to access a field in an unbounded object array of value Null");

			if (1 > pos || (check_upper_bound && pos > Size()))
				throw Inf::PBNI_Exception(L"Accesssing an out of bounds in an unbounded object array (" + std::to_wstring(pos) + L" >= " + std::to_wstring(Size()) + L")");
		}
	};

}
