#pragma once

#include "GameInfo.h"

class CEditorManager
{
private:
	class CHierarchyWindow*	m_HierarchyWindow;
	class CObjectWindow*	m_ObjectWindow;
	class CSceneWindow*		m_SceneWindow;
	class CAboutWindow*		m_AboutWindow;
	class CInfoWindow*		m_InfoWindow;

public:
	class CInfoWindow* GetInfoWindow()	const
	{
		return m_InfoWindow;
	}

	class CSceneWindow* GetSceneWindow()	const
	{
		return m_SceneWindow;
	}

	class CHierarchyWindow* GetHierarchyWindow()	const
	{
		return m_HierarchyWindow;
	}

	class CObjectWindow* GetObjectWindow()	const
	{
		return m_ObjectWindow;
	}

public:
	bool Init(HINSTANCE hInst);
	void CreateDefaultSceneMode();
	int Run();

public:
	void CamToggle();

public:
	Vector3 GetCameraPos()	const;
	Vector3 GetCameraFrontPos(float Dist)	const;

public:
	int GetBrushType()	const;
	class CLandScapeObj* GetLandScapeObj()	const;

public:
	void SetInfo(const std::string& SceneName);
	void CreateSceneMode(class CScene* Scene, size_t Type);
	class CGameObject* CreateObject(class CScene* Scene, size_t Type);
	class CComponent* CreateComponent(class CGameObject* Obj, size_t Type);

private:
	class CGameObject* CreateCharacter(CScene* Scene, size_t Type);
	class CGameObject* CreateObj1(CScene* Scene, size_t Type);
	class CGameObject* CreateObj2(CScene* Scene, size_t Type);

public:
	const char* GetHierarchyName(Object_Type Type)	const;
	void GetHierarchyNameAll(std::vector<const char*>& vecOutput);
	Object_Type GetHierarchyType(const char* Name)	const;
	Object_Type GetHierarchyType(const std::string& Name)	const;

	const char* GetMonsterName(Monster_Type Type)	const;
	const char* GetMonsterNameEng(Monster_Type Type)	const;
	void GetMonsterNameAll(std::vector<const char*>& vecOutput);
	Monster_Type GetMonsterType(const char* Name)	const;
	Monster_Type GetMonsterType(const std::string& Name)	const;

	class CEditorScene* GetEditorScene()	const;

	const char* GetFieldObjName(FieldObj_Type Type)	const;
	const char* GetFieldObjNameEng(FieldObj_Type Type)	const;
	void GetFieldObjNameAll(std::vector<const char*>& vecOutput);
	FieldObj_Type GetFieldObjType(const char* Name)	const;
	FieldObj_Type GetFieldObjType(const std::string& Name)	const;

	const char* GetTypeKorToEng(const std::string& KorTypeName);

	DECLARE_SINGLE(CEditorManager)
};