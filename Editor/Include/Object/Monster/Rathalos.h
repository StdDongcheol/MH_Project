
#pragma once

#include "GameObject/GameObject.h"
#include "Component/AnimationMeshComponent.h"
#include "Component/ColliderBox3D.h"

class CRathalos :
    public CGameObject
{
	friend class CScene;

protected:
	CRathalos();
	CRathalos(const CRathalos& obj);
	virtual ~CRathalos();

private:
	CSharedPtr<CAnimationMeshComponent>		m_Mesh;
	CSharedPtr<CColliderBox3D>				m_SpotCollider;

	CSharedPtr<CColliderBox3D>				m_RightLegCollider;
	CSharedPtr<CColliderBox3D>				m_LeftLegCollider;
	CSharedPtr<CColliderBox3D>				m_RightFootCollider;
	CSharedPtr<CColliderBox3D>				m_LeftFootCollider;
	CSharedPtr<CColliderBox3D>				m_Head1Collider;
	CSharedPtr<CColliderBox3D>				m_Head2Collider;
	CSharedPtr<CColliderBox3D>				m_BodyCollider;
	CSharedPtr<CColliderBox3D>				m_LeftWingCollider;
	CSharedPtr<CColliderBox3D>				m_RightWingCollider;
	CSharedPtr<CColliderBox3D>				m_TailWithBodyCollider;
	CSharedPtr<CColliderBox3D>				m_TailConnectionCollider;
	CSharedPtr<CColliderBox3D>				m_TailCollider;
public:
	virtual void Update(float DeltaTime);
	virtual bool Init();
	virtual void PostUpdate(float DeltaTime);
	virtual CRathalos* Clone();
};

