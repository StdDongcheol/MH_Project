#pragma once
#include "Scene/SceneMode.h"
class CEditorScene :
	public CSceneMode
{
public:
	CEditorScene();
	virtual ~CEditorScene();

private:
	class CFlightCamera* m_Camera;
	class CGameObject* m_PickingObject;
	class CObjectWindow* m_ObjectWindow;
	class CHierarchyWindow* m_HierarchyWindow;
	class CRenderWindow* m_RenderWindow;
	class CIMGUIGizmo* m_Gizmo;
	bool	m_UseCam;
	bool	m_Play;
	bool	m_UseBrushMode;
	bool	m_UseHeightBrush; // 지형을 쌓거나 파내기
	bool	m_UseSplattingBrush; // 스플래팅
	bool	m_First;
	float	m_BrushMinRange;
	float	m_BrushMaxRange;
	float	m_BrushRange;
	float	m_BrushRangeScale;

public:
	float GetBrushRangeScale()	const
	{
		return m_BrushRangeScale;
	}

	float GetBrushRange()	const
	{
		return m_BrushRange;
	}

	bool IsUseBrushMode()	const
	{
		return m_UseBrushMode;
	}

public:
	void UseBrushMode(bool Use)
	{
		m_UseBrushMode = Use;

		if (!m_UseBrushMode)
			m_PickingObject = nullptr;
	}

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);

public:
	void CamToggle();

private:
	void Space(float DeltaTime);

	void LClickDown(float DeltaTime);
	void LClickPush(float DeltaTime);
	void LClickUp(float DeltaTime);
	void RClickDown(float DeltaTime);
	void RClickPush(float DeltaTime);
	void RClickUp(float DeltaTime);

	void Exit(float DeltaTime);

public:
	void WheelUp(float DeltaTime);
	void WheelDown(float DeltaTime);
	void SetBrushModeRange();

private:
	void LoadFBX();

private:
	void LoadLandScape();
	void LoadPlayer();
	void LoadMonster();
	void LoadFieldObj();

public:
	Vector3 GetCameraPos()	const;
	Vector3 GetCameraFrontPos(float Dist)	const;

private:
	void AddLandScape(std::vector<TCHAR*>& vec, const TCHAR* Path);
	void SetLandScape(int Register, const std::string& Name, std::vector<TCHAR*>& vecFileName, const std::string& PathName = TEXTURE_PATH);
};