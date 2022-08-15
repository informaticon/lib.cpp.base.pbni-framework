#include "PBBlob.h"

#include "Errors.h"


Inf::PBBlob::PBBlob(IPB_Session* session, pbblob blob)
	: m_Session(session), m_Blob(blob)
{ }

Inf::PBBlob::PBBlob(IPB_Session * session, uint8_t * data, size_t size)
	: m_Session(session), m_Blob(session->NewBlob(data, size))
{ }

void Inf::PBBlob::SetData(uint8_t* data, size_t size)
{
	if (IsNull())
	{
		m_Blob = m_Session->NewBlob(data, size);
	}
	else
	{
		switch (m_Session->SetBlob(m_Blob, data, size))
		{
		case PBX_E_INVALID_ARGUMENT:
			throw Inf::PBNI_Exception(L"Errored while trying to copy Blob");
		case PBX_E_OUTOF_MEMORY:
			throw Inf::PBNI_Exception(L"Ran out of memory while trying to copy Blob");
		}
	}
}

uint8_t* Inf::PBBlob::GetData() const
{
	if (IsNull())
		throw Inf::PBNI_Exception(L"Tried to access the data of a Null Blob");

	return (uint8_t*)m_Session->GetBlob(m_Blob);
}

size_t Inf::PBBlob::Size() const
{
	if (IsNull())
		throw Inf::PBNI_Exception(L"Tried to get the length of a Null Blob");

	return m_Session->GetBlobLength(m_Blob);
}

bool Inf::PBBlob::IsNull() const
{
	return !m_Blob;
}

void Inf::PBBlob::SetToNull()
{
	m_Blob = 0;
}

Inf::PBBlob::PBBlob(IPB_Session* session, IPB_Value* value, bool acquire)
	: m_Session(session)
{
	if (value->IsNull())
	{
		m_Blob = 0;
	}
	else
	{
		if (acquire)
		{
			m_AcquiredValue = std::make_shared<Helper::AcquiredValue>(session, value);
			m_Blob = m_AcquiredValue->Value->GetBlob();
		}
		else
		{
			m_Blob = value->GetBlob();
		}
	}
}
