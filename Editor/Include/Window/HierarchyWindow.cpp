
#include "HierarchyWindow.h"
#include "ObjectWindow.h"
#include "SceneWindow.h"
#include "InfoWindow.h"
#include "IMGUIListBox.h"
#include "IMGUILabel.h"
#include "IMGUISameLine.h"
#include "Input.h"
#include "Component/LandScape.h"
#include "../EditorManager.h"
#include "../Object/LandScape/LandScapeObj.h"

CHierarchyWindow::CHierarchyWindow() :
	m_SceneListBox(nullptr),
	m_TypeListBox(nullptr),
	m_ObjectListBox(nullptr),
	m_SelectType(Object_Type::Max),
	m_InfoList(nullptr)
{
}

CHierarchyWindow::~CHierarchyWindow()
{
}

void CHierarchyWindow::DeleteSelectScene()
{
	if (m_SelectScene == "" || !m_InfoList)
		return;

	{
		auto	iter = m_SceneNameList.begin();
		auto	iterEnd = m_SceneNameList.end();

		for (; iter != iterEnd; ++iter)
		{
			if (!(*iter).compare(m_SelectScene))
			{
				m_SceneNameList.erase(iter);
				break;
			}
		}
	}

	{
		auto iter = m_InfoList->begin();
		auto iterEnd = m_InfoList->end();

		for (; iter != iterEnd; ++iter)
		{
			(*iter)->DeleteCharacterInfoAll();

			auto	iter1 = (*iter)->ObjectList->begin();
			auto	iter1End = (*iter)->ObjectList->end();

			for (; iter1 != iter1End; ++iter1)
			{
				(*iter1)->Destroy();
			}

			SAFE_DELETE((*iter)->ObjectList);
			SAFE_DELETE(*iter);
		}

		m_InfoList->clear();
		m_InfoList = nullptr;
	}

	RefreshScene();

	CEditorManager::GetInst()->GetObjectWindow()->ClearTarget();
}

void CHierarchyWindow::Cancel()
{
	CancelScene();
	CancelType();
	CancelObject();
}

bool CHierarchyWindow::Start()
{
	//m_SceneListBox->SetCancelFunction(this, &CHierarchyWindow::CancelScene);
	m_TypeListBox->SetCancelFunction(this, &CHierarchyWindow::CancelType);
	m_ObjectListBox->SetCancelFunction(this, &CHierarchyWindow::CancelObject);

	return true;
}

bool CHierarchyWindow::Init()
{
	CIMGUISameLine* Line = nullptr;
	CIMGUILabel* Label = nullptr;

	char	Name[256] = {};

	Label = AddWidget<CIMGUILabel>(UTF8("장면 이름"), 120.f, 20.f);
	Label->SetColor(69, 69, 138);
	Label->SetAlign(0.5f, 0.f);

	Line = AddWidget<CIMGUISameLine>("Line");

	Label = AddWidget<CIMGUILabel>(UTF8("오브젝트 유형"), 120.f, 20.f);
	Label->SetColor(69, 69, 138);
	Label->SetAlign(0.5f, 0.f);

	Line = AddWidget<CIMGUISameLine>("Line");

	Label = AddWidget<CIMGUILabel>(UTF8("오브젝트 이름"), 120.f, 20.f);
	Label->SetColor(69, 69, 138);
	Label->SetAlign(0.5f, 0.f);

	m_SceneListBox = AddWidget<CIMGUIListBox>("SceneListBox", 120.f, 80.f);
	m_SceneListBox->SetHideName(true);
	m_SceneListBox->SetPageItemCount(7);
	m_SceneListBox->SetSelectCallback(this, &CHierarchyWindow::SelectScene);

	Line = AddWidget<CIMGUISameLine>("Line");

	m_TypeListBox = AddWidget<CIMGUIListBox>("TypeListBox", 120.f, 80.f);
	m_TypeListBox->SetHideName(true);
	m_TypeListBox->SetPageItemCount(7);
	m_TypeListBox->SetSelectCallback(this, &CHierarchyWindow::SelectType);

	Line = AddWidget<CIMGUISameLine>("Line");

	m_ObjectListBox = AddWidget<CIMGUIListBox>("ObjectListBox", 120.f, 80.f);
	m_ObjectListBox->SetHideName(true);
	m_ObjectListBox->SetPageItemCount(7);
	m_ObjectListBox->SetSelectCallback(this, &CHierarchyWindow::SelectObject);

	return true;
}

void CHierarchyWindow::Update(float DeltaTime)
{
	CIMGUIWindow::Update(DeltaTime);

	if (m_SelectObject)
		CEditorManager::GetInst()->GetInfoWindow()->SetObjPos(m_SelectObject->GetWorldPos());
}

bool CHierarchyWindow::IsSameTypeSelectObject(size_t typeID)
{
	if (!m_SelectObject)
		return false;

	return m_SelectObject->GetTypeID() == typeID;
}

void CHierarchyWindow::FindInfo(const std::string& SceneName, std::vector<Object_Info*>& vecOutput) const
{
	if (m_InfoList->empty())
		return;

	auto	iter = m_InfoList->begin();
	auto	iterEnd = m_InfoList->end();

	for (; iter != iterEnd; ++iter)
	{
		if ((*iter)->SceneName == SceneName)
			vecOutput.push_back(*iter);
	}
}

void CHierarchyWindow::SetFieldObjNum(int Num, FieldObj_Type Type)
{
	Object_Info* Info = FindFieldObjInfo(Type, Num);

	if (!Info)
		ASSERT("if (!Info)");

	Info->FieldObjNum = Num;
}

Object_Info* CHierarchyWindow::FindMonsterInfo(Monster_Type Type)
{
	if (Type == Monster_Type::Max)
		return nullptr;

	std::vector<Object_Info*>	vecInfo;

	FindInfo(Object_Type::Monster, vecInfo);

	if (!vecInfo.empty())
	{
		size_t Size = vecInfo.size();

		for (size_t i = 0; i < Size; ++i)
		{
			if (vecInfo[i]->MonsterType == Type)
				return vecInfo[i];
		}
	}

	AddType(Object_Type::Monster);

	std::vector<Object_Info*>	vecInfo2;

	FindInfo(Object_Type::Monster, vecInfo2);

	size_t Size = vecInfo2.size();

	for (size_t i = 0; i < Size; ++i)
	{
		if (vecInfo2[i]->MonsterType == Monster_Type::Max)
		{
			vecInfo2[i]->MonsterType = Type;

			return vecInfo2[i];
		}
	}

	return nullptr;
}

Object_Info* CHierarchyWindow::FindFieldObjInfo(FieldObj_Type Type, int FieldObjNum)
{
	std::vector<Object_Info*>	vecInfo;

	FindInfo(Object_Type::FieldObj, vecInfo);

	if (!vecInfo.empty())
	{
		size_t Size = vecInfo.size();

		for (size_t i = 0; i < Size; ++i)
		{
			if (vecInfo[i]->FieldObjType == Type &&
				vecInfo[i]->FieldObjNum == FieldObjNum)
				return vecInfo[i];
		}
	}

	AddType(Object_Type::FieldObj);

	std::vector<Object_Info*>	vecInfo2;

	FindInfo(Object_Type::FieldObj, vecInfo2);

	size_t Size = vecInfo2.size();

	for (size_t i = 0; i < Size; ++i)
	{
		if (vecInfo2[i]->FieldObjType == FieldObj_Type::Max)
		{
			vecInfo2[i]->FieldObjType = Type;
			vecInfo2[i]->FieldObjNum = FieldObjNum;

			return vecInfo2[i];
		}
	}

	return nullptr;
}

Object_Info* CHierarchyWindow::FindInfo(Object_Type Type)	const
{
	if (!m_InfoList)
		return nullptr;

	if (m_InfoList->empty())
		return nullptr;

	auto	iter = m_InfoList->begin();
	auto	iterEnd = m_InfoList->end();

	for (; iter != iterEnd; ++iter)
	{
		if ((*iter)->Type == Type)
			return *iter;
	}

	return nullptr;
}

void CHierarchyWindow::FindInfo(Object_Type Type, std::vector<Object_Info*>& vecOutput) const
{
	if (m_InfoList->empty())
		return;

	auto	iter = m_InfoList->begin();
	auto	iterEnd = m_InfoList->end();

	for (; iter != iterEnd; ++iter)
	{
		if ((*iter)->Type == Type)
			vecOutput.push_back(*iter);
	}
}

Object_Info* CHierarchyWindow::GetSelectInfo() const
{
	return FindInfo(m_SelectType);
}

void CHierarchyWindow::AddType(const std::string& SceneName, Object_Type Type, std::list<Object_Info*>* ObjectList)
{
	if (m_SceneNameList.empty() || SceneName == "")
		return;

	if (Type == Object_Type::Max)
		return;

	if (!ObjectList)
	{
		Object_Info* NewInfo = DBG_NEW Object_Info;

		NewInfo->SceneName = SceneName;
		NewInfo->Type = Type;

		m_InfoList->push_back(NewInfo);
	}

	else
		m_InfoList = ObjectList;

	if (m_SelectScene == SceneName)
	{
		if (!m_TypeListBox->CheckItem(CEditorManager::GetInst()->GetHierarchyName(Type)))
			m_TypeListBox->AddItem(CEditorManager::GetInst()->GetHierarchyName(Type));
	}
}

void CHierarchyWindow::DeleteType(Object_Type Type)
{
	if (Type == Object_Type::Max)
		return;

	auto	iter = m_InfoList->begin();
	auto	iterEnd = m_InfoList->end();

	for (; iter != iterEnd; ++iter)
	{
		if ((*iter)->Type == Type)
		{
			SAFE_DELETE(*iter);
			m_InfoList->erase(iter);

			CancelType();

			m_TypeListBox->DeleteItem(CEditorManager::GetInst()->GetHierarchyName(Type));
			break;
		}
	}
}

bool CHierarchyWindow::FindType(Object_Type Type)	const
{
	return m_TypeListBox->CheckItem(CEditorManager::GetInst()->GetHierarchyName(Type));
}

void CHierarchyWindow::RefreshType()
{
	m_TypeListBox->Clear();

	if (m_InfoList)
	{
		auto	iter = m_InfoList->begin();
		auto	iterEnd = m_InfoList->end();

		for (; iter != iterEnd; ++iter)
		{
			if (*iter == nullptr)
				return;

			else if ((*iter)->SceneName != m_SelectScene)
				continue;

			const char* TypeText = CEditorManager::GetInst()->GetHierarchyName((*iter)->Type);

			if (!m_TypeListBox->CheckItem(TypeText))
				m_TypeListBox->AddItem(TypeText);
		}
	}

	RefreshObject();
}

void CHierarchyWindow::AddObject(const std::string& SceneName, Object_Type Type, int ObjectDetailType, int ObjectNum, CSharedPtr<CGameObject> Object, std::list<Object_Info*>* ObjectList)
{
	if (m_SceneNameList.empty() || SceneName == "")
		return;

	else if (!FindNameList(SceneName))
		return;

	if (!FindType(Type))
		AddType(SceneName, Type, ObjectList);

	if (!FindObject(SceneName, Type, ObjectDetailType, ObjectNum, Object->GetName()))
	{
		std::vector<Object_Info*>	vecInfo;
		FindInfo(Type, vecInfo);

		if (vecInfo.empty())
			return;

		Object_Info* Info = nullptr;
		size_t Size = vecInfo.size();

		for (size_t i = 0; i < Size; ++i)
		{
			if (Type == Object_Type::Monster)
			{
				if (vecInfo[i]->MonsterType == (Monster_Type)ObjectDetailType &&
					vecInfo[i]->FieldObjNum == ObjectNum)
				{
					Info = vecInfo[i];
					break;
				}
			}

			else if (Type == Object_Type::FieldObj)
			{
				if (vecInfo[i]->FieldObjType == (FieldObj_Type)ObjectDetailType &&
					vecInfo[i]->FieldObjNum == ObjectNum)
				{
					Info = vecInfo[i];
					break;
				}
			}

			else if (Type == Object_Type::Player || Type == Object_Type::LandScape)
			{
				Info = vecInfo[i];
				break;
			}
		}
		 
		Info->ObjectList->push_back(Object);

		if (m_SelectScene == SceneName)
		{
			if (Type == m_SelectType)
				m_ObjectListBox->AddItem(Object->GetName());
		}
	}
}

void CHierarchyWindow::DeleteObject(const std::string& SceneName, Object_Type Type, CSharedPtr<CGameObject> Object)
{
	if (!Object || Type == Object_Type::Max)
		return;

	else if (m_SceneNameList.empty() || SceneName == "")
		return;

	else if (!FindNameList(SceneName))
		return;

	if (!FindType(Type))
		ASSERT("if (!FindType(Type))");

	std::vector<Object_Info*>	vecInfo;
	FindInfo(Type, vecInfo);

	size_t Size = vecInfo.size();

	for (size_t i = 0; i < Size; ++i)
	{
		auto	iter = vecInfo[i]->ObjectList->begin();
		auto	iterEnd = vecInfo[i]->ObjectList->end();

		for (; iter != iterEnd; ++iter)
		{
			if (m_ObjectListBox->GetSelectItem() == (*iter)->GetName())
			{
				m_ObjectListBox->DeleteItem(Object->GetName());

				if ((*iter)->CheckType<CLandScapeObj>())
				{
					CLandScapeObj* LandScapeObj = CEditorManager::GetInst()->GetLandScapeObj();
					LandScapeObj->ReleaseMesh();
				}

				(*iter)->Destroy();

				vecInfo[i]->ObjectList->erase(iter);

				if (Type == Object_Type::Player)
					vecInfo[i]->DeleteCharacterInfo(Object->GetName());

				CancelObject();

				break;
			}
		}

		Vector3	none;

		CEditorManager::GetInst()->GetInfoWindow()->SetObjName("");
		CEditorManager::GetInst()->GetInfoWindow()->SetObjPos(none);

		if (vecInfo[i]->ObjectList->empty())
		{
			SAFE_DELETE(vecInfo[i]->ObjectList);

			auto	iter1 = m_InfoList->begin();
			auto	iter1End = m_InfoList->end();

			for (; iter1 != iter1End; ++iter1)
			{
				if (*iter1 == vecInfo[i])
				{
					m_InfoList->erase(iter1);
					break;
				}
			}

			SAFE_DELETE(vecInfo[i]);
			break;
		}
	}

	auto	iter = m_InfoList->begin();
	auto	iterEnd = m_InfoList->end();

	bool	Find = false;

	for (; iter != iterEnd; ++iter)
	{
		if ((*iter)->Type == Type)
		{
			Find = true;
			break;
		}
	}

	if (!Find)
	{
		CancelType();
		RefreshType();
	}

	else
	{
		CancelObject();
		RefreshObject();
	}
}

void CHierarchyWindow::DeleteSelectObject()
{
	DeleteObject(m_SelectScene, m_SelectType, m_SelectObject);
}

CSharedPtr<CGameObject> CHierarchyWindow::FindObject(const std::string& SceneName, Object_Type Type, int ObjectDetailType, int ObjectNum, const std::string& ObjectName)	const
{
	if (!FindNameList(SceneName))
		return nullptr;

	if (Type == Object_Type::Max)
		ASSERT("if (Type == Object_Type::Max)");

	std::vector<Object_Info*>	vecInfo;

	FindInfo(Type, vecInfo);

	if (vecInfo.empty())
		return nullptr;

	size_t Size = vecInfo.size();

	Object_Info* Info = nullptr;
	bool Break = false;

	for (size_t i = 0; i < Size; ++i)
	{
		switch (Type)
		{
		case Object_Type::Player:
			Info = vecInfo[i];
			Break = true;
			break;
		case Object_Type::Monster:
			if (vecInfo[i]->MonsterType == (Monster_Type)ObjectDetailType && 
				vecInfo[i]->FieldObjNum == ObjectNum)
			{
				Info = vecInfo[i];
				Break = true;
			}
			break;
		case Object_Type::LandScape:
			Info = vecInfo[i];
			Break = true;
			break;
		case Object_Type::FieldObj:
			if (vecInfo[i]->FieldObjType == (FieldObj_Type)ObjectDetailType &&
				vecInfo[i]->FieldObjNum == ObjectNum)
			{
				Info = vecInfo[i];
				Break = true;
			}
			break;
		}

		if (Break)
			break;
	}

	if (!Info)
		return nullptr;

	auto	iter = Info->ObjectList->begin();
	auto	iterEnd = Info->ObjectList->end();

	for (; iter != iterEnd; ++iter)
	{
		if ((*iter)->GetName() == ObjectName)
			return *iter;
	}

	return nullptr;
}

CSharedPtr<CGameObject> CHierarchyWindow::FindObject(size_t TypeID, const std::string& ObjectName) const
{
	auto	iter = m_InfoList->begin();
	auto	iterEnd = m_InfoList->end();

	for (; iter != iterEnd; ++iter)
	{
		auto	iter1 = (*iter)->ObjectList->begin();
		auto	iter1End = (*iter)->ObjectList->end();

		for (; iter1 != iter1End; ++iter1)
		{
			if ((*iter1)->GetTypeID() == TypeID)
			{
				if (!ObjectName.compare(""))
					return *iter1;

				else
				{
					if (!(*iter1)->GetName().compare(ObjectName))
						return *iter1;
				}
			}
		}
	}

	return nullptr;
}

void CHierarchyWindow::SelectObject(const std::string& Name)
{
	std::vector<Object_Info*>	vecInfo;
	FindInfo(m_SelectScene, vecInfo);

	size_t Size = vecInfo.size();
	bool	Find = false;
	int		ObjectDetailType = 0;
	int		ObjectNum = 0;

	for (size_t i = 0; i < Size; ++i)
	{
		auto	iter = vecInfo[i]->ObjectList->begin();
		auto	iterEnd = vecInfo[i]->ObjectList->end();

		for (; iter != iterEnd; ++iter)
		{
			if (!(*iter)->GetName().compare(Name))
			{
				m_SelectType = vecInfo[i]->Type;

				switch (m_SelectType)
				{
				case Object_Type::Monster:
					ObjectDetailType = (int)vecInfo[i]->MonsterType;
					ObjectNum = vecInfo[i]->FieldObjNum;
					break;
				case Object_Type::FieldObj:
					ObjectDetailType = (int)vecInfo[i]->FieldObjType;
					ObjectNum = vecInfo[i]->FieldObjNum;
					break;
				}

				Find = true;
				break;
			}
		}

		if (Find)
			break;
	}

	m_SelectObject = FindObject(m_SelectScene, m_SelectType, ObjectDetailType, ObjectNum, Name);

	m_SceneListBox->SetSelectItem(m_SelectScene);

	m_TypeListBox->SetSelectItem(CEditorManager::GetInst()->GetHierarchyName(m_SelectType));

	RefreshObject();

	m_ObjectListBox->SetSelectItem(Name);

	if (m_SelectType == Object_Type::Player ||
		m_SelectType == Object_Type::Monster)
	{
		Object_Info* Info = FindInfo(m_SelectType);

		if (Info)
		{
			CharacterInfo* CharInfo = Info->FindCharacterInfo(Name);

			if (CharInfo)
				CEditorManager::GetInst()->GetObjectWindow()->Refresh(m_SelectType, *CharInfo, m_SelectObject);

			else
				CEditorManager::GetInst()->GetObjectWindow()->Reset();
		}
	}

	CEditorManager::GetInst()->GetObjectWindow()->SetTarget(m_SelectObject);

	CEditorManager::GetInst()->GetInfoWindow()->SetObjName(m_SelectObject->GetName());
}

void CHierarchyWindow::Clear()
{
	Cancel();

	m_SceneListBox->Clear();
	m_TypeListBox->Clear();
	m_ObjectListBox->Clear();
}

void CHierarchyWindow::RefreshObject()
{
	m_ObjectListBox->Clear();

	if (m_InfoList)
	{
		std::vector<Object_Info*>	vecInfo;
		FindInfo(m_SelectType, vecInfo);

		if (vecInfo.empty())
			return;

		size_t Size = vecInfo.size();

		for (size_t i = 0; i < Size; ++i)
		{
			auto	iter = vecInfo[i]->ObjectList->begin();
			auto	iterEnd = vecInfo[i]->ObjectList->end();

			for (; iter != iterEnd; ++iter)
			{
				m_ObjectListBox->AddItem((*iter)->GetName());
			}
		}
	}
}

void CHierarchyWindow::SelectScene(const std::string& SceneName)
{
	auto	iter = m_SceneNameList.begin();
	auto	iterEnd = m_SceneNameList.end();

	for (; iter != iterEnd; ++iter)
	{
		if (*iter == SceneName)
		{
			m_SelectScene = SceneName;

			CEditorManager::GetInst()->SetInfo(m_SelectScene);
			break;
		}
	}

	CEditorManager::GetInst()->GetSceneWindow()->ObjectRenderUpdate(m_SelectScene);

	m_SceneListBox->SetSelectItem(m_SelectScene);
}

void CHierarchyWindow::CancelKey(float DeltaTime)
{
	Cancel();
}

void CHierarchyWindow::SelectScene(int Index, const char* Item)
{
	std::string	Name = m_SceneListBox->GetItem(Index);

	{
		auto	iter = m_SceneNameList.begin();
		auto	iterEnd = m_SceneNameList.end();

		for (; iter != iterEnd; ++iter)
		{
			if (*iter == Name)
			{
				m_SelectScene = Name;

				CEditorManager::GetInst()->SetInfo(m_SelectScene);
				break;
			}
		}
	}

	CEditorManager::GetInst()->GetSceneWindow()->ObjectRenderUpdate(m_SelectScene);
}

void CHierarchyWindow::CancelScene()
{
	m_SelectScene = "";

	m_SceneListBox->SetSelectCancel(true);

	m_TypeListBox->Clear();

	CEditorManager::GetInst()->GetSceneWindow()->ObjectRenderUpdate(m_SelectScene);

	CancelType();
}

void CHierarchyWindow::AddType(Object_Type Type)
{
	AddType(m_SelectScene, Type);
}

void CHierarchyWindow::RefreshScene(bool Cancel)
{
	if (Cancel)
		CancelScene();

	m_SceneListBox->Clear();

	auto	iter = m_SceneNameList.begin();
	auto	iterEnd = m_SceneNameList.end();

	for (; iter != iterEnd; ++iter)
	{
		if (!m_SceneListBox->CheckItem(*iter))
			m_SceneListBox->AddItem(*iter);
	}

	if (!m_InfoList)
		return;

	else if (m_InfoList->empty())
		return;

	RefreshType();
}

void CHierarchyWindow::CancelType()
{
	m_SelectType = Object_Type::Max;

	m_TypeListBox->SetSelectCancel(true);

	m_ObjectListBox->Clear();

	CancelObject();
}

void CHierarchyWindow::CancelObject()
{
	m_SelectObject = nullptr;

	m_ObjectListBox->SetSelectCancel(true);

	CEditorManager::GetInst()->GetObjectWindow()->ClearTarget();

	Vector3	none;

	CEditorManager::GetInst()->GetInfoWindow()->SetObjName("");
	CEditorManager::GetInst()->GetInfoWindow()->SetObjPos(none);
}

void CHierarchyWindow::SelectType(int Index, const char* Item)
{
	Object_Type Type = CEditorManager::GetInst()->GetHierarchyType(Item);

	if (!FindType(Type))
		return;

	CancelObject();

	m_ObjectListBox->Clear();

	m_SelectType = Type;

	std::vector<Object_Info*>	vecInfo;
	FindInfo(Type, vecInfo);

	if (vecInfo.empty())
		return;

	size_t Size = vecInfo.size();

	for (size_t i = 0; i < Size; ++i)
	{
		auto	iter = vecInfo[i]->ObjectList->begin();
		auto	iterEnd = vecInfo[i]->ObjectList->end();

		for (; iter != iterEnd; ++iter)
		{
			m_ObjectListBox->AddItem((*iter)->GetName());
		}
	}
}

void CHierarchyWindow::SelectObject(int Index, const char* Item)
{
	if (m_SelectType == Object_Type::Max || !FindType(m_SelectType))
		ASSERT("if (m_SelectType == Object_Type::Max || !FindType(m_SelectType))");

	std::vector< Object_Info*>	vecInfo;
	FindInfo(m_SelectType, vecInfo);

	if (vecInfo.empty())
		return;

	size_t Size = vecInfo.size();

	for (size_t i = 0; i < Size; ++i)
	{
		auto	iter = vecInfo[i]->ObjectList->begin();
		auto	iterEnd = vecInfo[i]->ObjectList->end();

		for (; iter != iterEnd; ++iter)
		{
			if (!(*iter)->GetName().compare(Item))
			{
				m_SelectObject = *iter;

				CEditorManager::GetInst()->GetObjectWindow()->Refresh(vecInfo[i]->Type, *(vecInfo[i]->FindCharacterInfo((*iter)->GetName())), m_SelectObject);
				CEditorManager::GetInst()->GetObjectWindow()->SetTarget(m_SelectObject);
				CEditorManager::GetInst()->GetInfoWindow()->SetObjName(m_SelectObject->GetName());
				return;
			}
		}
	}
}

bool CHierarchyWindow::HasObjectName(const std::string& Name)
{
	auto	iter = m_InfoList->begin();
	auto	iterEnd = m_InfoList->end();

	for (; iter != iterEnd; ++iter)
	{
		auto	iter1 = (*iter)->ObjectList->begin();
		auto	iter1End = (*iter)->ObjectList->end();

		for (; iter1 != iter1End; ++iter1)
		{
			if (!(*iter1)->GetName().compare(Name))
				return true;
		}
	}

	return false;
}
