#pragma once

#include <type_traits>
#include <stdint.h>

#include <pbext.h>

#include "PBString.h"


namespace Inf
{
	class PBBlob
	{
	public:
		PBBlob(IPB_Session* session, pbblob blob);
		PBBlob(IPB_Session* session, uint8_t* data, size_t size);
		// Deep copy
		void SetData(uint8_t* data, size_t size);
		uint8_t* GetData() const;
		size_t Size() const;
		bool IsNull() const;
		void SetToNull();

	private:
		template <typename T>
		friend struct Type;
		template <typename PBT, pblong... dims>
			requires (sizeof...(dims) <= 3 && !std::is_reference_v<PBT> && !std::is_pointer_v<PBT>)
		friend class PBArray;
		template <Helper::FixedString cls_name, pbgroup_type group_type>
		friend class PBObject;


		pbblob m_Blob;
		IPB_Session* m_Session;
	};
}
