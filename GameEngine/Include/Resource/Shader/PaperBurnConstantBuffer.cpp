
#include "PaperBurnConstantBuffer.h"
#include "ConstantBuffer.h"

CPaperBurnConstantBuffer::CPaperBurnConstantBuffer() :
	m_BufferData{}
{
	m_BufferData.OutLineColor = Vector4(0.f, 0.63f, 0.77f, 1.f);
	m_BufferData.InLineColor = Vector4(0.9f, 0.9f, 0.9f, 1.f);
	m_BufferData.CenterLineColor = Vector4(0.05f, 0.9f, 1.f, 1.f);
	m_BufferData.OutFilter = 0.1f;
	m_BufferData.CenterFilter = 0.07f;
	m_BufferData.InFilter = 0.05f;
}

CPaperBurnConstantBuffer::CPaperBurnConstantBuffer(const CPaperBurnConstantBuffer& Buffer) :
	CConstantBufferBase(Buffer)
{
	m_BufferData = Buffer.m_BufferData;
}

CPaperBurnConstantBuffer::~CPaperBurnConstantBuffer()
{
}

bool CPaperBurnConstantBuffer::Init()
{
	SetConstantBuffer("PaperBurnCBuffer");

	return true;
}

void CPaperBurnConstantBuffer::UpdateCBuffer()
{
	m_Buffer->UpdateBuffer(&m_BufferData);
}

CPaperBurnConstantBuffer* CPaperBurnConstantBuffer::Clone()
{
	return new CPaperBurnConstantBuffer(*this);
}
