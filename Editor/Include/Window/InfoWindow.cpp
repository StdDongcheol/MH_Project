
#include "InfoWindow.h"
#include "HierarchyWindow.h"
#include "IMGUIText.h"
#include "IMGUISameLine.h"
#include "Input.h"
#include "Scene/SceneManager.h"
#include "Scene/Scene.h"
#include "../EditorManager.h"

CInfoWindow::CInfoWindow()	:
	m_Hierarchy(nullptr),
	m_CamUI(nullptr),
	m_DDTUI(nullptr),
	m_ObjNameUI(nullptr),
	m_ObjPosUI(nullptr),
	m_DDTPosText{},
	m_CamPosText{},
	m_ObjPosText{},
	m_UseDDTPosText(false)
{
}

CInfoWindow::~CInfoWindow()
{
}

bool CInfoWindow::Init()
{
	CIMGUISameLine* Line = nullptr;
	CIMGUIText* Text = nullptr;

	m_Hierarchy = CEditorManager::GetInst()->GetHierarchyWindow();

	Text = AddWidget<CIMGUIText>("Text");
	Text->SetText("카메라 위치 ");

	Line = AddWidget<CIMGUISameLine>("Line");

	m_CamUI = AddWidget<CIMGUIText>("CamUI");

	//

	Text = AddWidget<CIMGUIText>("DDTText");
	Text->SetText("지형 마우스 위치 ");

	Line = AddWidget<CIMGUISameLine>("Line");

	m_DDTUI = AddWidget<CIMGUIText>("DDTUI");

	//

	Text = AddWidget<CIMGUIText>("ObjName");
	Text->SetText("이름 ");

	Line = AddWidget<CIMGUISameLine>("Line");

	m_ObjNameUI = AddWidget<CIMGUIText>("ObjNameUI");

	//

	Text = AddWidget<CIMGUIText>("ObjPos");
	Text->SetText("위치 ");

	Line = AddWidget<CIMGUISameLine>("Line");

	m_ObjPosUI = AddWidget<CIMGUIText>("ObjPosUI");

	return true;
}

void CInfoWindow::Update(float DeltaTime)
{
	CIMGUIWindow::Update(DeltaTime);

	ViewCamPos();
	ViewDDTPos();
	ViewSelectObject();
}
void CInfoWindow::ViewCamPos()
{
	m_CamPos = CSceneManager::GetInst()->GetScene()->GetCameraManager()->GetCurrentCamera()->GetWorldPos();

	memset(m_CamPosText, 0, sizeof(char) * 64);
	sprintf_s(m_CamPosText, "X : %.f, Y : %.f, Z : %.f", m_CamPos.x, m_CamPos.y, m_CamPos.z);
	m_CamUI->SetText(m_CamPosText);
}

void CInfoWindow::ViewDDTPos()
{
	memset(m_DDTPosText, 0, sizeof(char) * 64);
	sprintf_s(m_DDTPosText, "X : %.f, Y : %.f, Z : %.f", m_DDTPos.x, m_DDTPos.y, m_DDTPos.z);
	m_DDTUI->SetText(m_DDTPosText);
}


void CInfoWindow::ViewSelectObject()
{
	if (m_ObjName == "")
		m_ObjNameUI->SetText("없음");

	else
		m_ObjNameUI->SetText(m_ObjName.c_str());

	memset(m_ObjPosText, 0, sizeof(char) * 64);
	sprintf_s(m_ObjPosText, "X : %.1f, Y : %.1f, Z : %.1f", m_ObjPos.x, m_ObjPos.y, m_ObjPos.z);
	m_ObjPosUI->SetText(m_ObjPosText);
}
