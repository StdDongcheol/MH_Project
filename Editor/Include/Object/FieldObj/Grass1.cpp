
#include "Grass1.h"

CGrass1::CGrass1()
{
	SetTypeID<CGrass1>();
}

CGrass1::CGrass1(const CGrass1& obj)
{
	m_Mesh = (CStaticMeshComponent*)FindComponent("Mesh");
	m_ColliderBox = (CColliderBox3D*)FindComponent("Grass1Box");
}

CGrass1::~CGrass1()
{
}

bool CGrass1::Init()
{
	m_Mesh = CreateComponent<CStaticMeshComponent>("Mesh");
	m_ColliderBox = CreateComponent<CColliderBox3D>("Grass1Box");

	SetRootComponent(m_Mesh);
	m_Mesh->AddChild(m_ColliderBox);
	m_ColliderBox->Set3DExtent(5.f);
	m_ColliderBox->SetWorldPos(0.f, 0.f, 0.f);
	m_ColliderBox->SetInheritRot(true);

	m_Mesh->SetMesh("Grass1");
	m_Mesh->SetRenderStateAll("NoneCull");

	m_Mesh->SetRelativeScale(0.05f, 0.05f, 0.05f);
	m_Mesh->SetRelativePos(13.f, 0.f, 0.f);
	m_Mesh->SetWorldRotation(-90.f, 0.f, 0.f);

	return true;
}

void CGrass1::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

}

void CGrass1::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CGrass1* CGrass1::Clone()
{
	return DBG_NEW CGrass1(*this);
}
