#pragma once

#include "GameObject/GameObject.h"
#include "Component/StaticMeshComponent.h"
#include "Component/AnimationMeshComponent.h"
#include "Component/ColliderBox3D.h"


class CPlayer :
	public CGameObject
{
	friend class CScene;

protected:
	CPlayer();
	CPlayer(const CPlayer& obj);
	virtual ~CPlayer();

private:
	CSharedPtr<CAnimationMeshComponent>    m_Mesh;
	CSharedPtr<CStaticMeshComponent>	m_Face;
	CSharedPtr<CColliderBox3D>		m_ColliderBox;

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CPlayer* Clone();
};

