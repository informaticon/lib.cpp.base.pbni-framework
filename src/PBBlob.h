#pragma once

#include <type_traits>
#include <stdint.h>

#include "PBString.h"


namespace Inf
{
    /**
     * Small Wrapper for pbblob.
     */
    class PBBlob
    {
    public:
        /**
         * Creates a Wrapper to an already existing pbblob.
         * Will be Null if blob is 0.
         *
         * \param session   Current session
         * \param blob      The exsiting pbblob or 0
         */
        PBBlob(IPB_Session* session, pbblob blob);
        /**
         * Creates a new pbblob by copying the provided data.
         *
         * \param session   Current Session
         * \param data      The data to copy
         * \param size      The size of the data in bytes
         */
        PBBlob(IPB_Session* session, const pbbyte* data, pblong size);

        /**
         * Copies the Data to PowerBuilder. Creates a new Blob if Null.
         *
         * \param data  Pointer to the Data
         * \param size  Size of the Data
         */
        void SetData(const pbbyte* data, pblong size);
        /**
         * Retrieves a Pointer to the Raw Data.
         *
         * \return  Pointer to the PowerBuilder Data
         *
         * \throw Inf::PBNI_NullPointerException if Null
         */
        pbbyte* GetData() const;
        /**
         * Gets the size from PowerBuilder.
         * 
         * \return  Size in Bytes
         * 
         * \throw Inf::PBNI_NullPointerException if Null
         */
        pblong Size() const;

        /**
         * Copies the Vector to PowerBuilder. Creates a new Blob if Null.
         *
         * \param from  Vector containing the data to be copied
         */
        void FromVector(const std::vector<pbbyte>& from);
        /**
         * Copies the data from PowerBuilder to a Vector.
         *
         * \return  Newly created Vector
         *
         * \throw Inf::PBNI_NullPointerException if Null
         */
        std::vector<pbbyte> ToVector() const;

        /**
         * Checks whether pbblob is Null.
         * 
         * \return Is Null
         */
        bool IsNull() const;
        /**
         * Sets pbblob to Null.
         */
        void SetToNull();

        /**
         * Retrieve the private PB Reference
         */
        operator pbblob() const {
            return m_Blob;
        }

    private:
        friend class PBAny;
        template <typename PBT, pblong... dims>
            requires (sizeof...(dims) <= 3 && !std::is_reference_v<PBT> && !std::is_pointer_v<PBT>)
        friend class PBArray;
        template <Helper::FixedString class_id, pbgroup_type group_type>
        friend class PBObject;

        pbblob m_Blob;
        IPB_Session* m_Session;
        std::shared_ptr<Helper::AcquiredValue> m_AcquiredValue;

        PBBlob(IPB_Session* session, IPB_Value* value, bool acquire);
    };
}
