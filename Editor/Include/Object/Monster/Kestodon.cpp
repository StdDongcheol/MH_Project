#include "Kestodon.h"
#include "KestodonAnimation.h"
#include "Input.h"
#include "Resource/Animation/AnimationSequence.h"
#include "Engine.h"
#include "Scene/SceneManager.h"

CKestodon::CKestodon() 
{
	SetTypeID<CKestodon>();
	CurYRot = 180.f;
}

CKestodon::CKestodon(const CKestodon& obj)
{
	m_Mesh = (CAnimationMeshComponent*)FindComponent("Mesh");
}

CKestodon::~CKestodon()
{
}

bool CKestodon::Init()
{
	m_Mesh = CreateComponent<CAnimationMeshComponent>("Mesh");

	ColliderHead = CreateComponent<CColliderBox3D>("ColliderHead");
	ColliderUpperBody = CreateComponent<CColliderBox3D>("ColliderUpperBody");
	ColliderLowerBody = CreateComponent<CColliderBox3D>("ColliderLowerBody");
	ColliderLowerLowerBody = CreateComponent<CColliderBox3D>("ColliderLowerLowerBody");
	ColliderTail = CreateComponent<CColliderBox3D>("ColliderTail");
	ColliderLeftLeg = CreateComponent<CColliderBox3D>("ColliderLeftLeg");
	ColliderRightLeg = CreateComponent<CColliderBox3D>("ColliderRightLeg");
	ColliderHeadAttack = CreateComponent<CColliderBox3D>("ColliderHeadAttack");

	ColliderHead->Set3DExtent(2.5f, 2.5f, 2.5f);
	ColliderUpperBody->Set3DExtent(2.f, 2.f, 2.f);
	ColliderLowerBody->Set3DExtent(3.f, 3.f, 3.f);
	ColliderLowerLowerBody->Set3DExtent(2.f, 2.f, 2.f);
	ColliderTail->Set3DExtent(2.f, 2.f, 2.f);
	ColliderLeftLeg->Set3DExtent(1.2f, 1.8f, 1.2f);
	ColliderRightLeg->Set3DExtent(1.2f, 1.8f, 1.2f);
	ColliderHeadAttack->Set3DExtent(2.5f, 2.5f, 2.5f);

	ColliderHead->SetCollisionProfile("Monster");
	ColliderUpperBody->SetCollisionProfile("Monster");
	ColliderLowerBody->SetCollisionProfile("Monster");
	ColliderLowerLowerBody->SetCollisionProfile("Monster");
	ColliderTail->SetCollisionProfile("Monster");
	ColliderLeftLeg->SetCollisionProfile("Monster");
	ColliderRightLeg->SetCollisionProfile("Monster");
	ColliderHeadAttack->SetCollisionProfile("MonsterAttack");

	SetRootComponent(m_Mesh);
	m_Mesh->SetTransformState(Transform_State::Ground);
	m_State = Transform_State::Ground;
	m_Mesh->SetMesh("KestodonMesh");
	m_Mesh->CreateAnimationInstance<CKestodonAnimation>();

	m_Mesh->SetRelativeScale(0.05f, 0.05f, 0.05f);
	m_Mesh->SetRelativeRotation(Vector3(270.f, 180.f, 180.f));

	m_Mesh->AddChild(ColliderHead, "Head");
	m_Mesh->AddChild(ColliderUpperBody, "UpperBody");
	m_Mesh->AddChild(ColliderLowerBody, "LowerBody");
	m_Mesh->AddChild(ColliderLowerLowerBody, "LowerLowerBody");
	m_Mesh->AddChild(ColliderTail, "Tail");
	m_Mesh->AddChild(ColliderLeftLeg, "LeftLeg");
	m_Mesh->AddChild(ColliderRightLeg, "RightLeg");
	m_Mesh->AddChild(ColliderHead, "Head");

	ColliderCarving = CreateComponent<CColliderBox3D>("ColliderCarving");
	ColliderCarving->Set3DExtent(6.0f, 6.0f, 6.0f);
	ColliderCarving->SetCollisionProfile("Carving");
	m_Mesh->AddChild(ColliderCarving);
	ColliderCarving->Enable(false);

	return true;
}

void CKestodon::Start()
{
	CGameObject::Start();
}

void CKestodon::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	//FSM.Update();//Update에서 매 프레임마다 fsm 상태 갱신
		
}

void CKestodon::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);



}

CKestodon* CKestodon::Clone()
{
	return DBG_NEW CKestodon(*this);
}