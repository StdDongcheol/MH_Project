
#pragma once

#include "GameObject/GameObject.h"
#include "Component/AnimationMeshComponent.h"
#include "Component/ColliderBox3D.h"

class CAnjanath :
    public CGameObject
{
	friend class CScene;

protected:
	CAnjanath();
	CAnjanath(const CAnjanath& obj);
	virtual ~CAnjanath();

private:
	CSharedPtr<CAnimationMeshComponent>		m_Mesh;
	CSharedPtr<CColliderBox3D>				m_SpotCollider;

	CSharedPtr<CColliderBox3D>				m_RightBackLegCollider;
	CSharedPtr<CColliderBox3D>				m_LeftBackLegCollider;
	CSharedPtr<CColliderBox3D>				m_RightFrontLegCollider;
	CSharedPtr<CColliderBox3D>				m_LeftFrontLegCollider;
	CSharedPtr<CColliderBox3D>				m_RightFootCollider;
	CSharedPtr<CColliderBox3D>				m_LeftFootCollider;
	CSharedPtr<CColliderBox3D>				m_Head1Collider;
	CSharedPtr<CColliderBox3D>				m_Head2Collider;
	CSharedPtr<CColliderBox3D>				m_BodyCollider;
	CSharedPtr<CColliderBox3D>				m_TailWithBodyCollider;
	CSharedPtr<CColliderBox3D>				m_TailCollider;
public:
	virtual void Update(float DeltaTime);
	virtual bool Init();
	virtual void PostUpdate(float DeltaTime);
	virtual CAnjanath* Clone();
};
