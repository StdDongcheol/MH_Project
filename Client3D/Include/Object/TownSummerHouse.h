#pragma once

#include "GameObject/GameObject.h"
#include "Component/StaticMeshComponent.h"
#include "Component/ColliderBox3D.h"

class CTownSummerHouse :
    public CGameObject
{
	friend class CScene;

protected:
	CTownSummerHouse();
	CTownSummerHouse(const CTownSummerHouse& obj);
	virtual ~CTownSummerHouse();

private:
	CSharedPtr<CStaticMeshComponent>    m_Mesh;
	CSharedPtr<CColliderBox3D>			m_ColliderBox;

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CTownSummerHouse* Clone();
};

