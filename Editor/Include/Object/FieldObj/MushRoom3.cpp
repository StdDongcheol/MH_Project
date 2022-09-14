
#include "MushRoom3.h"

CMushRoom3::CMushRoom3()
{
	SetTypeID<CMushRoom3>();
}

CMushRoom3::CMushRoom3(const CMushRoom3& obj)
{
	m_Mesh = (CStaticMeshComponent*)FindComponent("Mesh");
	m_ColliderBox = (CColliderBox3D*)FindComponent("MushRoom3Box");
}

CMushRoom3::~CMushRoom3()
{
}

bool CMushRoom3::Init()
{
	m_Mesh = CreateComponent<CStaticMeshComponent>("Mesh");
	m_ColliderBox = CreateComponent<CColliderBox3D>("MushRoom3Box");

	SetRootComponent(m_Mesh);
	m_Mesh->AddChild(m_ColliderBox);
	m_ColliderBox->Set3DExtent(2.f);
	m_ColliderBox->SetWorldPos(0.f, 0.f, 0.f);
	m_ColliderBox->SetInheritRot(true);

	m_Mesh->SetMesh("MushRoom3");

	m_Mesh->SetRelativeScale(0.05f, 0.05f, 0.05f);
	m_Mesh->SetRelativePos(13.f, 0.f, 0.f);
	m_Mesh->SetWorldRotation(-90.f, 0.f, 0.f);

	return true;
}

void CMushRoom3::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

}

void CMushRoom3::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CMushRoom3* CMushRoom3::Clone()
{
	return DBG_NEW CMushRoom3(*this);
}
