#include "IMGUIWindow.h"
#include "IMGUIWidget.h"
#include "IMGUIManager.h"
#include "Engine.h"
#include "Input.h"

CIMGUIWindow::CIMGUIWindow()	:
	m_Open(true),
	m_ModalPopup(false),
	m_Start(false),
	m_Focus(true),
	m_WheelUpFunc(nullptr),
	m_WheelDownFunc(nullptr)
{
	m_WindowFlag = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize;
}

CIMGUIWindow::~CIMGUIWindow()
{
	size_t	Size = m_vecPopupWidget.size();

	for (size_t i = 0; i < Size; ++i)
	{
		SAFE_DELETE(m_vecPopupWidget[i]);
	}

	m_vecPopupWidget.clear();

	Size = m_vecWidget.size();

	for (size_t i = 0; i < Size; ++i)
	{
		SAFE_DELETE(m_vecWidget[i]);
	}

	m_vecWidget.clear();
}

void CIMGUIWindow::Open()
{
	m_Open = true;
}

void CIMGUIWindow::Close()
{
	m_Open = false;
}

void CIMGUIWindow::ClosePopup()
{
	ImGui::CloseCurrentPopup();

	size_t	Size = m_vecPopupWidget.size();

	for (size_t i = 0; i < Size; ++i)
	{
		SAFE_DELETE(m_vecPopupWidget[i]);
	}

	m_vecPopupWidget.clear();
}

CIMGUIWidget* CIMGUIWindow::FindWidget(const std::string& Name)
{
	size_t Size = m_vecWidget.size();

	for (size_t i = 0; i < Size; ++i)
	{
		if (m_vecWidget[i]->m_Name == Name)
			return m_vecWidget[i];
	}

	return nullptr;
}

bool CIMGUIWindow::IsKeyDown(unsigned char Key)
{
	if (!CEngine::GetInst()->IsFocus() && !m_Focus)
		return false;

	ImGuiKey ImGuiKey = -1;

	// 필요 시 더 추가할 것. (만약 없는 키였을 경우 imgui_impl_win32.cpp에도 넣을것)
	switch (Key)
	{
	case 'W':
		ImGuiKey = ImGuiKey_W;
		break;
	case 'S':
		ImGuiKey = ImGuiKey_S;
		break;
	case 'A':
		ImGuiKey = ImGuiKey_A;
		break;
	case 'D':
		ImGuiKey = ImGuiKey_D;
		break;
	case 'Q':
		ImGuiKey = ImGuiKey_Q;
		break;
	case 'E':
		ImGuiKey = ImGuiKey_E;
		break;
	case VK_F1:
		ImGuiKey = ImGuiKey_F1;
		break;
	case VK_F2:
		ImGuiKey = ImGuiKey_F2;
		break;
	case VK_F3:
		ImGuiKey = ImGuiKey_F3;
		break;
	case VK_F4:
		ImGuiKey = ImGuiKey_F4;
		break;
	case VK_ESCAPE:
		ImGuiKey = ImGuiKey_Escape;
		break;
	case VK_SPACE:
		ImGuiKey = ImGuiKey_Space;
		break;
	}

	return ImGuiKey == -1 ? false : ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey), false, 0.001f, 0.001f);
}

bool CIMGUIWindow::IsKeyPush(unsigned char Key)
{
	if (!CEngine::GetInst()->IsFocus() && !m_Focus)
		return false;

	ImGuiKey ImGuiKey = -1;

	// 필요 시 더 추가할 것. (만약 없는 키였을 경우 imgui_impl_win32.cpp에도 넣을것)
	switch (Key)
	{
	case 'W':
		ImGuiKey = ImGuiKey_W;
		break;
	case 'S':
		ImGuiKey = ImGuiKey_S;
		break;
	case 'A':
		ImGuiKey = ImGuiKey_A;
		break;
	case 'D':
		ImGuiKey = ImGuiKey_D;
		break;
	case 'Q':
		ImGuiKey = ImGuiKey_Q;
		break;
	case 'E':
		ImGuiKey = ImGuiKey_E;
		break;
	case VK_F1:
		ImGuiKey = ImGuiKey_F1;
		break;
	case VK_F2:
		ImGuiKey = ImGuiKey_F2;
		break;
	case VK_F3:
		ImGuiKey = ImGuiKey_F3;
		break;
	case VK_F4:
		ImGuiKey = ImGuiKey_F4;
		break;
	case VK_ESCAPE:
		ImGuiKey = ImGuiKey_Escape;
		break;
	case VK_SPACE:
		ImGuiKey = ImGuiKey_Space;
		break;
	case VK_TAB:
		ImGuiKey = ImGuiKey_Tab;
		break;
	}

	return ImGuiKey == -1 ? false : ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey), true, 0.001f, 0.001f);
}

bool CIMGUIWindow::IsKeyUp(unsigned char Key)
{
	if (!CEngine::GetInst()->IsFocus() && !m_Focus)
		return false;

	ImGuiKey ImGuiKey = -1;

	// 필요 시 더 추가할 것. (만약 없는 키였을 경우 imgui_impl_win32.cpp에도 넣을것)
	switch (Key)
	{
	case 'W':
		ImGuiKey = ImGuiKey_W;
		break;
	case 'S':
		ImGuiKey = ImGuiKey_S;
		break;
	case 'A':
		ImGuiKey = ImGuiKey_A;
		break;
	case 'D':
		ImGuiKey = ImGuiKey_D;
		break;
	case 'Q':
		ImGuiKey = ImGuiKey_Q;
		break;
	case 'E':
		ImGuiKey = ImGuiKey_E;
		break;
	case VK_F1:
		ImGuiKey = ImGuiKey_F1;
		break;
	case VK_F2:
		ImGuiKey = ImGuiKey_F2;
		break;
	case VK_F3:
		ImGuiKey = ImGuiKey_F3;
		break;
	case VK_F4:
		ImGuiKey = ImGuiKey_F4;
		break;
	case VK_ESCAPE:
		ImGuiKey = ImGuiKey_Escape;
		break;
	case VK_SPACE:
		ImGuiKey = ImGuiKey_Space;
		break;
	}

	return ImGuiKey == -1 ? false : ImGui::IsKeyReleased(ImGui::GetKeyIndex(ImGuiKey));
}

bool CIMGUIWindow::Init()
{
	return true;
}

bool CIMGUIWindow::Start()
{
	return true;
}

void CIMGUIWindow::Update(float DeltaTime)
{
	m_Focus = ImGui::IsWindowFocused(ImGuiFocusedFlags_AnyWindow);

	if (CEngine::GetInst()->IsFocus() || m_Focus)
	{
		ImGuiIO	IO = ImGui::GetIO();
		

		if (IsKeyDown(VK_F12))
			CEngine::GetInst()->Exit();

		if (IO.MouseWheel > 0.f)
		{
			if (m_WheelUpFunc)
				m_WheelUpFunc(DeltaTime);
		}

		else if (IO.MouseWheel < 0.f)
		{
			if (m_WheelDownFunc)
				m_WheelDownFunc(DeltaTime);
		}
	}

	if (!m_Open)
		return;

	if (!ImGui::Begin(m_Name.c_str(), &m_Open, m_WindowFlag))
		m_Open = false;

	CIMGUIManager::GetInst()->SetCurrentFont();

	size_t Size = m_vecWidget.size();

	for (size_t i = 0; i < Size; ++i)
	{
		m_vecWidget[i]->Render();
	}

	CIMGUIManager::GetInst()->ResetCurrentFont();

	ImGui::End();
}
