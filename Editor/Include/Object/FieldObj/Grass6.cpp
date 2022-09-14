
#include "Grass6.h"

CGrass6::CGrass6()
{
	SetTypeID<CGrass6>();
}

CGrass6::CGrass6(const CGrass6& obj)
{
	m_Mesh = (CStaticMeshComponent*)FindComponent("Mesh");
	m_ColliderBox = (CColliderBox3D*)FindComponent("Grass6Box");
}

CGrass6::~CGrass6()
{
}

bool CGrass6::Init()
{
	m_Mesh = CreateComponent<CStaticMeshComponent>("Mesh");
	m_ColliderBox = CreateComponent<CColliderBox3D>("Grass6Box");

	SetRootComponent(m_Mesh);
	m_Mesh->AddChild(m_ColliderBox);
	m_ColliderBox->Set3DExtent(6.f, 6.f, 3.f);
	m_ColliderBox->SetWorldPos(0.f, 0.f, 0.f);
	m_ColliderBox->SetInheritRot(true);

	m_Mesh->SetMesh("Grass6");
	m_Mesh->SetRenderStateAll("NoneCull");

	m_Mesh->SetRelativeScale(0.05f, 0.05f, 0.05f);
	m_Mesh->SetRelativePos(13.f, 0.f, 0.f);
	m_Mesh->SetWorldRotation(-90.f, 0.f, 0.f);

	return true;
}

void CGrass6::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

}

void CGrass6::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CGrass6* CGrass6::Clone()
{
	return DBG_NEW CGrass6(*this);
}
