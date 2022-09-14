#pragma once

#include "Monster.h"
#include "Component/StaticMeshComponent.h"
#include "Component/AnimationMeshComponent.h"
#include "Component/ColliderBox3D.h"

class CVespoid :
    public CMonster
{
    friend class CScene;

protected:
    CVespoid();
    CVespoid(const CVespoid& obj);
    virtual ~CVespoid();

private:
    CSharedPtr<CAnimationMeshComponent>    m_Mesh;



    CSharedPtr<CColliderBox3D>		ColliderUpperBody;
    CSharedPtr<CColliderBox3D>		ColliderLowerBody;

    CSharedPtr<CColliderBox3D>	    ColliderAttack;

    CSharedPtr<CColliderBox3D>          ColliderCarving;
   
public:
    virtual bool Init();
    virtual void Start();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual CVespoid* Clone();
};

