#pragma once

#include "SceneComponent.h"
#include "../Resource/Mesh/SpriteMesh.h"
#include "../Resource/Material/Material.h"

enum class Fade_State
{
	FadeIn,
	FadeOut,
	Duration
};

class CBillboardComponent :
    public CSceneComponent
{
	friend class CGameObject;
	friend class CCameraManager;

protected:
	CBillboardComponent();
	CBillboardComponent(const CBillboardComponent& com);
	virtual ~CBillboardComponent();

protected:
	CSharedPtr<CSpriteMesh> m_Mesh;
	CSharedPtr<CMaterial> m_Material;
	class CAnimationSequence2DInstance* m_Animation;

private:
	Fade_State	m_FadeState;

	float	m_FadeInTime;
	float	m_FadeInTimeAcc;
	float	m_FadeOutTime;
	float	m_FadeOutTimeAcc;
	float	m_DurationTime;
	float	m_DurationTimeAcc;

	bool	m_FadeLoop;

public:
	void SetFadeInTime(float Time)
	{
		m_FadeInTime = Time;
	}

	void SetFadeOutTime(float Time)
	{
		m_FadeOutTime = Time;
	}

	void SetDuration(float Time)
	{
		m_DurationTime = Time;
	}

	void SetFadeLoop(bool Loop)
	{
		m_FadeLoop = Loop;
	}

	// 시작부터 FadeIn으로 설정해야 할 경우에만 사용할 것.
	void SetFadeState(Fade_State State)
	{
		m_FadeState = State;
	}

public:
	void SetMaterial(const std::string& Name);
	void SetMaterial(CMaterial* Material);

	class CAnimationSequence2DInstance* GetAnimationInstance()  const
	{
		return m_Animation;
	}

public:
	void SetBaseColor(const Vector4& Color);
	void SetBaseColor(float r, float g, float b, float a);
	void SetRenderState(class CRenderState* State);
	void SetRenderState(const std::string& Name);
	void SetTransparency(bool Enable);
	void SetOpacity(float Opacity);
	void AddOpacity(float Opacity);

public:
	void AddTexture(int Register, int ShaderType, const std::string& Name, class CTexture* Texture);
	void AddTexture(int Register, int ShaderType, const std::string& Name, const TCHAR* FileName, const std::string& PathName = TEXTURE_PATH);
	void AddTextureFullPath(int Register, int ShaderType, const std::string& Name, const TCHAR* FullPath);
	void AddTexture(int Register, int ShaderType, const std::string& Name, const std::vector<TCHAR*>& vecFileName, const std::string& PathName = TEXTURE_PATH);


	void SetTexture(int Index, int Register, int ShaderType, const std::string& Name, class CTexture* Texture);
	void SetTexture(int Index, int Register, int ShaderType, const std::string& Name, const TCHAR* FileName, const std::string& PathName = TEXTURE_PATH);
	void SetTextureFullPath(int Index, int Register, int ShaderType, const std::string& Name, const TCHAR* FullPath);
	void SetTexture(int Index, int Register, int ShaderType, const std::string& Name, const std::vector<TCHAR*>& vecFileName, const std::string& PathName = TEXTURE_PATH);


public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void PrevRender();
	virtual void Render();
	virtual void RenderDebug();
	virtual void PostRender();
	virtual CBillboardComponent* Clone();
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);

public:
	template <typename T>
	void CreateAnimationInstance()
	{
		T* Anim = new T;

		Anim->SetScene(m_Scene);
		Anim->SetOwner(this);

		if (!Anim->Init())
		{
			SAFE_DELETE(Anim);
			return;
		}

		SAFE_DELETE(m_Animation);

		m_Animation = Anim;
	}


	template <typename T>
	void LoadAnimationInstance()
	{
		T* Anim = new T;

		Anim->SetScene(m_Scene);
		Anim->SetOwner(this);

		SAFE_DELETE(m_Animation);

		m_Animation = Anim;
	}
};

