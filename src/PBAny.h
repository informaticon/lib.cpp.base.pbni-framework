#pragma once

#include <any>

#include "Helper.h"
#include "PBValue.h"


namespace Inf
{
    /**
     * This is a Wrapper for IPB_Value.
     */
    class PBAny {
    public:
        enum AnyType : pbuint
        {
            Notype = pbvalue_notype,
            Int = pbvalue_int,
            Long = pbvalue_long,
            Real = pbvalue_real,
            Double = pbvalue_double,
            Dec = pbvalue_dec,
            String = pbvalue_string,
            Boolean = pbvalue_boolean,
            Uint = pbvalue_uint,
            Ulong = pbvalue_ulong,
            Blob = pbvalue_blob,
            Date = pbvalue_date,
            Time = pbvalue_time,
            DateTime = pbvalue_datetime,
            Char = pbvalue_char,
            Longlong = pbvalue_longlong,
            Byte = pbvalue_byte,
        
            Null = 200,
            Object = 201
        };

        /**
         * Creates a PBAny holding Null
         * 
         * \param session   Current session
         */
        PBAny(IPB_Session* session)
            : m_Session(session), m_Type(AnyType::Null)
        { }

        /**
         * Creates a PBAny holding the specified value
         * 
         * \param session   Current session
         * \param t         The thing that PBAny will be
         */
        template<typename T>
        PBAny(IPB_Session* session, const T& t)
            : PBAny(session)
        {
            Set(t);
        }
        
        /**
         * Creates a Wrapper to an already existing IPB_Value.
         * Will be Null if value is 0.
         * 
         * \param session   Current session
         * \param value     A value
         */
        PBAny(IPB_Session* session, IPB_Value* value, bool acquire);


        /**
         * Writes the PBAny to an IPB_Value*
         * 
         * \param value     The value to be written to
         */
        PBXRESULT ToValue(IPB_Value* value) const;

        /**
         * Checks whether the pbany is Null
         */
        bool IsNull() const
        {
            return m_Type == AnyType::Null;
        }

        /**
         * Sets itself to Null and releases the stored variable
         */
        void SetToNull()
        {
            m_Value.reset();
            m_IsArray = false;
            m_Type = AnyType::Null;
        }

        /**
         * Returns the type of the IPB_Value
         * To compare to a Type you can use Inf::Type<PBInt>::PBType
         */
        AnyType GetType() const
        {
            return m_Type;
        }
        
        /**
         * Returns whether the PBAny is holding an array
         */
        bool IsArray() const
        {
            return m_IsArray;
        }

        /**
         * This Function returns whether the IPB_Value can be used to retrieve the specified type.
         *
         * \return          true if its okay to convert, false otherwise.
         */
        template <typename T>
        bool Is() const
        {
            if constexpr (Helper::is_pb_array_v<T>)
            {
                if (!m_IsArray)
                    return false;
            
                using ItemType = T::_Item;
                if constexpr (Helper::is_pb_object_v<ItemType>)
                    return m_Type == AnyType::Object && m_Class == ItemType::PBClass(m_Session);
                else
                    return m_Type == (AnyType) Type<ItemType>::PBType;
            }
            else if constexpr (Helper::is_pb_object_v<T>)
                return m_Type == AnyType::Object && m_Class == T::PBClass(m_Session);
            else
                return m_Type == (AnyType) Type<T>::PBType;
        }

        /**
         * This Function Retrieves the specified Type from an IPB_Value.
         *
         * \param acquire   Whether or not to take ownership of the type, only relevant for complex types. The Type will free itself
         * \return          The returned Type
         */
        template <typename T>
        inline T Get()
        {
            if (!Is<T>())
                throw Inf::PBNI_Exception(L"Tried to cast a PBAny to the wrong Type");
            
            if constexpr (Helper::is_pb_array_v<T>)
                return { m_Session, IsNull() ? 0 : (pbarray) std::any_cast<PBArray<PBAny>>(m_Value) };
            else if constexpr (Helper::is_pb_object_v<T>)
                return { m_Session, IsNull() ? 0 : (pbobject) std::any_cast<PBObject<L"">>(m_Value) };
            else
            {
                if (IsNull())
                    return GetNulled(Type<T>());

                return std::any_cast<T>(m_Value);
            }
        }

        /**
         * This sets a value to a specified Type.
         *
         * \param t         Type to set Value to
         */
        template <typename T>
        inline void Set(const T& t)
        {
            if (t.IsNull())
            {
                m_Type = AnyType::Null;
                m_Value.reset();
                return;
            }

            m_IsArray = false;
            if constexpr (Helper::is_pb_array_v<T>)
            {
                m_IsArray = true;
                m_Value = PBArray<PBAny>(m_Session, (pbarray) t);

                using ItemType = T::_Item;
                if constexpr (Helper::is_pb_object_v<ItemType>)
                    m_Type = AnyType::Object;
                else
                    m_Type = (AnyType) Type<ItemType>::PBType;
            }
            else if constexpr (Helper::is_pb_object_v<T>)
            {
                m_Type = AnyType::Object;
                m_Value = PBObject<L"">(m_Session, t);
            }
            else
            {
                m_Type = (AnyType) Type<T>::PBType;
                m_Value = t;
            }
        }


    private:
        template <typename PBT, pblong... dims>
            requires (sizeof...(dims) <= 3 && !std::is_reference_v<PBT> && !std::is_pointer_v<PBT>)
        friend class PBArray;
        template <Helper::FixedString class_id, pbgroup_type group_type>
        friend class PBObject;

        std::any m_Value;

        AnyType m_Type = AnyType::Notype;
        bool m_IsArray = false;
        pbclass m_Class = 0;

        IPB_Session* m_Session;

        inline PBByte     GetNulled(Type<PBByte    >) { return PBByte(); }
        inline PBBoolean  GetNulled(Type<PBBoolean >) { return PBBoolean(); }
        inline PBChar     GetNulled(Type<PBChar    >) { return PBChar(); }
        inline PBInt      GetNulled(Type<PBInt     >) { return PBInt(); }
        inline PBUint     GetNulled(Type<PBUint    >) { return PBUint(); }
        inline PBLong     GetNulled(Type<PBLong    >) { return PBLong(); }
        inline PBUlong    GetNulled(Type<PBUlong   >) { return PBUlong(); }
        inline PBLongLong GetNulled(Type<PBLongLong>) { return PBLongLong(); }
        inline PBReal     GetNulled(Type<PBReal    >) { return PBReal(); }
        inline PBDouble   GetNulled(Type<PBDouble  >) { return PBDouble(); }
        inline PBDecimal  GetNulled(Type<PBDecimal >) { return { m_Session, 0 }; }
        inline PBTime     GetNulled(Type<PBTime    >) { return { m_Session, 0 }; }
        inline PBDate     GetNulled(Type<PBDate    >) { return { m_Session, 0 }; }
        inline PBDateTime GetNulled(Type<PBDateTime>) { return { m_Session, 0 }; }
        inline PBString   GetNulled(Type<PBString  >) { return { m_Session, (pbstring) 0 }; }
        inline PBBlob     GetNulled(Type<PBBlob    >) { return { m_Session, 0 }; }
    };
}