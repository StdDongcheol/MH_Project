#include "Vespoid.h"
#include "VespoidAnimation.h"
#include "Input.h"
#include "Resource/Animation/AnimationSequence.h"
#include "Engine.h"
#include "Scene/SceneManager.h"

CVespoid::CVespoid()
{
	SetTypeID<CVespoid>();
	CurYRot = 180.f;
}

CVespoid::CVespoid(const CVespoid& obj)
{
	m_Mesh = (CAnimationMeshComponent*)FindComponent("Mesh");
}

CVespoid::~CVespoid()
{
}

bool CVespoid::Init()
{
	m_Mesh = CreateComponent<CAnimationMeshComponent>("Mesh");


	ColliderUpperBody = CreateComponent<CColliderBox3D>("ColliderUpperBody");
	ColliderLowerBody = CreateComponent<CColliderBox3D>("ColliderLowerBody");

	ColliderAttack = CreateComponent<CColliderBox3D>("ColliderAttack");


	ColliderUpperBody->Set3DExtent(2.0f, 1.0f, 2.0f);
	ColliderLowerBody->Set3DExtent(1.0f, 1.0f, 1.0f);

	ColliderAttack->Set3DExtent(0.5f, 1.5f, 0.5f);

	ColliderUpperBody->SetCollisionProfile("Monster");
	ColliderLowerBody->SetCollisionProfile("Monster");

	ColliderAttack->SetCollisionProfile("MonsterAttack");

	SetRootComponent(m_Mesh);
	m_Mesh->SetTransformState(Transform_State::None);
	m_State = Transform_State::None;
	m_Mesh->SetMesh("VespoidMesh");
	m_Mesh->CreateAnimationInstance<CVespoidAnimation>();

	m_Mesh->SetRelativeScale(0.05f, 0.05f, 0.05f);
	m_Mesh->SetRelativeRotation(Vector3(250.f, 180.f, 180.f));

	m_Mesh->AddChild(ColliderUpperBody, "UpperBody");
	m_Mesh->AddChild(ColliderLowerBody, "LowerBody");
	m_Mesh->AddChild(ColliderAttack, "Attack");

	ColliderCarving = CreateComponent<CColliderBox3D>("ColliderCarving");
	ColliderCarving->Set3DExtent(4.0f, 4.0f, 4.0f);
	ColliderCarving->SetCollisionProfile("Carving");
	m_Mesh->AddChild(ColliderCarving);
	ColliderCarving->Enable(false);

	return true;
}

void CVespoid::Start()
{
	CGameObject::Start();
}

void CVespoid::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);


	
	//FSM.Update();//Update에서 매 프레임마다 fsm 상태 갱신
	

	
}

void CVespoid::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);



	
}

CVespoid* CVespoid::Clone()
{
	return DBG_NEW CVespoid(*this);
}

