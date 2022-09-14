#include "Slider.h"
#include "WidgetWindow.h"
#include "../Scene/Viewport.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Input.h"
#include "../Resource/ResourceManager.h"
#include "../Scene/SceneManager.h"
#include "../HDR.h"

CSlider::CSlider() 
{

}

CSlider::CSlider(const CSlider& widget) :
	CWidget(widget)
{
	
	m_ClickCallback = nullptr;
	
}

CSlider::~CSlider()
{
}

bool CSlider::SetTexture(const std::string& Name, const TCHAR* FileName, const std::string& PathName)
{
	if (m_Owner->GetViewport())
	{
		if (!m_Owner->GetViewport()->GetScene()->GetResource()->LoadTexture(Name, FileName, PathName))
			return false;

		m_Info.Texture = m_Owner->GetViewport()->GetScene()->GetResource()->FindTexture(Name);
	}

	else
	{
		if (!CResourceManager::GetInst()->LoadTexture(Name, FileName, PathName))
			return false;

		m_Info.Texture = CResourceManager::GetInst()->FindTexture(Name);
	}

	SetUseTexture(true);

	return true;
}

bool CSlider::SetTextureFullPath(const std::string& Name, const TCHAR* FullPath)
{
	if (m_Owner->GetViewport())
	{
		if (!m_Owner->GetViewport()->GetScene()->GetResource()->LoadTextureFullPath(Name, FullPath))
			return false;

		m_Info.Texture = m_Owner->GetViewport()->GetScene()->GetResource()->FindTexture(Name);
	}

	else
	{
		if (!CResourceManager::GetInst()->LoadTextureFullPath(Name, FullPath))
			return false;

		m_Info.Texture = CResourceManager::GetInst()->FindTexture(Name);
	}

	SetUseTexture(true);

	return true;
}

void CSlider::SetTextureTint(const Vector4& Tint)
{
	m_Info.Tint = Tint;
}

void CSlider::SetTextureTint(unsigned char r, unsigned char g,
	unsigned char b, unsigned char a)
{
	m_Info.Tint = Vector4(r / 255.f, g / 255.f, b / 255.f, a / 255.f);
}

void CSlider::AddFrameData(const Vector2& Start, const Vector2& Size)
{
	AnimationFrameData	Data;
	Data.Start = Start;
	Data.Size = Size;

	m_Info.vecFrameData.push_back(Data);
}

void CSlider::SetPlayTime(float PlayTime)
{
	m_Info.PlayTime = PlayTime;
}

void CSlider::SetPlayScale(float PlayScale)
{
	m_Info.PlayScale = PlayScale;
}


void CSlider::Start()
{
	CWidget::Start();

	
	if (!m_Info.vecFrameData.empty())
		m_Info.FrameTime = m_Info.PlayTime / m_Info.vecFrameData.size();
	
}

bool CSlider::Init()
{
	if (!CWidget::Init())
		return false;

	return true;
}

void CSlider::Update(float DeltaTime)
{
	CWidget::Update(DeltaTime);	
}

void CSlider::PostUpdate(float DeltaTime)
{
	CWidget::PostUpdate(DeltaTime);
}

void CSlider::Render()
{
	if (m_Info.Texture)
		m_Info.Texture->SetShader(0, (int)Buffer_Shader_Type::Pixel, 0);

	m_Tint = m_Info.Tint;

	CWidget::Render();
}

CSlider* CSlider::Clone()
{
	return new CSlider(*this);
}
