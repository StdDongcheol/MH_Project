#include "IMGUITree.h"

CIMGUITree::CIMGUITree()	:
	m_Flag(ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_None)
{
}

CIMGUITree::~CIMGUITree()
{
}

bool CIMGUITree::Init()
{
	if (!CIMGUIWidget::Init())
		return false;

	return true;
}

bool CIMGUITree::Render()
{
	if (!CIMGUIWidget::Render())
		return false;

	else if (ImGui::TreeNodeEx(m_Name.c_str(), m_Flag))
	{
		ShowWidget(true);

		ImGui::TreePop();
	}

	else
		ShowWidget(false);

	return true;
}

void CIMGUITree::Enable(bool IsEnable)
{
	m_Enable = IsEnable;

	ShowWidget(IsEnable);
}

void CIMGUITree::Disable()
{
	CIMGUIWidget::Disable();

	ShowWidget(false);
}

void CIMGUITree::ShowWidget(bool IsShow)
{
	size_t Size = m_vecWidget.size();

	for (size_t i = 0; i < Size; ++i)
	{
		m_vecWidget[i]->Hide(!IsShow);
	}
}