
#include "Player.h"
#include "PlayerAnimation.h"
#include "Input.h"
#include "Scene/Scene.h"
#include "Resource/Animation/AnimationSequence.h"
#include "Engine.h"

CPlayer::CPlayer()
{
	SetTypeID<CPlayer>();
}

CPlayer::CPlayer(const CPlayer& obj)
{
	m_Mesh = (CAnimationMeshComponent*)FindComponent("PlayerMeshComponent");
	m_ColliderBox = (CColliderBox3D*)FindComponent("PlayerBox");
}

CPlayer::~CPlayer()
{
}

bool CPlayer::Init()
{
	m_Mesh = CreateComponent<CAnimationMeshComponent>("PlayerMeshComponent");
	m_Face = CreateComponent<CStaticMeshComponent>("PlayerFaceMeshComponent");
	m_ColliderBox = CreateComponent<CColliderBox3D>("PlayerBox");

	SetRootComponent(m_Mesh);

	m_Mesh->AddChild(m_ColliderBox);
	m_ColliderBox->Set3DExtent(2.f, 4.f, 1.f);
	m_ColliderBox->SetOffset(0.f, m_ColliderBox->GetInfo().Length.z, 0.f);
	m_ColliderBox->SetCollisionProfile("Player");

	m_Mesh->SetMesh("PlayerMesh");
	m_Mesh->CreateAnimationInstance<CPlayerAnimation>();

	m_Mesh->SetRelativeScale(0.05f, 0.05f, 0.05f);
	m_Mesh->SetPivot(0.5f, 0.f, 0.5f);

	m_Face->SetMesh("PlayerFaceMesh");
	m_Face->SetRelativeRotation(90.f, 0.f, 0.f);
	m_Face->SetRelativePos(0.f, -4.f, -12.f);
	m_Face->SetTransformState(Transform_State::None);
	m_Mesh->AddChild(m_Face, "PlayerFace");

	m_Mesh->SetWorldRotation(Vector3(0.f, 180.f, 0.f));
	return true;
}

void CPlayer::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CPlayer::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CPlayer* CPlayer::Clone()
{
	return DBG_NEW CPlayer(*this);
}