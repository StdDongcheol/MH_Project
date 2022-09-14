
#include "ObjectWindow.h"
#include "HierarchyWindow.h"
#include "SceneWindow.h"
#include "IMGUISameLine.h"
#include "IMGUITree.h"
#include "IMGUIComboBox.h"
#include "IMGUICheckBox.h"
#include "IMGUIRadio.h"
#include "IMGUILabel.h"
#include "IMGUIText.h"
#include "IMGUITextInput.h"
#include "IMGUIButton.h"
#include "IMGUIGizmo.h"
#include "PathManager.h"
#include "Excel/ExcelManager.h"
#include "Excel/Excel.h"
#include "Scene/SceneManager.h"
#include "../EditorManager.h"
#include "../Scene/EditorScene.h"
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

CObjectWindow::CObjectWindow()	:
	m_CharacterTree(nullptr),
	m_LandScapeTree(nullptr),
	m_BrushModeCheckBox(nullptr),
	m_TypeComboBox(nullptr),
	m_MonsterComboBox(nullptr),
	m_FieldObjComboBox(nullptr),
	m_TextureTypeComboBox(nullptr),
	m_AttMin(nullptr),
	m_AttMax(nullptr),
	m_HP(nullptr),
	m_Stamina(nullptr),
	m_Speed(nullptr),
	m_BrushScaleText(nullptr),
	m_LandScapeSize(nullptr),
	m_LandScapeTextureNum(nullptr),
	m_FieldObjNum(nullptr),
	m_BrushScale(nullptr),
	m_ModifyButton(nullptr),
	m_SaveButton(nullptr),
	m_LoadButton(nullptr),
	m_NavButton(nullptr),
	m_CircleBrushTypeRadio(nullptr),
	m_RectBrushTypeRadio(nullptr),
	m_HeightRadio(nullptr),
	m_SplattingRadio(nullptr),
	m_BrushMode(false),
	m_BrushType((int)Brush_Type::Circle),
	m_BrushEditType((int)BrushEdit_Type::Height),
	m_Gizmo(nullptr),
	m_LandScapeCountLine(nullptr),
	m_MonsterTypeLine(nullptr),
	m_FieldTypeLine(nullptr),
	m_BrushScaleLine(nullptr)
{
}

CObjectWindow::~CObjectWindow()
{
}

int CObjectWindow::GetLandScapeType() const
{
	return m_TextureTypeComboBox->GetSelectIndex();
}

bool CObjectWindow::Init()
{
	CIMGUISameLine* Line = nullptr;
	CIMGUILabel* Label = nullptr;
	CIMGUIText* Text = nullptr;
	char	Name[256] = {};

	m_ModifyButton = AddWidget<CIMGUIButton>(UTF8("능력치 수정"), 126.f, 20.f);
	m_ModifyButton->SetClickCallback(this, &CObjectWindow::ModifyButton);

	Line = AddWidget<CIMGUISameLine>("Line");

	m_NavButton = AddWidget<CIMGUIButton>(UTF8("네비게이션 적용"), 120.f, 20.f);
	m_NavButton->SetClickCallback(this, &CObjectWindow::NavButton);

	//

	Text = AddWidget<CIMGUIText>("Text", 120.f, 20.f);
	Text->SetHideName();
	Text->SetText("기즈모 유형 : ");

	Line = AddWidget<CIMGUISameLine>("Line");

	m_Gizmo = AddWidget<CIMGUIGizmo>("Gizmo");

	//

	m_TypeComboBox = AddWidget<CIMGUIComboBox>(UTF8("생성할 오브젝트"), 126.f, 20.f);
	m_TypeComboBox->SetHideName();
	
	std::vector<const char*>	vecHierarchyName;
	CEditorManager::GetInst()->GetHierarchyNameAll(vecHierarchyName);

	size_t Size = vecHierarchyName.size();

	for (size_t i = 0; i < Size; ++i)
	{
		if (strcmp(vecHierarchyName[i], ""))
			m_TypeComboBox->AddItem(vecHierarchyName[i]);
	}

	//

	m_MonsterTypeLine = AddWidget<CIMGUISameLine>("Line");

	m_MonsterComboBox = AddWidget<CIMGUIComboBox>(UTF8("몬스터 종류"), 120.f, 20.f);
	m_MonsterComboBox->SetHideName();

	std::vector<const char*>	vecMonsterName;
	CEditorManager::GetInst()->GetMonsterNameAll(vecMonsterName);

	Size = vecMonsterName.size();

	for (size_t i = 0; i < Size; ++i)
	{
		if (strcmp(vecMonsterName[i], ""))
			m_MonsterComboBox->AddItem(vecMonsterName[i]);
	}

	m_FieldTypeLine = AddWidget<CIMGUISameLine>("Line");

	m_FieldObjComboBox = AddWidget<CIMGUIComboBox>(UTF8("필드 종류"), 120.f, 20.f);
	m_FieldObjComboBox->SetHideName();

	std::vector<const char*>	vecFieldObjName;
	CEditorManager::GetInst()->GetFieldObjNameAll(vecFieldObjName);

	Size = vecFieldObjName.size();

	for (size_t i = 0; i < Size; ++i)
	{
		if (strcmp(vecFieldObjName[i], ""))
			m_FieldObjComboBox->AddItem(vecFieldObjName[i]);
	}

	m_FieldObjComboBox->Disable();
	m_FieldObjComboBox->SetSelectCallback(this, &CObjectWindow::RefreshFieldObjIndex);

	m_FieldObjNum = AddWidget<CIMGUITextInput>("FieldObjNum", 70.f, 20.f);
	m_FieldObjNum->SetHideName();
	m_FieldObjNum->SetTextType(ImGuiText_Type::Int);
	m_FieldObjNum->AddFlag(ImGuiInputTextFlags_CharsDecimal);
	m_FieldObjNum->SetInt(1);
	m_FieldObjNum->SetIntMin(1);
	m_FieldObjNum->SetIntMax(1);
	m_FieldObjNum->SetValueIntSpeed(0);

	m_LandScapeCountLine = AddWidget<CIMGUISameLine>("LandScapeCountLine");

	m_LandScapeSize = AddWidget<CIMGUITextInput>("LandScapeSize", 80.f, 20.f);
	m_LandScapeSize->SetHideName();
	m_LandScapeSize->SetTextType(ImGuiText_Type::Int);
	m_LandScapeSize->AddFlag(ImGuiInputTextFlags_CharsDecimal);
	m_LandScapeSize->SetIntMin(100);
	m_LandScapeSize->SetInt(120);
	m_LandScapeSize->SetIntStep(100);

	//

	m_CharacterTree = AddWidget<CIMGUITree>(UTF8("캐릭터 능력치"));

	Label = AddWidget<CIMGUILabel>(UTF8("최소 공격력"), 65.f, 20.f);
	Label->SetColor(69, 69, 138);
	Label->SetAlign(0.5f, 0.f);
	m_CharacterTree->AddWidget(Label);

	Line = AddWidget<CIMGUISameLine>("Line");
	m_CharacterTree->AddWidget(Line);

	m_AttMin = AddWidget<CIMGUITextInput>("AttMin", 50.f, 20.f);
	m_AttMin->SetHideName();
	m_AttMin->AddFlag(ImGuiInputTextFlags_CharsDecimal);
	m_AttMin->SetTextType(ImGuiText_Type::Float);
	m_CharacterTree->AddWidget(m_AttMin);

	Line = AddWidget<CIMGUISameLine>("Line");
	m_CharacterTree->AddWidget(Line);

	Label = AddWidget<CIMGUILabel>(UTF8("최대 공격력"), 65.f, 20.f);
	Label->SetColor(69, 69, 138);
	Label->SetAlign(0.5f, 0.f);
	m_CharacterTree->AddWidget(Label);

	Line = AddWidget<CIMGUISameLine>("Line");
	m_CharacterTree->AddWidget(Line);

	m_AttMax = AddWidget<CIMGUITextInput>("AttMax", 50.f, 20.f);
	m_AttMax->SetHideName();
	m_AttMax->AddFlag(ImGuiInputTextFlags_CharsDecimal);
	m_AttMax->SetTextType(ImGuiText_Type::Float);
	m_CharacterTree->AddWidget(m_AttMax);

	Label = AddWidget<CIMGUILabel>(UTF8("체력"), 65.f, 20.f);
	Label->SetColor(69, 69, 138);
	Label->SetAlign(0.5f, 0.f);
	m_CharacterTree->AddWidget(Label);

	Line = AddWidget<CIMGUISameLine>("Line");
	m_CharacterTree->AddWidget(Line);

	m_HP = AddWidget<CIMGUITextInput>("HP", 50.f, 20.f);
	m_HP->SetHideName();
	m_HP->AddFlag(ImGuiInputTextFlags_CharsDecimal);
	m_HP->SetTextType(ImGuiText_Type::Float);
	m_CharacterTree->AddWidget(m_HP);

	Line = AddWidget<CIMGUISameLine>("Line");
	m_CharacterTree->AddWidget(Line);

	Label = AddWidget<CIMGUILabel>(UTF8("스테미너"), 65.f, 20.f);
	Label->SetColor(69, 69, 138);
	Label->SetAlign(0.5f, 0.f);
	m_CharacterTree->AddWidget(Label);

	Line = AddWidget<CIMGUISameLine>("Line");
	m_CharacterTree->AddWidget(Line);

	m_Stamina = AddWidget<CIMGUITextInput>("Stamina", 50.f, 20.f);
	m_Stamina->SetHideName();
	m_Stamina->AddFlag(ImGuiInputTextFlags_CharsDecimal);
	m_Stamina->SetTextType(ImGuiText_Type::Float);
	m_CharacterTree->AddWidget(m_Stamina);

	Label = AddWidget<CIMGUILabel>(UTF8("이동속도"), 65.f, 20.f);
	Label->SetColor(69, 69, 138);
	Label->SetAlign(0.5f, 0.f);
	m_CharacterTree->AddWidget(Label);

	Line = AddWidget<CIMGUISameLine>("Line");
	m_CharacterTree->AddWidget(Line);

	m_Speed = AddWidget<CIMGUITextInput>("Speed", 50.f, 20.f);
	m_Speed->SetHideName();
	m_Speed->AddFlag(ImGuiInputTextFlags_CharsDecimal);
	m_Speed->SetTextType(ImGuiText_Type::Float);
	m_CharacterTree->AddWidget(m_Speed);

	//

	m_LandScapeTree = AddWidget<CIMGUITree>(UTF8("지형"));

	m_BrushModeCheckBox = AddWidget<CIMGUICheckBox>(UTF8("브러쉬 모드"), 120.f, 20.f);
	m_BrushModeCheckBox->CheckBox(&m_BrushMode);
	m_LandScapeTree->AddWidget(m_BrushModeCheckBox);

	m_BrushScaleText = AddWidget<CIMGUIText>("BrushScaleText", 40.f, 20.f);
	m_BrushScaleText->SetHideName();
	m_BrushScaleText->SetText("브러쉬 강도");
	m_LandScapeTree->AddWidget(m_BrushScaleText);

	m_BrushScaleLine = AddWidget<CIMGUISameLine>("Line");
	m_LandScapeTree->AddWidget(m_BrushScaleLine);

	m_BrushScale = AddWidget<CIMGUITextInput>("BrushScale", 90.f, 20.f);
	m_BrushScale->SetHideName();
	m_BrushScale->SetTextType(ImGuiText_Type::Int);
	m_BrushScale->AddFlag(ImGuiInputTextFlags_CharsDecimal);
	m_BrushScale->SetInt(10);
	m_BrushScale->SetIntMin(10);
	m_BrushScale->SetIntMax(100);
	m_BrushScale->SetValueIntSpeed(0);
	m_BrushScale->SetIntStep(10);
	m_BrushScale->SetCallback(this, &CObjectWindow::SetBrushScale);
	m_LandScapeTree->AddWidget(m_BrushScale);

	m_CircleBrushTypeRadio = AddWidget<CIMGUIRadio>(UTF8("원 모양"));
	m_CircleBrushTypeRadio->RadioButton(&m_BrushType, (int)Brush_Type::Circle);
	m_LandScapeTree->AddWidget(m_CircleBrushTypeRadio);

	m_RectBrushTypeRadio = AddWidget<CIMGUIRadio>(UTF8("사각형 모양"));
	m_RectBrushTypeRadio->RadioButton(&m_BrushType, (int)Brush_Type::Rect);
	m_LandScapeTree->AddWidget(m_RectBrushTypeRadio);

	m_HeightRadio = AddWidget<CIMGUIRadio>(UTF8("높낮이"));
	m_HeightRadio->RadioButton(&m_BrushEditType, (int)BrushEdit_Type::Height);
	m_LandScapeTree->AddWidget(m_HeightRadio);

	m_SplattingRadio = AddWidget<CIMGUIRadio>(UTF8("스플래팅"));
	m_SplattingRadio->RadioButton(&m_BrushEditType, (int)BrushEdit_Type::Splatting);
	m_LandScapeTree->AddWidget(m_SplattingRadio);

	m_TextureTypeComboBox = AddWidget<CIMGUIComboBox>(UTF8("텍스쳐 종류"), 126.f, 20.f);
	m_TextureTypeComboBox->SetHideName();

	m_TextureTypeComboBox->AddItem("잔디");
	m_TextureTypeComboBox->AddItem("모래");
	m_TextureTypeComboBox->AddItem("바위");
	m_LandScapeTree->AddWidget(m_TextureTypeComboBox);

	m_LandScapeTextureNum = AddWidget<CIMGUITextInput>("LandScapeTextureNum", 64.f, 20.f);
	m_LandScapeTextureNum->SetHideName();
	m_LandScapeTextureNum->SetTextType(ImGuiText_Type::Int);
	m_LandScapeTextureNum->AddFlag(ImGuiInputTextFlags_CharsDecimal);
	m_LandScapeTextureNum->SetInt(1);
	m_LandScapeTextureNum->SetIntMin(1);
	m_LandScapeTextureNum->SetIntMax(2);
	m_LandScapeTree->AddWidget(m_LandScapeTextureNum);

	SetWheelUpCallback(this, &CObjectWindow::WheelUp);
	SetWheelDownCallback(this, &CObjectWindow::WheelDown);

	return true;
}

void CObjectWindow::Update(float DeltaTime)
{
	CIMGUIWindow::Update(DeltaTime);

	HideCheckBoxUpdater(m_BrushMode, m_BrushScaleText);
	HideCheckBoxUpdater(m_BrushMode, m_BrushScaleLine);
	HideCheckBoxUpdater(m_BrushMode, m_BrushScale);
	HideCheckBoxUpdater(m_BrushMode, m_CircleBrushTypeRadio);
	HideCheckBoxUpdater(m_BrushMode, m_RectBrushTypeRadio);
	HideCheckBoxUpdater(m_BrushMode, m_HeightRadio);
	HideCheckBoxUpdater(m_BrushMode, m_HeightRadio);
	HideCheckBoxUpdater(m_BrushMode, m_SplattingRadio);
	HideRadioUpdater();
	HideGizmoUpdater();
	HideComboBoxUpdater();

	IntInputUpdater();
	LandScapeUpdater();

	if (IsKeyDown(VK_F3))
		CreateAuto();

	else if (IsKeyDown(VK_F4))
		DeleteButton();
}

void CObjectWindow::SetTarget(CGameObject* obj)
{
	if (!obj->CheckType<CLandScapeObj>())
		m_Gizmo->SetTarget(obj);
}

void CObjectWindow::ClearTarget()
{
	m_Gizmo->ClearTarget();
}

void CObjectWindow::SetBrushScale()
{
	float Scale = (float)m_BrushScale->GetValueInt();

	CLandScapeObj* LandScape = CEditorManager::GetInst()->GetLandScapeObj();

	if (LandScape)
	{
		switch ((BrushEdit_Type)m_BrushEditType)
		{
		case BrushEdit_Type::Height:
			LandScape->SetBrushHeightScale(Scale);
			break;
		case BrushEdit_Type::Splatting:
			LandScape->SetBrushSplattingScale(Scale);
			break;
		}
	}
}

void CObjectWindow::Refresh(Object_Type Type, const CharacterInfo& Info, CSharedPtr<class CGameObject> SelectObject)
{
	const char* TypeName = CEditorManager::GetInst()->GetHierarchyName(Type);

	RefreshCharacterInfo(Info, Type);
}

void CObjectWindow::CreateAuto()
{
	std::string SelectTypeName = m_TypeComboBox->GetSelectItem();

	if (SelectTypeName.length() == 0)
		return;

	Object_Type SelectType = CEditorManager::GetInst()->GetHierarchyType(SelectTypeName);

	CHierarchyWindow* HierarchyWindow = CEditorManager::GetInst()->GetHierarchyWindow();

	std::string	SelectScene = HierarchyWindow->GetSelectScene();

	if (SelectScene == "")
	{
		SelectScene = "Scene";

		int Num = 1;
		char NumText[64] = {};

		// 이름 끝에 숫자를 더해가며 하이어라키에서 존재하지 않을 경우 성공, 존재할경우 계속 루프.
		while (true)
		{
			SelectScene = "Scene";
			memset(NumText, 0, sizeof(char) * 64);
			sprintf_s(NumText, "%d", Num);

			SelectScene += NumText;

			if (!CEditorManager::GetInst()->GetSceneWindow()->HasSceneName(SelectScene))
				break;

			++Num;
		}

		CEditorManager::GetInst()->GetSceneWindow()->CreateScene(SelectScene);

		CEditorManager::GetInst()->GetHierarchyWindow()->SelectScene(SelectScene);
	}

	std::string	Name;
	bool	UseNumber = false;

	switch (SelectType)
	{
	case Object_Type::Player:
		Name = "Player";
		break;
	case Object_Type::Monster:
	{
		std::string TypeName = m_MonsterComboBox->GetSelectItem();
		Monster_Type MonType = CEditorManager::GetInst()->GetMonsterType(TypeName);

		Name = CEditorManager::GetInst()->GetMonsterNameEng(MonType);

		UseNumber = true;
	}
		break;
	case Object_Type::LandScape:
		Name = "LandScape";
		break;
	case Object_Type::FieldObj:
	{
		std::string TypeName = m_FieldObjComboBox->GetSelectItem();
		FieldObj_Type FieldType = CEditorManager::GetInst()->GetFieldObjType(TypeName);

		Name = CEditorManager::GetInst()->GetFieldObjNameEng(FieldType);

		UseNumber = true;
	}
		break;
	}

	int Num = 1;
	char NumText[64] = {};
	std::string resultName = Name;

	// 이름 끝에 숫자를 더해가며 하이어라키에서 존재하지 않을 경우 성공, 존재할경우 계속 루프.
	while (UseNumber)
	{
		resultName = Name;
		memset(NumText, 0, sizeof(char) * 64);
		sprintf_s(NumText, "%d", Num);

		resultName += NumText;

		if (!CEditorManager::GetInst()->GetHierarchyWindow()->HasObjectName(resultName))
			UseNumber = false;

		++Num;
	}

	CEditorScene* Scene = CEditorManager::GetInst()->GetEditorScene();

	CGameObject* NewObject = nullptr;

	if (SelectType == Object_Type::Player)
	{
		if (HierarchyWindow->FindType(SelectType)) // 플레이어는 2개 이상 생성되면 안된다.
			return;

		NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CPlayer>(resultName);
	}

	else if (SelectType == Object_Type::Monster)
	{
		Monster_Type SelectMonsterType = CEditorManager::GetInst()->GetMonsterType(m_MonsterComboBox->GetSelectItem());

		if (SelectMonsterType == Monster_Type::Max)
			return;

		switch (SelectMonsterType)
		{
		case Monster_Type::Barnos:
			NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CBarnos>(resultName);
			break;
		case Monster_Type::Jagras:
			NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CJagras>(resultName);
			break;
		case Monster_Type::Kestodon:
			NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CKestodon>(resultName);
			break;
		case Monster_Type::Vespoid:
			NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CVespoid>(resultName);
			break;
		case Monster_Type::Anjanath:
			NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CAnjanath>(resultName);
			break;
		case Monster_Type::Rathalos:
			NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CRathalos>(resultName);
			break;
		}
	}

	else if (SelectType == Object_Type::LandScape)
	{
		if (CSceneManager::GetInst()->GetScene()->FindObject<CLandScapeObj>())
			return;

		NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CLandScapeObj>(resultName);

		CLandScapeObj* LandScape = (CLandScapeObj*)NewObject;

		LandScape->SetBrushRange(3.f);
		LandScape->SetBrushColor(Vector3::Blue);

		int Size = m_LandScapeSize->GetValueInt();

		LandScape->SetCountX(Size);
		LandScape->SetCountZ(Size);
	}

	else if (SelectType == Object_Type::FieldObj)
	{
		FieldObj_Type SelectFieldObjType = CEditorManager::GetInst()->GetFieldObjType(m_FieldObjComboBox->GetSelectItem());

		if (SelectFieldObjType == FieldObj_Type::Max)
			return;

		int Index = m_FieldObjNum->GetValueInt();

		switch (SelectFieldObjType)
		{
		case FieldObj_Type::SlidingBox:
			NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CSlidingBox>(resultName);
			break;
		case FieldObj_Type::HealFlower:
			NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CHealFlower>(resultName);
			break;
		case FieldObj_Type::SmallTree:
			if (Index == 1)
				NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CSmallTree1>(resultName);
			else if (Index == 2)
				NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CSmallTree2>(resultName);
			else if (Index == 3)
				NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CSmallTree3>(resultName);
			else if (Index == 4)
				NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CSmallTree4>(resultName);
			else if (Index == 5)
				NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CSmallTree5>(resultName);
			break;
		case FieldObj_Type::Tree:
			if (Index == 1)
				NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CTree1>(resultName);
			else if (Index == 2)
				NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CTree2>(resultName);
			else if (Index == 3)
				NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CTree3>(resultName);
			else if (Index == 4)
				NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CTree4>(resultName);
			else if (Index == 5)
				NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CTree5>(resultName);
			else if (Index == 6)
				NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CTree6>(resultName);
			else if (Index == 7)
				NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CTree7>(resultName);
			else if (Index == 8)
				NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CTree8>(resultName);
			else if (Index == 9)
				NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CTree9>(resultName);
			break;
		case FieldObj_Type::BigTree:
			NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CBigTree>(resultName);
			break;
		case FieldObj_Type::BrokenTree:
			if (Index == 1)
				NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CBrokenTree1>(resultName);
			else if (Index == 2)
				NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CBrokenTree2>(resultName);
			else if (Index == 3)
				NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CBrokenTree3>(resultName);
			break;
		case FieldObj_Type::MushRoom:
			if (Index == 1)
				NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CMushRoom1>(resultName);
			else if (Index == 2)
				NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CMushRoom2>(resultName);
			else if (Index == 3)
				NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CMushRoom3>(resultName);
			break;
		case FieldObj_Type::SmallGrass:
			NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CSmallGrass>(resultName);
			break;
		case FieldObj_Type::Grass:
			if (Index == 1)
				NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CGrass1>(resultName);
			else if (Index == 2)
				NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CGrass2>(resultName);
			else if (Index == 3)
				NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CGrass3>(resultName);
			else if (Index == 4)
				NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CGrass4>(resultName);
			else if (Index == 5)
				NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CGrass5>(resultName);
			else if (Index == 6)
				NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CGrass6>(resultName);
			else if (Index == 7)
				NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CGrass7>(resultName);
			else if (Index == 8)
				NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CGrass8>(resultName);
			else if (Index == 9)
				NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CGrass9>(resultName);
			break;
		case FieldObj_Type::Vine:
			if (Index == 1)
				NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CVine>(resultName);
			else if (Index == 2)
				NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CVine2>(resultName);
			else if (Index == 3)
				NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CVine3>(resultName);
			else if (Index == 4)
				NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CVine4>(resultName);
			else if (Index == 5)
				NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CVine5>(resultName);
			break;
		case FieldObj_Type::Precipice:
			if (Index == 1)
				NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CPrecipice>(resultName);
			else if (Index == 2)
				NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CPrecipice2>(resultName);
			break;
		case FieldObj_Type::Sculpture:
			NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CSculpture>(resultName);
			break;
		case FieldObj_Type::SmallStone:
			NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CSmallStone1>(resultName);
			break;
		case FieldObj_Type::GrassRock:
			if (Index == 1)
				NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CGrassRock1>(resultName);
			else if (Index == 2)
				NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CGrassRock2>(resultName);
			else if (Index == 3)
				NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CGrassRock3>(resultName);
			else if (Index == 4)
				NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CGrassRock4>(resultName);
			else if (Index == 5)
				NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CGrassRock5>(resultName);
			else if (Index == 6)
				NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CGrassRock6>(resultName);
			else if (Index == 7)
				NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CGrassRock7>(resultName);
			else if (Index == 8)
				NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CGrassRock8>(resultName);
			else if (Index == 9)
				NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CGrassRock9>(resultName);
			break;
		case FieldObj_Type::Wreck:
			NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CWreck1>(resultName);
			break;
		case FieldObj_Type::Tent:
			if (Index == 1)
				NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CTent1>(resultName);
			else if (Index == 2)
				NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CTent2>(resultName);
			break;
		case FieldObj_Type::Box:
			NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CBox1>(resultName);
			break;
		case FieldObj_Type::Far:
			NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CFar>(resultName);
			break;
		case FieldObj_Type::Stone:
			if (Index == 1)
				NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CStonej1>(resultName);
			else if (Index == 2)
				NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CStonej2>(resultName);
			else if (Index == 3)
				NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CStonej3>(resultName);
			else if (Index == 4)
				NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CStonej4>(resultName);
			else if (Index == 5)
				NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CStonej5>(resultName);
			else if (Index == 6)
				NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CStonej6>(resultName);
			else if (Index == 7)
				NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CStonej7>(resultName);
			else if (Index == 8)
				NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CStonej8>(resultName);
			else if (Index == 9)
				NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CStonej9>(resultName);
			else if (Index == 10)
				NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CStonej10>(resultName);
			else if (Index == 11)
				NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CStonej11>(resultName);
			else if (Index == 12)
				NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CStonej12>(resultName);
			else if (Index == 13)
				NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CStonej13>(resultName);
			else if (Index == 14)
				NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CStonej14>(resultName);
			else if (Index == 15)
				NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CStonej15>(resultName);
			else if (Index == 16)
				NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CStonej16>(resultName);
			else if (Index == 17)
				NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CStonej17>(resultName);
			else if (Index == 18)
				NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CStonej18>(resultName);
			else if (Index == 19)
				NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CStonej19>(resultName);
			else if (Index == 20)
				NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CStonej20>(resultName);
			else if (Index == 21)
				NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CStonej21>(resultName);
			else if (Index == 22)
				NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CStonej22>(resultName);
			else if (Index == 23)
				NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CStonej23>(resultName);
			else if (Index == 24)
				NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CStonej24>(resultName);
			else if (Index == 25)
				NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CStonej25>(resultName);
			else if (Index == 26)
				NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CStonej26>(resultName);
			else if (Index == 27)
				NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CStonej27>(resultName);
			else if (Index == 28)
				NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CStonej28>(resultName);
			else if (Index == 29)
				NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CStonej29>(resultName);
			else if (Index == 30)
				NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CStonej30>(resultName);
			else if (Index == 31)
				NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CStonej31>(resultName);
			else if (Index == 32)
				NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CStonej32>(resultName);
			else if (Index == 33)
				NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CStonej33>(resultName);
			else if (Index == 34)
				NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CStonej34>(resultName);
			else if (Index == 35)
				NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CStonej35>(resultName);
			else if (Index == 36)
				NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CStonej36>(resultName);
			else if (Index == 37)
				NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CStonej37>(resultName);
			break;
		case FieldObj_Type::TownBarrel:
			NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CTownBarrel>(resultName);
			break;
		case FieldObj_Type::TownCarriage:
			NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CTownCarriage>(resultName);
			break;
		case FieldObj_Type::TownCheckPoint:
			NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CTownCheckPoint>(resultName);
			break;
		case FieldObj_Type::TownDragonHead:
			NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CTownDragonHead>(resultName);
			break;
		case FieldObj_Type::TownPassage:
			NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CTownPassage>(resultName);
			break;
		case FieldObj_Type::TownPumpkinMan:
			NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CTownPumpkinMan>(resultName);
			break;
		case FieldObj_Type::TownRampart:
			NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CTownRampart>(resultName);
			break;
		case FieldObj_Type::TownShadeScreen:
			NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CTownShadeScreen>(resultName);
			break;
		case FieldObj_Type::TownSign:
			NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CTownSign>(resultName);
			break;
		case FieldObj_Type::TownStructure:
			NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CTownStructure>(resultName);
			break;
		case FieldObj_Type::TownSummerHouse:
			NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CTownSummerHouse>(resultName);
			break;
		case FieldObj_Type::TownTunnel:
			NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CTownTunnel>(resultName);
			break;
		case FieldObj_Type::DesertPebble:
			NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CDesertPebble>(resultName);
			break;
		case FieldObj_Type::DesertSmallStone:
			NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CDesertSmallStone>(resultName);
			break;
		case FieldObj_Type::DesertStone:
			if (Index == 1)
				NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CDesertStone1>(resultName);
			else if (Index == 2)
				NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CDesertStone2>(resultName);
			else if (Index == 3)
				NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CDesertStone3>(resultName);
			else if (Index == 4)
				NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CDesertStone4>(resultName);
			else if (Index == 5)
				NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CDesertStone5>(resultName);
			else if (Index == 6)
				NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CDesertStone6>(resultName);
			break;
		case FieldObj_Type::DesertBigStone:
			NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CDesertBigStone>(resultName);
			break;
		case FieldObj_Type::DesertRockWall:
			NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CDesertRockWall>(resultName);
			break;
		case FieldObj_Type::DesertStalactite:
			if (Index == 1)
				NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CDesertStalactite1>(resultName);
			else if (Index == 2)
				NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CDesertStalactite2>(resultName);
			else if (Index == 3)
				NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CDesertStalactite3>(resultName);
			else if (Index == 4)
				NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CDesertStalactite4>(resultName);
			break;
		case FieldObj_Type::DesertStalagmite:
			if (Index == 1)
				NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CDesertStalagmite1>(resultName);
			else if (Index == 2)
				NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CDesertStalagmite2>(resultName);
			else if (Index == 3)
				NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CDesertStalagmite3>(resultName);
			break;
		case FieldObj_Type::DesertMountain:
			if (Index == 1)
				NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CDesertMountain1>(resultName);
			else if (Index == 2)
				NewObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CDesertMountain2>(resultName);
		}
	}

	if (NewObject)
	{
		Object_Info* Info = nullptr;

		if (SelectType == Object_Type::Player || SelectType == Object_Type::Monster)
		{
			CharacterInfo* CharInfo = DBG_NEW CharacterInfo;
			CharInfo->CharacterName = resultName;

			CharInfo->AttackMin = m_AttMin->GetValueFloat();
			CharInfo->AttackMax = m_AttMax->GetValueFloat();
			CharInfo->HP = m_HP->GetValueFloat();
			CharInfo->Stamina = m_Stamina->GetValueFloat();
			CharInfo->Speed = m_Speed->GetValueFloat();

			Info = HierarchyWindow->FindInfo(SelectType);

			if (SelectType == Object_Type::Player)
			{
				if (!Info)
				{
					HierarchyWindow->AddType(SelectType);

					Info = HierarchyWindow->FindInfo(SelectType);
				}
			}

			else if (SelectType == Object_Type::Monster)
				Info = HierarchyWindow->FindMonsterInfo(CEditorManager::GetInst()->GetMonsterType(m_MonsterComboBox->GetSelectItem()));

			Info->CharacterInfoList.push_back(CharInfo);
		}

		else if (SelectType == Object_Type::FieldObj)
		{
			int Index = m_FieldObjNum->GetValueInt();

			Info = HierarchyWindow->FindFieldObjInfo(CEditorManager::GetInst()->GetFieldObjType(m_FieldObjComboBox->GetSelectItem()), Index);

			CEditorManager::GetInst()->GetHierarchyWindow()->SetFieldObjNum(Index, Info->FieldObjType);
		}

		int DetailType = 0;
		int Index = 0;

		switch (SelectType)
		{
		case Object_Type::Monster:
			DetailType = (int)Info->MonsterType;
			Index = Info->FieldObjNum;
			break;
		case Object_Type::FieldObj:
			DetailType = (int)Info->FieldObjType;
			Index = Info->FieldObjNum;
			break;
		}

		HierarchyWindow->AddObject(SelectScene, SelectType, DetailType, Index, NewObject);

		if (SelectType != Object_Type::LandScape)
		{
			CLandScapeObj* LandScape = CEditorManager::GetInst()->GetLandScapeObj();

			if (!LandScape)
			{
				Vector3	CamPos = CEditorManager::GetInst()->GetCameraFrontPos(85.f);

				CamPos.y = CamPos.y - 15.f < 20.f ? 20.f : CamPos.y - 15.f;

				NewObject->SetWorldPos(CamPos.x, CamPos.y, CamPos.z);
			}

			else
				NewObject->SetWorldPos(LandScape->GetDDTPos());
		}
	}
}

void CObjectWindow::DeleteButton()
{
	CHierarchyWindow* Hierarchy = CEditorManager::GetInst()->GetHierarchyWindow();

	Hierarchy->DeleteSelectObject();

	m_Gizmo->ClearTarget();
}

void CObjectWindow::ModifyButton()
{
	CHierarchyWindow* Hierarchy = CEditorManager::GetInst()->GetHierarchyWindow();

	if (!Hierarchy->IsSelectType() || !Hierarchy->IsSelectObject())
		return;

	CGameObject* SelectObject = Hierarchy->GetSelectObject();

	if (!SelectObject)
		ASSERT("if (!SelectObject)");
	
	Object_Info* SelectInfo = Hierarchy->GetSelectInfo();

	if (!SelectInfo)
		return;

	std::string	Name = SelectObject->GetName();

	if (SelectInfo->Type == Object_Type::Player ||
		SelectInfo->Type == Object_Type::Monster)
	{
		CharacterInfo* CharInfo = SelectInfo->FindCharacterInfo(Name);

		if (CharInfo)
		{
			CharInfo->CharacterName = Name;
			CharInfo->AttackMin = m_AttMin->GetValueFloat();
			CharInfo->AttackMax = m_AttMax->GetValueFloat();
			CharInfo->HP = m_HP->GetValueFloat();
			CharInfo->Stamina = m_Stamina->GetValueFloat();
			CharInfo->Speed = m_Speed->GetValueFloat();

			RefreshCharacterInfo(*CharInfo, SelectInfo->Type);
		}
	}

	Hierarchy->RefreshObject();

	Hierarchy->SelectObject(Name);
}

void CObjectWindow::NavButton()
{
	CLandScapeObj* LandScape = CEditorManager::GetInst()->GetLandScapeObj();

	if (LandScape)
		LandScape->SetNavData();
}

void CObjectWindow::Reset()
{
	m_AttMin->SetFloat(0.f);
	m_AttMax->SetFloat(0.f);
	m_HP->SetFloat(0.f);
	m_Stamina->SetFloat(0.f);
	m_Speed->SetFloat(0.f);

	CLandScapeObj* LandScape = CEditorManager::GetInst()->GetLandScapeObj();

	if (LandScape)
	{
		if (!m_BrushMode)
		{
			LandScape->SetBrushRange(3.f);
			LandScape->SetBrushColor(Vector3::Blue);
		}
	}
}

void CObjectWindow::HideComboBoxUpdater()
{
	int Index = m_TypeComboBox->GetSelectIndex();

	if (Index == (int)Object_Type::Monster)
	{
		m_MonsterTypeLine->Enable();
		m_MonsterComboBox->Enable();
		m_FieldTypeLine->Disable();
		m_FieldObjComboBox->Disable();
		m_FieldObjNum->Disable();
		m_FieldObjComboBox->Disable();
		m_LandScapeCountLine->Disable();
		m_LandScapeSize->Disable();
	}

	else if (Index == (int)Object_Type::FieldObj)
	{
		m_MonsterTypeLine->Disable();
		m_MonsterComboBox->Disable();
		m_FieldTypeLine->Enable();
		m_FieldObjComboBox->Enable();
		m_FieldObjNum->Enable();
		m_LandScapeCountLine->Disable();
		m_LandScapeSize->Disable();
	}

	else if (Index == (int)Object_Type::LandScape)
	{
		m_MonsterTypeLine->Disable();
		m_MonsterComboBox->Disable();
		m_FieldTypeLine->Disable();
		m_FieldObjComboBox->Disable();
		m_FieldObjNum->Disable();
		m_LandScapeCountLine->Enable();
		m_LandScapeSize->Enable();
	}

	else
	{
		m_MonsterTypeLine->Disable();
		m_MonsterComboBox->Disable();
		m_FieldTypeLine->Disable();
		m_FieldObjComboBox->Disable();
		m_FieldObjNum->Disable();
		m_LandScapeCountLine->Disable();
		m_LandScapeSize->Disable();
	}

}

void CObjectWindow::HideCheckBoxUpdater(const bool& IsCheck, CIMGUIWidget* HideWidget)
{
	if (IsCheck)
	{
		if (HideWidget->IsDisable())
			HideWidget->Enable();
	}

	else
	{
		if (HideWidget->IsEnable())
			HideWidget->Disable();
	}
}

void CObjectWindow::HideRadioUpdater()
{
	if (m_BrushMode)
	{
		if (m_BrushEditType == (int)BrushEdit_Type::Splatting)
		{
			m_TextureTypeComboBox->Enable();

			int TextureIndex = m_TextureTypeComboBox->GetSelectIndex();

			if (TextureIndex == (int)LandScape_TextureType::Grass || TextureIndex == (int)LandScape_TextureType::Sand || TextureIndex == (int)LandScape_TextureType::Rock)
				m_LandScapeTextureNum->Enable();

			return;
		}
	}

	m_TextureTypeComboBox->Disable();
	m_LandScapeTextureNum->Disable();
}

void CObjectWindow::HideGizmoUpdater()
{
	if (!m_BrushMode)
		m_Gizmo->Enable();

	else
		m_Gizmo->Disable();
}

void CObjectWindow::WheelUp(float DeltaTime)
{
	CEditorManager::GetInst()->GetEditorScene()->WheelUp(DeltaTime);
}

void CObjectWindow::WheelDown(float DeltaTime)
{
	CEditorManager::GetInst()->GetEditorScene()->WheelDown(DeltaTime);
}

void CObjectWindow::LandScapeUpdater()
{
	CLandScapeObj* LandScape = CEditorManager::GetInst()->GetLandScapeObj();

	if (LandScape)
	{
		bool PrevBrushMode = CEditorManager::GetInst()->GetEditorScene()->IsUseBrushMode();
		CEditorScene* Scene = CEditorManager::GetInst()->GetEditorScene();

		if (m_BrushMode)
		{
			LandScape->SelectMap(GetSelectTextureIndex());

			if (!PrevBrushMode)
			{
				LandScape->SetBrushColor(Vector3::Green);
				LandScape->SetBrushRange(Scene->GetBrushRange());
			}
		}

		else if (!m_BrushMode && PrevBrushMode)
		{
			LandScape->SetBrushRange(3.f);
			LandScape->SetBrushColor(Vector3::Blue);

			NavButton();
		}

		Scene->UseBrushMode(m_BrushMode);
	}
}

void CObjectWindow::IntInputUpdater()
{
	if (m_FieldObjComboBox->IsEnable())
	{
		if (m_FieldObjComboBox->GetSelectIndex() == (int)FieldObj_Type::SmallTree)
			m_FieldObjNum->SetIntMax(5);

		else if (m_FieldObjComboBox->GetSelectIndex() == (int)FieldObj_Type::Tree)
			m_FieldObjNum->SetIntMax(9);

		else if (m_FieldObjComboBox->GetSelectIndex() == (int)FieldObj_Type::BrokenTree)
			m_FieldObjNum->SetIntMax(3);

		else if (m_FieldObjComboBox->GetSelectIndex() == (int)FieldObj_Type::MushRoom)
			m_FieldObjNum->SetIntMax(3);

		else if (m_FieldObjComboBox->GetSelectIndex() == (int)FieldObj_Type::Grass)
			m_FieldObjNum->SetIntMax(9);

		else if (m_FieldObjComboBox->GetSelectIndex() == (int)FieldObj_Type::Vine)
			m_FieldObjNum->SetIntMax(5);

		else if (m_FieldObjComboBox->GetSelectIndex() == (int)FieldObj_Type::Precipice)
			m_FieldObjNum->SetIntMax(2);

		else if (m_FieldObjComboBox->GetSelectIndex() == (int)FieldObj_Type::DesertStone)
			m_FieldObjNum->SetIntMax(6);

		else if (m_FieldObjComboBox->GetSelectIndex() == (int)FieldObj_Type::DesertStalactite)
			m_FieldObjNum->SetIntMax(4);

		else if (m_FieldObjComboBox->GetSelectIndex() == (int)FieldObj_Type::DesertStalagmite)
			m_FieldObjNum->SetIntMax(3);

		else if (m_FieldObjComboBox->GetSelectIndex() == (int)FieldObj_Type::GrassRock)
			m_FieldObjNum->SetIntMax(9);

		else if (m_FieldObjComboBox->GetSelectIndex() == (int)FieldObj_Type::Tent)
			m_FieldObjNum->SetIntMax(2);

		else if (m_FieldObjComboBox->GetSelectIndex() == (int)FieldObj_Type::Stone)
			m_FieldObjNum->SetIntMax(37);

		else if (m_FieldObjComboBox->GetSelectIndex() == (int)FieldObj_Type::DesertMountain)
			m_FieldObjNum->SetIntMax(2);

		else
			m_FieldObjNum->SetIntMax(1);
	}

	if (m_TextureTypeComboBox->IsEnable())
	{
		if (m_TextureTypeComboBox->GetSelectIndex() == (int)LandScape_TextureType::Grass)
			m_LandScapeTextureNum->SetIntMax(4);

		else if (m_TextureTypeComboBox->GetSelectIndex() == (int)LandScape_TextureType::Sand)
			m_LandScapeTextureNum->SetIntMax(5);

		else if (m_TextureTypeComboBox->GetSelectIndex() == (int)LandScape_TextureType::Rock)
			m_LandScapeTextureNum->SetIntMax(3);

		else
			m_LandScapeTextureNum->SetIntMax(1);
	}
}

int CObjectWindow::GetSelectTextureIndex()
{
	int Index = -1;
	int TextureNum = m_LandScapeTextureNum->GetValueInt() - 1; // 1부터 시작이기 때문에 -1 해준다

	if (m_TextureTypeComboBox->GetSelectIndex() == (int)LandScape_TextureType::Grass)
		Index = TextureNum;

	else if (m_TextureTypeComboBox->GetSelectIndex() == (int)LandScape_TextureType::Sand)
		Index = TextureNum + 4; // Grass 텍스쳐 개수 4

	else if (m_TextureTypeComboBox->GetSelectIndex() == (int)LandScape_TextureType::Rock)
		Index = TextureNum + 9; // Grass + Sand 텍스쳐 개수 9

	return Index;
}

void CObjectWindow::RefreshCharacterInfo(const CharacterInfo& Info, Object_Type Type)
{
	if (Type == Object_Type::Player ||
		Type == Object_Type::Monster)
	{
		m_AttMin->SetFloat(Info.AttackMin);
		m_AttMax->SetFloat(Info.AttackMax);
		m_HP->SetFloat(Info.HP);
		m_Stamina->SetFloat(Info.Stamina);
		m_Speed->SetFloat(Info.Speed);
	}
}

void CObjectWindow::RefreshFieldObjIndex(int Index, const char* Item)
{
	m_FieldObjNum->SetInt(1);
}
