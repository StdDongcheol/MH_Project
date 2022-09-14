#include "IMGUIWidget.h"
#include "Engine.h"
#include "IMGUIWindow.h"

CIMGUIWidget::CIMGUIWidget() :
	m_Owner(nullptr),
	m_Font(nullptr),
	m_Color{ 1.f, 1.f, 1.f, 1.f },
	m_Size{ 100.f, 100.f },
	m_Enable(true),
	m_TreeHide(false),
	m_MouseCheck(false),
	m_IsHovered(false),
	m_IsClicked(false)
{
}

CIMGUIWidget::~CIMGUIWidget()
{
}

bool CIMGUIWidget::Init()
{
	return true;
}

bool CIMGUIWidget::Render()
{
	return m_Enable && !m_TreeHide;
}

bool CIMGUIWidget::IsKeyDown(unsigned char Key)
{
	if (!CEngine::GetInst()->IsFocus() && !m_Owner->IsFocus())
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

bool CIMGUIWidget::IsKeyPush(unsigned char Key)
{
	if (!CEngine::GetInst()->IsFocus() && !m_Owner->IsFocus())
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

	return ImGuiKey == -1 ? false : ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey), true, 0.001f, 0.001f);
}

bool CIMGUIWidget::IsKeyUp(unsigned char Key)
{
	if (!CEngine::GetInst()->IsFocus() && !m_Owner->IsFocus())
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

void CIMGUIWidget::CheckItemHovered()
{
	if (m_MouseCheck)
		m_IsHovered = ImGui::IsItemHovered();
}

void CIMGUIWidget::CheckItemClicked()
{
	if (m_MouseCheck)
		m_IsClicked = ImGui::IsItemClicked();
}
