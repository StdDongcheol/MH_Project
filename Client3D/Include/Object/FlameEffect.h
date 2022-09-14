#pragma once

#include "GameObject/GameObject.h"
#include "Component/BillboardComponent.h"
#include "Component/LightComponent.h"
#include "Component/ColliderBox3D.h"
class CFlameEffect :
    public CGameObject
{
    friend class CScene;

protected:
    CFlameEffect();
    CFlameEffect(const CFlameEffect& obj);
    virtual ~CFlameEffect();

private:
    CSharedPtr<CBillboardComponent> m_Billboard;
    CSharedPtr<CLightComponent>     m_Light;
    CSharedPtr<CColliderBox3D>      m_ColliderBox;

private:
    Vector3 m_Dir;
    float   m_Dist;
    float   m_Speed;
    bool    m_Moving;
    bool    m_Explosive;

public:
    void SetExplosive(bool bEnable)
    {
        m_Explosive = bEnable;
    }

public:
    void Move(Vector3 Dir, float Dist = 50.f, float Speed = 130.f);

    // ���� ������ ������ ����
    // 1. ���� Y���� �������� Billboard���� Landscape�� Decal�������θ� ����.
    // 2. �극�� Ÿ���� ������ Decal��������

    // Box3DCollider ����
    // �浹üũ
    // 1. LandScape�� ��� <<< �ٷ� ���� ��ġ�� Decal ����(�浹�ؾ��ϳ�?)
    // 2. Player�� ��� <<< Opacity ���� ���� ȭ������ �������θ� �Ǵ�.


public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual CFlameEffect* Clone();

private:
    void CreateEffects();

private:
    void OnCollisionBegin(const CollisionResult& result);

};

