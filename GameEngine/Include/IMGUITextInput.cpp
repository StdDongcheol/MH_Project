#include "IMGUITextInput.h"

CIMGUITextInput::CIMGUITextInput()	:
	m_TextType(ImGuiText_Type::String),
	m_Text{},
	m_wText{},
	m_TextUTF8{},
	m_HintText{},
	m_wHintText{},
	m_HintTextUTF8{},
	m_MultiLine(false),
	m_Flag(ImGuiInputTextFlags_CharsNoBlank),
	m_ValueInt(0),
	m_ValueFloat(0.f),
	m_IntMin(0),
	m_IntMax(10000),
	m_ValueIntSpeed(100),
	m_IntStep(1)
{
	strcpy_s(m_FloatSize, "%.1f");
}

CIMGUITextInput::~CIMGUITextInput()
{
}

void CIMGUITextInput::SetText(float f)
{
	char	Text[8] = {};

	sprintf_s(Text, "%.f", f);

	SetText(Text);
}

bool CIMGUITextInput::Init()
{
	return true;
}

bool CIMGUITextInput::Render()
{
	if (!CIMGUIWidget::Render())
		return false;

	bool	Input = false;

	ImGui::PushItemWidth(m_Size.x);

	if (m_MultiLine)
	{
		Input = ImGui::InputTextMultiline(m_Name.c_str(), m_Text, 1024, m_Size, m_Flag);
	}

	else
	{
		switch (m_TextType)
		{
		case ImGuiText_Type::String:
			if (strlen(m_HintText) > 0)
				Input = ImGui::InputTextWithHint(m_Name.c_str(), m_HintText, m_Text, 1024, m_Flag);

			else
				Input = ImGui::InputText(m_Name.c_str(), m_Text, 1024, m_Flag);
			break;
		case ImGuiText_Type::Int:
			if (m_ValueInt < m_IntMin)
				m_ValueInt = m_IntMin;

			else if (m_ValueInt > m_IntMax)
				m_ValueInt = m_IntMax;

			Input = ImGui::InputInt(m_Name.c_str(), &m_ValueInt, m_IntStep, m_ValueIntSpeed, m_Flag);
			break;
		case ImGuiText_Type::Float:
			Input = ImGui::InputFloat(m_Name.c_str(), &m_ValueFloat, 0.f, 0.f, m_FloatSize, m_Flag);
			break;
		}
	}

	if (Input)
	{
		if (m_TextType == ImGuiText_Type::String)
		{
			memset(m_wText, 0, sizeof(wchar_t) * 1024);
			memset(m_TextUTF8, 0, sizeof(char) * 1024);

			int	Length = MultiByteToWideChar(CP_ACP, 0, m_Text, -1, 0, 0);
			MultiByteToWideChar(CP_ACP, 0, m_Text, -1, m_wText, Length);

			// UTF8로 변환한다.
			Length = WideCharToMultiByte(CP_UTF8, 0, m_wText, -1, 0, 0, 0, 0);
			WideCharToMultiByte(CP_UTF8, 0, m_wText, -1, m_TextUTF8, Length, 0, 0);
		}

		if (m_InputCallback)
			m_InputCallback();
	}

	return true;
}
