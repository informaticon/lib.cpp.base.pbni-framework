#pragma once

#include "Helper.h"
#include "PBTypes.h"


namespace Inf
{
    namespace Helper
    {
        /**
         * This is a Wrapper for IPB_Value.
         */
        class PBValue
        {
        public:
            /**
             * Creates a Wrapper to an already existing IPB_Value.
             * Will be Null if value is 0.
             *
             * \param session   Current session
             * \param value     A value
             */
            PBValue(IPB_Session* session, IPB_Value* value)
                : m_Session(session), m_Value(value)
            { }


            /**
             * This Function returns whether the IPB_Value can be used to retrieve the specified type.
             *
             * \return          true if its okay to convert, false otherwise.
             */
            template <typename T>
            bool Is() const
            {
                if constexpr (std::is_same_v<PBAny, T>)
                    return true;

                else if constexpr (Helper::is_pb_array_v<T>)
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
                            is_correct =
                                info->arrayType == info->UnboundedArray &&
                                Helper::IsPBBaseClass(m_Session, T::_Item::PBClass(m_Session), info->valueType);
                        }
                        else
                        {
                            is_correct = 
                                info->arrayType == info->BoundedArray &&
                                info->itemGroup != 0 &&
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

                    return Helper::IsPBBaseClass(m_Session, T::PBClass(m_Session), m_Value->GetClass());
                }
                else if constexpr (std::is_same_v<DynPBObject, T>)
                {
                    return m_Value->IsObject();
                }
                else
                {
                    return m_Value->GetType() == pbvalue_any || m_Value->GetType() == Type<T>::PBType;
                }
            }

            /**
             * This Function Retrieves the specified Type from an IPB_Value.
             *
             * \param acquire   Whether or not to take ownership of the type, only relevant for complex types. The Type will free itself
             * \return          The returned Type
             */
            template <typename T>
            inline T Get(bool acquire = false) const
            {
                if constexpr (Helper::is_pb_array_v<T>)
                    return { m_Session, m_Value, acquire };
                else if constexpr (Helper::is_pb_object_v<T>)
                    return { m_Session, m_Value->GetObject() };
                else if constexpr (std::is_same_v<T, DynPBObject>)
                    return { m_Session, m_Value->GetObject(), m_Value->GetClass() };
                else if constexpr (std::is_same_v<T, PBAny>)
                    return { m_Session, m_Value, acquire };
                else
                    return GetImpl(Type<T>(), acquire);
            }

            /**
             * This sets a value to a specified Type.
             *
             * \param t         Type to set Value to
             */
            template <typename T>
            inline PBXRESULT Set(const T& t)
            {
                if (t.IsNull())
                    return PBX_OK;

                if constexpr (Helper::is_pb_array_v<T>)
                    return m_Value->SetArray(t);
                else if constexpr (Helper::is_pb_object_v<T>)
                    return m_Value->SetObject(t);
                else if constexpr (std::is_same_v<T, DynPBObject>)
                    return m_Value->SetObject(t);
                else if constexpr (std::is_same_v<T, PBAny>)
                    return t.ToValue(m_Value);
                else
                    return SetImpl(t);
            }

        private:
            IPB_Session* m_Session;
            IPB_Value* m_Value;

            PBValue(IPB_Session* session, IPB_Value* value, bool acquire);

            inline PBByte     GetImpl(Type<PBByte    >, bool acquire) const { return m_Value->IsNull() ? PBByte() : PBByte(m_Value->GetByte()); }
            inline PBBoolean  GetImpl(Type<PBBoolean >, bool acquire) const { return m_Value->IsNull() ? PBBoolean() : PBBoolean(m_Value->GetBool()); }
            inline PBChar     GetImpl(Type<PBChar    >, bool acquire) const { return m_Value->IsNull() ? PBChar() : PBChar(m_Value->GetChar()); }
            inline PBInt      GetImpl(Type<PBInt     >, bool acquire) const { return m_Value->IsNull() ? PBInt() : PBInt(m_Value->GetInt()); }
            inline PBUint     GetImpl(Type<PBUint    >, bool acquire) const { return m_Value->IsNull() ? PBUint() : PBUint(m_Value->GetUint()); }
            inline PBLong     GetImpl(Type<PBLong    >, bool acquire) const { return m_Value->IsNull() ? PBLong() : PBLong(m_Value->GetLong()); }
            inline PBUlong    GetImpl(Type<PBUlong   >, bool acquire) const { return m_Value->IsNull() ? PBUlong() : PBUlong(m_Value->GetUlong()); }
            inline PBLongLong GetImpl(Type<PBLongLong>, bool acquire) const { return m_Value->IsNull() ? PBLongLong() : PBLongLong(m_Value->GetLongLong()); }
            inline PBReal     GetImpl(Type<PBReal    >, bool acquire) const { return m_Value->IsNull() ? PBReal() : PBReal(m_Value->GetReal()); }
            inline PBDouble   GetImpl(Type<PBDouble  >, bool acquire) const { return m_Value->IsNull() ? PBDouble() : PBDouble(m_Value->GetDouble()); }
            inline PBDecimal  GetImpl(Type<PBDecimal >, bool acquire) const { return { m_Session, m_Value, acquire }; }
            inline PBTime     GetImpl(Type<PBTime    >, bool acquire) const { return { m_Session, m_Value, acquire }; }
            inline PBDate     GetImpl(Type<PBDate    >, bool acquire) const { return { m_Session, m_Value, acquire }; }
            inline PBDateTime GetImpl(Type<PBDateTime>, bool acquire) const { return { m_Session, m_Value, acquire }; }
            inline PBString   GetImpl(Type<PBString  >, bool acquire) const { return { m_Session, m_Value, acquire }; }
            inline PBBlob     GetImpl(Type<PBBlob    >, bool acquire) const { return { m_Session, m_Value, acquire }; }

            inline PBXRESULT SetImpl(const PBByte&     value) { return m_Value->SetByte(value); }
            inline PBXRESULT SetImpl(const PBBoolean&  value) { return m_Value->SetBool(value); }
            inline PBXRESULT SetImpl(const PBChar&     value) { return m_Value->SetChar(value); }
            inline PBXRESULT SetImpl(const PBInt&      value) { return m_Value->SetInt(value); }
            inline PBXRESULT SetImpl(const PBUint&     value) { return m_Value->SetUint(value); }
            inline PBXRESULT SetImpl(const PBLong&     value) { return m_Value->SetLong(value); }
            inline PBXRESULT SetImpl(const PBUlong&    value) { return m_Value->SetUlong(value); }
            inline PBXRESULT SetImpl(const PBLongLong& value) { return m_Value->SetLongLong(value); }
            inline PBXRESULT SetImpl(const PBReal&     value) { return m_Value->SetReal(value); }
            inline PBXRESULT SetImpl(const PBDouble&   value) { return m_Value->SetDouble(value); }
            inline PBXRESULT SetImpl(const PBDecimal&  value) { return m_Value->SetDecimal(value); }
            inline PBXRESULT SetImpl(const PBTime&     value) { return m_Value->SetTime(value); }
            inline PBXRESULT SetImpl(const PBDate&     value) { return m_Value->SetDate(value); }
            inline PBXRESULT SetImpl(const PBDateTime& value) { return m_Value->SetDateTime(value); }
            inline PBXRESULT SetImpl(const PBString&   value) { return m_Value->SetPBString(value); }
            inline PBXRESULT SetImpl(const PBBlob&     value) { return m_Value->SetBlob(value); }
        };
    }
}