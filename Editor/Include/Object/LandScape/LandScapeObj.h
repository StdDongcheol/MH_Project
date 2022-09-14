#pragma once

#include "GameObject\GameObject.h"
#include "Component/LandScape.h"

class CLandScapeObj :
	public CGameObject
{
	friend class CScene;

protected:
	CLandScapeObj();
	CLandScapeObj(const CLandScapeObj& obj);
	virtual ~CLandScapeObj();

private:
	CSharedPtr<CLandScape>		m_LandScape;
	int							m_CountX;
	int							m_CountZ;
	bool						m_First;

public:
	void SetBrushHeightScale(float Scale)
	{
		if (m_LandScape)
			m_LandScape->SetBrushHeightScale(Scale);
	}

	void SetBrushSplattingScale(float Scale)
	{
		if (m_LandScape)
			m_LandScape->SetBrushSplattingScale(Scale);
	}

	void SetCountX(int X)
	{
		m_CountX = X;
	}

	void SetCountZ(int Z)
	{
		m_CountZ = Z;
	}

public:
	int GetCountX()	const
	{
		return m_CountX;
	}

	int GetCountZ()	const
	{
		return m_CountZ;
	}

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CLandScapeObj* Clone();
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);

public:
	void ReleaseMesh();
	Vector3 GetDDTPos()	const;

public:
	void SelectMap(int Map);
	void SetBrushType(int Type);
	void SetBrushType(Brush_Type Type);
	void SetBrushLocation(const Vector3& Location);
	void SetBrushRange(float Range);
	void SetBrushColor(const Vector3& Color);

public:
	int GetBrushType()	const;
	Vector3 GetBrushLocation()	const;
	float GetBrushRange()	const;
	Vector3 GetBrushColor()	const;

public:
	void PlayBrush(float DeltaTime, bool Up);
	void PlaySplatting(float DeltaTime, bool Draw, int TypeNumb);
	void SetNavData();
};