#include "SceneWindow.h"
#include "HierarchyWindow.h"
#include "ObjectWindow.h"
#include "InfoWindow.h"
#include "IMGUISameLine.h"
#include "IMGUITree.h"
#include "IMGUILabel.h"
#include "IMGUITextInput.h"
#include "IMGUIButton.h"
#include "IMGUIListBox.h"
#include "Engine.h"
#include "PathManager.h"
#include "Object_Info.h"
#include "Excel/Excel.h"
#include "Excel/ExcelManager.h"
#include "Scene/SceneManager.h"
#include "../EditorManager.h"
#include "../Object/Player/Player.h"
#include "../Object/LandScape/LandScapeObj.h"
#include "../Object/Monster/Barnos.h"
#include "../Object/Monster/Jagras.h"
#include "../Object/Monster/Kestodon.h"
#include "../Object/Monster/Vespoid.h"
#include "../Object/Monster/Anjanath.h"
#include "../Object/Monster/Rathalos.h"
#include "../Object/FieldObj/SlidingBox.h"
#include "../Object/FieldObj/HealFlower.h"
#include "../Object/FieldObj/SmallTree1.h"
#include "../Object/FieldObj/SmallTree2.h"
#include "../Object/FieldObj/SmallTree3.h"
#include "../Object/FieldObj/SmallTree4.h"
#include "../Object/FieldObj/SmallTree5.h"
#include "../Object/FieldObj/Tree1.h"
#include "../Object/FieldObj/Tree2.h"
#include "../Object/FieldObj/Tree3.h"
#include "../Object/FieldObj/Tree4.h"
#include "../Object/FieldObj/Tree5.h"
#include "../Object/FieldObj/Tree6.h"
#include "../Object/FieldObj/Tree7.h"
#include "../Object/FieldObj/Tree8.h"
#include "../Object/FieldObj/Tree9.h"
#include "../Object/FieldObj/BigTree.h"
#include "../Object/FieldObj/BrokenTree1.h"
#include "../Object/FieldObj/BrokenTree2.h"
#include "../Object/FieldObj/BrokenTree3.h"
#include "../Object/FieldObj/MushRoom1.h"
#include "../Object/FieldObj/MushRoom2.h"
#include "../Object/FieldObj/MushRoom3.h"
#include "../Object/FieldObj/Grass1.h"
#include "../Object/FieldObj/Grass2.h"
#include "../Object/FieldObj/Grass3.h"
#include "../Object/FieldObj/Grass4.h"
#include "../Object/FieldObj/Grass5.h"
#include "../Object/FieldObj/Grass6.h"
#include "../Object/FieldObj/Grass7.h"
#include "../Object/FieldObj/Grass8.h"
#include "../Object/FieldObj/Grass9.h"
#include "../Object/FieldObj/SmallGrass.h"
#include "../Object/FieldObj/Vine.h"
#include "../Object/FieldObj/Vine2.h"
#include "../Object/FieldObj/Vine3.h"
#include "../Object/FieldObj/Vine4.h"
#include "../Object/FieldObj/Vine5.h"
#include "../Object/FieldObj/Precipice.h"
#include "../Object/FieldObj/Precipice2.h"
#include "../Object/FieldObj/Sculpture.h"
#include "../Object/FieldObj/SmallStone1.h"
#include "../Object/FieldObj/GrassRock1.h"
#include "../Object/FieldObj/GrassRock2.h"
#include "../Object/FieldObj/GrassRock3.h"
#include "../Object/FieldObj/GrassRock4.h"
#include "../Object/FieldObj/GrassRock5.h"
#include "../Object/FieldObj/GrassRock6.h"
#include "../Object/FieldObj/GrassRock7.h"
#include "../Object/FieldObj/GrassRock8.h"
#include "../Object/FieldObj/GrassRock9.h"
#include "../Object/FieldObj/Wreck1.h"
#include "../Object/FieldObj/Tent1.h"
#include "../Object/FieldObj/Tent2.h"
#include "../Object/FieldObj/Box1.h"
#include "../Object/FieldObj/Far.h"
#include "../Object/FieldObj/DesertPebble.h"
#include "../Object/FieldObj/DesertSmallStone.h"
#include "../Object/FieldObj/DesertStone1.h"
#include "../Object/FieldObj/DesertStone2.h"
#include "../Object/FieldObj/DesertStone3.h"
#include "../Object/FieldObj/DesertStone4.h"
#include "../Object/FieldObj/DesertStone5.h"
#include "../Object/FieldObj/DesertStone6.h"
#include "../Object/FieldObj/DesertBigStone.h"
#include "../Object/FieldObj/DesertRockWall.h"
#include "../Object/FieldObj/DesertStalactite1.h"
#include "../Object/FieldObj/DesertStalactite2.h"
#include "../Object/FieldObj/DesertStalactite3.h"
#include "../Object/FieldObj/DesertStalactite4.h"
#include "../Object/FieldObj/DesertStalagmite1.h"
#include "../Object/FieldObj/DesertStalagmite2.h"
#include "../Object/FieldObj/DesertStalagmite3.h"
#include "../Object/FieldObj/Stonej1.h"
#include "../Object/FieldObj/Stonej2.h"
#include "../Object/FieldObj/Stonej3.h"
#include "../Object/FieldObj/Stonej4.h"
#include "../Object/FieldObj/Stonej5.h"
#include "../Object/FieldObj/Stonej6.h"
#include "../Object/FieldObj/Stonej7.h"
#include "../Object/FieldObj/Stonej8.h"
#include "../Object/FieldObj/Stonej9.h"
#include "../Object/FieldObj/Stonej10.h"
#include "../Object/FieldObj/Stonej11.h"
#include "../Object/FieldObj/Stonej12.h"
#include "../Object/FieldObj/Stonej13.h"
#include "../Object/FieldObj/Stonej14.h"
#include "../Object/FieldObj/Stonej15.h"
#include "../Object/FieldObj/Stonej16.h"
#include "../Object/FieldObj/Stonej17.h"
#include "../Object/FieldObj/Stonej18.h"
#include "../Object/FieldObj/Stonej19.h"
#include "../Object/FieldObj/Stonej20.h"
#include "../Object/FieldObj/Stonej21.h"
#include "../Object/FieldObj/Stonej22.h"
#include "../Object/FieldObj/Stonej23.h"
#include "../Object/FieldObj/Stonej24.h"
#include "../Object/FieldObj/Stonej25.h"
#include "../Object/FieldObj/Stonej26.h"
#include "../Object/FieldObj/Stonej27.h"
#include "../Object/FieldObj/Stonej28.h"
#include "../Object/FieldObj/Stonej29.h"
#include "../Object/FieldObj/Stonej30.h"
#include "../Object/FieldObj/Stonej31.h"
#include "../Object/FieldObj/Stonej32.h"
#include "../Object/FieldObj/Stonej33.h"
#include "../Object/FieldObj/Stonej34.h"
#include "../Object/FieldObj/Stonej35.h"
#include "../Object/FieldObj/Stonej36.h"
#include "../Object/FieldObj/Stonej37.h"
#include "../Object/FieldObj/TownBarrel.h"
#include "../Object/FieldObj/TownCarriage.h"
#include "../Object/FieldObj/TownCheckPoint.h"
#include "../Object/FieldObj/TownDragonHead.h"
#include "../Object/FieldObj/TownPassage.h"
#include "../Object/FieldObj/TownPumpkinMan.h"
#include "../Object/FieldObj/TownRampart.h"
#include "../Object/FieldObj/TownShadeScreen.h"
#include "../Object/FieldObj/TownSign.h"
#include "../Object/FieldObj/TownStructure.h"
#include "../Object/FieldObj/TownSummerHouse.h"
#include "../Object/FieldObj/TownTunnel.h"
#include "../Object/FieldObj/DesertMountain1.h"
#include "../Object/FieldObj/DesertMountain2.h"

CSceneWindow::CSceneWindow()	:
	m_NameTextInput(nullptr),
	m_CreateButton(nullptr),
	m_DeleteButton(nullptr),
	m_SaveButton(nullptr),
	m_LoadButton(nullptr)
{
}

CSceneWindow::~CSceneWindow()
{
	auto	iter = m_mapScene.begin();
	auto	iterEnd = m_mapScene.end();

	for (; iter != iterEnd; ++iter)
	{
		auto	iter1 = iter->second->begin();
		auto	iter1End = iter->second->end();

		for (; iter1 != iter1End; ++iter1)
		{
			SAFE_DELETE(*iter1); // Object_Info
		}

		SAFE_DELETE(iter->second);
	}
}

bool CSceneWindow::Init()
{
	CIMGUISameLine* Line = nullptr;

	m_NameTextInput = AddWidget<CIMGUITextInput>("NameTextInput", 120.f, 20.f);
	m_NameTextInput->SetHideName();
	m_NameTextInput->SetTextType(ImGuiText_Type::String);	
	m_NameTextInput->SetText("Scene1");

	m_CreateButton = AddWidget<CIMGUIButton>(UTF8("생성"), 60.f, 20.f);
	m_CreateButton->SetClickCallback(this, &CSceneWindow::Create);

	Line = AddWidget<CIMGUISameLine>("Line");

	m_DeleteButton = AddWidget<CIMGUIButton>(UTF8("삭제"), 52.f, 20.f);
	m_DeleteButton->SetClickCallback(this, &CSceneWindow::Delete);
	m_DeleteButton->SetColor(255, 0, 0);

	m_SaveButton = AddWidget<CIMGUIButton>(UTF8("세이브"), 60.f, 20.f);
	m_SaveButton->SetClickCallback(this, &CSceneWindow::Save);

	Line = AddWidget<CIMGUISameLine>("Line");

	m_LoadButton = AddWidget<CIMGUIButton>(UTF8("로드"), 52.f, 20.f);
	m_LoadButton->SetClickCallback(this, &CSceneWindow::Load);

	return true;
}

void CSceneWindow::Update(float DeltaTime)
{
	if (IsKeyDown(VK_F1))
		CEditorManager::GetInst()->CamToggle();

	CIMGUIWindow::Update(DeltaTime);
}

void CSceneWindow::Create()
{
	const wchar_t* Text = m_NameTextInput->GetText();

	if (Text == L"")
		return;

	int	Length = WideCharToMultiByte(CP_ACP, 0, Text, -1, 0, 0, 0, 0);

	char* Convert = DBG_NEW char[Length + 1];
	WideCharToMultiByte(CP_ACP, 0, Text, -1, Convert, Length, 0, 0);

	if (Convert != 0)
	{
		auto	iter = m_mapScene.find(Convert);

		if (iter != m_mapScene.end())
		{
			SAFE_DELETE_ARRAY(Convert);
			return;
		}

		std::list<Object_Info*>* NewObjectList = DBG_NEW std::list<Object_Info*>;

		m_mapScene.insert(std::make_pair(Convert, NewObjectList));

		CEditorManager::GetInst()->GetHierarchyWindow()->AddSceneName(Convert);
	}

	SAFE_DELETE_ARRAY(Convert);
}

void CSceneWindow::Delete()
{
	const std::string SelectName = CEditorManager::GetInst()->GetHierarchyWindow()->GetSelectScene();

	if (SelectName == "")
		return;

	auto	iter = m_mapScene.find(SelectName);

	if (iter == m_mapScene.end())
		return;

	CEditorManager::GetInst()->GetHierarchyWindow()->DeleteSelectScene();

	auto	iter1 = iter->second->begin();
	auto	iter1End = iter->second->end();

	for (; iter1 != iter1End; ++iter1)
	{
		SAFE_DELETE(*iter1);
	}

	SAFE_DELETE(iter->second);

	m_mapScene.erase(iter);

	Vector3	none;

	CEditorManager::GetInst()->GetInfoWindow()->SetObjName("");
	CEditorManager::GetInst()->GetInfoWindow()->SetObjPos(none);

	CEditorManager::GetInst()->GetObjectWindow()->Reset();
}

void CSceneWindow::Save()
{
	if (m_mapScene.empty())
		return;

	else if (CEditorManager::GetInst()->GetHierarchyWindow()->Empty())
		return;

	TCHAR   SCNPath[MAX_PATH] = {};

	OPENFILENAME    OpenFile = {};

	OpenFile.lStructSize = sizeof(OPENFILENAME);
	OpenFile.hwndOwner = CEngine::GetInst()->GetWindowHandle();
	OpenFile.lpstrFilter = TEXT("Scene Data (*.scn)\0*.scn");
	OpenFile.lpstrFile = SCNPath;
	OpenFile.nMaxFile = MAX_PATH;
	OpenFile.lpstrInitialDir = CPathManager::GetInst()->FindPath(DATA_PATH)->Path;

	if (GetSaveFileName(&OpenFile) != 0)
	{
		// .scn이 붙었는지 확인
		size_t	PathLength = lstrlen(SCNPath);

		TCHAR	scn[5] = TEXT("ncs.");
		bool	Find = true;

		for (size_t i = 1; i < 5; ++i)
		{
			if (SCNPath[PathLength - i] != scn[i - 1])
			{
				Find = false;
				break;
			}
		}

		if (!Find) // scn 확장자가 붙지 않았을 경우 붙여준다.
			lstrcat(SCNPath, TEXT(".scn"));

		char    SCNFullPath[MAX_PATH] = {};

		int Length = WideCharToMultiByte(CP_ACP, 0, SCNPath, -1, 0, 0, 0, 0);
		WideCharToMultiByte(CP_ACP, 0, SCNPath, -1, SCNFullPath, Length, 0, 0);

		FILE* File = nullptr;

		fopen_s(&File, SCNFullPath, "wb");

		if (!File)
			return;

		CLandScapeObj* LandScape = CEditorManager::GetInst()->GetLandScapeObj();

		if (LandScape)
			LandScape->SetNavData();

		CExcel* NewExcel = nullptr;
		
		std::string	SelectScene = CEditorManager::GetInst()->GetHierarchyWindow()->GetSelectScene();
		size_t SceneNameLen = SelectScene.length();
		fwrite(&SceneNameLen, sizeof(size_t), 1, File);

		const char* SelectSceneMultibyte = SelectScene.c_str();
		fwrite(SelectSceneMultibyte, sizeof(char*) * SceneNameLen, 1, File);

		auto Sceneiter = m_mapScene.find(SelectScene);

		if (Sceneiter == m_mapScene.end())
			ASSERT("if (iter == m_mapScene.end())");

		size_t ObjectInfoListMax = Sceneiter->second->size();
		fwrite(&ObjectInfoListMax, sizeof(size_t), 1, File);

		auto	ObjectInfoIter = Sceneiter->second->begin();
		auto	ObjectInfoIterEnd = Sceneiter->second->end();

		for (; ObjectInfoIter != ObjectInfoIterEnd; ++ObjectInfoIter)
		{
			size_t GameObjectListMax = (*ObjectInfoIter)->ObjectList->size();
			fwrite(&GameObjectListMax, sizeof(size_t), 1, File);

			size_t Previ = 0;
			size_t IterCount = 0;

			auto	GameObjectIter = (*ObjectInfoIter)->ObjectList->begin();
			auto	GameObjectIterEnd = (*ObjectInfoIter)->ObjectList->end();

			for (; GameObjectIter != GameObjectIterEnd; ++GameObjectIter)
			{
				std::string	ObjectName = (*GameObjectIter)->GetName();

				size_t ObjectNameSize = ObjectName.length();
				fwrite(&ObjectNameSize, sizeof(size_t), 1, File);

				const char* ObjectNameMultibyte = ObjectName.c_str();
				fwrite(ObjectNameMultibyte, sizeof(char) * ObjectNameSize, 1, File);

				Object_Type	Type = (*ObjectInfoIter)->Type;
				fwrite(&Type, sizeof(Object_Type), 1, File);

				Monster_Type MonsterType = (*ObjectInfoIter)->MonsterType;
				fwrite(&MonsterType, sizeof(Monster_Type), 1, File);

				FieldObj_Type FieldObjType = (*ObjectInfoIter)->FieldObjType;
				fwrite(&FieldObjType, sizeof(FieldObj_Type), 1, File);

				int FieldObjNum = (*ObjectInfoIter)->FieldObjNum;
				fwrite(&FieldObjNum, sizeof(int), 1, File);

				size_t CharacterInfoListMax = (*ObjectInfoIter)->CharacterInfoList.size();
				fwrite(&CharacterInfoListMax, sizeof(size_t), 1, File);

				if (CharacterInfoListMax > 0)
				{
					auto	iter2 = (*ObjectInfoIter)->CharacterInfoList.begin();

					if (Previ < IterCount)
					{
						++iter2;
						++Previ;
					}

					char	resultPath[MAX_PATH] = {};
					strcpy_s(resultPath, MAX_PATH, SCNFullPath);

					size_t FullLength = strlen(resultPath);

					for (size_t i = FullLength; i > 0; --i)
					{
						if (resultPath[i] == '\\')
						{
							memset(&resultPath[i], 0, sizeof(char) * (FullLength - i));
							break;
						}
					}

					const char* TypeName = CEditorManager::GetInst()->GetHierarchyName(Type);

					size_t CharNameLen = (*iter2)->CharacterName.length();
					fwrite(&CharNameLen, sizeof(size_t), 1, File);

					const char* CharacterNameMultibyte = (*iter2)->CharacterName.c_str();
					fwrite(CharacterNameMultibyte, sizeof(char*) * CharNameLen, 1, File);

					char FileName[128] = {};

					strcpy_s(FileName, 128, TypeName);
					strcat_s(FileName, 128, "_");
					strcat_s(FileName, 128, (*iter2)->CharacterName.c_str());

					NewExcel = CExcelManager::GetInst()->CreateExcel(FileName, resultPath, true);

					if (!NewExcel)
						ASSERT("if (!NewExcel)");

					NewExcel->WriteString(L"AttackMin");
					NewExcel->WriteNumber((double)(*iter2)->AttackMin);

					NewExcel->NewLine();

					NewExcel->WriteString(L"AttackMax");
					NewExcel->WriteNumber((double)(*iter2)->AttackMax);

					NewExcel->NewLine();

					NewExcel->WriteString(L"HP");
					NewExcel->WriteNumber((double)(*iter2)->HP);

					NewExcel->NewLine();

					NewExcel->WriteString(L"Stamina");
					NewExcel->WriteNumber((double)(*iter2)->Stamina);

					NewExcel->NewLine();

					NewExcel->WriteString(L"Speed");
					NewExcel->WriteNumber((double)(*iter2)->Speed);

					NewExcel->NewLine();

					if (!NewExcel->Save())
						ASSERT("if (!NewExcel->Save())");

					++IterCount;
				}

				Vector3 WorldPos = (*GameObjectIter)->GetWorldPos();
				fwrite(&WorldPos, sizeof(Vector3), 1, File);

				Vector3 WorldScale = (*GameObjectIter)->GetWorldScale();
				fwrite(&WorldScale, sizeof(Vector3), 1, File);

				Vector3 WorldRot = (*GameObjectIter)->GetWorldRot();
				fwrite(&WorldRot, sizeof(Vector3), 1, File);

				if (Type == Object_Type::LandScape)
					(*GameObjectIter)->Save(File);
			}
		}

		fclose(File);
	}
}

void CSceneWindow::Load()
{
	TCHAR   SCNPath[MAX_PATH] = {};

	OPENFILENAME    OpenFile = {};

	OpenFile.lStructSize = sizeof(OPENFILENAME);
	OpenFile.hwndOwner = CEngine::GetInst()->GetWindowHandle();
	OpenFile.lpstrFilter = TEXT("Scene Data (*.scn)\0*.scn");
	OpenFile.lpstrFile = SCNPath;
	OpenFile.nMaxFile = MAX_PATH;
	OpenFile.lpstrInitialDir = CPathManager::GetInst()->FindPath(DATA_PATH)->Path;

	if (GetOpenFileName(&OpenFile) != 0)
	{
		// .scn이 붙었는지 확인
		size_t	PathLength = lstrlen(SCNPath);

		TCHAR	scn[5] = TEXT("ncs.");
		bool	Find = true;

		for (size_t i = 1; i < 5; ++i)
		{
			if (SCNPath[PathLength - i] != scn[i - 1])
			{
				Find = false;
				break;
			}
		}

		if (!Find) // scn 확장자가 붙지 않았을 경우 붙여준다.
			lstrcat(SCNPath, TEXT(".scn"));

		char    SCNFullPath[MAX_PATH] = {};

		int Length = WideCharToMultiByte(CP_ACP, 0, SCNPath, -1, 0, 0, 0, 0);
		WideCharToMultiByte(CP_ACP, 0, SCNPath, -1, SCNFullPath, Length, 0, 0);

		FILE* File = nullptr;

		fopen_s(&File, SCNFullPath, "rb");

		if (!File)
			return;

		CExcel* NewExcel = nullptr;

		size_t SceneNameLen = 0;
		fread(&SceneNameLen, sizeof(size_t), 1, File);

		char SelectSceneMultibyte[128] = {};
		fread(SelectSceneMultibyte, sizeof(char*) * SceneNameLen, 1, File);

		if (!SelectSceneMultibyte)
			ASSERT("if (!SelectSceneMultibyte)");

		std::string	SelectScene = SelectSceneMultibyte;

		if (FindInfo(SelectScene))
			return;

		CEditorManager::GetInst()->GetHierarchyWindow()->Clear();

		std::list<Object_Info*>* NewObjectInfoList = DBG_NEW std::list<Object_Info*>;

		size_t ObjectInfoListMax = 0;
		fread(&ObjectInfoListMax, sizeof(size_t), 1, File);

		for (size_t ObjectInfoListi = 0; ObjectInfoListi < ObjectInfoListMax; ++ObjectInfoListi)
		{
			Object_Info* NewInfo = DBG_NEW Object_Info;

			CEditorManager::GetInst()->GetHierarchyWindow()->AddSceneName(SelectScene);

			NewInfo->SceneName = SelectScene;

			size_t GameObjectListMax = 0;
			fread(&GameObjectListMax, sizeof(size_t), 1, File);

			CGameObject* NewObject = nullptr;

			for (size_t i = 0; i < GameObjectListMax; ++i)
			{
				size_t ObjectNameSize = 0;
				fread(&ObjectNameSize, sizeof(size_t), 1, File);

				char* ObjectNameMultibyte = DBG_NEW char[ObjectNameSize + 1];
				memset(ObjectNameMultibyte, 0, sizeof(char) * ObjectNameSize + 1);
				fread(ObjectNameMultibyte, sizeof(char) * ObjectNameSize, 1, File);

				Object_Type	Type = Object_Type::Max;
				fread(&Type, sizeof(Object_Type), 1, File);
				NewInfo->Type = Type;

				Monster_Type MonsterType = Monster_Type::Max;
				fread(&MonsterType, sizeof(Monster_Type), 1, File);
				NewInfo->MonsterType = MonsterType;

				FieldObj_Type FieldObjType = FieldObj_Type::Max;
				fread(&FieldObjType, sizeof(FieldObj_Type), 1, File);
				NewInfo->FieldObjType = FieldObjType;

				int FieldObjNum = 0;
				fread(&FieldObjNum, sizeof(int), 1, File);
				NewInfo->FieldObjNum = FieldObjNum;

				size_t CharacterInfoListMax = 0;
				fread(&CharacterInfoListMax, sizeof(size_t), 1, File);

				if (CharacterInfoListMax > 0)
				{
					CharacterInfo* NewCharacterInfo = DBG_NEW CharacterInfo;

					char	resultPath[MAX_PATH] = {};
					strcpy_s(resultPath, MAX_PATH, SCNFullPath);

					size_t FullLength = strlen(resultPath);

					for (size_t i = FullLength; i > 0; --i)
					{
						if (resultPath[i] == '\\')
						{
							memset(&resultPath[i], 0, sizeof(char) * (FullLength - i));
							break;
						}
					}

					const char* TypeName = CEditorManager::GetInst()->GetHierarchyName(Type);

					size_t CharNameLen = 0;
					fread(&CharNameLen, sizeof(size_t), 1, File);

					char CharacterNameMultibyte[128] = {};
					fread(CharacterNameMultibyte, sizeof(char*) * CharNameLen, 1, File);
					NewCharacterInfo->CharacterName = CharacterNameMultibyte;

					if (CharacterNameMultibyte == "")
						ASSERT("if (CharacterNameMultibyte == "")");

					char FileName[128] = {};

					strcpy_s(FileName, 128, TypeName);
					strcat_s(FileName, 128, "_");
					strcat_s(FileName, 128, NewCharacterInfo->CharacterName.c_str());

					NewExcel = CExcelManager::GetInst()->CreateExcel(FileName, resultPath, false);

					if (!NewExcel)
						ASSERT("if (!NewExcel)");

					NewExcel->NextLine(); // AttackMin
					NewCharacterInfo->AttackMin = NewExcel->ReadNumberFloat();

					NewExcel->NewLine();

					NewExcel->NextLine(); // AttackMax
					NewCharacterInfo->AttackMax = NewExcel->ReadNumberFloat();

					NewExcel->NewLine();

					NewExcel->NextLine(); // HP
					NewCharacterInfo->HP = NewExcel->ReadNumberFloat();

					NewExcel->NewLine();

					NewExcel->NextLine(); // Stamina
					NewCharacterInfo->Stamina = NewExcel->ReadNumberFloat();

					NewExcel->NewLine();

					NewExcel->NextLine(); // Speed
					NewCharacterInfo->Speed = NewExcel->ReadNumberFloat();

					NewInfo->CharacterInfoList.push_back(NewCharacterInfo);
				}

				if (NewInfo->Type == Object_Type::Player)
				{
					NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CPlayer>(ObjectNameMultibyte);
					CSceneManager::GetInst()->GetScene()->SetPlayerObject(NewObject);
				}

				else if (NewInfo->Type == Object_Type::Monster)
				{
					switch (NewInfo->MonsterType)
					{
					case Monster_Type::Barnos:
						NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CBarnos>(ObjectNameMultibyte);
						break;
					case Monster_Type::Jagras:
						NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CJagras>(ObjectNameMultibyte);
						break;
					case Monster_Type::Kestodon:
						NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CKestodon>(ObjectNameMultibyte);
						break;
					case Monster_Type::Vespoid:
						NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CVespoid>(ObjectNameMultibyte);
						break;
					case Monster_Type::Anjanath:
						NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CAnjanath>(ObjectNameMultibyte);
						break;
					case Monster_Type::Rathalos:
						NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CRathalos>(ObjectNameMultibyte);
						break;
					}
				}

				else if (NewInfo->Type == Object_Type::LandScape)
					NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CLandScapeObj>(ObjectNameMultibyte);

				else if (NewInfo->Type == Object_Type::FieldObj)
				{
					switch (NewInfo->FieldObjType)
					{
					case FieldObj_Type::SlidingBox:
						NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CSlidingBox>(ObjectNameMultibyte);
						break;
					case FieldObj_Type::HealFlower:
						NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CHealFlower>(ObjectNameMultibyte);
						break;
					case FieldObj_Type::SmallTree:
						if (NewInfo->FieldObjNum == 1)
							NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CSmallTree1>(ObjectNameMultibyte);
						else if (NewInfo->FieldObjNum == 2)
							NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CSmallTree2>(ObjectNameMultibyte);
						else if (NewInfo->FieldObjNum == 3)
							NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CSmallTree3>(ObjectNameMultibyte);
						else if (NewInfo->FieldObjNum == 4)
							NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CSmallTree4>(ObjectNameMultibyte);
						else if (NewInfo->FieldObjNum == 5)
							NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CSmallTree5>(ObjectNameMultibyte);
						break;
					case FieldObj_Type::Tree:
						if (NewInfo->FieldObjNum == 1)
							NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CTree1>(ObjectNameMultibyte);
						else if (NewInfo->FieldObjNum == 2)
							NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CTree2>(ObjectNameMultibyte);
						else if (NewInfo->FieldObjNum == 3)
							NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CTree3>(ObjectNameMultibyte);
						else if (NewInfo->FieldObjNum == 4)
							NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CTree4>(ObjectNameMultibyte);
						else if (NewInfo->FieldObjNum == 5)
							NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CTree5>(ObjectNameMultibyte);
						else if (NewInfo->FieldObjNum == 6)
							NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CTree6>(ObjectNameMultibyte);
						else if (NewInfo->FieldObjNum == 7)
							NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CTree7>(ObjectNameMultibyte);
						else if (NewInfo->FieldObjNum == 8)
							NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CTree8>(ObjectNameMultibyte);
						else if (NewInfo->FieldObjNum == 9)
							NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CTree9>(ObjectNameMultibyte);
						break;
					case FieldObj_Type::BigTree:
						NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CBigTree>(ObjectNameMultibyte);
						break;
					case FieldObj_Type::BrokenTree:
						if (NewInfo->FieldObjNum == 1)
							NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CBrokenTree1>(ObjectNameMultibyte);
						else if (NewInfo->FieldObjNum == 2)
							NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CBrokenTree2>(ObjectNameMultibyte);
						else if (NewInfo->FieldObjNum == 3)
							NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CBrokenTree3>(ObjectNameMultibyte);
						break;
					case FieldObj_Type::MushRoom:
						if (NewInfo->FieldObjNum == 1)
							NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CMushRoom1>(ObjectNameMultibyte);
						else if (NewInfo->FieldObjNum == 2)
							NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CMushRoom2>(ObjectNameMultibyte);
						else if (NewInfo->FieldObjNum == 3)
							NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CMushRoom3>(ObjectNameMultibyte);
						break;
					case FieldObj_Type::SmallGrass:
						NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CSmallGrass>(ObjectNameMultibyte);
						break;
					case FieldObj_Type::Grass:
						if (NewInfo->FieldObjNum == 1)
							NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CGrass1>(ObjectNameMultibyte);
						else if (NewInfo->FieldObjNum == 2)
							NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CGrass2>(ObjectNameMultibyte);
						else if (NewInfo->FieldObjNum == 3)
							NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CGrass3>(ObjectNameMultibyte);
						else if (NewInfo->FieldObjNum == 4)
							NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CGrass4>(ObjectNameMultibyte);
						else if (NewInfo->FieldObjNum == 5)
							NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CGrass5>(ObjectNameMultibyte);
						else if (NewInfo->FieldObjNum == 6)
							NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CGrass6>(ObjectNameMultibyte);
						else if (NewInfo->FieldObjNum == 7)
							NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CGrass7>(ObjectNameMultibyte);
						else if (NewInfo->FieldObjNum == 8)
							NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CGrass8>(ObjectNameMultibyte);
						else if (NewInfo->FieldObjNum == 9)
							NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CGrass9>(ObjectNameMultibyte);
						break;
					case FieldObj_Type::Vine:
						if (NewInfo->FieldObjNum == 1)
							NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CVine>(ObjectNameMultibyte);
						else if (NewInfo->FieldObjNum == 2)
							NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CVine2>(ObjectNameMultibyte);
						else if (NewInfo->FieldObjNum == 3)
							NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CVine3>(ObjectNameMultibyte);
						else if (NewInfo->FieldObjNum == 4)
							NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CVine4>(ObjectNameMultibyte);
						else if (NewInfo->FieldObjNum == 5)
							NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CVine5>(ObjectNameMultibyte);
						break;
					case FieldObj_Type::Precipice:
						if (NewInfo->FieldObjNum == 1)
							NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CPrecipice>(ObjectNameMultibyte);
						else if (NewInfo->FieldObjNum == 2)
							NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CPrecipice2>(ObjectNameMultibyte);
						break;
					case FieldObj_Type::Sculpture:
						NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CSculpture>(ObjectNameMultibyte);
						break;
					case FieldObj_Type::SmallStone:
						NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CSmallStone1>(ObjectNameMultibyte);
						break;
					case FieldObj_Type::GrassRock:
						if (NewInfo->FieldObjNum == 1)
							NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CGrassRock1>(ObjectNameMultibyte);
						else if (NewInfo->FieldObjNum == 2)
							NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CGrassRock2>(ObjectNameMultibyte);
						else if (NewInfo->FieldObjNum == 3)
							NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CGrassRock3>(ObjectNameMultibyte);
						else if (NewInfo->FieldObjNum == 4)
							NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CGrassRock4>(ObjectNameMultibyte);
						else if (NewInfo->FieldObjNum == 5)
							NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CGrassRock5>(ObjectNameMultibyte);
						else if (NewInfo->FieldObjNum == 6)
							NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CGrassRock6>(ObjectNameMultibyte);
						else if (NewInfo->FieldObjNum == 7)
							NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CGrassRock7>(ObjectNameMultibyte);
						else if (NewInfo->FieldObjNum == 8)
							NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CGrassRock8>(ObjectNameMultibyte);
						else if (NewInfo->FieldObjNum == 9)
							NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CGrassRock9>(ObjectNameMultibyte);
						break;
					case FieldObj_Type::Wreck:
						NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CWreck1>(ObjectNameMultibyte);
						break;
					case FieldObj_Type::Tent:
						if (NewInfo->FieldObjNum == 1)
							NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CTent1>(ObjectNameMultibyte);
						else if (NewInfo->FieldObjNum == 2)
							NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CTent2>(ObjectNameMultibyte);
						break;
					case FieldObj_Type::Box:
						NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CBox1>(ObjectNameMultibyte);
						break;
					case FieldObj_Type::Far:
						NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CFar>(ObjectNameMultibyte);
						break;
					case FieldObj_Type::Stone:
						if (NewInfo->FieldObjNum == 1)
							NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CStonej1>(ObjectNameMultibyte);
						else if (NewInfo->FieldObjNum == 2)
							NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CStonej2>(ObjectNameMultibyte);
						else if (NewInfo->FieldObjNum == 3)
							NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CStonej3>(ObjectNameMultibyte);
						else if (NewInfo->FieldObjNum == 4)
							NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CStonej4>(ObjectNameMultibyte);
						else if (NewInfo->FieldObjNum == 5)
							NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CStonej5>(ObjectNameMultibyte);
						else if (NewInfo->FieldObjNum == 6)
							NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CStonej6>(ObjectNameMultibyte);
						else if (NewInfo->FieldObjNum == 7)
							NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CStonej7>(ObjectNameMultibyte);
						else if (NewInfo->FieldObjNum == 8)
							NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CStonej8>(ObjectNameMultibyte);
						else if (NewInfo->FieldObjNum == 9)
							NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CStonej9>(ObjectNameMultibyte);
						else if (NewInfo->FieldObjNum == 10)
							NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CStonej10>(ObjectNameMultibyte);
						else if (NewInfo->FieldObjNum == 11)
							NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CStonej11>(ObjectNameMultibyte);
						else if (NewInfo->FieldObjNum == 12)
							NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CStonej12>(ObjectNameMultibyte);
						else if (NewInfo->FieldObjNum == 13)
							NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CStonej13>(ObjectNameMultibyte);
						else if (NewInfo->FieldObjNum == 14)
							NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CStonej14>(ObjectNameMultibyte);
						else if (NewInfo->FieldObjNum == 15)
							NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CStonej15>(ObjectNameMultibyte);
						else if (NewInfo->FieldObjNum == 16)
							NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CStonej16>(ObjectNameMultibyte);
						else if (NewInfo->FieldObjNum == 17)
							NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CStonej17>(ObjectNameMultibyte);
						else if (NewInfo->FieldObjNum == 18)
							NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CStonej18>(ObjectNameMultibyte);
						else if (NewInfo->FieldObjNum == 19)
							NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CStonej19>(ObjectNameMultibyte);
						else if (NewInfo->FieldObjNum == 20)
							NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CStonej20>(ObjectNameMultibyte);
						else if (NewInfo->FieldObjNum == 21)
							NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CStonej21>(ObjectNameMultibyte);
						else if (NewInfo->FieldObjNum == 22)
							NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CStonej22>(ObjectNameMultibyte);
						else if (NewInfo->FieldObjNum == 23)
							NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CStonej23>(ObjectNameMultibyte);
						else if (NewInfo->FieldObjNum == 24)
							NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CStonej24>(ObjectNameMultibyte);
						else if (NewInfo->FieldObjNum == 25)
							NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CStonej25>(ObjectNameMultibyte);
						else if (NewInfo->FieldObjNum == 26)
							NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CStonej26>(ObjectNameMultibyte);
						else if (NewInfo->FieldObjNum == 27)
							NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CStonej27>(ObjectNameMultibyte);
						else if (NewInfo->FieldObjNum == 28)
							NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CStonej28>(ObjectNameMultibyte);
						else if (NewInfo->FieldObjNum == 29)
							NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CStonej29>(ObjectNameMultibyte);
						else if (NewInfo->FieldObjNum == 30)
							NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CStonej30>(ObjectNameMultibyte);
						else if (NewInfo->FieldObjNum == 31)
							NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CStonej31>(ObjectNameMultibyte);
						else if (NewInfo->FieldObjNum == 32)
							NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CStonej32>(ObjectNameMultibyte);
						else if (NewInfo->FieldObjNum == 33)
							NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CStonej33>(ObjectNameMultibyte);
						else if (NewInfo->FieldObjNum == 34)
							NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CStonej34>(ObjectNameMultibyte);
						else if (NewInfo->FieldObjNum == 35)
							NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CStonej35>(ObjectNameMultibyte);
						else if (NewInfo->FieldObjNum == 36)
							NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CStonej36>(ObjectNameMultibyte);
						else if (NewInfo->FieldObjNum == 37)
							NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CStonej37>(ObjectNameMultibyte);
						break;
					case FieldObj_Type::TownBarrel:
						NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CTownBarrel>(ObjectNameMultibyte);
						break;
					case FieldObj_Type::TownCarriage:
						NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CTownCarriage>(ObjectNameMultibyte);
						break;
					case FieldObj_Type::TownCheckPoint:
						NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CTownCheckPoint>(ObjectNameMultibyte);
						break;
					case FieldObj_Type::TownDragonHead:
						NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CTownDragonHead>(ObjectNameMultibyte);
						break;
					case FieldObj_Type::TownPassage:
						NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CTownPassage>(ObjectNameMultibyte);
						break;
					case FieldObj_Type::TownPumpkinMan:
						NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CTownPumpkinMan>(ObjectNameMultibyte);
						break;
					case FieldObj_Type::TownRampart:
						NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CTownRampart>(ObjectNameMultibyte);
						break;
					case FieldObj_Type::TownShadeScreen:
						NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CTownShadeScreen>(ObjectNameMultibyte);
						break;
					case FieldObj_Type::TownSign:
						NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CTownSign>(ObjectNameMultibyte);
						break;
					case FieldObj_Type::TownStructure:
						NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CTownStructure>(ObjectNameMultibyte);
						break;
					case FieldObj_Type::TownSummerHouse:
						NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CTownSummerHouse>(ObjectNameMultibyte);
						break;
					case FieldObj_Type::TownTunnel:
						NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CTownTunnel>(ObjectNameMultibyte);
						break;
					case FieldObj_Type::DesertPebble:
						NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CDesertPebble>(ObjectNameMultibyte);
						break;
					case FieldObj_Type::DesertSmallStone:
						NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CDesertSmallStone>(ObjectNameMultibyte);
						break;
					case FieldObj_Type::DesertStone:
						if (NewInfo->FieldObjNum == 1)
							NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CDesertStone1>(ObjectNameMultibyte);
						else if (NewInfo->FieldObjNum == 2)
							NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CDesertStone2>(ObjectNameMultibyte);
						else if (NewInfo->FieldObjNum == 3)
							NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CDesertStone3>(ObjectNameMultibyte);
						else if (NewInfo->FieldObjNum == 4)
							NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CDesertStone4>(ObjectNameMultibyte);
						else if (NewInfo->FieldObjNum == 5)
							NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CDesertStone5>(ObjectNameMultibyte);
						else if (NewInfo->FieldObjNum == 6)
							NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CDesertStone6>(ObjectNameMultibyte);
						break;
					case FieldObj_Type::DesertBigStone:
						NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CDesertBigStone>(ObjectNameMultibyte);
						break;
					case FieldObj_Type::DesertRockWall:
						NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CDesertRockWall>(ObjectNameMultibyte);
						break;
					case FieldObj_Type::DesertStalactite:
						if (NewInfo->FieldObjNum == 1)
							NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CDesertStalactite1>(ObjectNameMultibyte);
						else if (NewInfo->FieldObjNum == 2)
							NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CDesertStalactite2>(ObjectNameMultibyte);
						else if (NewInfo->FieldObjNum == 3)
							NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CDesertStalactite3>(ObjectNameMultibyte);
						else if (NewInfo->FieldObjNum == 4)
							NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CDesertStalactite4>(ObjectNameMultibyte);
						break;
					case FieldObj_Type::DesertStalagmite:
						if (NewInfo->FieldObjNum == 1)
							NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CDesertStalagmite1>(ObjectNameMultibyte);
						else if (NewInfo->FieldObjNum == 2)
							NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CDesertStalagmite2>(ObjectNameMultibyte);
						else if (NewInfo->FieldObjNum == 3)
							NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CDesertStalagmite3>(ObjectNameMultibyte);
						break;
					case FieldObj_Type::DesertMountain:
						if (NewInfo->FieldObjNum == 1)
							NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CDesertMountain1>(ObjectNameMultibyte);
						else if (NewInfo->FieldObjNum == 2)
							NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CDesertMountain2>(ObjectNameMultibyte);
					}
				}

				SAFE_DELETE_ARRAY(ObjectNameMultibyte);

				Vector3 WorldPos, WorldScale, WorldRot;

				fread(&WorldPos, sizeof(Vector3), 1, File);
				fread(&WorldScale, sizeof(Vector3), 1, File);
				fread(&WorldRot, sizeof(Vector3), 1, File);

				NewObject->SetWorldPos(WorldPos);
				NewObject->SetWorldScale(WorldScale);

				if (Type == Object_Type::LandScape)
					NewObject->Load(File);

				else
					NewObject->SetWorldRot(WorldRot);

				bool AddSkip = false;

				if (!NewObjectInfoList->empty())
				{
					auto	iter = NewObjectInfoList->begin();
					auto	iterEnd = NewObjectInfoList->end();

					for (; iter != iterEnd; ++iter)
					{
						switch (NewInfo->Type)
						{
						case Object_Type::Monster:
							if ((*iter)->MonsterType == NewInfo->MonsterType)
								AddSkip = true;
							break;
						case Object_Type::FieldObj:
							if ((*iter)->FieldObjType == NewInfo->FieldObjType &&
								(*iter)->FieldObjNum == NewInfo->FieldObjNum)
								AddSkip = true;
							break;
						}

						if (AddSkip)
							break;
					}

				}

				if (!AddSkip)
					NewObjectInfoList->push_back(NewInfo);

				if (NewObject)
				{
					int DetailType = 0;
					int Index = 0;

					switch (NewInfo->Type)
					{
					case Object_Type::Monster:
						DetailType = (int)NewInfo->MonsterType;
						Index = (int)NewInfo->FieldObjNum;
						break;
					case Object_Type::FieldObj:
						DetailType = (int)NewInfo->FieldObjType;
						Index = (int)NewInfo->FieldObjNum;
						break;
					}

					CEditorManager::GetInst()->GetHierarchyWindow()->AddObject(SelectScene, NewInfo->Type, DetailType, Index, NewObject, NewObjectInfoList);
				}
			}
		}

		m_mapScene.insert(std::make_pair(SelectScene, NewObjectInfoList));

		fclose(File);

		CEditorManager::GetInst()->GetObjectWindow()->Reset();
	}
}

void CSceneWindow::CreateScene(const std::string& Name)
{
	std::list<Object_Info*>* NewObjectList = DBG_NEW std::list<Object_Info*>;

	m_mapScene.insert(std::make_pair(Name, NewObjectList));

	CEditorManager::GetInst()->GetHierarchyWindow()->AddSceneName(Name);
}

void CSceneWindow::ObjectRenderUpdate(const std::string& SceneName)
{
	auto	iter = m_mapScene.begin();
	auto	iterEnd = m_mapScene.end();

	for (; iter != iterEnd; ++iter)
	{
		if (!SceneName.compare(iter->first))
		{
			auto	iter1 = iter->second->begin();
			auto	iter1End = iter->second->end();

			for (; iter1 != iter1End; ++iter1)
			{
				auto	iter2 = (*iter1)->ObjectList->begin();
				auto	iter2End = (*iter1)->ObjectList->end();

				for (; iter2 != iter2End; ++iter2)
				{
					(*iter2)->Render();
					(*iter2)->Enable();
				}
			}
		}

		else
		{
			auto	iter1 = iter->second->begin();
			auto	iter1End = iter->second->end();

			for (; iter1 != iter1End; ++iter1)
			{
				auto	iter2 = (*iter1)->ObjectList->begin();
				auto	iter2End = (*iter1)->ObjectList->end();

				for (; iter2 != iter2End; ++iter2)
				{
					(*iter2)->Disable();
				}
			}
		}
	}
}

std::list<Object_Info*>* CSceneWindow::FindInfo(const std::string& SceneName)
{
	auto	iter = m_mapScene.find(SceneName);

	if (iter == m_mapScene.end())
		return nullptr;

	return iter->second;
}
