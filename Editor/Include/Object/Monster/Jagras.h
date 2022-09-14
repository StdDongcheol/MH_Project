#pragma once

#include "Monster.h"
#include "Component/StaticMeshComponent.h"
#include "Component/AnimationMeshComponent.h"
#include "Component/ColliderBox3D.h"

class CJagras :
    public CMonster
{
    friend class CScene;

protected:
    CJagras();
    CJagras(const CJagras& obj);
    virtual ~CJagras();

private:
    CSharedPtr<CAnimationMeshComponent>    m_Mesh;

    CSharedPtr<CColliderBox3D>          ColliderHead;
    CSharedPtr<CColliderBox3D>          ColliderBody1;
    CSharedPtr<CColliderBox3D>          ColliderBody2;
    CSharedPtr<CColliderBox3D>          ColliderBody3;
    CSharedPtr<CColliderBox3D>          ColliderBody4;
    CSharedPtr<CColliderBox3D>          ColliderBody5;
    CSharedPtr<CColliderBox3D>          ColliderTail1;
    CSharedPtr<CColliderBox3D>          ColliderTail2;
    CSharedPtr<CColliderBox3D>          ColliderRightFrontLeg;
    CSharedPtr<CColliderBox3D>          ColliderLeftFrontLeg;
    CSharedPtr<CColliderBox3D>          ColliderRightBackLeg;
    CSharedPtr<CColliderBox3D>          ColliderLeftBackLeg;

    CSharedPtr<CColliderBox3D>          ColliderHeadAttack;
    CSharedPtr<CColliderBox3D>          ColliderLeftArmAttack;
    CSharedPtr<CColliderBox3D>          ColliderRightArmAttack;

    CSharedPtr<CColliderBox3D>          ColliderCarving;

public:
    virtual bool Init();
    virtual void Start();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual CJagras* Clone();
};

