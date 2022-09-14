#pragma once

#include "IMGUIWindow.h"
#include "Object_Info.h"

class CSceneWindow :
	public CIMGUIWindow
{
	friend class CEditorManager;

public:
	CSceneWindow();
	virtual ~CSceneWindow();

private:
	std::unordered_map<std::string, std::list<Object_Info*>*> m_mapScene;
	class CIMGUITextInput* m_NameTextInput;
	class CIMGUIButton* m_CreateButton;
	class CIMGUIButton* m_DeleteButton;
	class CIMGUIButton* m_SaveButton;
	class CIMGUIButton* m_LoadButton;

public:
	bool HasSceneName(const std::string& Name)
	{
		auto	iter = m_mapScene.find(Name);

		return iter != m_mapScene.end();
	}

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);

private:
	void Create();
	void Delete();
	void Save();
	void Load();

public:
	void CreateScene(const std::string& Name);

public:
	void ObjectRenderUpdate(const std::string& SceneName);

private:
	std::list<Object_Info*>* FindInfo(const std::string& SceneName);
};

