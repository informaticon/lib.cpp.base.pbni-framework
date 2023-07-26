#pragma once

#include "PBNumbers.h"
#include "PBDateTimes.h"
#include "PBString.h"
#include "PBBlob.h"


namespace Inf
{
	template <Helper::FixedString class_id, pbgroup_type group_type>
	class PBObject;

	template <typename Item, pblong... dims>
		requires (sizeof...(dims) <= 3 && !std::is_reference_v<Item> && !std::is_pointer_v<Item>)
	class PBArray;

	namespace Helper
	{
		template <typename T>
		struct is_pb_object : public std::false_type {};

		template <Helper::FixedString class_id, pbgroup_type group_type>
		struct is_pb_object<PBObject<class_id, group_type>> : public std::true_type {};

		template <typename T>
		inline constexpr bool is_pb_object_v = is_pb_object<T>::value;


		template <typename>
		struct is_pb_array : public std::false_type {};

		template <typename Item, pblong... dims>
		struct is_pb_array<PBArray<Item, dims...>> : public std::true_type {};

		template <typename T>
		inline constexpr bool is_pb_array_v = is_pb_array<T>::value;
	};


	/**
	 * Wrapper for simple Arrays.
	 *
	 * \tparam Item Type of the Array Items
	 * \tparam ...dims The Bounds of the Bounded Array, Unbounded Array if empty
	 */
	template <typename Item, pblong... dims>
		requires (sizeof...(dims) <= 3 && !std::is_reference_v<Item> && !std::is_pointer_v<Item>)
	class PBArray
	{
	public:
		struct Iterator
		{
			using iterator_category = std::input_iterator_tag;
			using difference_type = pblong;
			using value_type = Item;
			using pointer = Item;
			using reference = Item;

			Iterator(PBArray<Item, dims...>& array, pblong index)
				: m_Array(array), m_Index(index)
			{ }

			reference operator*() const { return m_Array.Get(m_Index); }
			pointer operator->() { return m_Array.Get(m_Index); }

			Iterator& operator++() { m_Index++; return *this; }  
			Iterator operator++(int) { Iterator m_Index = *this; ++(*this); return m_Index; }
			Iterator& operator--() { m_Index--; return *this; }  
			Iterator operator--(int) { Iterator m_Index = *this; --(*this); return m_Index; }

			friend bool operator== (const Iterator& a, const Iterator& b) { return a.m_Index == b.m_Index && (pbarray) a.m_Array == (pbarray) b.m_Array; };
			friend bool operator!= (const Iterator& a, const Iterator& b) { return a.m_Index != b.m_Index || (pbarray) a.m_Array != (pbarray) b.m_Array; };

		private:
			PBArray<value_type, dims...>& m_Array;
			pblong m_Index;
		};

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
			if constexpr (sizeof...(dims) != 0)
			{
				if (!IsNull())
					m_ArrayInfo = std::shared_ptr<PBArrayInfo>(m_Session->GetArrayInfo(m_Array), [=](PBArrayInfo* info) { m_Session->ReleaseArrayInfo(info); });
			}
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
				if constexpr (Helper::is_pb_object_v<Item>)
				{
					m_Array = m_Session->NewUnboundedObjectArray(Item::PBClass(m_Session));
				}
				else
				{
					m_Array = m_Session->NewUnboundedSimpleArray(Type<Item>::PBType);
				}
			}
			else
			{
				PBArrayInfo::ArrayBound bounds[] = { { dims, 1 }... };
				if constexpr (Helper::is_pb_object_v<Item>)
				{
					m_Array = m_Session->NewBoundedObjectArray(Item::PBClass(m_Session), sizeof...(dims), bounds);
				}
				else
				{
					m_Array = m_Session->NewBoundedSimpleArray(Type<Item>::PBType, sizeof...(dims), bounds);
				}

				m_ArrayInfo = std::shared_ptr<PBArrayInfo>(m_Session->GetArrayInfo(m_Array), [=](PBArrayInfo* info) { m_Session->ReleaseArrayInfo(info); });
			}

		}

	#pragma region UnboundedArray_Functions
		/**
		 * Sets an Item in an Unbounded Array.
		 * Copies if Item is string or blob.
		 *
		 * \param pos	The Position
		 * \param t		The Value to set from
		 *
		 * \throw Inf::PBNI_NullPointerException		If is Null
		 * \throw Inf::PBNI_IndexOutOfBoundsException	If out of bounds
		 * \throw Inf::PBNI_PowerBuilderException		If PowerBuilder function doesnt return PBX_SUCESS
		 */
		void Set(pblong pos, const Item& t)
			requires (sizeof...(dims) == 0)
		{
			AssertInside(pos, false);

			if (t.IsNull())
			{
				m_Session->SetArrayItemToNull(m_Array, &pos);
			}
			else
			{
				PBXRESULT res;
				if constexpr (Helper::is_pb_object_v<Item>)
				{
					res = m_Session->SetObjectArrayItem(m_Array, &pos, t.m_Object);
				}
				else
				{
					res = SetImpl<Item>(&pos, t);
				}

				if (res != PBX_SUCCESS)
					throw PBNI_PowerBuilderException(L"IPB_Session::Set<Type>ArrayItem for " + Type<Item>::GetPBName(L""), res);
			}
		}

		/**
		 * Retrieves an Item in an Unbounded Array.
		 * If Item is complex, it will return a reference.
		 *
		 * \param pos	The Position, starts with 1
		 * \return		The Value
		 *
		 * \throw Inf::PBNI_NullPointerException		If is Null
		 * \throw Inf::PBNI_IndexOutOfBoundsException	If out of bounds
		 */
		Item Get(pblong pos)
			requires (sizeof...(dims) == 0)
		{
			AssertInside(pos);

			if constexpr (Helper::is_pb_object_v<Item>)
			{
				pbboolean is_null = false;
				pbobject obj = m_Session->GetObjectArrayItem(m_Array, &pos, is_null);
				return { m_Session, is_null ? 0 : obj };
			}
			else
			{
				return GetImpl<Item>(&pos);
			}
		}
		/**
		 * Sets an Item in an Unbounded Array To Null.
		 *
		 * \param pos	The Position
		 *
		 * \throw Inf::PBNI_NullPointerException		If is Null
		 * \throw Inf::PBNI_IndexOutOfBoundsException	If out of bounds
		 * \throw Inf::PBNI_PowerBuilderException		If PowerBuilder function doesnt return PBX_SUCESS
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
		 * \throw Inf::PBNI_NullPointerException		If is Null
		 * \throw Inf::PBNI_IndexOutOfBoundsException	If out of bounds
		 */
		bool IsItemNull(pblong pos)
			requires (sizeof...(dims) == 0)
		{
			// No need to check upper bound
			AssertInside(pos, false);

			return m_Session->IsArrayItemNull(m_Array, &pos);
		}

		/**
		 * Creates new Iterator pointing to the first element
		 *
		 * \return		New Iterator
		 *
		 * \throw Inf::PBNI_NullPointerException		If is Null
		 */
		Iterator begin()
			requires (sizeof...(dims) == 0)
		{
			if (IsNull())
				throw PBNI_NullPointerException(L"PBArray");

			return { *this, 1 };
		}
		/**
		 * Creates new Iterator pointing to the current last + 1 element
		 *
		 * \return		New Iterator
		 *
		 * \throw Inf::PBNI_NullPointerException		If is Null
		 */
		Iterator end()
			requires (sizeof...(dims) == 0)
		{
			if (IsNull())
				throw PBNI_NullPointerException(L"PBArray");

			return { *this, Size() + 1 };
		}

	#pragma endregion

	#pragma region BoundedArray_Functions
		/**
		 * Sets an Item in a Bounded Array.
		 * Copies if Item is string or blob.
		 *
		 * \param pos	Array of Positions
		 * \param t		The Value to set from
		 *
		 * \throw Inf::PBNI_NullPointerException		If is Null
		 * \throw Inf::PBNI_IndexOutOfBoundsException	If out of bounds
		 * \throw Inf::PBNI_PowerBuilderException		If PowerBuilder function doesnt return PBX_SUCESS
		 */
		void Set(std::array<pblong, sizeof...(dims)> pos, const Item& t)
			requires (sizeof...(dims) != 0)
		{
			AssertInside(pos);

			if (t.IsNull())
			{
				m_Session->SetArrayItemToNull(m_Array, pos.data());
			}
			else
			{
				PBXRESULT res;
				if constexpr (Helper::is_pb_object_v<Item>)
				{
					res = m_Session->SetObjectArrayItem(m_Array, pos.data(), t.m_Object);
				}
				else
				{
					res = SetImpl<Item>(pos.data(), t);
				}

				if (res != PBX_SUCCESS)
					throw PBNI_PowerBuilderException(L"IPB_Session::Set<Type>ArrayItem for " + Type<Item>::GetPBName(L""), res);
			}
		}

		/**
		 * Retrieves an Item in a Bounded Array.
		 * If Item is complex, it will return a reference.
		 *
		 * \param pos	Array of Positions
		 * \return		The Value
		 *
		 * \throw Inf::PBNI_NullPointerException		If is Null
		 * \throw Inf::PBNI_IndexOutOfBoundsException	If out of bounds
		 */
		Item Get(std::array<pblong, sizeof...(dims)> pos)
			requires (sizeof...(dims) != 0)
		{
			AssertInside(pos);

			if constexpr (Helper::is_pb_object_v<Item>)
			{
				pbboolean is_null = false;
				pbobject obj = m_Session->GetObjectArrayItem(m_Array, pos.data(), is_null);
				return { m_Session, is_null ? 0 : obj };
			}
			else
			{
				return GetImpl<Item>(pos.data());
			}
		}

		/**
		 * Sets an Item in a Bounded Array To Null.
		 *
		 * \param pos	Array of Positions
		 *
		 * \throw Inf::PBNI_NullPointerException		If is Null
		 * \throw Inf::PBNI_IndexOutOfBoundsException	If out of bounds
		 * \throw Inf::PBNI_PowerBuilderException		If PowerBuilder function doesnt return PBX_SUCESS
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
		 * \throw Inf::PBNI_NullPointerException		If is Null
		 * \throw Inf::PBNI_IndexOutOfBoundsException	If out of bounds
		 */
		bool IsItemNull(std::array<pblong, sizeof...(dims)> pos)
			requires (sizeof...(dims) != 0)
		{
			AssertInside(pos);

			return m_Session->IsArrayItemNull(m_Array, pos);
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

		/**
		 * This conversion operator is currently the only way of getting the pbarray.
		 *
		 * \return	The pbarray used for PowerBuilder functions
		 */
		operator pbarray() const
		{
			return m_Array;
		}

	private:
		friend Type<PBArray>;

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
		 * \throw Inf::PBNI_NullPointerException		If is Null
		 * \throw Inf::PBNI_IndexOutOfBoundsException	If out of bounds
		 */
		void AssertInside(std::array<pblong, sizeof...(dims)> pos)
			requires (sizeof...(dims) != 0)
		{
			if (IsNull())
				throw PBNI_NullPointerException(L"PBBoundedArray");

			for (pbbyte i = 0; i < sizeof...(dims); i++)
			{
				if (m_ArrayInfo->bounds[i].lowerBound > pos[i] || pos[i] > m_ArrayInfo->bounds[i].upperBound)
					throw PBNI_IndexOutOfBoundsException(pos, Bounds(), i);
			}
		}

		/**
		 * Asserts whether a position is inside an Unbounded Array.
		 *
		 * \param pos					The Position
		 * \param check_upper_bound		Whether to Check if the Position is too big
		 *
		 * \throw Inf::PBNI_NullPointerException	If is Null
		 * \throw Inf::PBNI_IndexOutOfBoundsException		If out of bounds
		 */
		void AssertInside(pblong pos, bool check_upper_bound = true)
			requires (sizeof...(dims) == 0)
		{
			if (IsNull())
				throw PBNI_NullPointerException(L"PBUnboundedArray");

			if (pos < 1 || (check_upper_bound && pos > Size()))
				throw PBNI_IndexOutOfBoundsException(pos, Size());
		}


		template <typename T>
		inline PBXRESULT SetImpl(pblong* dim, const T t) = delete;
		template <typename T>
		inline T GetImpl(pblong* dim) const = delete;

		template<> inline PBXRESULT SetImpl<PBByte		>(pblong* dim, const PBByte		t) { return m_Session->SetByteArrayItem(m_Array, dim, t); }
		template<> inline PBXRESULT SetImpl<PBBoolean	>(pblong* dim, const PBBoolean	t) { return m_Session->SetCharArrayItem(m_Array, dim, t); }
		template<> inline PBXRESULT SetImpl<PBChar		>(pblong* dim, const PBChar		t) { return m_Session->SetCharArrayItem(m_Array, dim, t); }
		template<> inline PBXRESULT SetImpl<PBInt		>(pblong* dim, const PBInt		t) { return m_Session->SetIntArrayItem(m_Array, dim, t); }
		template<> inline PBXRESULT SetImpl<PBUint		>(pblong* dim, const PBUint		t) { return m_Session->SetUintArrayItem(m_Array, dim, t); }
		template<> inline PBXRESULT SetImpl<PBLong		>(pblong* dim, const PBLong		t) { return m_Session->SetLongArrayItem(m_Array, dim, t); }
		template<> inline PBXRESULT SetImpl<PBUlong		>(pblong* dim, const PBUlong	t) { return m_Session->SetUlongArrayItem(m_Array, dim, t); }
		template<> inline PBXRESULT SetImpl<PBLongLong	>(pblong* dim, const PBLongLong	t) { return m_Session->SetLongLongArrayItem(m_Array, dim, t); }
		template<> inline PBXRESULT SetImpl<PBReal		>(pblong* dim, const PBReal		t) { return m_Session->SetRealArrayItem(m_Array, dim, t); }
		template<> inline PBXRESULT SetImpl<PBDouble	>(pblong* dim, const PBDouble	t) { return m_Session->SetDoubleArrayItem(m_Array, dim, t); }
		template<> inline PBXRESULT SetImpl<PBDecimal	>(pblong* dim, const PBDecimal	t) { return m_Session->SetDecArrayItem(m_Array, dim, t.m_Decimal); }
		template<> inline PBXRESULT SetImpl<PBTime		>(pblong* dim, const PBTime		t) { return m_Session->SetTimeArrayItem(m_Array, dim, t.m_Time); }
		template<> inline PBXRESULT SetImpl<PBDate		>(pblong* dim, const PBDate		t) { return m_Session->SetDateArrayItem(m_Array, dim, t.m_Date); }
		template<> inline PBXRESULT SetImpl<PBDateTime	>(pblong* dim, const PBDateTime	t) { return m_Session->SetDateTimeArrayItem(m_Array, dim, t.m_DateTime); }
		template<> inline PBXRESULT SetImpl<PBString	>(pblong* dim, const PBString	t) { return m_Session->SetPBStringArrayItem(m_Array, dim, t.m_String); }
		template<> inline PBXRESULT SetImpl<PBBlob		>(pblong* dim, const PBBlob		t) { return m_Session->SetBlobArrayItem(m_Array, dim, t.m_Blob); }

		template<> inline PBByte		GetImpl<PBByte		>(pblong* dim) const { pbboolean is_null = false; pbbyte pb_byte			= m_Session->GetByteArrayItem(m_Array, dim, is_null);		return is_null ? PBByte()		: PBByte(pb_byte); }
		template<> inline PBBoolean		GetImpl<PBBoolean	>(pblong* dim) const { pbboolean is_null = false; pbboolean pb_boolean		= m_Session->GetCharArrayItem(m_Array, dim, is_null);		return is_null ? PBBoolean()	: PBBoolean(pb_boolean); }
		template<> inline PBChar		GetImpl<PBChar		>(pblong* dim) const { pbboolean is_null = false; pbchar pb_char			= m_Session->GetCharArrayItem(m_Array, dim, is_null);		return is_null ? PBChar()		: PBChar(pb_char); }
		template<> inline PBInt			GetImpl<PBInt		>(pblong* dim) const { pbboolean is_null = false; pbint pb_int				= m_Session->GetIntArrayItem(m_Array, dim, is_null);		return is_null ? PBInt()		: PBInt(pb_int); }
		template<> inline PBUint		GetImpl<PBUint		>(pblong* dim) const { pbboolean is_null = false; pbuint pb_uint			= m_Session->GetUintArrayItem(m_Array, dim, is_null);		return is_null ? PBUint()		: PBUint(pb_uint); }
		template<> inline PBLong		GetImpl<PBLong		>(pblong* dim) const { pbboolean is_null = false; pblong pb_long			= m_Session->GetLongArrayItem(m_Array, dim, is_null);		return is_null ? PBLong()		: PBLong(pb_long); }
		template<> inline PBUlong		GetImpl<PBUlong		>(pblong* dim) const { pbboolean is_null = false; pbulong pb_ulong			= m_Session->GetUlongArrayItem(m_Array, dim, is_null);		return is_null ? PBUlong()		: PBUlong(pb_ulong); }
		template<> inline PBLongLong	GetImpl<PBLongLong	>(pblong* dim) const { pbboolean is_null = false; pblonglong pb_longlong	= m_Session->GetLongLongArrayItem(m_Array, dim, is_null);	return is_null ? PBLongLong()	: PBLongLong(pb_longlong); }
		template<> inline PBReal		GetImpl<PBReal		>(pblong* dim) const { pbboolean is_null = false; pbreal pb_real			= m_Session->GetRealArrayItem(m_Array, dim, is_null);		return is_null ? PBReal()		: PBReal(pb_real); }
		template<> inline PBDouble		GetImpl<PBDouble	>(pblong* dim) const { pbboolean is_null = false; pbdouble pb_double		= m_Session->GetDoubleArrayItem(m_Array, dim, is_null);		return is_null ? PBDouble()		: PBDouble(pb_double); }
		template<> inline PBDecimal		GetImpl<PBDecimal	>(pblong* dim) const { pbboolean is_null = false; pbdec pb_dec				= m_Session->GetDecArrayItem(m_Array, dim, is_null);		return { m_Session, is_null ? 0 : pb_dec }; }
		template<> inline PBTime		GetImpl<PBTime		>(pblong* dim) const { pbboolean is_null = false; pbtime pb_time			= m_Session->GetTimeArrayItem(m_Array, dim, is_null);		return { m_Session, is_null ? 0 : pb_time }; }
		template<> inline PBDate		GetImpl<PBDate		>(pblong* dim) const { pbboolean is_null = false; pbdate pb_date			= m_Session->GetDateArrayItem(m_Array, dim, is_null);		return { m_Session, is_null ? 0 : pb_date }; }
		template<> inline PBDateTime	GetImpl<PBDateTime	>(pblong* dim) const { pbboolean is_null = false; pbdatetime pb_datetime	= m_Session->GetDateTimeArrayItem(m_Array, dim, is_null);	return { m_Session, is_null ? 0 : pb_datetime }; }
		template<> inline PBString		GetImpl<PBString	>(pblong* dim) const { pbboolean is_null = false; pbstring pb_string		= m_Session->GetStringArrayItem(m_Array, dim, is_null);		return { m_Session, is_null ? 0 : pb_string }; }
		template<> inline PBBlob		GetImpl<PBBlob		>(pblong* dim) const { pbboolean is_null = false; pbblob pb_blob			= m_Session->GetBlobArrayItem(m_Array, dim, is_null);		return { m_Session, is_null ? 0 : pb_blob }; }
	};
}

