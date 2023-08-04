#pragma once

#include "PBTypes.h"
#include "PBArray.h"


namespace Inf
{
	/**
	 * This is a Wrapper for IPB_Value.
	 */
	class PBAny {
	public:
		/**
		 * Creates a Wrapper to an already existing pbtime.
		 * Will be Null if time is 0.
		 * 
		 * \param session	Current session
		 * \param value		A value
		 */
		PBAny(IPB_Session* session, IPB_Value* value)
			: m_Session(session), m_Value(value)
		{ }

		/**
		 * Checks whether the pbtime is Null
		 */
		bool IsNull() const
        {
			return m_Value->IsNull();
        }
		/**
		 * Sets the pbtime to Null.
		 */
		void SetToNull()
		{
			m_Value->SetToNull();
		}

		/**
		 * Check if the type is a reference
		 */
		bool IsRef()
		{
			return m_Value->IsByRef();
		}

		/**
		 * Check if the type is a readonly
		 */
		bool IsReadOnly()
		{
			return m_Value->IsReadOnly();
		}

		/**
		 * Returns the type of the IPB_Value
		 * To compare you can use Inf::Type<PBInt>::PBType
		 */
		pbuint GetType()
		{
			return m_Value->GetType();
		}

		/**
		 * This Function returns whether the IPB_Value can be used to retrieve the specified type.
		 *
		 * \return			true if its okay to convert, false otherwise.
		 */
		template <typename T>
		bool Is() {
			if constexpr (std::is_same_v<PBAny, T>)
			{
				return true;
			}
			if constexpr (Helper::is_pb_array_v<T>)
			{
				if (!m_Value->IsArray())
					return false;
				if (m_Value->IsNull())
					return true;

				bool is_correct = false;

				PBArrayInfo* info = m_Session->GetArrayInfo(m_Value->GetArray());
			
				using ItemType = T::_Item;
				if constexpr (Helper::is_pb_object_v<ItemType>)
				{
					if constexpr (T::_dims.size() == 0)
					{
						is_correct = info->arrayType == info->UnboundedArray && info->itemGroup != 0;
					}
					else
					{
						is_correct = \
							info->arrayType == info->BoundedArray && \
							info->itemGroup != 0 && \
							info->numDimensions == T::_dims.size();

						for (uint8_t i = 0; i < T::_dims.size(); i++)
							is_correct = is_correct && info->bounds[i].upperBound - info->bounds[i++].lowerBound == T::_dims[i];
					}
				}
				else
				{

					if constexpr (T::_dims.size() == 0)
					{
						is_correct = info->arrayType == info->UnboundedArray && info->valueType == Type<ItemType>::PBType;
					}
					else
					{
						is_correct = \
							info->arrayType == info->BoundedArray && \
							info->valueType == Type<ItemType>::PBType && \
							info->numDimensions == T::_dims.size();
							
						for (uint8_t i = 0; i < T::_dims.size(); i++)
							is_correct = is_correct && info->bounds[i].upperBound - info->bounds[i++].lowerBound == T::_dims[i];
					}
				}

				m_Session->ReleaseArrayInfo(info);
				return is_correct;
			}
			else if constexpr (Helper::is_pb_object_v<T>)
			{
				if (!m_Value->IsObject())
					return false;
				if (m_Value->IsNull())
					return true;
				
				// TODO works?
				return m_Value->GetClass() == T::PBClass(m_Session);
			}
			else
			{
				return m_Value->GetType() == Type<T>::PBType;
			}
		}

		/**
		 * This Function Retrieves the specified Type from an IPB_Value.
		 *
		 * \param acquire	Whether or not to take ownership of the type, only relevant for complex types. The Type will free itself
		 * \return			The returned Type
		 */
		template <typename T>
		inline T Get(bool acquire = false)
		{
			if constexpr (Helper::is_pb_array_v<T>)
			{
				return { m_Session, m_Value, acquire };
			}
			else if constexpr (Helper::is_pb_object_v<T>)
			{
				// TODO acquire
				return { m_Session, m_Value->GetObject() };
			}
			else
			{
				return GetImpl<T>(acquire);
			}
		}

		/**
		 * This sets a value to a specified Type.
		 *
		 * \param t			Type to set Value to
		 */
		template <typename T>
		inline PBXRESULT Set(const T& t)
		{
			if (t.IsNull())
				return m_Value->SetToNull();

			if constexpr (Helper::is_pb_array_v<T>)
			{
				return m_Value->SetArray(t);
			}
			else if constexpr (Helper::is_pb_object_v<T>)
			{
				return m_Value->SetObject(t);
			}
			else
			{
				return SetImpl(t);
			}
		}

	private:
		template <typename T>
		friend struct Type;
		template <typename PBT, pblong... dims>
			requires (sizeof...(dims) <= 3 && !std::is_reference_v<PBT> && !std::is_pointer_v<PBT>)
		friend class PBArray;
		template <Helper::FixedString class_id, pbgroup_type group_type>
		friend class PBObject;

		IPB_Session* m_Session;
		IPB_Value* m_Value;

		PBAny(IPB_Session* session, IPB_Value* value, bool acquire);

		template <typename T>
		inline T GetImpl(bool acquire) = delete;
		template<> inline PBByte GetImpl(bool acquire) { return m_Value->IsNull() ? PBByte() : PBByte(m_Value->GetByte()); }
		template<> inline PBBoolean GetImpl(bool acquire) { return m_Value->IsNull() ? PBBoolean() : PBBoolean(m_Value->GetBool()); }
		template<> inline PBChar GetImpl(bool acquire) { return m_Value->IsNull() ? PBChar() : PBChar(m_Value->GetChar()); }
		template<> inline PBInt GetImpl(bool acquire) { return m_Value->IsNull() ? PBInt() : PBInt(m_Value->GetInt()); }
		template<> inline PBUint GetImpl(bool acquire) { return m_Value->IsNull() ? PBUint() : PBUint(m_Value->GetUint()); }
		template<> inline PBLong GetImpl(bool acquire) { return m_Value->IsNull() ? PBLong() : PBLong(m_Value->GetLong()); }
		template<> inline PBUlong GetImpl(bool acquire) { return m_Value->IsNull() ? PBUlong() : PBUlong(m_Value->GetUlong()); }
		template<> inline PBLongLong GetImpl(bool acquire) { return m_Value->IsNull() ? PBLongLong() : PBLongLong(m_Value->GetLongLong()); }
		template<> inline PBReal GetImpl(bool acquire) { return m_Value->IsNull() ? PBReal() : PBReal(m_Value->GetReal()); }
		template<> inline PBDouble GetImpl(bool acquire) { return m_Value->IsNull() ? PBDouble() : PBDouble(m_Value->GetDouble()); }
		template<> inline PBDecimal GetImpl(bool acquire) { return { m_Session, m_Value, acquire }; }
		template<> inline PBTime GetImpl(bool acquire) { return { m_Session, m_Value, acquire }; }
		template<> inline PBDate GetImpl(bool acquire) { return { m_Session, m_Value, acquire }; }
		template<> inline PBDateTime GetImpl(bool acquire) { return { m_Session, m_Value, acquire }; }
		template<> inline PBString GetImpl(bool acquire) { return { m_Session, m_Value, acquire }; }
		template<> inline PBBlob GetImpl(bool acquire) { return { m_Session, m_Value, acquire }; }
		template<> inline PBAny GetImpl(bool acquire) { return { m_Session, m_Value }; }

		template <typename T>
		inline PBXRESULT SetImpl(const T& t) = delete;
		template<> inline PBXRESULT SetImpl(const PBByte& value) { return m_Value->SetByte(value); }
		template<> inline PBXRESULT SetImpl(const PBBoolean& value) { return m_Value->SetBool(value); }
		template<> inline PBXRESULT SetImpl(const PBChar& value) { return m_Value->SetChar(value); }
		template<> inline PBXRESULT SetImpl(const PBInt& value) { return m_Value->SetInt(value); }
		template<> inline PBXRESULT SetImpl(const PBUint& value) { return m_Value->SetUint(value); }
		template<> inline PBXRESULT SetImpl(const PBLong& value) { return m_Value->SetLong(value); }
		template<> inline PBXRESULT SetImpl(const PBUlong& value) { return m_Value->SetUlong(value); }
		template<> inline PBXRESULT SetImpl(const PBLongLong& value) { return m_Value->SetLongLong(value); }
		template<> inline PBXRESULT SetImpl(const PBReal& value) { return m_Value->SetReal(value); }
		template<> inline PBXRESULT SetImpl(const PBDouble& value) { return m_Value->SetDouble(value); }
		template<> inline PBXRESULT SetImpl(const PBDecimal& value) { return m_Value->SetDecimal(value); }
		template<> inline PBXRESULT SetImpl(const PBTime& value) { return m_Value->SetTime(value); }
		template<> inline PBXRESULT SetImpl(const PBDate& value) { return m_Value->SetDate(value); }
		template<> inline PBXRESULT SetImpl(const PBDateTime& value) { return m_Value->SetDateTime(value); }
		template<> inline PBXRESULT SetImpl(const PBString& value) { return m_Value->SetPBString(value); }
		template<> inline PBXRESULT SetImpl(const PBBlob& value) { return m_Value->SetBlob(value); }
		template<> inline PBXRESULT SetImpl(const PBAny& value) { m_Value = value.m_Value; return PBX_SUCCESS; }
	};
}