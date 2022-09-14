
#include "BillboardComponent.h"
#include "../GameObject/GameObject.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Scene/CameraManager.h"
#include "CameraComponent.h"
#include "../Animation/AnimationSequence2DInstance.h"
#include "../Resource/Shader/Standard2DConstantBuffer.h"
#include "../Render/RenderManager.h"

CBillboardComponent::CBillboardComponent()	:
	m_Animation(nullptr),
	m_FadeInTime(0.f),
	m_FadeInTimeAcc(0.f),
	m_FadeOutTime(0.f),
	m_FadeOutTimeAcc(0.f),
	m_DurationTime(0.f),
	m_DurationTimeAcc(0.f),
	m_FadeLoop(false),
	m_FadeState(Fade_State::Duration)
{
	SetTypeID<CBillboardComponent>();
	m_Render = true;

	SetLayerName("Particle");
}

CBillboardComponent::CBillboardComponent(const CBillboardComponent& com) :
	CSceneComponent(com)
{
	m_Mesh = com.m_Mesh;

	if (com.m_Animation)
		m_Animation = com.m_Animation->Clone();

	if (com.m_Material)
		m_Material = com.m_Material->Clone();
}

CBillboardComponent::~CBillboardComponent()
{
	SAFE_DELETE(m_Animation);
}

void CBillboardComponent::SetMaterial(const std::string& Name)
{
	m_Material = m_Scene->GetResource()->FindMaterial(Name);
}

void CBillboardComponent::SetMaterial(CMaterial* Material)
{
	m_Material = Material;
}

void CBillboardComponent::SetBaseColor(const Vector4& Color)
{
	m_Material->SetBaseColor(Color);
}

void CBillboardComponent::SetBaseColor(float r, float g, float b, float a)
{
	m_Material->SetBaseColor(r, g, b, a);
}

void CBillboardComponent::SetRenderState(CRenderState* State)
{
	m_Material->SetRenderState(State);
}

void CBillboardComponent::SetRenderState(const std::string& Name)
{
	m_Material->SetRenderState(Name);
}

void CBillboardComponent::SetTransparency(bool Enable)
{
	m_Material->SetTransparency(Enable);
}

void CBillboardComponent::SetOpacity(float Opacity)
{
	m_Material->SetOpacity(Opacity);
}

void CBillboardComponent::AddOpacity(float Opacity)
{
	m_Material->AddOpacity(Opacity);
}

void CBillboardComponent::AddTexture(int Register, int ShaderType, const std::string& Name, CTexture* Texture)
{
	m_Material->AddTexture(Register, ShaderType, Name, Texture);
}

void CBillboardComponent::AddTexture(int Register, int ShaderType, const std::string& Name, const TCHAR* FileName,
	const std::string& PathName)
{
	m_Material->AddTexture(Register, ShaderType, Name, FileName, PathName);
}

void CBillboardComponent::AddTextureFullPath(int Register, int ShaderType, const std::string& Name, const TCHAR* FullPath)
{
	m_Material->AddTextureFullPath(Register, ShaderType, Name, FullPath);
}

void CBillboardComponent::AddTexture(int Register, int ShaderType, const std::string& Name,
	const std::vector<TCHAR*>& vecFileName, const std::string& PathName)
{
	m_Material->AddTexture(Register, ShaderType, Name, vecFileName, PathName);
}

void CBillboardComponent::SetTexture(int Index, int Register, int ShaderType, const std::string& Name, CTexture* Texture)
{
	m_Material->SetTexture(Index, Register, ShaderType, Name, Texture);
}

void CBillboardComponent::SetTexture(int Index, int Register, int ShaderType, const std::string& Name, const TCHAR* FileName,
	const std::string& PathName)
{
	m_Material->SetTexture(Index, Register, ShaderType, Name, FileName, PathName);
}

void CBillboardComponent::SetTextureFullPath(int Index, int Register, int ShaderType, const std::string& Name,
	const TCHAR* FullPath)
{
	m_Material->SetTextureFullPath(Index, Register, ShaderType, Name, FullPath);
}

void CBillboardComponent::SetTexture(int Index, int Register, int ShaderType, const std::string& Name,
	const std::vector<TCHAR*>& vecFileName, const std::string& PathName)
{
	m_Material->SetTexture(Index, Register, ShaderType, Name, vecFileName, PathName);
}
void CBillboardComponent::Start()
{
	CSceneComponent::Start();

	if (m_Animation)
		m_Animation->Start();
}

bool CBillboardComponent::Init()
{
	if (!CSceneComponent::Init())
		return false;

	m_Mesh = (CSpriteMesh*)m_Scene->GetResource()->FindMesh("SpriteMesh");
	m_Material = m_Scene->GetResource()->FindMaterial("Billboard")->Clone();

	SetPivot(0.5f, 0.5f, 0.f);
	SetRelativeScale(1.f, 1.f, 1.f);
	SetMeshSize(1.f, 1.f, 0.f);

	return true;
}

void CBillboardComponent::Update(float DeltaTime)
{
	CSceneComponent::Update(DeltaTime);

	if (m_Animation)
		m_Animation->Update(DeltaTime);

	Matrix matView = m_Scene->GetCameraManager()->GetCurrentCamera()->GetViewMatrix();

	memset(&matView._41, 0, sizeof(Vector3));

	matView.Inverse();

	m_Transform->SetRotationAxis(matView);

	// Fade State Logic
	switch (m_FadeState)
	{
	case Fade_State::FadeIn:
		m_FadeInTimeAcc += DeltaTime;

		m_Material->SetOpacity(m_FadeInTimeAcc / m_FadeInTime);

		if (m_FadeInTimeAcc >= m_FadeInTime)
		{
			m_FadeState = Fade_State::Duration;

			m_Material->SetOpacity(1.f);
		}
		break;
	case Fade_State::FadeOut:
		m_FadeOutTimeAcc += DeltaTime;

		m_Material->SetOpacity(1.f - m_FadeOutTimeAcc / m_FadeOutTime);

		if (m_FadeOutTimeAcc >= m_FadeOutTime)
		{
			if (m_FadeLoop)
			{
				m_FadeInTimeAcc = 0.f;
				m_FadeOutTimeAcc = 0.f;
				m_DurationTimeAcc = 0.f;

				if (m_FadeInTime > 0.f)
				{
					m_FadeState = Fade_State::FadeIn;
					m_Material->SetOpacity(0.f);
				}

				else
				{
					m_FadeState = Fade_State::Duration;
					m_Material->SetOpacity(1.f);
				}
			}

			else
				m_Object->Destroy();
		}
		break;
	case Fade_State::Duration:
		if (m_DurationTime > 0.f)
		{
			m_DurationTimeAcc += DeltaTime;

			if (m_DurationTimeAcc >= m_DurationTime)
			{
				if (m_FadeOutTime > 0.f)
					m_FadeState = Fade_State::FadeOut;

				else if (m_FadeLoop)
				{
					m_FadeInTimeAcc = 0.f;
					m_FadeOutTimeAcc = 0.f;
					m_DurationTimeAcc = 0.f;

					if (m_FadeInTime > 0.f)
					{
						m_FadeState = Fade_State::FadeIn;
						m_Material->SetOpacity(0.f);
					}
				}

				else
					m_Object->Destroy();
			}
		}
		break;
	}

}

void CBillboardComponent::PostUpdate(float DeltaTime)
{
	CSceneComponent::PostUpdate(DeltaTime);
}

void CBillboardComponent::PrevRender()
{
	CSceneComponent::PrevRender();
}

void CBillboardComponent::Render()
{
	CSceneComponent::Render();

	if (m_Animation)
	{
		CRenderManager::GetInst()->GetStandard2DCBuffer()->SetAnimation2DEnable(m_Animation->GetAnimationCount() > 0);
		CRenderManager::GetInst()->GetStandard2DCBuffer()->UpdateCBuffer();

		m_Animation->SetShader();
	}

	m_Material->Render();

	m_Mesh->Render();

	m_Material->Reset();
}

void CBillboardComponent::RenderDebug()
{
	CSceneComponent::RenderDebug();
}

void CBillboardComponent::PostRender()
{
	CSceneComponent::PostRender();
}

CBillboardComponent* CBillboardComponent::Clone()
{
	return new CBillboardComponent(*this);
}

void CBillboardComponent::Save(FILE* File)
{
	CSceneComponent::Save(File);
}

void CBillboardComponent::Load(FILE* File)
{
	CSceneComponent::Load(File);
}
