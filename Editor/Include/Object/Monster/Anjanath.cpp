
#include "Anjanath.h"
#include "AnjanathAnimation.h"
#include "Scene/Scene.h"

CAnjanath::CAnjanath()
{
	SetTypeID<CAnjanath>();
}

CAnjanath::CAnjanath(const CAnjanath& obj)
{
	m_Mesh = (CAnimationMeshComponent*)FindComponent("AnjanathMesh");
}

CAnjanath::~CAnjanath()
{
}

bool CAnjanath::Init()
{
	if (!CGameObject::Init())
		return false;

	m_Mesh = CreateComponent<CAnimationMeshComponent>("AnjanathMesh");
	m_Mesh->SetMesh("AnjanathMesh");
	m_Mesh->CreateAnimationInstance<CAnjanathAnimation>();


	m_SpotCollider = CreateComponent<CColliderBox3D>("ColliderBox");
	m_RightBackLegCollider = CreateComponent<CColliderBox3D>("RightBackLegCollider");
	m_LeftBackLegCollider = CreateComponent<CColliderBox3D>("LeftBackLegCollider");
	m_RightFrontLegCollider = CreateComponent<CColliderBox3D>("RightFrontLegCollider");
	m_LeftFrontLegCollider = CreateComponent<CColliderBox3D>("LeftFrontLegCollider");
	m_RightFootCollider = CreateComponent<CColliderBox3D>("RightFootCollider");
	m_LeftFootCollider = CreateComponent<CColliderBox3D>("LeftFootCollider");
	m_Head1Collider = CreateComponent<CColliderBox3D>("Head1Collider");
	m_Head2Collider = CreateComponent<CColliderBox3D>("Head2Collider");
	m_BodyCollider = CreateComponent<CColliderBox3D>("BodyCollider");
	m_TailWithBodyCollider = CreateComponent<CColliderBox3D>("TailWithBodyCollider");
	m_TailCollider = CreateComponent<CColliderBox3D>("TailCollider");

	m_RightBackLegCollider->Set3DExtent(2.f, 2.f, 2.f);
	m_LeftBackLegCollider->Set3DExtent(2.f, 2.f, 2.f);
	m_RightFrontLegCollider->Set3DExtent(2.f, 2.f, 2.f);
	m_LeftFrontLegCollider->Set3DExtent(2.f, 2.f, 2.f);
	m_RightFootCollider->Set3DExtent(2.f, 2.f, 2.f);
	m_LeftFootCollider->Set3DExtent(2.f, 2.f, 2.f);
	m_Head1Collider->Set3DExtent(2.f, 2.f, 2.f);
	m_Head2Collider->Set3DExtent(2.f, 2.f, 2.f);
	m_BodyCollider->Set3DExtent(5.f, 8.f, 3.f);
	m_TailWithBodyCollider->Set3DExtent(2.f, 4.f, 2.f);
	m_TailCollider->Set3DExtent(4.f, 5.f, 2.f);
	m_SpotCollider->Set3DExtent(10.f, 10.f, 10.f);

	m_SpotCollider->SetOffset(0.f, 5.f, 0.f);

	m_RightBackLegCollider->SetCollisionProfile("Monster");
	m_LeftBackLegCollider->SetCollisionProfile("Monster");
	m_RightFrontLegCollider->SetCollisionProfile("Monster");
	m_LeftFrontLegCollider->SetCollisionProfile("Monster");
	m_RightFootCollider->SetCollisionProfile("Monster");
	m_LeftFootCollider->SetCollisionProfile("Monster");
	m_Head1Collider->SetCollisionProfile("Monster");
	m_Head2Collider->SetCollisionProfile("Monster");
	m_BodyCollider->SetCollisionProfile("Monster");
	m_TailWithBodyCollider->SetCollisionProfile("Monster");
	m_TailCollider->SetCollisionProfile("Monster");
	m_SpotCollider->SetCollisionProfile("MonsterAttack");

	m_RightBackLegCollider->SetInheritRotY(true);
	m_LeftBackLegCollider->SetInheritRotY(true);
	m_RightFrontLegCollider->SetInheritRotY(true);
	m_LeftFrontLegCollider->SetInheritRotY(true);
	m_RightFootCollider->SetInheritRotY(true);
	m_LeftFootCollider->SetInheritRotY(true);
	m_Head1Collider->SetInheritRotY(true);
	m_Head2Collider->SetInheritRotY(true);
	m_BodyCollider->SetInheritRotY(true);
	m_TailWithBodyCollider->SetInheritRotY(true);
	m_TailCollider->SetInheritRotY(true);
	m_SpotCollider->SetInheritRotY(true);


	m_Mesh->AddChild(m_SpotCollider);

	m_Mesh->AddChild(m_RightBackLegCollider, "RightBackLeg");
	m_Mesh->AddChild(m_LeftBackLegCollider, "LeftBackLeg");
	m_Mesh->AddChild(m_RightFrontLegCollider, "RightFrontLeg");
	m_Mesh->AddChild(m_LeftFrontLegCollider, "LeftFrontLeg");
	m_Mesh->AddChild(m_RightFootCollider, "RightBackFoot");
	m_Mesh->AddChild(m_LeftFootCollider, "LeftBackFoot");
	m_Mesh->AddChild(m_Head1Collider, "Head1");
	m_Mesh->AddChild(m_Head2Collider, "Head2");
	m_Mesh->AddChild(m_BodyCollider, "Body");
	m_Mesh->AddChild(m_TailWithBodyCollider, "TailWithBody");
	m_Mesh->AddChild(m_TailCollider, "Tail");

	m_Mesh->SetRelativeScale(0.03f, 0.03f, 0.03f);
	m_Mesh->SetRelativeRotation(Vector3(-90.f, 180.f, 180.f));

	return true;
}

void CAnjanath::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CAnjanath::PostUpdate(float DeltaTime)
{	
	CGameObject::PostUpdate(DeltaTime);
}

CAnjanath* CAnjanath::Clone()
{
	return DBG_NEW CAnjanath(*this);
}
