
#include "EditorScene.h"
#include "Input.h"
#include "IMGUIGizmo.h"
#include "Scene/Scene.h"
#include "../EditorManager.h"
#include "../Object/Camera/FlightCamera.h"
#include "../Object/LandScape/LandScapeObj.h"
#include "../Window/ObjectWindow.h"
#include "../Window/HierarchyWindow.h"

CEditorScene::CEditorScene()	:
	m_Camera(nullptr),
	m_PickingObject(nullptr),
	m_ObjectWindow(nullptr),
	m_HierarchyWindow(nullptr),
	m_RenderWindow(nullptr),
	m_Gizmo(nullptr),
	m_UseCam(false),
	m_Play(false),
	m_UseBrushMode(false),
	m_UseHeightBrush(false),
	m_UseSplattingBrush(false),
	m_First(false),
	m_BrushMinRange(1.f),
	m_BrushMaxRange(10000.f),
	m_BrushRange(5.f),
	m_BrushRangeScale(5.f)
{
	SetTypeID<CEditorScene>();
}

CEditorScene::~CEditorScene()
{
}

void CEditorScene::Start()
{
	CInput::GetInst()->SetKeyCallback("CamToggle", Key_State::KeyState_Down, this, &CEditorScene::CamToggle);

	//CInput::GetInst()->SetKeyCallback("Space", Key_State::KeyState_Down, this, &CEditorScene::Space);

	CInput::GetInst()->SetKeyCallback("LClick", Key_State::KeyState_Down, this, &CEditorScene::LClickDown);
	CInput::GetInst()->SetKeyCallback("LClick", Key_State::KeyState_Push, this, &CEditorScene::LClickPush);
	CInput::GetInst()->SetKeyCallback("LClick", Key_State::KeyState_Up, this, &CEditorScene::LClickUp);
	CInput::GetInst()->SetKeyCallback("RClick", Key_State::KeyState_Down, this, &CEditorScene::RClickDown);
	CInput::GetInst()->SetKeyCallback("RClick", Key_State::KeyState_Push, this, &CEditorScene::RClickPush);
	CInput::GetInst()->SetKeyCallback("RClick", Key_State::KeyState_Up, this, &CEditorScene::RClickUp);

	m_ObjectWindow = CEditorManager::GetInst()->GetObjectWindow();
	m_HierarchyWindow = CEditorManager::GetInst()->GetHierarchyWindow();

	m_Gizmo = (CIMGUIGizmo*)m_ObjectWindow->FindWidget("Gizmo");
}

bool CEditorScene::Init()
{
	if (!CSceneMode::Init())
		return false;

	LoadFBX();
	LoadLandScape();
	LoadPlayer();
	LoadMonster();
	LoadFieldObj();

	m_Camera = m_Scene->CreateGameObject<CFlightCamera>("Camera");

	m_Scene->AddIgnoreTypeID(typeid(CLandScapeObj).hash_code());

	return true;
}

void CEditorScene::Update(float DeltaTime)
{
	CSceneMode::Update(DeltaTime);

	CLandScapeObj* LandScape = CEditorManager::GetInst()->GetLandScapeObj();

	if (LandScape)
		LandScape->SetBrushType(CEditorManager::GetInst()->GetBrushType());

	if (!m_First)
	{
		m_First = true;

		CResourceManager::GetInst()->SoundPlay("EditorBGM");
	}
}

void CEditorScene::CamToggle()
{
	if (m_Play)
		return;

	m_UseCam = !m_UseCam;

	m_Camera->SetUseCam(m_UseCam);
}

void CEditorScene::Space(float DeltaTime)
{
}

void CEditorScene::LClickDown(float DeltaTime)
{
	if (m_ObjectWindow)
	{
		CLandScapeObj* LandScape = CEditorManager::GetInst()->GetLandScapeObj();

		if (!LandScape)
			return;

		if (m_ObjectWindow->IsBrushMode())
		{
			LandScape->SetBrushType(m_ObjectWindow->GetBrushType());

			if (CEditorManager::GetInst()->GetObjectWindow()->GetBrushEditType() == (int)BrushEdit_Type::Height)
				m_UseHeightBrush = true;

			else if (CEditorManager::GetInst()->GetObjectWindow()->GetBrushEditType() == (int)BrushEdit_Type::Splatting)
				m_UseSplattingBrush = true;
		}
	}
}

void CEditorScene::LClickPush(float DeltaTime)
{
	CLandScapeObj* LandScape = CEditorManager::GetInst()->GetLandScapeObj();

	if (!LandScape)
		return;

	if (m_UseHeightBrush)
		LandScape->PlayBrush(DeltaTime, true);

	else if (m_UseSplattingBrush)
		LandScape->PlaySplatting(DeltaTime, true, m_ObjectWindow->GetLandScapeType());
}

void CEditorScene::LClickUp(float DeltaTime)
{
	m_UseHeightBrush = false;
	m_UseSplattingBrush = false;

	if (!m_ObjectWindow->IsBrushMode())
	{
		CGameObject* PickingObj = nullptr;

		if (m_Scene->PickingBox(PickingObj))
		{
			CEditorManager::GetInst()->GetHierarchyWindow()->CancelType();
			CEditorManager::GetInst()->GetHierarchyWindow()->SelectObject(PickingObj->GetName());
		}
	}
}

void CEditorScene::RClickDown(float DeltaTime)
{
	if (m_ObjectWindow)
	{
		CLandScapeObj* LandScape = CEditorManager::GetInst()->GetLandScapeObj();

		if (!LandScape)
			return;

		if (m_ObjectWindow->IsBrushMode())
		{
			LandScape->SetBrushType(m_ObjectWindow->GetBrushType());

			if (CEditorManager::GetInst()->GetObjectWindow()->GetBrushEditType() == (int)BrushEdit_Type::Height)
				m_UseHeightBrush = true;

			else if (CEditorManager::GetInst()->GetObjectWindow()->GetBrushEditType() == (int)BrushEdit_Type::Splatting)
				m_UseSplattingBrush = true;
		}
	}
}

void CEditorScene::RClickPush(float DeltaTime)
{
	CLandScapeObj* LandScape = CEditorManager::GetInst()->GetLandScapeObj();

	if (!LandScape)
		return;

	if (m_UseHeightBrush)
		LandScape->PlayBrush(DeltaTime, false);

	else if (m_UseSplattingBrush)
		LandScape->PlaySplatting(DeltaTime, false, m_ObjectWindow->GetLandScapeType());
}

void CEditorScene::RClickUp(float DeltaTime)
{
	m_UseHeightBrush = false;
	m_UseSplattingBrush = false;
}

void CEditorScene::Exit(float DeltaTime)
{
	CEngine::GetInst()->Exit();
}

void CEditorScene::WheelUp(float DeltaTime)
{
	if (m_UseBrushMode)
	{
		CLandScapeObj* LandScape = CEditorManager::GetInst()->GetLandScapeObj();

		if (LandScape)
		{
			m_BrushRange += m_BrushRangeScale;

			if (m_BrushRange > m_BrushMaxRange)
				m_BrushRange = m_BrushMaxRange;

			LandScape->SetBrushRange(m_BrushRange);
		}
	}
}

void CEditorScene::WheelDown(float DeltaTime)
{
	if (m_UseBrushMode)
	{
		CLandScapeObj* LandScape = CEditorManager::GetInst()->GetLandScapeObj();

		if (LandScape)
		{
			m_BrushRange -= m_BrushRangeScale;

			if (m_BrushRange < m_BrushMinRange)
				m_BrushRange = m_BrushMinRange;

			LandScape->SetBrushRange(m_BrushRange);
		}
	}
}

void CEditorScene::SetBrushModeRange()
{
	CLandScapeObj* LandScape = CEditorManager::GetInst()->GetLandScapeObj();

	if (LandScape)
		LandScape->SetBrushRange(m_BrushRange);
}

Vector3 CEditorScene::GetCameraPos()	const
{
	return m_Camera->GetWorldPos();
}

Vector3 CEditorScene::GetCameraFrontPos(float Dist) const
{
	return m_Camera->GetWorldPos() + m_Camera->GetWorldAxis(AXIS::AXIS_Z) * Dist;
}

void CEditorScene::AddLandScape(std::vector<TCHAR*>& vec, const TCHAR* Path)
{
	TCHAR* FileName = DBG_NEW TCHAR[MAX_PATH];
	memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);
	lstrcpy(FileName, Path);
	vec.push_back(FileName);
}

void CEditorScene::SetLandScape(int Register, const std::string& Name, std::vector<TCHAR*>& vecFileName, const std::string& PathName)
{
	CMaterial* Material = m_Scene->GetResource()->FindMaterial("LandScape");

	Material->AddTextureArray(Register, (int)Buffer_Shader_Type::Pixel, Name, vecFileName, PathName);

	SAFE_DELETE_ARRAY_VECLIST(vecFileName);
}