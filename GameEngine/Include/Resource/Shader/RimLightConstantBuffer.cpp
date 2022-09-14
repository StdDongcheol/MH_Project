
#include "RimLightConstantBuffer.h"
#include "ConstantBuffer.h"

CRimLightConstantBuffer::CRimLightConstantBuffer() :
	m_BufferData{}
{
	m_BufferData.RimLightEnable = 0;
	m_BufferData.RimColor = Vector3(0.f, 0.f, 0.f);
	m_BufferData.RimPower = 1.f;
}

CRimLightConstantBuffer::CRimLightConstantBuffer(const CRimLightConstantBuffer& Buffer) :
	CConstantBufferBase(Buffer)
{
	m_BufferData = Buffer.m_BufferData;
}

CRimLightConstantBuffer::~CRimLightConstantBuffer()
{
}

bool CRimLightConstantBuffer::Init()
{
	SetConstantBuffer("RimLightCBuffer");

	return true;
}

void CRimLightConstantBuffer::UpdateCBuffer()
{
	m_Buffer->UpdateBuffer(&m_BufferData);
}

CRimLightConstantBuffer* CRimLightConstantBuffer::Clone()
{
	return new CRimLightConstantBuffer(*this);
}
