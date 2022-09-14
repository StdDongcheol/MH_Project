
#include "MainWindow.h"
#include "../Scene/StartSceneMode.h"
#include "../Scene/LoadingSceneMode.h"
#include "../Object/EventManager.h"
#include "Widget/Image.h"
#include "Scene/Viewport.h"
#include "Scene/Scene.h"
#include "Scene/SceneResource.h"
#include "Scene/SceneManager.h"
#include "Component/CameraComponent.h"
#include "Component/SceneComponent.h"
#include "Input.h"
#include "../Object/FlameEffect.h"
#include "../Object/TargetingCamera.h"
#include "../Object/ObjectManager.h"
#include "../Object/Mernos.h"

CMainWindow::CMainWindow() :
	m_LoadType(Stage_Type::None),
	m_FadeSetStart(false),
	m_FadeSetTime(1.0f),
	m_FadeSetTimeAcc(0.f)
{
	SetTypeID<CMainWindow>();
}

CMainWindow::CMainWindow(const CMainWindow& Window) :
	CWidgetWindow(Window)
{
}

CMainWindow::~CMainWindow()
{
}

void CMainWindow::Start()
{
	CWidgetWindow::Start();
}

bool CMainWindow::Init()
{
	if (!CWidgetWindow::Init())
	{
		return false;
	}

	SetZOrder(10);

	SetSize(0.f, 0.f);

	m_FadeImage = CreateWidget<CImage>("FadeImage");

	m_FadeImage->SetSize(1280.f, 720.f);
	m_FadeImage->SetZOrder(1);
	m_FadeImage->SetTexture("LoadingBack", TEXT("LoadingBack.jpg"));
	m_FadeImage->SetTextureTint(Vector4().Black);
	m_FadeImage->SetOpacity(0.f);
	m_FadeImage->SetFadeSpeed(1.f);

	m_FadeImage->AddFadeCallback<CMainWindow>(Widget_Fade_State::FadeIn, this, &CMainWindow::FadeOutCallback);
	m_FadeImage->AddFadeCallback<CMainWindow>(Widget_Fade_State::FadeOut, this, &CMainWindow::FadeInCallback);

	CInput::GetInst()->SetKeyCallback<CMainWindow>("CameraDeploy", Key_State::KeyState_Down, this, &CMainWindow::CameraDeploy);

	CEventManager::GetInst()->AddEventCallback<CMainWindow>("QuestAcept", this, &CMainWindow::CameraDeploy);

	CEventManager::GetInst()->AddEventCallback<CMainWindow>("SceneFadeInStart", this, &CMainWindow::FadeInStart);
	CEventManager::GetInst()->AddEventCallback<CMainWindow>("SceneFadeOutStart", this, &CMainWindow::FadeOutStart);

	return true;
}

void CMainWindow::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);

	if (m_FadeSetStart)
	{
		m_FadeSetTimeAcc += DeltaTime;

		if (m_FadeSetTimeAcc > m_FadeSetTime)
		{
			m_FadeSetStart = false;

			CEventManager::GetInst()->CallEvent("SceneFadeOutStart");
		}
	}
}

void CMainWindow::PostUpdate(float DeltaTime)
{
	CWidgetWindow::PostUpdate(DeltaTime);
}

void CMainWindow::Render()
{
	CWidgetWindow::Render();
}

/// <summary>
/// �����Ȳ.
/// 
/// �޸��뽺 ȣ���ϸ� 
/// �÷��̾ ���ڱ� ��û���ӵ��� ���ư��鼭 �޸��뽺���� �� ����ä�� ���ư�.
/// ī�޶� ������ �������°Ű�����
/// �ٵ� ���ư��鼭 SceneFadeOut ȣ���� �ȵǴ°Ͱ���(���Ǽ�. Ȯ�ιٶ�.)
/// ��Ȯ�� ��� �������� �ľ��� ���� �ȵ���.
/// </summary>

void CMainWindow::CameraDeploy()
{
	m_FadeSetStart = true;

	// �޸��뽺 ȣ��, �÷��̾� ȣ��ִϸ��̼� ���۽� �Ʒ� ���� �����ؾ���.
	m_RotCam = GetViewport()->GetScene()->CreateGameObject<CTargetingCamera>("RotCam");
	CGameObject* Player = GetViewport()->GetScene()->GetPlayerObject();

	Vector3 CamPos = ((CSceneComponent*)Player->FindComponent("CamPosBox"))->GetWorldPos();
	CamPos.y -= 1.f;

	m_RotCam->SetCameraFixedPos(CamPos);
	m_RotCam->SetLookAtTarget(Player, "HitBreath");
	m_RotCam->SetMoveDir(Vector3().Zero);
}

void CMainWindow::LeavingMernosDeploy()
{
	//CGameObject* PlayerObj = CSceneManager::GetInst()->GetPlayerObject();
	//
	//Vector3 PlayerPos = PlayerObj->GetWorldPos();
	//
	//PlayerPos.y += 15.f;
	//
	//Vector3 PlayerDir = PlayerObj->GetWorldAxis(AXIS::AXIS_Z);
	//
	//CMernos* Mernos = CSceneManager::GetInst()->GetScene()->CreateGameObject<CMernos>("Mernos");
	//Mernos->SetWorldPos(PlayerPos + PlayerDir * 30.f);
	//
	//CObjectManager::GetInst()->SaveCheckToPointFunc(Check_Type::LoadingToStage);
}

// ȭ�� ����ȭ ����
void CMainWindow::FadeInStart()
{
	m_FadeImage->SetPos(0.f, 0.f);
	m_FadeImage->SetOpacity(1.f);
	m_FadeImage->SetFadeOut(true);
}

// ȭ�� ���� ��ĥ ����
void CMainWindow::FadeOutStart()
{
	m_FadeImage->SetPos(0.f, 0.f);
	m_FadeImage->SetOpacity(0.f);
	m_FadeImage->SetFadeIn(true);
}

// �ء� ȥ�� ����!! �ء�
// ȭ���� ������ ������������ ȣ��Ǵ� Callback.
void CMainWindow::FadeInCallback()
{
}

// �ء� ȥ�� ����!! �ء�
// ȭ�� ���� ��ĥ�� ������ �������� ȣ��Ǵ� Callback.
void CMainWindow::FadeOutCallback()
{
	CSceneManager::GetInst()->CreateNextScene();
	CSceneManager::GetInst()->CreateSceneMode<CLoadingSceneMode>(false);

	CInput::GetInst()->ClearCallback();
}
