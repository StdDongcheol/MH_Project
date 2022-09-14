#pragma once

#include "../Ref.h"
#include "../Resource/Texture/Texture.h"

struct WidgetImageInfo
{
	CSharedPtr<CTexture>	Texture;
	Vector4			Tint;
	std::vector<AnimationFrameData> vecFrameData;

	int		Frame;		// 현재 애니메이션 프레임
	float	Time;			// 애니메이션 동작 시간
	float	FrameTime;	// 1프레임당 시간
	float	PlayTime;
	float	PlayScale;		// 재생 비율

	WidgetImageInfo()
	{
		Tint = Vector4::White;
		Frame = 0;
		Time = 0.f;
		FrameTime = 0.f;
		PlayTime = 1.f;
		PlayScale = 1.f;
	}
};

class CWidget :
	public CRef
{
	friend class CWidgetWindow;

protected:
	CWidget();
	CWidget(const CWidget& widget);
	virtual ~CWidget();

protected:
	class CWidgetWindow* m_Owner;
	int     m_ZOrder;
	Vector2	m_Pos;
	Vector2	m_RenderPos;
	Vector2	m_Size;
	float	m_Angle;
	bool	m_UsePivot;
	bool	m_Start;
	float	m_Opacity;
	bool	m_MouseHovered;
	bool	m_CollisionMouseEnable;
	Vector4	m_Tint;
	class CWidgetConstantBuffer* m_CBuffer;
	CSharedPtr<class CShader>	m_Shader;
	CSharedPtr<class CMesh>		m_Mesh;

protected:
	class  CPaperBurnConstantBuffer* m_PaperCBuffer;
	CSharedPtr<CTexture>			m_BurnTexture;
	bool							m_StartPaperBurn;
	bool							m_UsePaperBurn;
	float							m_FinishTime;
	float							m_Filter;

private:
	float       m_FadeSpeed;
	float       m_FadeAnimSetTime;
	float       m_FadeAnimTime;
	bool        m_FadeAnimSet;
	bool        m_FadeIn;
	bool        m_FadeOut;
	bool        m_FadeRepeat;

private:
	Widget_Fade_State m_FadeState;
	bool		m_FadeLoop;
	float		m_FadeInTime;
	float		m_FadeInTimeAcc;
	float		m_FadeOutTime;
	float		m_FadeOutTimeAcc;
	float		m_DurationTime;
	float		m_DurationTimeAcc;

private:
	std::list<std::function<void()>>  m_FadeCallback[(int)Widget_Fade_State::Max];

public:
	bool IsMouseHovered() const
	{
		return m_MouseHovered;
	}

	virtual void Enable(bool bEnable)
	{
		CRef::Enable(bEnable);
	}

	class CWidgetWindow* GetOwner()	const
	{
		return m_Owner;
	}

	Vector2 GetWindowPos()	const
	{
		return m_Pos;
	}

	Vector2 GetWindowSize()	const
	{
		return m_Size;
	}

	int GetZOrder()	const
	{
		return m_ZOrder;
	}

	float GetAngle()	const
	{
		return m_Angle;
	}

	float GetOpacity()	const
	{
		return m_Opacity;
	}

	Vector2 GetPos()  const
	{
		return m_Pos;
	}

	Vector2 GetSize() const
	{
		return m_Size;
	}

	class CMaterial* GetMeshMaterial(int Index) const;

public:
	void SetOpacity(float Opacity)
	{
		m_Opacity = Opacity;
	}

	void SetZOrder(int ZOrder)
	{
		m_ZOrder = ZOrder;
	}

	void SetPos(const Vector2& Pos)
	{
		m_Pos = Pos;
	}

	void SetPos(float x, float y)
	{
		m_Pos = Vector2(x, y);
	}

	virtual void SetSize(const Vector2& Size)
	{
		m_Size = Size;
	}

	virtual void SetSize(float x, float y)
	{
		m_Size = Vector2(x, y);
	}

	void SetOwner(class CWidgetWindow* Owner)
	{
		m_Owner = Owner;
	}

	void SetAngle(float Angle)
	{
		m_Angle = Angle;
	}

public:
	void SetFadeSpeed(float Speed)
	{
		m_FadeSpeed = Speed;
	}

	void SetFadeIn(bool Enable, bool AutoFadeOut = false)
	{
		m_FadeIn = Enable;
		m_FadeAnimSet = AutoFadeOut;
	}

	void SetFadeOut(bool Enable)
	{
		m_FadeOut = Enable;
	}

	void SetFadeRepeat(bool Enable)
	{
		m_FadeRepeat = Enable;
	}

	void SetFadeWaitTime(float Time)
	{
		m_FadeAnimSetTime = Time;
	}


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

	void SetFadeState(Widget_Fade_State State)
	{
		m_FadeState = State;
	}

	void SetCenterPivot(bool bEnable)
	{
		m_UsePivot = bEnable;
	}

public:
	void SetShader(const std::string& Name);
	void SetUseTexture(bool Use);

	// ==================== PaperBurn ======================
public:
	void SetUsePaperBurn(bool Use);
	void StartPaperBurn();
	void SetPaperMaterial(class CMaterial* Material);
	void SetInverse(bool Enable);
	void SetFinishTime(float Time)
	{
		m_FinishTime = Time;
	}

	void SetBurnTexture(const std::string& Name, const TCHAR* FileName, const std::string& PathName = TEXTURE_PATH);

	void SetOutLineColor(const Vector4& Color);
	void SetOutLineColor(float r, float g, float b, float a);
	void SetInLineColor(const Vector4& Color);
	void SetInLineColor(float r, float g, float b, float a);
	void SetCenterLineColor(const Vector4& Color);
	void SetCenterLineColor(float r, float g, float b, float a);
	void SetInFilter(float Filter);
	void SetOutFilter(float Filter);
	void SetCenterFilter(float Filter);
	void SetPaperBurnShader();

private:
	void CallFadeCallback(Widget_Fade_State State);


public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render();
	virtual bool CollisionMouse(const Vector2& MousePos);
	virtual CWidget* Clone();



	// Fade상태가 완전히 끝났을때 동작하는 Callback.
	// ** SetFadeIn-Out 함수와 SetFadeIn-OutTime과 같이 사용할경우,
	// Callback이 두 번 호출될수 있음을 유의
public:
	template <typename T>
	void AddFadeCallback(Widget_Fade_State State, T* Obj, void(T::* Func)())
	{
		m_FadeCallback[(int)State].push_back(std::bind(Func, Obj));
	}

};

