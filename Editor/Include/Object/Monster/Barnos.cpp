#include "Barnos.h"
#include "BarnosAnimation.h"
#include "Input.h"
#include "Resource/Animation/AnimationSequence.h"
#include "Engine.h"
#include "Scene/SceneManager.h"

CBarnos::CBarnos()
{
	SetTypeID<CBarnos>();
}

CBarnos::CBarnos(const CBarnos& obj)
{
	m_Mesh = (CAnimationMeshComponent*)FindComponent("Mesh");

}

CBarnos::~CBarnos()
{
}


bool CBarnos::Init()
{
	m_Mesh = CreateComponent<CAnimationMeshComponent>("Mesh");

	ColliderHead = CreateComponent<CColliderBox3D>("ColliderHead");
	ColliderBody1 = CreateComponent<CColliderBox3D>("ColliderBody1");
	ColliderBody2 = CreateComponent<CColliderBox3D>("ColliderBody2");
	ColliderBody3 = CreateComponent<CColliderBox3D>("ColliderBody3");
	ColliderBody4 = CreateComponent<CColliderBox3D>("ColliderBody4");
	ColliderRightWing1 = CreateComponent<CColliderBox3D>("ColliderRightWing1");
	ColliderRightWing2 = CreateComponent<CColliderBox3D>("ColliderRightWing2");
	ColliderRightWing3 = CreateComponent<CColliderBox3D>("ColliderRightWing3");
	ColliderRightWing4 = CreateComponent<CColliderBox3D>("ColliderRightWing4");
	ColliderRightWing5 = CreateComponent<CColliderBox3D>("ColliderRightWing5");
	ColliderLeftWing1 = CreateComponent<CColliderBox3D>("ColliderLeftWing1");
	ColliderLeftWing2 = CreateComponent<CColliderBox3D>("ColliderLeftWing2");
	ColliderLeftWing3 = CreateComponent<CColliderBox3D>("ColliderLeftWing3");
	ColliderLeftWing4 = CreateComponent<CColliderBox3D>("ColliderLeftWing4");
	ColliderLeftWing5 = CreateComponent<CColliderBox3D>("ColliderLeftWing5");

	ColliderLeftFoot = CreateComponent<CColliderBox3D>("ColliderLeftFoot");
	ColliderRightFoot = CreateComponent<CColliderBox3D>("ColliderRightFoot");

	ColliderHeadAttack = CreateComponent<CColliderBox3D>("ColliderHeadAttack");
	ColliderLeftFootAttack = CreateComponent<CColliderBox3D>("ColliderLeftFootAttack");
	ColliderRightFootAttack = CreateComponent<CColliderBox3D>("ColliderRightFootAttack");

	ColliderHead->Set3DExtent(1.5f, 1.5f, 1.5f);
	ColliderBody1->Set3DExtent(1.5f, 1.5f, 1.5f);
	ColliderBody2->Set3DExtent(1.5f, 1.5f, 1.5f);
	ColliderBody3->Set3DExtent(2.f, 2.f, 2.f);
	ColliderBody4->Set3DExtent(1.5f, 1.5f, 1.5f);
	ColliderRightWing1->Set3DExtent(2.3f, 2.3f, 2.3f);
	ColliderRightWing2->Set3DExtent(2.3f, 2.3f, 2.3f);
	ColliderRightWing3->Set3DExtent(2.3f, 2.3f, 2.3f);
	ColliderRightWing4->Set3DExtent(2.3f, 2.3f, 2.3f);
	ColliderRightWing5->Set3DExtent(2.3f, 2.3f, 2.3f);
	ColliderLeftWing1->Set3DExtent(2.3f, 2.3f, 2.3f);
	ColliderLeftWing2->Set3DExtent(2.3f, 2.3f, 2.3f);
	ColliderLeftWing3->Set3DExtent(2.3f, 2.3f, 2.3f);
	ColliderLeftWing4->Set3DExtent(2.3f, 2.3f, 2.3f);
	ColliderLeftWing5->Set3DExtent(2.3f, 2.3f, 2.3f);

	ColliderLeftFoot->Set3DExtent(1.5f, 1.5f, 1.5f);
	ColliderRightFoot->Set3DExtent(1.5f, 1.5f, 1.5f);

	ColliderHeadAttack->Set3DExtent(1.5f, 1.5f, 1.5f);
	ColliderLeftFootAttack->Set3DExtent(1.5f, 1.5f, 1.5f);
	ColliderRightFootAttack->Set3DExtent(1.5f, 1.5f, 1.5f);

	ColliderHead->SetCollisionProfile("Monster");
	ColliderBody1->SetCollisionProfile("Monster");
	ColliderBody2->SetCollisionProfile("Monster");
	ColliderBody3->SetCollisionProfile("Monster");
	ColliderBody4->SetCollisionProfile("Monster");
	ColliderRightWing1->SetCollisionProfile("Monster");
	ColliderRightWing2->SetCollisionProfile("Monster");
	ColliderRightWing3->SetCollisionProfile("Monster");
	ColliderRightWing4->SetCollisionProfile("Monster");
	ColliderRightWing5->SetCollisionProfile("Monster");
	ColliderLeftWing1->SetCollisionProfile("Monster");
	ColliderLeftWing2->SetCollisionProfile("Monster");
	ColliderLeftWing3->SetCollisionProfile("Monster");
	ColliderLeftWing4->SetCollisionProfile("Monster");
	ColliderLeftWing5->SetCollisionProfile("Monster");
	ColliderLeftFoot->SetCollisionProfile("Monster");
	ColliderRightFoot->SetCollisionProfile("Monster");

	ColliderHeadAttack->SetCollisionProfile("MonsterAttack");
	ColliderLeftFootAttack->SetCollisionProfile("MonsterAttack");
	ColliderRightFootAttack->SetCollisionProfile("MonsterAttack");


	SetRootComponent(m_Mesh);
	m_Mesh->SetTransformState(Transform_State::None);
	m_State = Transform_State::None;
	m_Mesh->SetMesh("BarnosMesh");
	m_Mesh->CreateAnimationInstance<CBarnosAnimation>();

	m_Mesh->SetRelativeScale(0.05f, 0.05f, 0.05f);
	m_Mesh->SetRelativeRotation(Vector3(250.f, 180.f, 180.f));

	ColliderCarving = CreateComponent<CColliderBox3D>("ColliderCarving");
	ColliderCarving->Set3DExtent(6.0f, 6.0f, 6.0f);
	ColliderCarving->SetCollisionProfile("Carving");
	m_Mesh->AddChild(ColliderCarving);
	ColliderCarving->Enable(false);

	m_Mesh->AddChild(ColliderHead, "Head");
	m_Mesh->AddChild(ColliderBody1, "Body1");
	m_Mesh->AddChild(ColliderBody2, "Body2");
	m_Mesh->AddChild(ColliderBody3, "Body3");
	m_Mesh->AddChild(ColliderBody4, "Body4");

	m_Mesh->AddChild(ColliderRightWing1, "RightWing1");
	m_Mesh->AddChild(ColliderRightWing2, "RightWing2");
	m_Mesh->AddChild(ColliderRightWing3, "RightWing3");
	m_Mesh->AddChild(ColliderRightWing4, "RightWing4");
	m_Mesh->AddChild(ColliderRightWing5, "RightWing5");

	m_Mesh->AddChild(ColliderLeftWing1, "LeftWing1");
	m_Mesh->AddChild(ColliderLeftWing2, "LeftWing2");
	m_Mesh->AddChild(ColliderLeftWing3, "LeftWing3");
	m_Mesh->AddChild(ColliderLeftWing4, "LeftWing4");
	m_Mesh->AddChild(ColliderLeftWing5, "LeftWing5");

	m_Mesh->AddChild(ColliderLeftFoot, "RightFoot");
	m_Mesh->AddChild(ColliderRightFoot, "LeftFoot");

	m_Mesh->AddChild(ColliderHeadAttack, "Head");
	m_Mesh->AddChild(ColliderLeftFootAttack, "RightFoot");
	m_Mesh->AddChild(ColliderRightFootAttack, "LeftFoot");


	return true;
}


void CBarnos::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CBarnos::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CBarnos* CBarnos::Clone()
{
	return DBG_NEW CBarnos(*this);
}

void CBarnos::Save(FILE* File)
{
	CMonster::Save(File);

	if (m_Mesh->GetAnimationInstance())
		m_Mesh->GetAnimationInstance()->Save(File);
}

void CBarnos::Load(FILE* File)
{
	CMonster::Load(File);

	m_Mesh = (CAnimationMeshComponent*)FindComponent("Mesh");

	ColliderHead = (CColliderBox3D*)FindComponent("ColliderHead");
	ColliderBody1 = (CColliderBox3D*)FindComponent("ColliderBody1");
	ColliderBody2 = (CColliderBox3D*)FindComponent("ColliderBody2");
	ColliderBody3 = (CColliderBox3D*)FindComponent("ColliderBody3");
	ColliderBody4 = (CColliderBox3D*)FindComponent("ColliderBody4");
	ColliderRightWing1 = (CColliderBox3D*)FindComponent("ColliderRightWing1");
	ColliderRightWing2 = (CColliderBox3D*)FindComponent("ColliderRightWing2");
	ColliderRightWing3 = (CColliderBox3D*)FindComponent("ColliderRightWing3");
	ColliderRightWing4 = (CColliderBox3D*)FindComponent("ColliderRightWing4");
	ColliderRightWing5 = (CColliderBox3D*)FindComponent("ColliderRightWing5");
	ColliderLeftWing1 = (CColliderBox3D*)FindComponent("ColliderLeftWing1");
	ColliderLeftWing2 = (CColliderBox3D*)FindComponent("ColliderLeftWing2");
	ColliderLeftWing3 = (CColliderBox3D*)FindComponent("ColliderLeftWing3");
	ColliderLeftWing4 = (CColliderBox3D*)FindComponent("ColliderLeftWing4");
	ColliderLeftWing5 = (CColliderBox3D*)FindComponent("ColliderLeftWing5");

	ColliderLeftFoot = (CColliderBox3D*)FindComponent("ColliderLeftFoot");
	ColliderRightFoot = (CColliderBox3D*)FindComponent("ColliderRightFoot");

	ColliderHeadAttack = (CColliderBox3D*)FindComponent("ColliderHeadAttack");
	ColliderLeftFootAttack = (CColliderBox3D*)FindComponent("ColliderLeftFootAttack");
	ColliderRightFootAttack = (CColliderBox3D*)FindComponent("ColliderRightFootAttack");

	m_Mesh->LoadAnimationInstance<CBarnosAnimation>();
	m_Mesh->GetAnimationInstance()->Load(File);

	m_Mesh->SetMesh("BarnosMesh");

	ColliderCarving = (CColliderBox3D*)FindComponent("ColliderCarving");
	ColliderCarving->Enable(false);
}
