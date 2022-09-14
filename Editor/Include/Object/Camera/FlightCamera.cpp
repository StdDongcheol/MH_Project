
#include "FlightCamera.h"
#include "Input.h"
#include "Scene/Scene.h"
#include "IMGUIGizmo.h"
#include "../../EditorManager.h"
#include "../../Window/ObjectWindow.h"

CFlightCamera::CFlightCamera() :
	m_CenterPoint{},
	m_FlightSpeed(140.f),
	m_UseCam(false),
	m_Gizmo(nullptr)
{
	SetTypeID<CFlightCamera>();
}

CFlightCamera::CFlightCamera(const CFlightCamera& obj) :
	CGameObject(obj)
{
	m_Arm = (CArm*)FindComponent("Arm");
	m_Camera = (CCameraComponent*)FindComponent("Camera");

	m_Gizmo = nullptr;
}

CFlightCamera::~CFlightCamera()
{
}

void CFlightCamera::Start()
{
	CGameObject::Start();

	m_Gizmo = (CIMGUIGizmo*)CEditorManager::GetInst()->GetObjectWindow()->FindWidget("Gizmo");
}

bool CFlightCamera::Init()
{
	m_Arm = CreateComponent<CArm>("Arm");

	m_Camera = m_Scene->GetCameraManager()->GetCurrentCamera();

	m_Arm->AddChild(m_Camera);

	m_Camera->SetInheritRotX(true);
	m_Camera->SetInheritRotY(true);
	m_Camera->SetInheritRotZ(true);


	Resolution RS = CEngine::GetInst()->GetRS();

	m_CenterPoint.x = (LONG)(RS.Width / 2);
	m_CenterPoint.y = (LONG)(RS.Height / 2);

	ClientToScreen(CEngine::GetInst()->GetWindowHandle(), &m_CenterPoint);

	CInput::GetInst()->SetKeyCallback<CFlightCamera>("Front", KeyState_Push, this, &CFlightCamera::MoveFront);
	CInput::GetInst()->SetKeyCallback<CFlightCamera>("Back", KeyState_Push, this, &CFlightCamera::MoveBack);
	CInput::GetInst()->SetKeyCallback<CFlightCamera>("Left", KeyState_Push, this, &CFlightCamera::MoveLeft);
	CInput::GetInst()->SetKeyCallback<CFlightCamera>("Right", KeyState_Push, this, &CFlightCamera::MoveRight);
	CInput::GetInst()->SetKeyCallback<CFlightCamera>("Up", KeyState_Push, this, &CFlightCamera::MoveUp);
	CInput::GetInst()->SetKeyCallback<CFlightCamera>("Down", KeyState_Push, this, &CFlightCamera::MoveDown);

	m_Arm->SetWorldPos(50.f, 50.f, -20.f);

	return true;
}

void CFlightCamera::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	RotationX(DeltaTime);

	if (m_Gizmo->IsHovered())
	{
		if (m_Gizmo->IsKeyPush('W'))
			MoveFront(DeltaTime);

		if (m_Gizmo->IsKeyPush('S'))
			MoveBack(DeltaTime);

		if (m_Gizmo->IsKeyPush('A'))
			MoveLeft(DeltaTime);

		if (m_Gizmo->IsKeyPush('D'))
			MoveRight(DeltaTime);

		if (m_Gizmo->IsKeyPush('Q'))
			MoveUp(DeltaTime);

		if (m_Gizmo->IsKeyPush('E'))
			MoveDown(DeltaTime);
	}
}

void CFlightCamera::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CFlightCamera* CFlightCamera::Clone()
{
	return DBG_NEW CFlightCamera(*this);
}

void CFlightCamera::MoveFront(float DeltaTime)
{
	if (!m_UseCam)
		return;

	Vector3 CamZ = m_Camera->GetWorldAxis(AXIS::AXIS_Z);

	m_Arm->AddWorldPos(CamZ * m_FlightSpeed * DeltaTime);
}

void CFlightCamera::MoveBack(float DeltaTime)
{
	if (!m_UseCam)
		return;

	Vector3 CamZ = m_Camera->GetWorldAxis(AXIS::AXIS_Z);

	m_Arm->AddWorldPos(CamZ * -m_FlightSpeed * DeltaTime);
}

void CFlightCamera::MoveLeft(float DeltaTime)
{
	if (!m_UseCam)
		return;

	Vector3 CamX = m_Camera->GetWorldAxis(AXIS::AXIS_X);

	m_Arm->AddWorldPos(CamX * -m_FlightSpeed * DeltaTime);
}

void CFlightCamera::MoveRight(float DeltaTime)
{
	if (!m_UseCam)
		return;

	Vector3 CamX = m_Camera->GetWorldAxis(AXIS::AXIS_X);

	m_Arm->AddWorldPos(CamX * m_FlightSpeed * DeltaTime);
}

void CFlightCamera::MoveUp(float DeltaTime)
{
	if (!m_UseCam)
		return;

	Vector3 CamY = m_Camera->GetWorldAxis(AXIS::AXIS_Y);

	m_Arm->AddWorldPos(CamY * m_FlightSpeed * DeltaTime);
}

void CFlightCamera::MoveDown(float DeltaTime)
{
	if (!m_UseCam)
		return;

	Vector3 CamY = m_Camera->GetWorldAxis(AXIS::AXIS_Y);

	m_Arm->AddWorldPos(CamY * -m_FlightSpeed * DeltaTime);
}

void CFlightCamera::RotationX(float DeltaTime)
{
	if (!m_UseCam)
		return;

	POINT MousePoint = {};

	GetCursorPos(&MousePoint);

	m_MouseMove.y += (float)(MousePoint.x - m_CenterPoint.x) / 5.f;
	m_MouseMove.x += (float)(MousePoint.y - m_CenterPoint.y) / 5.f;

	m_Arm->SetRelativeRotationY(m_MouseMove.y);
	m_Arm->SetRelativeRotationX(m_MouseMove.x);

	if (m_MouseMove.x >= 89.f)
	{
		m_MouseMove.x = 89.f;
		m_Arm->SetRelativeRotationX(m_MouseMove.x);
	}

	else if (m_MouseMove.x <= -89.f)
	{ 
		m_MouseMove.x = -89.f;
		m_Arm->SetRelativeRotationX(m_MouseMove.x);
	}

	SetCursorPos(m_CenterPoint.x, m_CenterPoint.y);
}
