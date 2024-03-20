#pragma once

#include "Errors.h"


namespace Inf
{
    /**
     * Wrapper for Enum type.
     *
     * \tparam class_id     ID of Group and Class
     * \tparam group_type   The Group Type used by PowerBuilder (struct, userobject, ...)
     */
    template <Helper::FixedString name>
    class PBEnum
    {
    public:
        static constexpr Helper::FixedString _name = name;

        /**
         * Creates a new Enum
         *
         * \param session       Current Session
         * \param name          The Class name of the Enum
         * \param value         Value of the enum, without a '!' at the end
         */
        PBEnum(IPB_Session* session, std::wstring value)
            : PBEnum(session, session->GetEnumItemValue(_name.data, value.c_str()))
        { }

        /**
         * Creates a new Wrapper for an already existing Enum
         * Will be Null if value is -1.
         *
         * \param session       Current Session
         * \param name          The Class name of the Enum
         * \param value         Value of the enum
         *
         * \throw Inf::PBNI_Exception   If the Group or Class cannot be found
         */
        PBEnum(IPB_Session* session, pblong value)
            : m_Session(session), m_Value(value)
        { }

        /**
         * Creates a new Null Enum
         *
         * \param session       Current Session
         * \param name          The Class name of the Enum
         * \param value         Value of the enum, without a '!' at the end
         */
        PBEnum(IPB_Session* session)
            : PBEnum(session, -1)
        { }


        /**
         * Whether the enum is Null.
         *
         * \return Is Null
         */
        bool IsNull() const
        {
            return m_Value == -1;
        }

        /**
         * Set the Object to Null
         */
        void SetNull()
        {
            m_Value = -1;
        }

        /**
         * Get the name of the Value
         * 
         * \throws PBNI_InvalidEnumException
         *
         * \return  Class name
         */
        std::wstring GetValueName() const
        {
            if (IsNull())
                throw PBNI_NullPointerException(_name.data);

            LPCTSTR value_freeable = m_Session->GetEnumItemName(_name.data, m_Value);
            if (!value_freeable)
                throw PBNI_InvalidEnumException(_name.data, m_Value);

            std::wstring value = value_freeable;
            m_Session->ReleaseString(value_freeable);
            return value;
        }

        /**
         * This conversion operator is currently the only way of getting the pblong value
         *
         * \return  The pbobject used for PowerBuilder functions
         */
        operator pblong() const
        {
            if (IsNull())
                throw PBNI_NullPointerException(_name.data);

            return m_Value;
        }
    private:
        IPB_Session* m_Session;
        pblong m_Value;
    };
}
