#pragma once
#include "ConstantBufferBase.h"
class CPickingConstantBuffer :
	public CConstantBufferBase
{
public:
	CPickingConstantBuffer();
	CPickingConstantBuffer(const CPickingConstantBuffer& Buffer);
	virtual ~CPickingConstantBuffer();

protected:
	PickingCBuffer	m_BufferData;

public:
	virtual bool Init();
	virtual void UpdateCBuffer();
	virtual CPickingConstantBuffer* Clone();

public:
	void SetRayPos(const Vector3& Pos)
	{
		m_BufferData.Pos = Pos;
	}

	void SetRayDir(const Vector3& Dir)
	{
		m_BufferData.Dir = Dir;
	}

	void SetRayOutputSize(unsigned int OutputSize)
	{
		m_BufferData.OutputSize = OutputSize;
	}
};