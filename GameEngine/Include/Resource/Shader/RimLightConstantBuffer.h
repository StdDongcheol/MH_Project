#pragma once
#include "ConstantBufferBase.h"
class CRimLightConstantBuffer :
    public CConstantBufferBase
{
public:
	CRimLightConstantBuffer();
	CRimLightConstantBuffer(const CRimLightConstantBuffer& Buffer);
	virtual ~CRimLightConstantBuffer();

protected:
	RimLightCBuffer	m_BufferData;

public:
	virtual bool Init();
	virtual void UpdateCBuffer();
	virtual CRimLightConstantBuffer* Clone();

public:
	bool GetRimLightEnable()
	{
		return m_BufferData.RimLightEnable;
	}

	void SetRimLightEnable(int Enable)
	{
		m_BufferData.RimLightEnable = Enable ? 1 : 0;
	}

	void SetRimLightCameraPos(const Vector3& CamerPos)
	{
		m_BufferData.RimCameraPos = CamerPos;
	}

	void SetRimColor(const Vector3& Color)
	{
		m_BufferData.RimColor = Color;
	}

	void SetRimPower(float Power)
	{
		m_BufferData.RimPower = Power;
	}

	void SetRimEmissiveColor(const Vector3& Color)
	{
		m_BufferData.RimEmissiveColor = Color;
	}
};

