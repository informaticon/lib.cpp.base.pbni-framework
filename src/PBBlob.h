#pragma once

#include <type_traits>
#include <stdint.h>

#include <pbext.h>

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
		 * \param session	Current session
		 * \param blob		The exsiting pbblob or 0
		 */
		PBBlob(IPB_Session* session, pbblob blob);
		/**
		 * Creates a new pbblob.
		 *
		 * \param session	Current Session
		 */
		PBBlob(IPB_Session* session, pbbyte* data, pblong size);

		/**
		 * Copies the Data to PowerBuilder. Creates a new Blob if Null.
		 *
		 * \param data	Pointer to the Data
		 * \param size	Size of the Data
		 */
		void SetData(pbbyte* data, pblong size);
		/**
		 * Retrieves a Pointer to the Raw Data.
		 *
		 * \return	Pointer to the PowerBuilder Data
		 *
		 * \throw Inf::PBNI_NullPointerException if Null
		 */
		pbbyte* GetData() const;
		/**
		 * Gets the size from PowerBuilder.
		 * 
		 * \return	Size in Bytes
		 * 
		 * \throw Inf::PBNI_NullPointerException if Null
		 */
		pblong Size() const;

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

	private:
		template <typename T>
		friend struct Type;
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
