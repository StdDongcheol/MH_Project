
#include "Grass9.h"

CGrass9::CGrass9()
{
	SetTypeID<CGrass9>();
}

CGrass9::CGrass9(const CGrass9& obj)
{
	m_Mesh = (CStaticMeshComponent*)FindComponent("Mesh");
	m_ColliderBox = (CColliderBox3D*)FindComponent("Grass9Box");
}

CGrass9::~CGrass9()
{
}

bool CGrass9::Init()
{
	m_Mesh = CreateComponent<CStaticMeshComponent>("Mesh");
	m_ColliderBox = CreateComponent<CColliderBox3D>("Grass9Box");

	SetRootComponent(m_Mesh);
	m_Mesh->AddChild(m_ColliderBox);
	m_ColliderBox->Set3DExtent(6.f, 6.f, 3.f);
	m_ColliderBox->SetWorldPos(0.f, 0.f, 0.f);
	m_ColliderBox->SetInheritRot(true);

	m_Mesh->SetMesh("Grass9");
	m_Mesh->SetRenderStateAll("NoneCull");

	m_Mesh->SetRelativeScale(0.05f, 0.05f, 0.05f);
	m_Mesh->SetRelativePos(13.f, 0.f, 0.f);
	m_Mesh->SetWorldRotation(-90.f, 0.f, 0.f);

	return true;
}

void CGrass9::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

}

void CGrass9::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CGrass9* CGrass9::Clone()
{
	return DBG_NEW CGrass9(*this);
}
