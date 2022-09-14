
#include "SmallGrass.h"

CSmallGrass::CSmallGrass()
{
	SetTypeID<CSmallGrass>();
}

CSmallGrass::CSmallGrass(const CSmallGrass& obj)
{
	m_Mesh = (CStaticMeshComponent*)FindComponent("Mesh");
	m_ColliderBox = (CColliderBox3D*)FindComponent("SmallGrassBox");
}

CSmallGrass::~CSmallGrass()
{
}

bool CSmallGrass::Init()
{
	m_Mesh = CreateComponent<CStaticMeshComponent>("Mesh");
	m_ColliderBox = CreateComponent<CColliderBox3D>("SmallGrassBox");

	SetRootComponent(m_Mesh);
	m_Mesh->AddChild(m_ColliderBox);

	m_ColliderBox->SetInheritRot(true);
	m_ColliderBox->Set3DExtent(6.f, 6.f, 3.f);
	m_ColliderBox->SetRelativePos(0.f, 0.f, m_ColliderBox->GetInfo().Length.z);
	m_ColliderBox->SetCollisionProfile("FieldObj");

	m_Mesh->SetMesh("SmallGrass");
	
	m_Mesh->SetRelativeScale(0.05f, 0.05f, 0.05f);
	m_Mesh->SetRelativePos(13.f, 0.f, 0.f);
	m_Mesh->SetWorldRotation(-90.f, 0.f, 0.f);

	return true;
}

void CSmallGrass::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

}

void CSmallGrass::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CSmallGrass* CSmallGrass::Clone()
{
	return DBG_NEW CSmallGrass(*this);
}
