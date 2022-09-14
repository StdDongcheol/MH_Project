
#include "Widget.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Scene/CameraManager.h"
#include "../Component/CameraComponent.h"
#include "../Resource/Shader/WidgetConstantBuffer.h"
#include "../Resource/Shader/PaperBurnConstantBuffer.h"
#include "../Resource/ResourceManager.h"
#include "../Scene/SceneManager.h"

CWidget::CWidget() :
	m_Owner(nullptr),
	m_ZOrder(0),
	m_Start(false),
	m_Angle(0.f),
	m_CBuffer(nullptr),
	m_PaperCBuffer(nullptr),
	m_Size(50.f, 50.f),
	m_UsePivot(false),
	m_MouseHovered(false),
	m_CollisionMouseEnable(true),
	m_Opacity(1.f),
	m_FadeSpeed(1.f),
	m_FadeAnimSet(false),
	m_FadeIn(false),
	m_FadeOut(false),
	m_FadeRepeat(false),
	m_FadeAnimSetTime(0.f),
	m_FadeAnimTime(0.f),
	m_FinishTime(1.f),
	m_Filter(0.f),
	m_UsePaperBurn(false),
	m_StartPaperBurn(false),
	m_FadeInTime(0.f),
	m_FadeInTimeAcc(0.f),
	m_FadeOutTime(0.f),
	m_FadeOutTimeAcc(0.f),
	m_DurationTime(0.f),
	m_DurationTimeAcc(0.f),
	m_FadeLoop(false),
	m_FadeState(Widget_Fade_State::Duration)
{
}

CWidget::CWidget(const CWidget& widget)
{
	*this = widget;

	m_RefCount = 0;

	m_Owner = nullptr;
	m_MouseHovered = false;

	m_CBuffer = new CWidgetConstantBuffer;

	m_CBuffer->Init();
}

CWidget::~CWidget()
{
	SAFE_DELETE(m_CBuffer);

	SAFE_DELETE(m_PaperCBuffer);
}

CMaterial* CWidget::GetMeshMaterial(int Index) const
{
	return m_Mesh->GetMaterial(Index);
}

void CWidget::SetShader(const std::string& Name)
{
	if (m_Owner->GetViewport())
		m_Shader = m_Owner->GetViewport()->GetScene()->GetResource()->FindShader(Name);

	else
		m_Shader = CResourceManager::GetInst()->FindShader(Name);
}

void CWidget::SetUseTexture(bool Use)
{
	m_CBuffer->SetUseTexture(Use);
}

void CWidget::SetUsePaperBurn(bool Use)
{
	m_UsePaperBurn = Use;

	m_PaperCBuffer = new CPaperBurnConstantBuffer;

	m_PaperCBuffer->Init();

	m_PaperCBuffer->SetOutColor(Vector4(0.95f, 0.95f, 0.95f, 0.8f));
	m_PaperCBuffer->SetInColor(Vector4(0.9f, 0.9f, 0.9f, 0.95f));
	m_PaperCBuffer->SetCenterColor(Vector4(0.15f, 0.7f, 0.85f, 1.f));	// 밝은 하늘색

	m_PaperCBuffer->SetOutFilter(0.02f);
	m_PaperCBuffer->SetInFilter(0.02f);
	m_PaperCBuffer->SetCenterFilter(0.04f);
}

void CWidget::StartPaperBurn()
{
	if (m_StartPaperBurn)
		return;

	m_CBuffer->SetPaperBurnEnable(true);
	m_StartPaperBurn = true;
}

void CWidget::SetPaperMaterial(CMaterial* Material)
{
	m_Mesh->AddMaterialSlot(Material);

	m_Mesh->GetMaterial(0)->AddRenderCallback(this, &CWidget::SetPaperBurnShader);
}

void CWidget::SetInverse(bool Enable)
{
	m_PaperCBuffer->SetInverse(Enable);
}

void CWidget::SetBurnTexture(const std::string& Name, const TCHAR* FileName, const std::string& PathName)
{
	if (m_Owner->GetViewport())
	{
		m_Owner->GetViewport()->GetScene()->GetResource()->LoadTexture(Name, FileName, PathName);

		m_BurnTexture = GetOwner()->GetViewport()->GetScene()->GetResource()->FindTexture(Name);
	}

	else
	{
		CResourceManager::GetInst()->LoadTexture(Name, FileName, PathName);

		m_BurnTexture = CResourceManager::GetInst()->FindTexture(Name);
	}
}

void CWidget::SetOutLineColor(const Vector4& Color)
{
	m_PaperCBuffer->SetOutColor(Color);
}

void CWidget::SetOutLineColor(float r, float g, float b, float a)
{
	m_PaperCBuffer->SetOutColor(r, g, b, a);
}

void CWidget::SetInLineColor(const Vector4& Color)
{
	m_PaperCBuffer->SetInColor(Color);
}

void CWidget::SetInLineColor(float r, float g, float b, float a)
{
	m_PaperCBuffer->SetInColor(r, g, b, a);
}

void CWidget::SetCenterLineColor(const Vector4& Color)
{
	m_PaperCBuffer->SetCenterColor(Color);
}

void CWidget::SetCenterLineColor(float r, float g, float b, float a)
{
	m_PaperCBuffer->SetCenterColor(r, g, b, a);
}

void CWidget::SetInFilter(float Filter)
{
	m_PaperCBuffer->SetInFilter(Filter);
}

void CWidget::SetOutFilter(float Filter)
{
	m_PaperCBuffer->SetOutFilter(Filter);
}

void CWidget::SetCenterFilter(float Filter)
{
	m_PaperCBuffer->SetCenterFilter(Filter);
}

void CWidget::SetPaperBurnShader()
{
	m_PaperCBuffer->UpdateCBuffer();

	m_BurnTexture->SetShader(101, (int)Buffer_Shader_Type::Pixel, 0);
}

void CWidget::CallFadeCallback(Widget_Fade_State State)
{
	auto	iter = m_FadeCallback[(int)State].begin();
	auto	iterEnd = m_FadeCallback[(int)State].end();

	for (; iter != iterEnd; ++iter)
	{
		(*iter)();
	}
}

void CWidget::Start()
{
	m_Start = true;

	if (m_FadeIn)
		m_Opacity = 0.f;
}

bool CWidget::Init()
{
	if (m_Owner->GetViewport())
		m_Shader = m_Owner->GetViewport()->GetScene()->GetResource()->FindShader("WidgetShader");

	else
		m_Shader = CResourceManager::GetInst()->FindShader("WidgetShader");


	if (m_Owner->GetViewport())
		m_Mesh = m_Owner->GetViewport()->GetScene()->GetResource()->FindMesh("WidgetMesh");

	else
		m_Mesh = CResourceManager::GetInst()->FindMesh("WidgetMesh");

	SetBurnTexture("DefaultBurnTexture", TEXT("DefaultPaperBurn.png"));


	m_CBuffer = new CWidgetConstantBuffer;

	m_CBuffer->Init();

	return true;
}

void CWidget::Update(float DeltaTime)
{
	if (!m_Start)
		Start();

	if (m_StartPaperBurn)
	{
		m_Filter += DeltaTime / m_FinishTime;

		if (m_Filter >= 1.f)
		{
			m_Filter = 1.f;
		}

		m_PaperCBuffer->SetFilter(m_Filter);
	}


	// WidgetWindow에서 Render상태를 제어하기 위한 FadeIn, Out의 Update 구간.
	if (m_FadeOut)
	{
		SetOpacity(m_Opacity - (m_FadeSpeed * DeltaTime));

		if (m_Opacity <= 0.f)
		{
			SetOpacity(0.f);
			CallFadeCallback(Widget_Fade_State::FadeOut);
			SetFadeOut(false);
		}
	}

	if (m_FadeIn)
	{
		SetOpacity(m_Opacity + (m_FadeSpeed * DeltaTime));

		if (m_Opacity >= 1.f)
		{
			CallFadeCallback(Widget_Fade_State::FadeIn);
			SetOpacity(1.f);

			if (m_FadeAnimSet)
			{
				m_FadeAnimTime += DeltaTime;

				if (m_FadeAnimTime >= m_FadeAnimSetTime)
				{
					m_FadeAnimTime -= m_FadeAnimTime;
					SetFadeOut(true);
					SetFadeIn(false);
					m_FadeAnimSet = false;
				}
			}

			else
			{
				SetFadeIn(false);
			}
		}
	}

	if (m_FadeRepeat)
	{
		if (m_Opacity >= 1.f)
		{
			SetFadeOut(true);
		}

		else if (m_Opacity <= 0.f)
		{
			SetFadeIn(true);
		}
	}


	// Widget 단독 FadeIn, Out 적용 Update 구간.
	switch (m_FadeState)
	{
	case Widget_Fade_State::FadeIn:
		m_FadeInTimeAcc += DeltaTime;

		SetOpacity(m_FadeInTimeAcc / m_FadeInTime);

		if (m_FadeInTimeAcc >= m_FadeInTime)
		{
			CallFadeCallback(Widget_Fade_State::FadeIn);

			m_FadeState = Widget_Fade_State::Duration;

			SetOpacity(1.f);
		}
		break;
	case Widget_Fade_State::FadeOut:
		m_FadeOutTimeAcc += DeltaTime;

		SetOpacity(1.f - m_FadeOutTimeAcc / m_FadeOutTime);

		if (m_FadeOutTimeAcc >= m_FadeOutTime)
		{
			m_FadeInTimeAcc = 0.f;
			m_FadeOutTimeAcc = 0.f;
			m_DurationTimeAcc = 0.f;

			if (m_FadeLoop)
			{
				if (m_FadeInTime > 0.f)
				{
					m_FadeState = Widget_Fade_State::FadeIn;
					SetOpacity(0.f);
				}

				else
				{
					m_FadeState = Widget_Fade_State::Duration;
					SetOpacity(1.f);
				}
			}

			else
			{
				CallFadeCallback(Widget_Fade_State::FadeOut);
				Enable(false);
			}
		}
		break;
	case Widget_Fade_State::Duration:
		if (m_DurationTime > 0.f)
		{
			m_DurationTimeAcc += DeltaTime;

			if (m_DurationTimeAcc >= m_DurationTime)
			{
				if (m_FadeOutTime > 0.f)
					m_FadeState = Widget_Fade_State::FadeOut;

				else if (m_FadeLoop)
				{
					m_FadeInTimeAcc = 0.f;
					m_FadeOutTimeAcc = 0.f;
					m_DurationTimeAcc = 0.f;

					if (m_FadeInTime > 0.f)
					{
						m_FadeState = Widget_Fade_State::FadeIn;
						SetOpacity(0.f);
					}
				}

				else
				{
					CallFadeCallback(Widget_Fade_State::Duration);
					Enable(false);
				}
			}
		}
		break;
	}

}

void CWidget::PostUpdate(float DeltaTime)
{
	if (!m_Start)
		Start();

	m_RenderPos = m_Pos;

	if (m_Owner)
		m_RenderPos += m_Owner->GetWindowPos();
}

void CWidget::Render()
{
	if (!m_Start)
		Start();

	Matrix	matScale, matRot, matTrans;

	matScale.Scaling(m_Size.x, m_Size.y, 1.f);
	matRot.Rotation(0.f, 0.f, m_Angle);
	matTrans.Translation(m_RenderPos.x, m_RenderPos.y, 0.f);

	CCameraComponent* UICamera = nullptr;

	if (m_Owner->GetViewport())
		UICamera = m_Owner->GetViewport()->GetScene()->GetCameraManager()->GetUICamera();

	else
		UICamera = CSceneManager::GetInst()->GetScene()->GetCameraManager()->GetUICamera();

	Matrix	matWP = matScale * matRot * matTrans * UICamera->GetProjMatrix();
	matWP.Transpose();

	if (m_PaperCBuffer)
	{
		m_PaperCBuffer->UpdateCBuffer();

		m_BurnTexture->SetShader(101, (int)Buffer_Shader_Type::Pixel, 0);
	}

	m_CBuffer->SetWP(matWP);
	m_CBuffer->SetTint(m_Tint);
	m_CBuffer->SetOpacity(m_Opacity);
	m_CBuffer->SetPaperBurnEnable(m_StartPaperBurn);
	m_CBuffer->SetPivot(m_UsePivot);

	m_CBuffer->UpdateCBuffer();

	m_Shader->SetShader();

	m_Mesh->Render();
}

bool CWidget::CollisionMouse(const Vector2& MousePos)
{
	this;
	if (!m_CollisionMouseEnable)
		return false;

	if (m_RenderPos.x > MousePos.x)
	{
		return false;
	}
	else if (m_RenderPos.x + m_Size.x < MousePos.x)
	{
		return false;
	}
	else if (m_RenderPos.y > MousePos.y)
	{
		return false;
	}
	else if (m_RenderPos.y + m_Size.y < MousePos.y)
	{
		return false;
	}
	
	return true;
}

CWidget* CWidget::Clone()
{
	return new CWidget(*this);
}
