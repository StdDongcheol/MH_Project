#pragma once

#include "IMGUIWindow.h"
#include "Object_Info.h"

class CHierarchyWindow :
	public CIMGUIWindow
{
	friend class CEditorManager;

public:
	CHierarchyWindow();
	virtual ~CHierarchyWindow();

private:
	std::list<Object_Info*>*	m_InfoList;
	std::list<std::string>		m_SceneNameList;
	class CIMGUIListBox*		m_SceneListBox;
	class CIMGUIListBox*		m_TypeListBox;
	class CIMGUIListBox*		m_ObjectListBox;
	std::string					m_SelectScene;
	CSharedPtr<CGameObject>		m_SelectObject;
	Object_Type					m_SelectType;

public:
	bool FindNameList(const std::string& Name)	const
	{
		auto	iter = m_SceneNameList.begin();
		auto	iterEnd = m_SceneNameList.end();

		for (; iter != iterEnd; ++iter)
		{
			if ((*iter) == Name)
				return true;
		}

		return false;
	}

	bool Empty()	const
	{
		if (!m_InfoList)
			return true;

		return m_InfoList->empty();
	}

	bool IsSelectType()	const
	{
		return m_SelectType != Object_Type::Max;
	}

	bool IsSelectObject()	const
	{
		return m_SelectObject != nullptr;
	}

	const std::string& GetSelectScene()	const
	{
		return m_SelectScene;
	}

	Object_Type GetSelectType()	const
	{
		return m_SelectType;
	}

	CSharedPtr<CGameObject> GetSelectObject()	const
	{
		return m_SelectObject;
	}

public:
	void AddSceneName(const std::string& Name)
	{
		auto	iter = m_SceneNameList.begin();
		auto	iterEnd = m_SceneNameList.end();

		for (; iter != iterEnd; ++iter)
		{
			if (!(*iter).compare(Name))
				return;
		}

		m_SceneNameList.push_back(Name);

		RefreshScene(false);

		SelectScene(Name);
	}

	void SetInfo(std::list<Object_Info*>* ObjectList)
	{
		if (!ObjectList)
			return;

		m_InfoList = ObjectList;

		RefreshType();
	}

public:
	virtual bool Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);

public:
	bool IsSameTypeSelectObject(size_t typeID);

public:
	bool HasObjectName(const std::string& Name);
	Object_Info* FindInfo(Object_Type Type)	const;
	void FindInfo(Object_Type Type, std::vector<Object_Info*>& vecOutput)	const;
	void FindInfo(const std::string& SceneName, std::vector<Object_Info*>& vecOutput)	const;
	void SetFieldObjNum(int Num, FieldObj_Type Type);

public:
	Object_Info* FindMonsterInfo(Monster_Type Type);
	Object_Info* FindFieldObjInfo(FieldObj_Type Type, int FieldObjNum);

public:
	Object_Info* GetSelectInfo()	const;

public:
	void DeleteSelectScene();

public:
	void AddObject(const std::string& SceneName, Object_Type Type, int ObjectDetailType, int ObjectNum, CSharedPtr<CGameObject> Object, std::list<Object_Info*>* ObjectList = nullptr);
	void DeleteObject(const std::string& SceneName, Object_Type Type, CSharedPtr<CGameObject> Object);
	void DeleteSelectObject();
	CSharedPtr<CGameObject> FindObject(const std::string& SceneName, Object_Type Type, int ObjectDetailType, int ObjectNum, const std::string& ObjectName)	const;
	CSharedPtr<CGameObject> FindObject(size_t TypeID, const std::string& ObjectName = "")	const;
	void SelectObject(const std::string& Name);

public:
	void Clear();
	void Cancel();
	void CancelType();

public:
	void SelectScene(const std::string& SceneName);

private:
	void SelectScene(int Index, const char* Item);
	void CancelScene();

public:
	void AddType(Object_Type Type);
	bool FindType(Object_Type Type)	const;

private:
	void AddType(const std::string& SceneName, Object_Type Type, std::list<Object_Info*>* ObjectList = nullptr);
	void DeleteType(Object_Type Type);
	void SelectType(int Index, const char* Item);

private:
	void CancelObject();
	void SelectObject(int Index, const char* Item);

public:
	void RefreshScene(bool Cancel = true);
	void RefreshType();
	void RefreshObject();

private:
	void CancelKey(float DeltaTime);
};