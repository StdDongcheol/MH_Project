
#include "Grass4.h"

CGrass4::CGrass4()
{
	SetTypeID<CGrass4>();
}

CGrass4::CGrass4(const CGrass4& obj)
{
	m_Mesh = (CStaticMeshComponent*)FindComponent("Mesh");
	m_ColliderBox = (CColliderBox3D*)FindComponent("Grass4Box");
}

CGrass4::~CGrass4()
{
}

bool CGrass4::Init()
{
	m_Mesh = CreateComponent<CStaticMeshComponent>("Mesh");
	m_ColliderBox = CreateComponent<CColliderBox3D>("Grass4Box");

	SetRootComponent(m_Mesh);
	m_Mesh->AddChild(m_ColliderBox);
	m_ColliderBox->Set3DExtent(5.f);
	m_ColliderBox->SetWorldPos(0.f, 0.f, 0.f);
	m_ColliderBox->SetInheritRot(true);

	m_Mesh->SetMesh("Grass4");
	m_Mesh->SetRenderStateAll("NoneCull");

	m_Mesh->SetRelativeScale(0.05f, 0.05f, 0.05f);
	m_Mesh->SetRelativePos(13.f, 0.f, 0.f);
	m_Mesh->SetWorldRotation(-90.f, 0.f, 0.f);

	return true;
}

void CGrass4::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

}

void CGrass4::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CGrass4* CGrass4::Clone()
{
	return DBG_NEW CGrass4(*this);
}
