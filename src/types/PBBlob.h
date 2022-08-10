#pragma once

#include <type_traits>
#include <stdint.h>

#include <pbext.h>

namespace Inf
{
	template <typename PBT, pblong... dims>
		requires (sizeof...(dims) <= 3 && !std::is_reference_v<PBT> && !std::is_pointer_v<PBT>)
	class PBArray;

	template <typename T>
	class Type;


	class PBBlob
	{
	public:
		PBBlob(IPB_Session* session, pbblob blob);
		// Deep copy
		void SetData(uint8_t* data, size_t size);
		uint8_t* GetData() const;
		size_t Size() const;
		bool IsNull() const;
		void SetToNull();

	private:
		friend Type<PBBlob>;
		friend PBArray<PBBlob>;

		pbblob m_Blob;
		IPB_Session* m_Session;
	};
}
