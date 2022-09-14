
#include "SceneMode.h"
#include "../Input.h"
#include "../Engine.h"
#include "../GameObject/GameObject.h"

CSceneMode::CSceneMode()	:
	m_Scene(nullptr)
{
	SetTypeID<CSceneMode>();
}

CSceneMode::~CSceneMode()
{
}

void CSceneMode::SetPlayerObject(CGameObject* Obj)
{
	m_PlayerObject = Obj;
}

void CSceneMode::Start()
{
}

bool CSceneMode::Init()
{
	CInput::GetInst()->CreateKey("ToggleRenderCollision", VK_F2);
	CInput::GetInst()->SetKeyCallback("ToggleRenderCollision", Key_State::KeyState_Up, this, &CSceneMode::ToggleRenderCollision);

	return true;
}

void CSceneMode::Update(float DeltaTime)
{
}

void CSceneMode::PostUpdate(float DeltaTime)
{
}

void CSceneMode::ToggleRenderCollision(float DeltaTime)
{
	CEngine::GetInst()->ToggleRenderCollision();
}
