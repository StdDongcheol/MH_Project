#pragma once

#include "Scene.h"

class CSceneManager
{
private:
	CRITICAL_SECTION	m_Crt;
	CScene* m_Scene;
	CScene* m_NextScene;
	std::function<void(CScene*, size_t)>	m_CreateSceneModeCallback;
	std::function<CGameObject* (CScene*, size_t)>	m_CreateObjectCallback;
	std::function<class CComponent* (CGameObject* Obj, size_t Type)>	m_CreateComponentCallback;
	std::function<void(class CSpriteComponent* Sprite, size_t Type)>	m_CreateAnimInstanceCallback;

public:
	bool IsStart()	const
	{
		return m_Scene->IsStart();
	}

	void SetPlayerObject(CGameObject* Obj)
	{
		m_Scene->SetPlayerObject(Obj);
	}

	CGameObject* GetPlayerObject()	const
	{
		return m_Scene->GetPlayerObject();
	}

	CScene* GetScene()	const
	{
		return m_Scene;
	}

	void CallCreateSceneMode(CScene* Scene, size_t Type)
	{
		if (m_CreateSceneModeCallback)
			m_CreateSceneModeCallback(Scene, Type);
	}

	CGameObject* CallCreateObject(CScene* Scene, size_t Type)
	{
		if (m_CreateObjectCallback)
			return m_CreateObjectCallback(Scene, Type);

		return nullptr;
	}

	class CComponent* CallCreateComponent(CGameObject* Obj, size_t Type)
	{
		if (m_CreateComponentCallback)
			return m_CreateComponentCallback(Obj, Type);

		return nullptr;
	}

	void CallCreateAnimInstance(class CSpriteComponent* Sprite, size_t Type)
	{
		if (m_CreateAnimInstanceCallback)
			m_CreateAnimInstanceCallback(Sprite, Type);
	}

public:
	void Start();
	bool Init();
	bool Update(float DeltaTime);
	bool PostUpdate(float DeltaTime);

private:
	bool ChangeScene();

public:
	void CreateNextScene(bool AutoChange = true);
	void ChangeNextScene();

	template <typename T>
	bool CreateSceneMode(bool Current = true)
	{
		if (Current)
			return m_Scene->CreateSceneMode<T>();

		return m_NextScene->CreateSceneMode<T>();
	}

	template <typename T>
	T* CreateSceneModeEmpty(bool Current = true)
	{
		if (Current)
			return m_Scene->CreateSceneModeEmpty<T>();

		return m_NextScene->CreateSceneModeEmpty<T>();
	}

	template <typename T>
	void SetCreateSceneModeFunction(T* Obj, void(T::* Func)(CScene*, size_t))
	{
		m_CreateSceneModeCallback = std::bind(Func, Obj, std::placeholders::_1, std::placeholders::_2);
	}

	template <typename T>
	void SetCreateObjectFunction(T* Obj, CGameObject* (T::* Func)(CScene*, size_t))
	{
		m_CreateObjectCallback = std::bind(Func, Obj, std::placeholders::_1, std::placeholders::_2);
	}

	template <typename T>
	void SetCreateComponentFunction(T* Obj, class CComponent* (T::* Func)(CGameObject*, size_t))
	{
		m_CreateComponentCallback = std::bind(Func, Obj, std::placeholders::_1, std::placeholders::_2);
	}

	template <typename T>
	void SetCreateAnimInstanceFunction(T* Obj, void (T::* Func)(CSpriteComponent*, size_t))
	{
		m_CreateAnimInstanceCallback = std::bind(Func, Obj, std::placeholders::_1, std::placeholders::_2);
	}

	DECLARE_SINGLE(CSceneManager)
};

