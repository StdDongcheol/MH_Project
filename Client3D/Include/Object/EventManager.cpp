
#include "EventManager.h"
#include "Input.h"
#include "Scene/Scene.h"
#include "Scene/SceneManager.h"
#include "Component/CameraComponent.h"

DEFINITION_SINGLE(CEventManager)

CEventManager::CEventManager()
{
}

CEventManager::~CEventManager()
{
	ClearAllCallback();

	m_mapEvent.clear();
}

bool CEventManager::Init()
{
	// AddEventName �Լ��� ����� Key���� ����Ͻø� �˴ϴ�

	AddEventName("BossDead");				// �������� ���� ����
	AddEventName("BossDeadEnd");			// �������� ���� ����
	AddEventName("PlayerMonsterContant");	// ���Ϳ� ���� ����
	AddEventName("PlayerMonsterRelease");	// ���Ϳ� ���� ����
	AddEventName("QuestAcept");				// ����Ʈ ���� ���� �޸��뽺 ��ȯ ���
	AddEventName("SceneFadeInStart");		// �� ��ȯ ��, FadeIn ����
	AddEventName("SceneFadeOutStart");		// �� ��ȯ ������ FadeOut ����


	CInput::GetInst()->SetKeyCallback<CEventManager>("Shake", Key_State::KeyState_Down, this, &CEventManager::ShakeOn);


	return true;
}

void CEventManager::ShakeOn()
{
	CSceneManager::GetInst()->GetScene()->GetCameraManager()->GetCurrentCamera()->ShakeOn();
}
