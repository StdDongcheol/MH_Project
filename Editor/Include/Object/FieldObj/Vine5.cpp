
#include "Vine5.h"

CVine5::CVine5()
{
	SetTypeID<CVine5>();
}

CVine5::CVine5(const CVine5& obj)
{
	m_Mesh = (CStaticMeshComponent*)FindComponent("Mesh");
	m_ColliderBox = (CColliderBox3D*)FindComponent("Vine5Box");
}

CVine5::~CVine5()
{
}

bool CVine5::Init()
{
	m_Mesh = CreateComponent<CStaticMeshComponent>("Mesh");
	m_ColliderBox = CreateComponent<CColliderBox3D>("Vine5Box");

	SetRootComponent(m_Mesh);
	m_Mesh->AddChild(m_ColliderBox);
	m_ColliderBox->Set3DExtent(13.f, 3.f, 5.f);
	m_ColliderBox->SetWorldPos(0.f, 0.f, 0.f);
	m_ColliderBox->SetInheritRot(true);

	m_Mesh->SetMesh("Vine5");
	m_Mesh->SetRenderStateAll("NoneCull");
	m_Mesh->SetTransformState(Transform_State::None);

	m_Mesh->SetRelativeScale(0.05f, 0.05f, 0.05f);
	m_Mesh->SetRelativePos(13.f, 0.f, 0.f);
	m_Mesh->SetWorldRotation(-90.f, 0.f, 0.f);

	return true;
}

void CVine5::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

}

void CVine5::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CVine5* CVine5::Clone()
{
	return DBG_NEW CVine5(*this);
}
