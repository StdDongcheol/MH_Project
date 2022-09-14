
#include "Rathalos.h"
#include "RathalosAnimation.h"
#include "Scene/Scene.h"

CRathalos::CRathalos()
{
	SetTypeID<CRathalos>();
}

CRathalos::CRathalos(const CRathalos& obj)
{
	m_Mesh = (CAnimationMeshComponent*)FindComponent("RathalosMesh");
}

CRathalos::~CRathalos()
{
}

bool CRathalos::Init()
{
	if (!CGameObject::Init())
		return false;

	m_Mesh = CreateComponent<CAnimationMeshComponent>("RathalosMesh");
	m_Mesh->SetMesh("RathalosMesh");
	m_Mesh->CreateAnimationInstance<CRathalosAnimation>();

	m_RightLegCollider = CreateComponent<CColliderBox3D>("RightLegCollider");
	m_LeftLegCollider = CreateComponent<CColliderBox3D>("LeftLegCollider");
	m_RightFootCollider = CreateComponent<CColliderBox3D>("RightFootCollider");
	m_LeftFootCollider = CreateComponent<CColliderBox3D>("LeftFootCollider");
	m_Head1Collider = CreateComponent<CColliderBox3D>("Head1Collider");
	m_Head2Collider = CreateComponent<CColliderBox3D>("Head2Collider");
	m_BodyCollider = CreateComponent<CColliderBox3D>("BodyCollider");
	m_LeftWingCollider = CreateComponent<CColliderBox3D>("LeftWingCollider");
	m_RightWingCollider = CreateComponent<CColliderBox3D>("RightWingCollider");
	m_TailWithBodyCollider = CreateComponent<CColliderBox3D>("TailWithBodyCollider");
	m_TailConnectionCollider = CreateComponent<CColliderBox3D>("TailConnectionCollider");
	m_TailCollider = CreateComponent<CColliderBox3D>("TailCollider");
	m_SpotCollider = CreateComponent<CColliderBox3D>("SpotCollider");


	m_RightLegCollider->Set3DExtent(2.f, 2.f, 2.f);
	m_LeftLegCollider->Set3DExtent(2.f, 2.f, 2.f);
	m_RightFootCollider->Set3DExtent(2.f, 2.f, 2.f);
	m_LeftFootCollider->Set3DExtent(2.f, 2.f, 2.f);
	m_Head1Collider->Set3DExtent(2.f, 2.f, 2.f);
	m_Head2Collider->Set3DExtent(2.f, 2.f, 2.f);
	m_BodyCollider->Set3DExtent(4.f, 4.f, 10.f);
	m_LeftWingCollider->Set3DExtent(5.f, 2.f, 7.f);
	m_RightWingCollider->Set3DExtent(5.f, 2.f, 7.f);
	m_TailWithBodyCollider->Set3DExtent(2.f, 2.f, 2.f);
	m_TailConnectionCollider->Set3DExtent(2.f, 2.f, 2.f);
	m_TailCollider->Set3DExtent(2.f, 2.f, 2.f);
	m_SpotCollider->Set3DExtent(10.f, 10.f, 10.f);

	m_SpotCollider->SetOffset(0.f, 5.f, 0.f);

	m_RightLegCollider->SetCollisionProfile("Monster");
	m_LeftLegCollider->SetCollisionProfile("Monster");
	m_RightFootCollider->SetCollisionProfile("Monster");
	m_LeftFootCollider->SetCollisionProfile("Monster");
	m_Head1Collider->SetCollisionProfile("Monster");
	m_Head2Collider->SetCollisionProfile("Monster");
	m_BodyCollider->SetCollisionProfile("Monster");
	m_LeftWingCollider->SetCollisionProfile("Monster");
	m_RightWingCollider->SetCollisionProfile("Monster");
	m_TailWithBodyCollider->SetCollisionProfile("Monster");
	m_TailConnectionCollider->SetCollisionProfile("Monster");
	m_TailCollider->SetCollisionProfile("Monster");
	m_SpotCollider->SetCollisionProfile("Monster");

	m_RightLegCollider->SetInheritRotY(true);
	m_LeftLegCollider->SetInheritRotY(true);
	m_RightFootCollider->SetInheritRotY(true);
	m_LeftFootCollider->SetInheritRotY(true);
	m_Head1Collider->SetInheritRotY(true);
	m_Head2Collider->SetInheritRotY(true);
	m_BodyCollider->SetInheritRotY(true);
	m_LeftWingCollider->SetInheritRotY(true);
	m_RightWingCollider->SetInheritRotY(true);
	m_TailWithBodyCollider->SetInheritRotY(true);
	m_TailConnectionCollider->SetInheritRotY(true);
	m_TailCollider->SetInheritRotY(true);
	m_SpotCollider->SetInheritRotY(true);

	m_Mesh->AddChild(m_SpotCollider);

	m_Mesh->AddChild(m_RightLegCollider, "RightLeg");
	m_Mesh->AddChild(m_LeftLegCollider, "LeftLeg");
	m_Mesh->AddChild(m_RightFootCollider, "RightFoot");
	m_Mesh->AddChild(m_LeftFootCollider, "LeftFoot");
	m_Mesh->AddChild(m_Head1Collider, "Head1");
	m_Mesh->AddChild(m_Head2Collider, "Head2");
	m_Mesh->AddChild(m_BodyCollider, "Body");
	m_Mesh->AddChild(m_LeftWingCollider, "LeftWing");
	m_Mesh->AddChild(m_RightWingCollider, "RightWing");
	m_Mesh->AddChild(m_TailWithBodyCollider, "TailWithBody");
	m_Mesh->AddChild(m_TailConnectionCollider, "TailConnection");
	m_Mesh->AddChild(m_TailCollider, "Tail");

	m_Mesh->SetRelativeScale(0.03f, 0.03f, 0.03f);
	m_Mesh->SetRelativeRotationY(180.f);

	return true;
}

void CRathalos::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CRathalos::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CRathalos* CRathalos::Clone()
{
	return DBG_NEW CRathalos(*this);
}