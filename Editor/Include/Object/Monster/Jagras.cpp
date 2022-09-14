#include "Jagras.h"
#include "JagrasAnimation.h"
#include "Input.h"
#include "Resource/Animation/AnimationSequence.h"
#include "Engine.h"
#include "Scene/SceneManager.h"

CJagras::CJagras()	
{
	SetTypeID<CJagras>();
	CurYRot = 180.f;
}

CJagras::CJagras(const CJagras& obj)
{
	m_Mesh = (CAnimationMeshComponent*)FindComponent("Mesh");
}

CJagras::~CJagras()
{
}

bool CJagras::Init()
{

	m_Mesh = CreateComponent<CAnimationMeshComponent>("Mesh");


	ColliderHead = CreateComponent<CColliderBox3D>("ColliderHead");
	ColliderBody1 = CreateComponent<CColliderBox3D>("ColliderBody1");
	ColliderBody2 = CreateComponent<CColliderBox3D>("ColliderBody2");
	ColliderBody3 = CreateComponent<CColliderBox3D>("ColliderBody3");
	ColliderBody4 = CreateComponent<CColliderBox3D>("ColliderBody4");
	ColliderBody5 = CreateComponent<CColliderBox3D>("ColliderBody5");
	ColliderTail1 = CreateComponent<CColliderBox3D>("ColliderTail1");
	ColliderTail2 = CreateComponent<CColliderBox3D>("ColliderTail2");
	ColliderRightFrontLeg = CreateComponent<CColliderBox3D>("ColliderRightFrontLeg");
	ColliderLeftFrontLeg = CreateComponent<CColliderBox3D>("ColliderLeftFrontLeg");
	ColliderRightBackLeg = CreateComponent<CColliderBox3D>("ColliderRightBackLeg");
	ColliderLeftBackLeg = CreateComponent<CColliderBox3D>("ColliderLeftBackLeg");


	ColliderHeadAttack = CreateComponent<CColliderBox3D>("ColliderHeadAttack");
	ColliderLeftArmAttack = CreateComponent<CColliderBox3D>("ColliderLeftArmAttack");
	ColliderRightArmAttack = CreateComponent<CColliderBox3D>("ColliderRightArmAttack");

	ColliderHead->Set3DExtent(1.0f, 1.0f, 1.0f);
	ColliderBody1->Set3DExtent(1.5f, 1.5f, 1.5f);
	ColliderBody2->Set3DExtent(1.5f, 1.5f, 1.5f);
	ColliderBody3->Set3DExtent(1.5f, 1.5f, 1.5f);
	ColliderBody4->Set3DExtent(1.5f, 1.5f, 1.5f);
	ColliderBody5->Set3DExtent(1.5f, 1.5f, 1.5f);
	ColliderTail1->Set3DExtent(1.5f, 1.5f, 1.5f);
	ColliderTail2->Set3DExtent(1.0f, 1.0f, 1.0f);
	ColliderRightFrontLeg->Set3DExtent(1.0f, 1.5f, 1.0f);
	ColliderLeftFrontLeg->Set3DExtent(1.0f, 1.5f, 1.0f);
	ColliderRightBackLeg->Set3DExtent(1.0f, 1.5f, 1.0f);
	ColliderLeftBackLeg->Set3DExtent(1.0f, 1.5f, 1.0f);

	ColliderHeadAttack->Set3DExtent(1.0f, 1.0f, 1.0f);
	ColliderLeftArmAttack->Set3DExtent(1.0f, 1.0f, 1.0f);
	ColliderRightArmAttack->Set3DExtent(1.0f, 1.0f, 1.0f);

	ColliderHead->SetCollisionProfile("Monster");
	ColliderBody1->SetCollisionProfile("Monster");
	ColliderBody2->SetCollisionProfile("Monster");
	ColliderBody3->SetCollisionProfile("Monster");
	ColliderBody4->SetCollisionProfile("Monster");
	ColliderBody5->SetCollisionProfile("Monster");
	ColliderTail1->SetCollisionProfile("Monster");
	ColliderTail2->SetCollisionProfile("Monster");
	ColliderRightFrontLeg->SetCollisionProfile("Monster");
	ColliderLeftFrontLeg->SetCollisionProfile("Monster");
	ColliderRightBackLeg->SetCollisionProfile("Monster");
	ColliderLeftBackLeg->SetCollisionProfile("Monster");

	ColliderHeadAttack->SetCollisionProfile("MonsterAttack");
	ColliderLeftArmAttack->SetCollisionProfile("MonsterAttack");
	ColliderRightArmAttack->SetCollisionProfile("MonsterAttack");


	SetRootComponent(m_Mesh);
	m_Mesh->SetTransformState(Transform_State::Ground);
	m_State = Transform_State::Ground;
	m_Mesh->SetMesh("JagrasMesh");
	m_Mesh->CreateAnimationInstance<CJagrasAnimation>();

	m_Mesh->SetRelativeScale(0.05f, 0.05f, 0.05f);
	m_Mesh->SetRelativeRotation(Vector3(270.f, 180.f, 180.f));

	ColliderCarving = CreateComponent<CColliderBox3D>("ColliderCarving");
	ColliderCarving->Set3DExtent(5.0f, 5.0f, 5.0f);
	ColliderCarving->SetCollisionProfile("Carving");
	m_Mesh->AddChild(ColliderCarving);
	ColliderCarving->Enable(false);

	m_Mesh->AddChild(ColliderHead, "Head");
	m_Mesh->AddChild(ColliderBody1, "Body1");
	m_Mesh->AddChild(ColliderBody2, "Body2");
	m_Mesh->AddChild(ColliderBody3, "Body3");
	m_Mesh->AddChild(ColliderBody4, "Body4");
	m_Mesh->AddChild(ColliderBody5, "Body5");
	m_Mesh->AddChild(ColliderTail1, "Tail1");
	m_Mesh->AddChild(ColliderTail2, "Tail2");
	m_Mesh->AddChild(ColliderRightFrontLeg, "RightFrontLeg");
	m_Mesh->AddChild(ColliderLeftFrontLeg, "LeftFrontLeg");
	m_Mesh->AddChild(ColliderRightBackLeg, "RightBackLeg");
	m_Mesh->AddChild(ColliderLeftBackLeg, "LeftBackLeg");
	m_Mesh->AddChild(ColliderHeadAttack, "Head");
	m_Mesh->AddChild(ColliderLeftArmAttack, "LeftFoot");
	m_Mesh->AddChild(ColliderRightArmAttack, "RightFoot");

	return true;
}

void CJagras::Start()
{
	CGameObject::Start();
}

void CJagras::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);


	//FSM.Update();//Update에서 매 프레임마다 fsm 상태 갱신

}

void CJagras::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CJagras* CJagras::Clone()
{
	return DBG_NEW CJagras(*this);
}