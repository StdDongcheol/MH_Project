
#pragma once

#include "Monster.h"
#include "Component/StaticMeshComponent.h"
#include "Component/AnimationMeshComponent.h"
#include "Component/ColliderBox3D.h"

class CBarnos :
    public CMonster
{
    friend class CScene;

protected:
    CBarnos();
    CBarnos(const CBarnos& obj);
    virtual ~CBarnos();

private:
    CSharedPtr<CAnimationMeshComponent>    m_Mesh;

    CSharedPtr<CColliderBox3D>		ColliderHead;
    CSharedPtr<CColliderBox3D>		ColliderBody1;
    CSharedPtr<CColliderBox3D>		ColliderBody2;
    CSharedPtr<CColliderBox3D>		ColliderBody3;
    CSharedPtr<CColliderBox3D>		ColliderBody4;

    CSharedPtr<CColliderBox3D>	    ColliderRightWing1;
    CSharedPtr<CColliderBox3D>	    ColliderRightWing2;
    CSharedPtr<CColliderBox3D>	    ColliderRightWing3;
    CSharedPtr<CColliderBox3D>	    ColliderRightWing4;
    CSharedPtr<CColliderBox3D>	    ColliderRightWing5;

    CSharedPtr<CColliderBox3D>		ColliderLeftWing1;
    CSharedPtr<CColliderBox3D>		ColliderLeftWing2;
    CSharedPtr<CColliderBox3D>		ColliderLeftWing3;
    CSharedPtr<CColliderBox3D>		ColliderLeftWing4;
    CSharedPtr<CColliderBox3D>		ColliderLeftWing5;

    CSharedPtr<CColliderBox3D>		ColliderLeftFoot;
    CSharedPtr<CColliderBox3D>		ColliderRightFoot;

    CSharedPtr<CColliderBox3D>		ColliderHeadAttack;
    CSharedPtr<CColliderBox3D>		ColliderLeftFootAttack;
    CSharedPtr<CColliderBox3D>		ColliderRightFootAttack;

    CSharedPtr<CColliderBox3D>          ColliderCarving;

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual CBarnos* Clone();
    virtual void Save(FILE* File);
    virtual void Load(FILE* File);
};

