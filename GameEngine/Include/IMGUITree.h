#pragma once
#include "IMGUIWidget.h"
class CIMGUITree :
    public CIMGUIWidget
{
	friend class CIMGUIWindow;

protected:
	CIMGUITree();
	virtual ~CIMGUITree();

private:
	std::vector<CIMGUIWidget*>	m_vecWidget;
	ImGuiTreeNodeFlags_			m_Flag;

public:
	void AddWidget(CIMGUIWidget* IncludeWidget)
	{
		size_t Size = m_vecWidget.size();

		for (size_t i = 0; i < Size; ++i)
		{
			if (m_vecWidget[i] == IncludeWidget)
				return;
		}

		m_vecWidget.push_back(IncludeWidget);
	}

	void DefaultOpen()
	{
		m_Flag = ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_DefaultOpen;
	}

public:
	bool IsOpened()	const
	{
		return ImGui::IsItemToggledOpen();
	}

public:
	virtual bool Init();
	virtual bool Render();
	virtual void Enable(bool IsEnable = true);
	virtual void Disable();

private:
	void ShowWidget(bool IsShow);
};

