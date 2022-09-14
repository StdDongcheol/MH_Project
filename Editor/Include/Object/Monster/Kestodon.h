
#pragma once

#include "Monster.h"
#include "Component/StaticMeshComponent.h"
#include "Component/AnimationMeshComponent.h"
#include "Component/ColliderBox3D.h"

class CKestodon :
	public CMonster
{
	friend class CScene;

protected:
	CKestodon();
	CKestodon(const CKestodon& obj);
	virtual ~CKestodon();

private:
	CSharedPtr<CAnimationMeshComponent>    m_Mesh;

	CSharedPtr<CColliderBox3D>          ColliderHead;
	CSharedPtr<CColliderBox3D>          ColliderUpperBody;
	CSharedPtr<CColliderBox3D>          ColliderLowerBody;
	CSharedPtr<CColliderBox3D>          ColliderLowerLowerBody;
	CSharedPtr<CColliderBox3D>          ColliderTail;
	CSharedPtr<CColliderBox3D>          ColliderLeftLeg;
	CSharedPtr<CColliderBox3D>          ColliderRightLeg;
	CSharedPtr<CColliderBox3D>          ColliderHeadAttack;

	CSharedPtr<CColliderBox3D>          ColliderCarving;

public:
	virtual bool Init();
	virtual void Start();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CKestodon* Clone();
};

