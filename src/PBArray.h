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
	 * This Class is just there to put some duplicate code into one place.
	 */
	template <pblong... dims>
	class IPBArray
	{
	public:
		IPBArray(IPB_Session* session, pbarray arr = 0)
			: m_Session(session), m_Array(arr)
		{
			if (!IsNull())
				this->m_ArrayInfo = std::shared_ptr<PBArrayInfo>(this->m_Session->GetArrayInfo(this->m_Array), [=](PBArrayInfo* info) { this->m_Session->ReleaseArrayInfo(info); });

		}

	#pragma region UnboundedObjectArray_Functions
		/**
		 * Sets an Item in an Unbounded Array To Null.
		 *
		 * \param pos	The Position
		 * 
		 * \throw Inf::PBNI_NullPointerException	If is Null
		 * \throw Inf::PBNI_IndexOutOfBounds		If out of bounds
		 * \throw Inf::PBNI_PowerBuilderException	If PowerBuilder function doesnt return PBX_SUCESS
		 */
		inline void SetItemToNull(pblong pos)
			requires (sizeof...(dims) == 0)
		{
			// No need to check upper bound
			AssertInside(pos, false);

			PBXRESULT res = m_Session->SetArrayItemToNull(m_Array, &pos);

			if (res != PBX_SUCCESS)
				throw PBNI_PowerBuilderException(L"IPB_Session::SetArrayItemToNull", res);
		}

		/**
		 * Checks wheter an Item in an Unbounded Array is Null.
		 *
		 * \param pos	The Position
		 * \return		Is Null
		 * 
		 * \throw Inf::PBNI_NullPointerException	If is Null
		 * \throw Inf::PBNI_IndexOutOfBounds		If out of bounds
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
		 * Sets an Item in a Bounded Array To Null.
		 *
		 * \param pos	Array of Positions
		 * 
		 * \throw Inf::PBNI_NullPointerException	If is Null
		 * \throw Inf::PBNI_IndexOutOfBounds		If out of bounds
		 * \throw Inf::PBNI_PowerBuilderException	If PowerBuilder function doesnt return PBX_SUCESS
		 */
		void SetItemToNull(std::array<pblong, sizeof...(dims)> pos)
			requires (sizeof...(dims) != 0)
		{
			AssertInside(pos);

			PBXRESULT res = m_Session->SetArrayItemToNull(m_Array, pos.data());

			if (res != PBX_SUCCESS)
				throw PBNI_PowerBuilderException(L"IPB_Session::SetArrayItemToNull", res);
		}

		/**
		 * Checks wheter an Item in a Bounded Array is Null.
		 *
		 * \param pos	Array of Positions
		 * \return		Is Null
		 * 
		 * \throw Inf::PBNI_NullPointerException	If is Null
		 * \throw Inf::PBNI_IndexOutOfBounds		If out of bounds
		 */
		bool IsItemNull(std::array<pblong, sizeof...(dims)> pos)
			requires (sizeof...(dims) != 0)
		{
			AssertInside(pos);

			return m_Session->IsArrayItemNull(pos);
		}

		/**
		 * Gets the Bounds of a Bounded Array From PowerBuilder.
		 *
		 * \return	An Array of Bounds
		 */
		std::array<std::pair<pblong, pblong>, sizeof...(dims)> Bounds() const
			requires (sizeof...(dims) != 0)
		{
			if (IsNull())
				throw PBNI_NullPointerException(L"PBBoundedArray");

			std::array<std::pair<pblong, pblong>, sizeof...(dims)> bounds;

			for (uint8_t i = 0; i < sizeof...(dims); i++)
				bounds[i] = { m_ArrayInfo->bounds[i].lowerBound, m_ArrayInfo->bounds[i].upperBound };

			return bounds;
		}
	#pragma endregion

		/**
		 * Retrieves the Length of the Array from PowerBuilder.
		 *
		 * \return	The Size
		 * 
		 * \throw Inf::PBNI_NullPointerException	If is Null
		 */
		pblong Size()
		{
			if (IsNull())
				throw PBNI_NullPointerException(L"PBArray");
				
			return m_Session->GetArrayLength(m_Array);
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

	protected:

		IPB_Session* m_Session;
		pbarray m_Array;
		std::shared_ptr<PBArrayInfo> m_ArrayInfo;
		std::shared_ptr<Helper::AcquiredValue> m_AcquiredValue;


		/**
		 * Constructor used to get an array out of a value and acquire if needed.
		 * 
		 * \param session	Current Session
		 * \param value		IPB_Value holding the Array
		 * \param acquire	Whether to take ownership of the IPB_Value
		 */
		IPBArray(IPB_Session* session, IPB_Value* value, bool acquire)
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
		 * \throw Inf::PBNI_NullPointerException	If is Null
		 * \throw Inf::PBNI_IndexOutOfBounds		If out of bounds
		 */
		void AssertInside(std::array<pblong, sizeof...(dims)> pos)
			requires (sizeof...(dims) != 0)
		{
			if (IsNull())
				throw PBNI_NullPointerException(L"PBBoundedArray");

			for (pbbyte i = 0; i < sizeof...(dims); i++)
			{
				if (m_ArrayInfo->bounds[i].lowerBound > pos[i] || pos[i] > m_ArrayInfo->bounds[i].upperBound)
					throw PBNI_IndexOutOfBounds(pos, Bounds(), i);
			}
		}

		/**
		 * Asserts whether a position is inside an Unbounded Array.
		 *
		 * \param pos					The Position
		 * \param check_upper_bound		Whether to Check if the Position is too big
		 *
		 * \throw Inf::PBNI_NullPointerException	If is Null
		 * \throw Inf::PBNI_IndexOutOfBounds		If out of bounds
		 */
		void AssertInside(pblong pos, bool check_upper_bound = true)
			requires (sizeof...(dims) == 0)
		{
			if (IsNull())
				throw PBNI_NullPointerException(L"PBUnboundedArray");

			if (1 > pos || (check_upper_bound && pos < Size()))
				throw PBNI_IndexOutOfBounds(pos, Size());
		}
	};


	/**
	 * Wrapper for simple Arrays.
	 * 
	 * \tparam PBT Type of the Array Items
	 * \tparam dims... The Bounds of the Bounded Array, Unbounded Array if empty
	 */
	template <typename PBT, pblong... dims>
		requires (sizeof...(dims) <= 3 && !std::is_reference_v<PBT> && !std::is_pointer_v<PBT>)
	class PBArray : public IPBArray<dims...> // Because we extend a templated class we need to use this-> everywhere when accessing the base fields.
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
			: IPBArray<dims...>(session, arr)
		{ }
		
		/**
		 * Creates a new Bounded or Unbounded Array.
		 * 
		 * \param session	Current Session
		 */
		PBArray(IPB_Session* session)
			: IPBArray<dims...>(session)
		{
			if constexpr (sizeof...(dims) == 0)
			{
				this->m_Array = this->m_Session->NewUnboundedSimpleArray(Type<PBT>::PBType);
			}
			else
			{
				PBArrayInfo::ArrayBound bounds[] = { { dims, 1 }... };
				this->m_Array = this->m_Session->NewBoundedSimpleArray(Type<PBT>::PBType, sizeof...(dims), bounds);
			}

			this->m_ArrayInfo = std::shared_ptr<PBArrayInfo>(this->m_Session->GetArrayInfo(this->m_Array), [=](PBArrayInfo* info) { this->m_Session->ReleaseArrayInfo(info); });
		}

	#pragma region UnboundedSimpleArray_Functions
		/**
		 * Sets an Item in an Unbounded Array.
		 * Copies if PBT is string or blob.
		 * 
		 * \param pos	The Position
		 * \param t		The Value to set from
		 * 
		 * \throw Inf::PBNI_NullPointerException	If is Null
		 * \throw Inf::PBNI_IndexOutOfBounds		If out of bounds
		 * \throw Inf::PBNI_PowerBuilderException	If PowerBuilder function doesnt return PBX_SUCESS
		 */
		void Set(pblong pos, const PBT t)
			requires (sizeof...(dims) == 0)
		{
			this->AssertInside(pos, false);

			if (t.IsNull())
			{
				this->m_Session->SetArrayItemToNull(this->m_Array, &pos);
			}
			else
			{
				PBXRESULT res = SetImpl<PBT>(&pos, t) + 15;

				if (res != PBX_SUCCESS)
					throw PBNI_PowerBuilderException(L"IPB_Session::Set<Type>ArrayItem for " + Type<PBT>::GetPBName(L""), res);
			}
		}

		/**
		 * Retrieves an Item in an Unbounded Array.
		 * If PBT is complex, it will return a reference.
		 * 
		 * \param pos	The Position
		 * \return		The Value
		 * 
		 * \throw Inf::PBNI_NullPointerException	If is Null
		 * \throw Inf::PBNI_IndexOutOfBounds		If out of bounds
		 */
		PBT Get(pblong pos)
			requires (sizeof...(dims) == 0)
		{
			this->AssertInside(pos);

			return GetImpl<PBT>(&pos);
		}
	#pragma endregion

	#pragma region BoundedSimpleArray_Functions
		/**
		 * Sets an Item in a Bounded Array.
		 * Copies if PBT is string or blob.
		 *
		 * \param pos	Array of Positions
		 * \param t		The Value to set from
		 * 
		 * \throw Inf::PBNI_NullPointerException	If is Null
		 * \throw Inf::PBNI_IndexOutOfBounds		If out of bounds
		 * \throw Inf::PBNI_PowerBuilderException	If PowerBuilder function doesnt return PBX_SUCESS
		 */
		void Set(std::array<pblong, sizeof...(dims)> pos, const PBT t)
			requires (sizeof...(dims) != 0)
		{
			this->AssertInside(pos);

			if (t.IsNull())
			{
				this->m_Session->SetArrayItemToNull(this->m_Array, pos.data());
			}
			else
			{
				PBXRESULT res = SetImpl<PBT>(&pos, t);
			
				if (res != PBX_SUCCESS)
					throw PBNI_PowerBuilderException(L"IPB_Session::Set<Type>ArrayItem for " + Type<PBT>::GetPBName(L""), res);
			}
		}

		/**
		 * Retrieves an Item in a Bounded Array.
		 * If PBT is complex, it will return a reference.
		 *
		 * \param pos	Array of Positions
		 * \return		The Value
		 * 
		 * \throw Inf::PBNI_NullPointerException	If is Null
		 * \throw Inf::PBNI_IndexOutOfBounds		If out of bounds
		 */
		PBT Get(std::array<pblong, sizeof...(dims)> pos)
			requires (sizeof...(dims) != 0)
		{
			this->AssertInside(pos);

			return GetImpl<PBT>(pos.data());
		}
	#pragma endregion

	private:
		friend Type<PBArray>;

		/**
		 * Constructor used to get an array out of a value and acquire if needed.
		 *
		 * \param session	Current Session
		 * \param value		IPB_Value holding the Array
		 * \param acquire	Whether to take ownership of the IPB_Value
		 */
		PBArray(IPB_Session* session, IPB_Value* value, bool acquire)
			: IPBArray<dims...>(session, value, acquire)
		{ }


		template <typename T>
		inline PBXRESULT SetImpl(pblong* dim, const T t) = delete;
		template <typename T>
		inline T GetImpl(pblong* dim) const = delete;

		// Array template definitinos
		template<> inline PBXRESULT SetImpl<PBByte>		(pblong* dim, const PBByte t)		{ return this->m_Session->SetByteArrayItem(this->m_Array, dim, t); }
		template<> inline PBXRESULT SetImpl<PBBoolean>	(pblong* dim, const PBBoolean t)	{ return this->m_Session->SetCharArrayItem(this->m_Array, dim, t); }
		template<> inline PBXRESULT SetImpl<PBChar>		(pblong* dim, const PBChar t)		{ return this->m_Session->SetCharArrayItem(this->m_Array, dim, t); }
		template<> inline PBXRESULT SetImpl<PBInt>		(pblong* dim, const PBInt t)		{ return this->m_Session->SetIntArrayItem(this->m_Array, dim, t); }
		template<> inline PBXRESULT SetImpl<PBUint>		(pblong* dim, const PBUint t)		{ return this->m_Session->SetUintArrayItem(this->m_Array, dim, t); }
		template<> inline PBXRESULT SetImpl<PBLong>		(pblong* dim, const PBLong t)		{ return this->m_Session->SetLongArrayItem(this->m_Array, dim, t); }
		template<> inline PBXRESULT SetImpl<PBUlong>	(pblong* dim, const PBUlong t)		{ return this->m_Session->SetUlongArrayItem(this->m_Array, dim, t); }
		template<> inline PBXRESULT SetImpl<PBLongLong>	(pblong* dim, const PBLongLong t)	{ return this->m_Session->SetLongLongArrayItem(this->m_Array, dim, t); }
		template<> inline PBXRESULT SetImpl<PBReal>		(pblong* dim, const PBReal t)		{ return this->m_Session->SetRealArrayItem(this->m_Array, dim, t); }
		template<> inline PBXRESULT SetImpl<PBDouble>	(pblong* dim, const PBDouble t)		{ return this->m_Session->SetDoubleArrayItem(this->m_Array, dim, t); }
		template<> inline PBXRESULT SetImpl<PBDecimal>	(pblong* dim, const PBDecimal t)	{ return this->m_Session->SetDecArrayItem(this->m_Array, dim, t.m_Decimal); }
		template<> inline PBXRESULT SetImpl<PBTime>		(pblong* dim, const PBTime t)		{ return this->m_Session->SetTimeArrayItem(this->m_Array, dim, t.m_Time); }
		template<> inline PBXRESULT SetImpl<PBDate>		(pblong* dim, const PBDate t)		{ return this->m_Session->SetDateArrayItem(this->m_Array, dim, t.m_Date); }
		template<> inline PBXRESULT SetImpl<PBDateTime>	(pblong* dim, const PBDateTime t)	{ return this->m_Session->SetDateTimeArrayItem(this->m_Array, dim, t.m_DateTime); }
		template<> inline PBXRESULT SetImpl<PBString>	(pblong* dim, const PBString t)		{ return this->m_Session->SetPBStringArrayItem(this->m_Array, dim, t.m_String); }
		template<> inline PBXRESULT SetImpl<PBBlob>		(pblong* dim, const PBBlob t)		{ return this->m_Session->SetBlobArrayItem(this->m_Array, dim, t.m_Blob); }

		template<> inline PBByte		GetImpl<PBByte>		(pblong* dim) const	{ pbboolean is_null = false; pbbyte pb_byte			= this->m_Session->GetByteArrayItem(this->m_Array, dim, is_null);		return is_null ? PBByte()		: PBByte(pb_byte); }
		template<> inline PBBoolean		GetImpl<PBBoolean>	(pblong* dim) const	{ pbboolean is_null = false; pbboolean pb_boolean	= this->m_Session->GetCharArrayItem(this->m_Array, dim, is_null);		return is_null ? PBBoolean()	: PBBoolean(pb_boolean); }
		template<> inline PBChar		GetImpl<PBChar>		(pblong* dim) const	{ pbboolean is_null = false; pbchar pb_char			= this->m_Session->GetCharArrayItem(this->m_Array, dim, is_null);		return is_null ? PBChar()		: PBChar(pb_char); }
		template<> inline PBInt			GetImpl<PBInt>		(pblong* dim) const	{ pbboolean is_null = false; pbint pb_int			= this->m_Session->GetIntArrayItem(this->m_Array, dim, is_null);		return is_null ? PBInt()		: PBInt(pb_int); }
		template<> inline PBUint		GetImpl<PBUint>		(pblong* dim) const	{ pbboolean is_null = false; pbuint pb_uint			= this->m_Session->GetUintArrayItem(this->m_Array, dim, is_null);		return is_null ? PBUint()		: PBUint(pb_uint); }
		template<> inline PBLong		GetImpl<PBLong>		(pblong* dim) const	{ pbboolean is_null = false; pblong pb_long			= this->m_Session->GetLongArrayItem(this->m_Array, dim, is_null);		return is_null ? PBLong()		: PBLong(pb_long); }
		template<> inline PBUlong		GetImpl<PBUlong>	(pblong* dim) const	{ pbboolean is_null = false; pbulong pb_ulong		= this->m_Session->GetUlongArrayItem(this->m_Array, dim, is_null);		return is_null ? PBUlong()		: PBUlong(pb_ulong); }
		template<> inline PBLongLong	GetImpl<PBLongLong>	(pblong* dim) const	{ pbboolean is_null = false; pblonglong pb_longlong	= this->m_Session->GetLongLongArrayItem(this->m_Array, dim, is_null);	return is_null ? PBLongLong()	: PBLongLong(pb_longlong); }
		template<> inline PBReal		GetImpl<PBReal>		(pblong* dim) const	{ pbboolean is_null = false; pbreal pb_real			= this->m_Session->GetRealArrayItem(this->m_Array, dim, is_null);		return is_null ? PBReal()		: PBReal(pb_real); }
		template<> inline PBDouble		GetImpl<PBDouble>	(pblong* dim) const	{ pbboolean is_null = false; pbdouble pb_double		= this->m_Session->GetDoubleArrayItem(this->m_Array, dim, is_null);		return is_null ? PBDouble()		: PBDouble(pb_double); }
		template<> inline PBDecimal		GetImpl<PBDecimal>	(pblong* dim) const { pbboolean is_null = false; pbdec pb_dec			= this->m_Session->GetDecArrayItem(this->m_Array, dim, is_null);		return { this->m_Session, is_null ? 0 : pb_dec }; }
		template<> inline PBTime		GetImpl<PBTime>		(pblong* dim) const	{ pbboolean is_null = false; pbtime pb_time			= this->m_Session->GetTimeArrayItem(this->m_Array, dim, is_null);		return { this->m_Session, is_null ? 0 : pb_time }; }
		template<> inline PBDate		GetImpl<PBDate>		(pblong* dim) const	{ pbboolean is_null = false; pbdate pb_date			= this->m_Session->GetDateArrayItem(this->m_Array, dim, is_null);		return { this->m_Session, is_null ? 0 : pb_date }; }
		template<> inline PBDateTime	GetImpl<PBDateTime>	(pblong* dim) const	{ pbboolean is_null = false; pbdatetime pb_datetime	= this->m_Session->GetDateTimeArrayItem(this->m_Array, dim, is_null);	return { this->m_Session, is_null ? 0 : pb_datetime }; }
		template<> inline PBString		GetImpl<PBString>	(pblong* dim) const	{ pbboolean is_null = false; pbstring pb_string		= this->m_Session->GetStringArrayItem(this->m_Array, dim, is_null);		return { this->m_Session, is_null ? 0 : pb_string }; }
		template<> inline PBBlob		GetImpl<PBBlob>		(pblong* dim) const	{ pbboolean is_null = false; pbblob pb_blob			= this->m_Session->GetBlobArrayItem(this->m_Array, dim, is_null);		return { this->m_Session, is_null ? 0 : pb_blob }; }
	};


	/**
	 * Wrapper for Object Arrays.
	 * ObjectArrays need their own class, because there is no partial specialization for functions.
	 * 
	 * \tparam class_id		The ID of the Group and Class, split with '.', or just the Class
	 * \tparam group_type	The Group Type used by PowerBuilder (struct, userobject, ...)
	 * \tparam ...dims		The Bounds of the Bounded Array, Unbounded Array if empty
	 */
	template <Helper::FixedString class_id, pbgroup_type group_type, pblong... dims>
	class PBArray<PBObject<class_id, group_type>, dims...> : public IPBArray<dims...> // Because we extend a templated class we need to use this-> everywhere when accessing the base fields.
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
			: IPBArray<dims...>(session, arr)
		{ }

		/**
		 * Creates a new Bounded or Unbounded Array.
		 *
		 * \param session	Current Session
		 */
		PBArray(IPB_Session* session)
			: IPBArray<dims...>(session)
		{
			pbclass cls = PBObject<class_id, group_type>::PBClass(session);

			if constexpr (sizeof...(dims) == 0)
			{
				this->m_Array = this->m_Session->NewUnboundedObjectArray(cls);
			}
			else
			{
				PBArrayInfo::ArrayBound bounds[] = { { dims, 1 }... };
				this->m_Array = this->m_Session->NewBoundedObjectArray(cls, sizeof...(dims), bounds);
			}
		
			this->m_ArrayInfo = std::shared_ptr<PBArrayInfo>(this->m_Session->GetArrayInfo(this->m_Array), [=](PBArrayInfo* info) { this->m_Session->ReleaseArrayInfo(info); });
		}

	#pragma region UnboundedObjectArray_Functions
		/**
		 * Sets an Item in an Unbounded Array.
		 * Copies if PBT is string or blob.
		 *
		 * \param pos	The Position
		 * \param t		The Value to set from
		 * 
		 * \throw Inf::PBNI_NullPointerException	If is Null
		 * \throw Inf::PBNI_IndexOutOfBounds		If out of bounds
		 * \throw Inf::PBNI_PowerBuilderException	If PowerBuilder function doesnt return PBX_SUCESS
		 */
		inline void Set(pblong pos, const PBObject<class_id, group_type>& t)
			requires (sizeof...(dims) == 0)
		{
			// No need to check upper bound
			this->AssertInside(pos, false);

			if (t.IsNull())
			{
				this->m_Session->SetArrayItemToNull(this->m_Array, &pos);
			}
			else
			{
				PBXRESULT res = this->m_Session->SetObjectArrayItem(this->m_Array, &pos, t.m_Object);

				if (res != PBX_SUCCESS)
					throw PBNI_PowerBuilderException(L"IPB_Session::SetObjectArrayItem", res);
			}
		}

		/**
		 * Retrieves an Item in an Unbounded Array.
		 * If PBT is complex, it will return a reference.
		 *
		 * \param pos	The Position
		 * \return		The Value
		 * 
		 * \throw Inf::PBNI_NullPointerException	If is Null
		 * \throw Inf::PBNI_IndexOutOfBounds		If out of bounds
		 */
		inline PBObject<class_id, group_type> Get(pblong pos)
			requires (sizeof...(dims) == 0)
		{
			this->AssertInside(pos);

			pbboolean is_null;
			pbobject obj = this->m_Session->GetObjectArrayItem(this->m_Array, &pos, is_null);
			return { this->m_Session, is_null ? 0 : obj };
		}
	#pragma endregion

	#pragma region BoundedObjectArray_Functions
		/**
		 * Sets an Item in a Bounded Array.
		 * Copies if PBT is string or blob.
		 *
		 * \param pos	Array of Positions
		 * \param t		The Value to set from
		 * 
		 * \throw Inf::PBNI_NullPointerException	If is Null
		 * \throw Inf::PBNI_IndexOutOfBounds		If out of bounds
		 * \throw Inf::PBNI_PowerBuilderException	If PowerBuilder function doesnt return PBX_SUCESS
		 */
		inline void Set(std::array<pblong, sizeof...(dims)> pos, const PBObject<class_id, group_type>& t)
			requires (sizeof...(dims) != 0)
		{
			this->AssertInside(pos);

			if (t.IsNull())
			{
				this->m_Session->SetArrayItemToNull(this->m_Array, pos.data());
			}
			else
			{
				PBXRESULT res = this->m_Session->SetObjectArrayItem(this->m_Array, pos.data(), t.m_Object);

				if (res != PBX_SUCCESS)
					throw PBNI_PowerBuilderException(L"IPB_Session::SetObjectArrayItem", res);
			}
		}

		/**
		 * Retrieves an Item in a Bounded Array.
		 * If PBT is complex, it will return a reference.
		 *
		 * \param pos	Array of Positions
		 * \return		The Value
		 * 
		 * \throw Inf::PBNI_NullPointerException	If is Null
		 * \throw Inf::PBNI_IndexOutOfBounds		If out of bounds
		 */
		inline PBObject<class_id, group_type> Get(std::array<pblong, sizeof...(dims)> pos)
			requires (sizeof...(dims) != 0)
		{
			this->AssertInside(pos);

			pbboolean is_null;
			pbobject obj = this->m_Session->GetObjectArrayItem(this->m_Array, pos.data(), is_null);
			return { this->m_Session, is_null ? 0 : obj };
		}
	#pragma endregion

	private:
		friend Type<PBArray>;

		/**
		 * Constructor used to get an array out of a value and acquire if needed.
		 *
		 * \param session	Current Session
		 * \param value		IPB_Value holding the Array
		 * \param acquire	Whether to take ownership of the IPB_Value
		 */
		PBArray(IPB_Session* session, IPB_Value* value, bool acquire)
			: IPBArray<dims...>(session, value, acquire)
		{ }
	};
}
