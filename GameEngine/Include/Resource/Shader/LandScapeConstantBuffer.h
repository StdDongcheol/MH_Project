#pragma once
#include "ConstantBufferBase.h"
class CLandScapeConstantBuffer :
	public CConstantBufferBase
{
public:
	CLandScapeConstantBuffer();
	CLandScapeConstantBuffer(const CLandScapeConstantBuffer& Buffer);
	virtual ~CLandScapeConstantBuffer();

protected:
	LandScapeCBuffer	m_BufferData;

public:
	virtual bool Init();
	virtual void UpdateCBuffer();
	virtual CLandScapeConstantBuffer* Clone();

public:
	int GetBrushType()	const
	{
		return m_BufferData.B_Type;
	}

	Vector3 GetBrushLocation()	const
	{
		return m_BufferData.B_Location;
	}

	float GetBrushRange()	const
	{
		return m_BufferData.B_Range;
	}

	Vector3 GetBrushColor()	const
	{
		return m_BufferData.B_Color;
	}

	float GetDetailLevel()	const
	{
		return m_BufferData.DetailLevel;
	}

	int GetSplatCount()	const
	{
		return m_BufferData.SplatCount;
	}

public:
	void SetBrushColor(const Vector3& Color)
	{
		m_BufferData.B_Color = Color;
	}

	void SetBrushRange(float Range)
	{
		m_BufferData.B_Range = Range;
	}

	void SetBrushLocation(const Vector3& Location)
	{
		m_BufferData.B_Location = Location;
	}

	void SetBrushType(Brush_Type Type)
	{
		m_BufferData.B_Type = (int)Type;
	}

	void SetBrushType(int Type)
	{
		m_BufferData.B_Type = Type;
	}

	void SetDetailLevel(float Level)
	{
		m_BufferData.DetailLevel = Level;
	}

	void SetSplatCount(int Count)
	{
		m_BufferData.SplatCount = Count;
	}
};

