
#include "Wreck1.h"

CWreck1::CWreck1()
{
	SetTypeID<CWreck1>();
}

CWreck1::CWreck1(const CWreck1& obj)
{
	m_Mesh = (CStaticMeshComponent*)FindComponent("Mesh");
	m_ColliderBox = (CColliderBox3D*)FindComponent("Wreck1Box");
}

CWreck1::~CWreck1()
{
}

bool CWreck1::Init()
{
	m_Mesh = CreateComponent<CStaticMeshComponent>("Mesh");
	m_ColliderBox = CreateComponent<CColliderBox3D>("Wreck1Box");

	SetRootComponent(m_Mesh);
	m_Mesh->AddChild(m_ColliderBox);

	m_ColliderBox->SetInheritRot(true);
	m_ColliderBox->Set3DExtent(15.f, 15.f, 1.f);
	m_ColliderBox->SetRelativePos(-1.f, 0.f, m_ColliderBox->GetInfo().Length.z);
	m_ColliderBox->SetCollisionProfile("FieldObj");

	m_Mesh->SetMesh("Wreck1");

	m_Mesh->SetRelativeScale(0.05f, 0.05f, 0.05f);
	m_Mesh->SetRelativePos(13.f, 0.f, 0.f);
	m_Mesh->SetWorldRotation(-90.f, 0.f, 0.f);
	m_Mesh->SetTransformState(Transform_State::None);

	return true;
}

void CWreck1::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

}

void CWreck1::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CWreck1* CWreck1::Clone()
{
	return DBG_NEW CWreck1(*this);
}
