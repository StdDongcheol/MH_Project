
#include "PickingConstantBuffer.h"
#include "ConstantBuffer.h"

CPickingConstantBuffer::CPickingConstantBuffer() :
	m_BufferData{}
{
}

CPickingConstantBuffer::CPickingConstantBuffer(const CPickingConstantBuffer& Buffer) :
	CConstantBufferBase(Buffer)
{
	m_BufferData = Buffer.m_BufferData;
}

CPickingConstantBuffer::~CPickingConstantBuffer()
{
}

bool CPickingConstantBuffer::Init()
{
	SetConstantBuffer("PickingCBuffer");

	return true;
}

void CPickingConstantBuffer::UpdateCBuffer()
{
	m_Buffer->UpdateBuffer(&m_BufferData);
}

CPickingConstantBuffer* CPickingConstantBuffer::Clone()
{
	return DBG_NEW CPickingConstantBuffer(*this);
}
