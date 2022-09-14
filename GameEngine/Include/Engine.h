#pragma once

#include "GameInfo.h"
#include "Timer.h"

class CEngine
{
private:
	HINSTANCE	m_hInst;
	HWND		m_hWnd;
	Resolution	m_RS;
	RECT		m_WindowRect;
	static bool	m_Loop;
	float		m_ClearColor[4];
	class CTimer* m_Timer;
	bool		m_Start;
	bool		m_Play;
	Engine_Space	m_Space;
	int				m_ShowCursorCount;
	Mouse_State		m_MouseState;
	CSharedPtr<class CWidgetWindow>	m_MouseWidget[(int)Mouse_State::Max];
	class CGlobalConstantBuffer* m_GlobalCBuffer;
	float			m_GlobalAccTime;
	CSharedPtr<class CTexture>	m_GlobalNoiseTexture;
	class CStructuredBuffer* m_RandomBuffer;
	bool		m_IsMouseInClient;
	bool		m_EditMode;
	bool		m_RenderCollision;

public:
	const RECT& GetWindowPos()
	{
		GetWindowRect(m_hWnd, &m_WindowRect);

		return m_WindowRect;
	}

	// 윈도우가 활성화 되어 있는지의 여부를 반환한다
	bool IsFocus()	const
	{
		return m_hWnd == GetFocus();
	}

	bool IsRenderCollision()	const
	{
		return m_RenderCollision;
	}

	bool IsEditMode()	const
	{
		return m_EditMode;
	}

	bool IsMouseInClient()	const
	{
		return m_IsMouseInClient;
	}

	Resolution GetRS()	const
	{
		return m_RS;
	}

	class CWidgetWindow* GetMouseWidget()	const
	{
		return m_MouseWidget[(int)m_MouseState];
	}

	class CWidgetWindow* GetMouseWidget(Mouse_State State)
	{
		return m_MouseWidget[(int)State];
	}

	Engine_Space GetEngineSpace()	const
	{
		return m_Space;
	}

	bool IsPlay()	const
	{
		return m_Play;
	}

	HWND GetWindowHandle()	const
	{
		return m_hWnd;
	}

	HINSTANCE GetWindowInstance()	const
	{
		return m_hInst;
	}

	float GetFPS()	const
	{
		return m_Timer->GetFPS();
	}

	float GetDeltaTime()	const
	{
		return m_Timer->GetDeltaTime();
	}

public:
	void ToggleRenderCollision()
	{
		m_RenderCollision = !m_RenderCollision;
	}

	bool SetRenderCollision(bool Render)
	{
		m_RenderCollision = Render;
	}

	void EnableEditorMode()
	{
		m_EditMode = true;
	}

	void SetEngineSpace(Engine_Space Space)
	{
		m_Space = Space;
	}

	void SetPlay(bool Play)
	{
		m_Play = Play;
	}

	void Exit()
	{
		DestroyWindow(m_hWnd);
	}

public:
	bool Init(HINSTANCE hInst, const TCHAR* Name, unsigned int Width,
		unsigned int Height, int IconID,
		bool WindowMode = true);
	bool Init(HINSTANCE hInst, HWND hWnd, unsigned int Width,
		unsigned int Height, bool WindowMode = true);
	int Run();
	void Logic();

private:
	bool Update(float DeltaTime);
	bool PostUpdate(float DeltaTime);
	bool Render(float DeltaTime);

private:
	ATOM Register(const TCHAR* Name, int IconID);
	BOOL Create(const TCHAR* Name);
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

public:
	// WidgetWindow의 렌더링만 제외시켜, 커서를 안보이게 하는 함수.
	// true : 모든 상태의 커서는 렌더링됨.
	// false : 모든 상태의 커서는 렌더링되지 않음.
	void ShowUICursor(bool bEnable);
	void SetMouseState(Mouse_State State);

public:
	template <typename T>
	T* CreateMouse(Mouse_State State, const std::string& Name)
	{
		T* Window = new T;

		Window->SetName(Name);

		if (!Window->Init())
		{
			SAFE_RELEASE(Window);
			return nullptr;
		}

		m_MouseWidget[(int)State] = Window;

		return Window;
	}

	DECLARE_SINGLE(CEngine)
};

