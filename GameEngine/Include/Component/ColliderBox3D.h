#pragma once

#include "ColliderComponent.h"

class CColliderBox3D :
    public CColliderComponent
{
	friend class CGameObject;

protected:
	CColliderBox3D();
	CColliderBox3D(const CColliderBox3D& com);
	virtual ~CColliderBox3D();

protected:
	Box3DInfo	m_Info;

public:
	Box3DInfo GetInfo()	const
	{
		return m_Info;
	}

	Box_Type GetBoxType()	const
	{
		return m_Info.BoxType;
	}

public:
	void Set3DExtent(float xyz)
	{
		m_Info.Length.x = xyz;
		m_Info.Length.y = xyz;
		m_Info.Length.z = xyz;
	}

	void Set3DExtent(float Width, float Height, float Depth)
	{
		m_Info.Length.x = Width;
		m_Info.Length.y = Height;
		m_Info.Length.z = Depth;
	}

public:
	Box3DInfo GetBox3DInfoViewSpace()	const;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void PrevRender();
	virtual void Render();
	virtual void PostRender();
	virtual CColliderBox3D* Clone();
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);
	virtual bool Collision(CColliderComponent* Dest);
	virtual bool CollisionMouse(const Vector2& MousePos);
	virtual bool CollisionRay(const Ray& ray);

private:
	void ResultNormalVec(Vector3& NormalVec);
};

