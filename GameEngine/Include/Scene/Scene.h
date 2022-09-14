#pragma once

#include "SceneMode.h"
#include "SceneResource.h"
#include "SceneCollision.h"
#include "CameraManager.h"
#include "Viewport.h"
#include "NavigationManager.h"
#include "Navigation3DManager.h"
#include "LightManager.h"
#include "../GameObject/GameObject.h"

class CScene
{
	friend class CSceneManager;

private:
	CScene();
	~CScene();

private:
	CSharedPtr<CSceneMode> m_Mode;
	CSceneResource* m_Resource;
	CSceneCollision* m_Collision;
	CCameraManager* m_CameraManager;
	CViewport* m_Viewport;
	CNavigationManager* m_NavManager;
	CNavigation3DManager* m_Nav3DManager;
	CLightManager* m_LightManager;
	
	std::list<CSharedPtr<CGameObject>>	m_ObjList;
	CSharedPtr<CGameObject>		m_SkyObject;
	bool		m_Start;
	bool		m_Change;
	std::list<class CSceneComponent*>	m_RenderComponentList;
	std::list<class CColliderBox3D*>	m_ColliderList;

	// 피킹 시 무시할 오브젝트 TypeID
	std::vector<size_t>	m_vecIgnoreObject;

public:
	void SetPlayerObject(CGameObject* Obj)
	{
		m_Mode->SetPlayerObject(Obj);
	}

	void SetAutoChange(bool Change)
	{
		m_Change = Change;
	}

public:
	bool IsStart()	const
	{
		return m_Start;
	}

	CSharedPtr<CSceneMode> GetSceneMode()	const
	{
		return m_Mode;
	}

	CGameObject* GetSkyObject()	const
	{
		return m_SkyObject;
	}

	CSceneResource* GetResource()	const
	{
		return m_Resource;
	}

	CSceneCollision* GetCollision()	const
	{
		return m_Collision;
	}

	CCameraManager* GetCameraManager()	const
	{
		return m_CameraManager;
	}

	CViewport* GetViewport()	const
	{
		return m_Viewport;
	}

	CNavigationManager* GetNavigationManager()	const
	{
		return m_NavManager;
	}

	CNavigation3DManager* GetNavigation3DManager()	const
	{
		return m_Nav3DManager;
	}

	CLightManager* GetLightManager()	const
	{
		return m_LightManager;
	}

	CGameObject* GetPlayerObject()	const
	{
		return m_Mode->GetPlayerObject();
	}

	std::list<CSharedPtr<CGameObject>> GetObjectList() const
	{
		return m_ObjList;
	}

	template <typename T>
	CGameObject* FindObject()
	{
		auto	iter = m_ObjList.begin();
		auto	iterEnd = m_ObjList.end();

		for (; iter != iterEnd; ++iter)
		{
			if ((*iter)->CheckType<T>())
				return *iter;
		}

		return nullptr;
	}

	CGameObject* FindObject(const std::string& Name)
	{
		auto	iter = m_ObjList.begin();
		auto	iterEnd = m_ObjList.end();

		for (; iter != iterEnd; ++iter)
		{
			if ((*iter)->GetName() == Name)
				return *iter;
		}

		return nullptr;
	}

public:
	bool Picking(CGameObject*& result);
	bool PickingBox(CGameObject*& result);
	bool ForwardRayCollision(CGameObject*& result);

public:
	bool FindIgnoreTypeID(size_t TypeID);
	void AddIgnoreTypeID(size_t TypeID);

public:
	void Start();
	void Update(float DeltaTime);
	void PostUpdate(float DeltaTime);
	void Save(const char* FileName, const std::string& PathName = SCENE_PATH);
	void SaveFullPath(const char* FullPath);
	void Load(const char* FileName, const std::string& PathName = SCENE_PATH);
	void LoadFullPath(const char* FullPath);

public:
	template <typename T>
	bool CreateSceneMode()
	{
		m_Mode = DBG_NEW T;

		m_Mode->m_Scene = this;

		if (!m_Mode->Init())
		{
			m_Mode = nullptr;
			return false;
		}

		return true;
	}

	template <typename T>
	T* CreateSceneModeEmpty()
	{
		m_Mode = DBG_NEW T;

		m_Mode->m_Scene = this;

		return (T*)*m_Mode;
	}

	template <typename T>
	bool LoadSceneMode()
	{
		m_Mode = DBG_NEW T;

		m_Mode->m_Scene = this;

		return true;
	}

	template <typename T>
	T* CreateGameObject(const std::string& Name)
	{
		T* Obj = DBG_NEW T;

		Obj->SetName(Name);
		Obj->SetScene(this);

		if (!Obj->Init())
		{
			SAFE_RELEASE(Obj);
			return nullptr;
		}

		m_ObjList.push_back(Obj);

		if (m_Start)
			Obj->Start();

		return Obj;
	}

	template <typename T>
	T* LoadGameObject()
	{
		T* Obj = DBG_NEW T;

		Obj->SetScene(this);

		m_ObjList.push_back(Obj);

		if (m_Start)
			Obj->Start();

		return Obj;
	}

private:
	static bool SortRenderList(class CSceneComponent* Src, class CSceneComponent* Dest);
	static bool SortColliderRenderList(class CColliderBox3D* Src, class CColliderBox3D* Dest);
};

