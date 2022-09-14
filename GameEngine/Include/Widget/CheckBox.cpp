#include "CheckBox.h"
#include "WidgetWindow.h"
#include "../Scene/Viewport.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Input.h"
#include "../Resource/ResourceManager.h"
#include "../Scene/SceneManager.h"

CCheckBox::CCheckBox() :
	IsChecked(true)
{
}

CCheckBox::CCheckBox(const CCheckBox& widget) :
	CWidget(widget)
{
	IsChecked = true;


}

CCheckBox::~CCheckBox()
{
}

bool CCheckBox::SetTexture(bool Checked, const std::string& Name, const TCHAR* FileName, const std::string& PathName)
{
	if (m_Owner->GetViewport())
	{
		if (!m_Owner->GetViewport()->GetScene()->GetResource()->LoadTexture(Name, FileName, PathName))
			return false;

		if (false == Checked)
		{
			Info[0].Texture = m_Owner->GetViewport()->GetScene()->GetResource()->FindTexture(Name);
		}
		else
		{
			Info[1].Texture = m_Owner->GetViewport()->GetScene()->GetResource()->FindTexture(Name);
		}
		
	}

	else
	{
		if (!CResourceManager::GetInst()->LoadTexture(Name, FileName, PathName))
			return false;

		if (false == Checked)
		{
			Info[0].Texture = m_Owner->GetViewport()->GetScene()->GetResource()->FindTexture(Name);
		}
		else
		{
			Info[1].Texture = m_Owner->GetViewport()->GetScene()->GetResource()->FindTexture(Name);
		}
	}

	SetUseTexture(true);

	return true;
}

bool CCheckBox::SetTextureFullPath(bool Checked, const std::string& Name, const TCHAR* FullPath)
{
	if (m_Owner->GetViewport())
	{
		if (!m_Owner->GetViewport()->GetScene()->GetResource()->LoadTextureFullPath(Name, FullPath))
			return false;

		if (false == Checked)
		{
			Info[0].Texture = m_Owner->GetViewport()->GetScene()->GetResource()->FindTexture(Name);
		}
		else
		{
			Info[1].Texture = m_Owner->GetViewport()->GetScene()->GetResource()->FindTexture(Name);
		}
	}

	else
	{
		if (!CResourceManager::GetInst()->LoadTextureFullPath(Name, FullPath))
			return false;

		if (false == Checked)
		{
			Info[0].Texture = m_Owner->GetViewport()->GetScene()->GetResource()->FindTexture(Name);
		}
		else
		{
			Info[1].Texture = m_Owner->GetViewport()->GetScene()->GetResource()->FindTexture(Name);
		}
	}

	SetUseTexture(true);

	return true;
}

void CCheckBox::SetTextureTint(bool Checked, const Vector4& Tint)
{
	if (false==Checked)
	{
		Info[0].Tint = Tint;
	}
	else
	{
		Info[1].Tint = Tint;
	}
}

void CCheckBox::SetTextureTint(bool Checked, unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
	if (false == Checked)
	{
		Info[0].Tint = Vector4(r / 255.f, g / 255.f, b / 255.f, a / 255.f);
	}
	else
	{
		Info[1].Tint = Vector4(r / 255.f, g / 255.f, b / 255.f, a / 255.f);
	}

	
}

void CCheckBox::Start()
{
	CWidget::Start();


	for (int i = 0; i < 2; ++i)
	{
		if (!Info[i].vecFrameData.empty())
			Info[i].FrameTime = Info[i].PlayTime / Info[i].vecFrameData.size();
	}
}

bool CCheckBox::Init()
{
	if (!CWidget::Init())
		return false;

	return true;
}

void CCheckBox::Update(float DeltaTime)
{
	CWidget::Update(DeltaTime);

	if (CInput::GetInst()->IsDown("Attack")&&m_MouseHovered)
	{
		if (IsChecked)
		{
			IsChecked = false;
		}
		else
		{
			IsChecked = true;
		}
		if (m_ClickCallback)
			m_ClickCallback();
	}	
}

void CCheckBox::PostUpdate(float DeltaTime)
{
	CWidget::PostUpdate(DeltaTime);
}

void CCheckBox::Render()
{
	
	if (false == IsChecked)
	{
		if (Info[0].Texture)
			Info[0].Texture->SetShader(0, (int)Buffer_Shader_Type::Pixel, 0);

		m_Tint = Info[0].Tint;
	}
	else
	{
		if (Info[1].Texture)
			Info[1].Texture->SetShader(0, (int)Buffer_Shader_Type::Pixel, 0);

		m_Tint = Info[1].Tint;
	}
	


	CWidget::Render();
}

CCheckBox* CCheckBox::Clone()
{
	return new CCheckBox(*this);
}
