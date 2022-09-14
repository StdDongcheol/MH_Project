#include "EditorManager.h"
#include "Engine.h"
#include "resource.h"
#include "IMGUIManager.h"
#include "Input.h"
#include "Window/HierarchyWindow.h"
#include "Window/ObjectWindow.h"
#include "Window/SceneWindow.h"
#include "Window/AboutWindow.h"
#include "Window/InfoWindow.h"
#include "Scene/SceneManager.h"
#include "Scene/EditorScene.h"
#include "Scene/SceneResource.h"
#include "Object/Player/Player.h"
#include "Object/LandScape/LandScapeObj.h"
#include "Object/Monster/Barnos.h"
#include "Object/Monster/Jagras.h"
#include "Object/Monster/Kestodon.h"
#include "Object/Monster/Vespoid.h"
#include "Object/Monster/Anjanath.h"
#include "Object/Monster/Rathalos.h"
#include "Object/FieldObj/SlidingBox.h"
#include "Object/FieldObj/HealFlower.h"
#include "Object/FieldObj/SmallTree1.h"
#include "Object/FieldObj/SmallTree2.h"
#include "Object/FieldObj/SmallTree3.h"
#include "Object/FieldObj/SmallTree4.h"
#include "Object/FieldObj/SmallTree5.h"
#include "Object/FieldObj/Tree1.h"
#include "Object/FieldObj/Tree2.h"
#include "Object/FieldObj/Tree3.h"
#include "Object/FieldObj/Tree4.h"
#include "Object/FieldObj/Tree5.h"
#include "Object/FieldObj/Tree6.h"
#include "Object/FieldObj/Tree7.h"
#include "Object/FieldObj/Tree8.h"
#include "Object/FieldObj/Tree9.h"
#include "Object/FieldObj/BigTree.h"
#include "Object/FieldObj/BrokenTree1.h"
#include "Object/FieldObj/BrokenTree2.h"
#include "Object/FieldObj/BrokenTree3.h"
#include "Object/FieldObj/MushRoom1.h"
#include "Object/FieldObj/MushRoom2.h"
#include "Object/FieldObj/MushRoom3.h"
#include "Object/FieldObj/Grass1.h"
#include "Object/FieldObj/Grass2.h"
#include "Object/FieldObj/Grass3.h"
#include "Object/FieldObj/Grass4.h"
#include "Object/FieldObj/Grass5.h"
#include "Object/FieldObj/Grass6.h"
#include "Object/FieldObj/Grass7.h"
#include "Object/FieldObj/Grass8.h"
#include "Object/FieldObj/Grass9.h"
#include "Object/FieldObj/SmallGrass.h"
#include "Object/FieldObj/Vine.h"
#include "Object/FieldObj/Vine2.h"
#include "Object/FieldObj/Vine3.h"
#include "Object/FieldObj/Vine4.h"
#include "Object/FieldObj/Vine5.h"
#include "Object/FieldObj/Precipice.h"
#include "Object/FieldObj/Precipice2.h"
#include "Object/FieldObj/Sculpture.h"
#include "Object/FieldObj/SmallStone1.h"
#include "Object/FieldObj/GrassRock1.h"
#include "Object/FieldObj/GrassRock2.h"
#include "Object/FieldObj/GrassRock3.h"
#include "Object/FieldObj/GrassRock4.h"
#include "Object/FieldObj/GrassRock5.h"
#include "Object/FieldObj/GrassRock6.h"
#include "Object/FieldObj/GrassRock7.h"
#include "Object/FieldObj/GrassRock8.h"
#include "Object/FieldObj/GrassRock9.h"
#include "Object/FieldObj/Wreck1.h"
#include "Object/FieldObj/Tent1.h"
#include "Object/FieldObj/Tent2.h"
#include "Object/FieldObj/Box1.h"
#include "Object/FieldObj/Far.h"
#include "Object/FieldObj/DesertPebble.h"
#include "Object/FieldObj/DesertSmallStone.h"
#include "Object/FieldObj/DesertStone1.h"
#include "Object/FieldObj/DesertStone2.h"
#include "Object/FieldObj/DesertStone3.h"
#include "Object/FieldObj/DesertStone4.h"
#include "Object/FieldObj/DesertStone5.h"
#include "Object/FieldObj/DesertStone6.h"
#include "Object/FieldObj/DesertBigStone.h"
#include "Object/FieldObj/DesertRockWall.h"
#include "Object/FieldObj/DesertStalactite1.h"
#include "Object/FieldObj/DesertStalactite2.h"
#include "Object/FieldObj/DesertStalactite3.h"
#include "Object/FieldObj/DesertStalactite4.h"
#include "Object/FieldObj/DesertStalagmite1.h"
#include "Object/FieldObj/DesertStalagmite2.h"
#include "Object/FieldObj/DesertStalagmite3.h"
#include "Object/FieldObj/Stonej1.h"
#include "Object/FieldObj/Stonej2.h"
#include "Object/FieldObj/Stonej3.h"
#include "Object/FieldObj/Stonej4.h"
#include "Object/FieldObj/Stonej5.h"
#include "Object/FieldObj/Stonej6.h"
#include "Object/FieldObj/Stonej7.h"
#include "Object/FieldObj/Stonej8.h"
#include "Object/FieldObj/Stonej9.h"
#include "Object/FieldObj/Stonej10.h"
#include "Object/FieldObj/Stonej11.h"
#include "Object/FieldObj/Stonej12.h"
#include "Object/FieldObj/Stonej13.h"
#include "Object/FieldObj/Stonej14.h"
#include "Object/FieldObj/Stonej15.h"
#include "Object/FieldObj/Stonej16.h"
#include "Object/FieldObj/Stonej17.h"
#include "Object/FieldObj/Stonej18.h"
#include "Object/FieldObj/Stonej19.h"
#include "Object/FieldObj/Stonej20.h"
#include "Object/FieldObj/Stonej21.h"
#include "Object/FieldObj/Stonej22.h"
#include "Object/FieldObj/Stonej23.h"
#include "Object/FieldObj/Stonej24.h"
#include "Object/FieldObj/Stonej25.h"
#include "Object/FieldObj/Stonej26.h"
#include "Object/FieldObj/Stonej27.h"
#include "Object/FieldObj/Stonej28.h"
#include "Object/FieldObj/Stonej29.h"
#include "Object/FieldObj/Stonej30.h"
#include "Object/FieldObj/Stonej31.h"
#include "Object/FieldObj/Stonej32.h"
#include "Object/FieldObj/Stonej33.h"
#include "Object/FieldObj/Stonej34.h"
#include "Object/FieldObj/Stonej35.h"
#include "Object/FieldObj/Stonej36.h"
#include "Object/FieldObj/Stonej37.h"
#include "Object/FieldObj/SlidingBox.h"
#include "Object/FieldObj/TownBarrel.h"
#include "Object/FieldObj/TownCarriage.h"
#include "Object/FieldObj/TownCheckPoint.h"
#include "Object/FieldObj/TownDragonHead.h"
#include "Object/FieldObj/TownPassage.h"
#include "Object/FieldObj/TownPumpkinMan.h"
#include "Object/FieldObj/TownRampart.h"
#include "Object/FieldObj/TownShadeScreen.h"
#include "Object/FieldObj/TownSign.h"
#include "Object/FieldObj/TownStructure.h"
#include "Object/FieldObj/TownSummerHouse.h"
#include "Object/FieldObj/TownTunnel.h"
#include "Object/FieldObj/DesertMountain1.h"
#include "Object/FieldObj/DesertMountain2.h"
#include "Component/Arm.h"
#include "Component/AnimationMeshComponent.h"
#include "Component/SpriteComponent.h"
#include "Component/LandScape.h"
#include "Component/CameraComponent.h"
#include "Component/ColliderSphere.h"
#include "Component/ColliderBox3D.h"

DEFINITION_SINGLE(CEditorManager)

CEditorManager::CEditorManager()	:
	m_HierarchyWindow(nullptr),
	m_ObjectWindow(nullptr),
	m_SceneWindow(nullptr),
	m_AboutWindow(nullptr),
	m_InfoWindow(nullptr)
{
}

CEditorManager::~CEditorManager()
{
	CEngine::DestroyInst();
}

bool CEditorManager::Init(HINSTANCE hInst)
{
	CEngine::GetInst()->EnableEditorMode();

	TCHAR	Title[64] = {};

#ifdef _DEBUG
	lstrcpy(Title, TEXT("[디버그] 몬스터 헌터 월드 - 에디터 모드"));
#else
	lstrcpy(Title, TEXT("몬스터 헌터 월드 - 에디터 모드"));
#endif // _DEBUG

	if (!CEngine::GetInst()->Init(hInst, Title, 1280, 720, IDI_ICON1))
	{
		CEngine::DestroyInst();
		return false;
	}

	wchar_t		m_wText[1024] = {};
	char		m_TextUTF8[1024] = {};

	m_HierarchyWindow = CIMGUIManager::GetInst()->AddWindow<CHierarchyWindow>(UTF8("하이어라키"));
	m_ObjectWindow = CIMGUIManager::GetInst()->AddWindow<CObjectWindow>(UTF8("오브젝트 및 컴퍼넌트"));
	m_SceneWindow = CIMGUIManager::GetInst()->AddWindow<CSceneWindow>(UTF8("장면"));
	m_AboutWindow = CIMGUIManager::GetInst()->AddWindow<CAboutWindow>(UTF8("사용방법"));
	m_InfoWindow = CIMGUIManager::GetInst()->AddWindow<CInfoWindow>(UTF8("정보"));

	CInput::GetInst()->CreateKey("Front", 'W');
	CInput::GetInst()->CreateKey("Back", 'S');
	CInput::GetInst()->CreateKey("Left", 'A');
	CInput::GetInst()->CreateKey("Right", 'D');
	CInput::GetInst()->CreateKey("Up", 'Q');
	CInput::GetInst()->CreateKey("Down", 'E');
	CInput::GetInst()->CreateKey("ESC", VK_ESCAPE);
	CInput::GetInst()->CreateKey("LClick", VK_LBUTTON);
	CInput::GetInst()->CreateKey("RClick", VK_RBUTTON);
	CInput::GetInst()->CreateKey("Space", VK_SPACE);

	CSceneManager::GetInst()->SetCreateSceneModeFunction<CEditorManager>(this, &CEditorManager::CreateSceneMode);
	CSceneManager::GetInst()->SetCreateObjectFunction<CEditorManager>(this, &CEditorManager::CreateObject);
	CSceneManager::GetInst()->SetCreateComponentFunction<CEditorManager>(this, &CEditorManager::CreateComponent);

	CResourceManager::GetInst()->CreateSoundChannelGroup("BGM");
	CResourceManager::GetInst()->LoadSound("BGM", true, "EditorBGM", "Editor.flac");
	CResourceManager::GetInst()->SetVolume("BGM", 30);

	return true;
}

void CEditorManager::CreateDefaultSceneMode()
{
	CSceneManager::GetInst()->CreateSceneMode<CEditorScene>();
}

int CEditorManager::Run()
{
	return CEngine::GetInst()->Run();
}

void CEditorManager::CamToggle()
{
	GetEditorScene()->CamToggle();
}

Vector3 CEditorManager::GetCameraPos() const
{
	return GetEditorScene()->GetCameraPos();
}

Vector3 CEditorManager::GetCameraFrontPos(float Dist) const
{
	return GetEditorScene()->GetCameraFrontPos(Dist);
}

int CEditorManager::GetBrushType() const
{
	return m_ObjectWindow->GetBrushType();
}

CLandScapeObj* CEditorManager::GetLandScapeObj() const
{
	CGameObject* FindObj = CSceneManager::GetInst()->GetScene()->FindObject<CLandScapeObj>();
	CLandScapeObj* LandScape = dynamic_cast<CLandScapeObj*>(FindObj);

	return LandScape;
}

void CEditorManager::SetInfo(const std::string& SceneName)
{
	m_HierarchyWindow->SetInfo(m_SceneWindow->FindInfo(SceneName));
}

void CEditorManager::CreateSceneMode(CScene* Scene, size_t Type)
{
}

CGameObject* CEditorManager::CreateObject(CScene* Scene, size_t Type)
{
	CGameObject* Obj = nullptr;

	Obj = CreateCharacter(Scene, Type);

	if (Obj)
		return Obj;

	Obj = CreateObj1(Scene, Type);

	if (Obj)
		return Obj;

	Obj = CreateObj2(Scene, Type);

	return Obj;
}

CComponent* CEditorManager::CreateComponent(CGameObject* Obj, size_t Type)
{
	if (Type == typeid(CSceneComponent).hash_code())
	{
		CSceneComponent* Root = Obj->GetRootComponent();

		CComponent* Component = Obj->LoadComponent<CSceneComponent>();

		if (Root)
			Root->AddChild((CSceneComponent*)Component);

		return Component;
	}

	else if (Type == typeid(CSpriteComponent).hash_code())
	{
		CSceneComponent* Root = Obj->GetRootComponent();

		CComponent* Component = Obj->LoadComponent<CSpriteComponent>();

		if (Root)
			Root->AddChild((CSceneComponent*)Component);

		return Component;
	}

	else if (Type == typeid(CStaticMeshComponent).hash_code())
	{
		CSceneComponent* Root = Obj->GetRootComponent();

		CComponent* Component = Obj->LoadComponent<CStaticMeshComponent>();

		if (Root)
			Root->AddChild((CSceneComponent*)Component);

		return Component;
	}

	else if (Type == typeid(CArm).hash_code())
	{
		CSceneComponent* Root = Obj->GetRootComponent();

		CArm* Component = Obj->LoadComponent<CArm>();

		if (Root)
			Root->AddChild((CSceneComponent*)Component);

		return Component;
	}

	else if (Type == typeid(CAnimationMeshComponent).hash_code())
	{
		CSceneComponent* Root = Obj->GetRootComponent();

		CAnimationMeshComponent* Component = Obj->LoadComponent<CAnimationMeshComponent>();

		if (Root)
			Root->AddChild((CSceneComponent*)Component);

		return Component;
	}

	else if (Type == typeid(CLandScape).hash_code())
	{
		CSceneComponent* Root = Obj->GetRootComponent();

		CLandScape* Component = Obj->LoadComponent<CLandScape>();

		if (Root)
			Root->AddChild((CSceneComponent*)Component);

		return Component;
	}

	else if (Type == typeid(CCameraComponent).hash_code())
	{
		CSceneComponent* Root = Obj->GetRootComponent();

		CCameraComponent* Component = Obj->LoadComponent<CCameraComponent>();

		if (Root)
			Root->AddChild((CSceneComponent*)Component);

		return Component;
	}

	else if (Type == typeid(CColliderSphere).hash_code())
	{
		CSceneComponent* Root = Obj->GetRootComponent();

		CColliderSphere* Component = Obj->LoadComponent<CColliderSphere>();

		if (Root)
			Root->AddChild((CSceneComponent*)Component);

		return Component;
	}

	else if (Type == typeid(CColliderBox3D).hash_code())
	{
		CSceneComponent* Root = Obj->GetRootComponent();

		CColliderBox3D* Component = Obj->LoadComponent<CColliderBox3D>();

		if (Root)
			Root->AddChild((CSceneComponent*)Component);

		return Component;
	}

	return nullptr;
}

CGameObject* CEditorManager::CreateCharacter(CScene* Scene, size_t Type)
{
	if (Type == typeid(CGameObject).hash_code())
	{
		CGameObject* Obj = Scene->LoadGameObject<CGameObject>();

		return Obj;
	}

	else if (Type == typeid(CPlayer).hash_code())
	{
		CPlayer* Obj = Scene->LoadGameObject<CPlayer>();

		return Obj;
	}

	else if (Type == typeid(CLandScapeObj).hash_code())
	{
		CLandScapeObj* Obj = Scene->LoadGameObject<CLandScapeObj>();

		return Obj;
	}

	else if (Type == typeid(CBarnos).hash_code())
	{
		CBarnos* Obj = Scene->LoadGameObject<CBarnos>();

		return Obj;
	}

	else if (Type == typeid(CJagras).hash_code())
	{
		CJagras* Obj = Scene->LoadGameObject<CJagras>();

		return Obj;
	}

	else if (Type == typeid(CKestodon).hash_code())
	{
		CKestodon* Obj = Scene->LoadGameObject<CKestodon>();

		return Obj;
	}

	else if (Type == typeid(CVespoid).hash_code())
	{
		CVespoid* Obj = Scene->LoadGameObject<CVespoid>();

		return Obj;
	}

	else if (Type == typeid(CAnjanath).hash_code())
	{
		CAnjanath* Obj = Scene->LoadGameObject<CAnjanath>();

		return Obj;
	}

	else if (Type == typeid(CRathalos).hash_code())
	{
		CRathalos* Obj = Scene->LoadGameObject<CRathalos>();

		return Obj;
	}

	return nullptr;
}

CGameObject* CEditorManager::CreateObj1(CScene* Scene, size_t Type)
{
	CGameObject* Obj = nullptr;

	if (Type == typeid(CSlidingBox).hash_code())
	{
		CSlidingBox* Obj = Scene->LoadGameObject<CSlidingBox>();

		return Obj;
	}

	else if (Type == typeid(CHealFlower).hash_code())
	{
		CHealFlower* Obj = Scene->LoadGameObject<CHealFlower>();

		return Obj;
	}

	else if (Type == typeid(CSmallTree1).hash_code())
	{
		CSmallTree1* Obj = Scene->LoadGameObject<CSmallTree1>();

		return Obj;
	}

	else if (Type == typeid(CSmallTree2).hash_code())
	{
		CSmallTree2* Obj = Scene->LoadGameObject<CSmallTree2>();

		return Obj;
	}

	else if (Type == typeid(CSmallTree3).hash_code())
	{
		CSmallTree3* Obj = Scene->LoadGameObject<CSmallTree3>();

		return Obj;
	}

	else if (Type == typeid(CSmallTree4).hash_code())
	{
		CSmallTree4* Obj = Scene->LoadGameObject<CSmallTree4>();

		return Obj;
	}

	else if (Type == typeid(CSmallTree5).hash_code())
	{
		CSmallTree5* Obj = Scene->LoadGameObject<CSmallTree5>();

		return Obj;
	}

	else if (Type == typeid(CTree1).hash_code())
	{
		CTree1* Obj = Scene->LoadGameObject<CTree1>();

		return Obj;
	}

	else if (Type == typeid(CTree2).hash_code())
	{
		CTree2* Obj = Scene->LoadGameObject<CTree2>();

		return Obj;
	}

	else if (Type == typeid(CTree3).hash_code())
	{
		CTree3* Obj = Scene->LoadGameObject<CTree3>();

		return Obj;
	}

	else if (Type == typeid(CTree4).hash_code())
	{
		CTree4* Obj = Scene->LoadGameObject<CTree4>();

		return Obj;
	}

	else if (Type == typeid(CTree5).hash_code())
	{
		CTree5* Obj = Scene->LoadGameObject<CTree5>();

		return Obj;
	}

	else if (Type == typeid(CTree6).hash_code())
	{
		CTree6* Obj = Scene->LoadGameObject<CTree6>();

		return Obj;
	}

	else if (Type == typeid(CTree7).hash_code())
	{
		CTree7* Obj = Scene->LoadGameObject<CTree7>();

		return Obj;
	}

	else if (Type == typeid(CTree8).hash_code())
	{
		CTree8* Obj = Scene->LoadGameObject<CTree8>();

		return Obj;
	}

	else if (Type == typeid(CTree9).hash_code())
	{
		CTree9* Obj = Scene->LoadGameObject<CTree9>();

		return Obj;
	}

	else if (Type == typeid(CBigTree).hash_code())
	{
		CBigTree* Obj = Scene->LoadGameObject<CBigTree>();

		return Obj;
	}

	else if (Type == typeid(CBrokenTree1).hash_code())
	{
		CBrokenTree1* Obj = Scene->LoadGameObject<CBrokenTree1>();

		return Obj;
	}

	else if (Type == typeid(CBrokenTree2).hash_code())
	{
		CBrokenTree2* Obj = Scene->LoadGameObject<CBrokenTree2>();

		return Obj;
	}

	else if (Type == typeid(CBrokenTree3).hash_code())
	{
		CBrokenTree3* Obj = Scene->LoadGameObject<CBrokenTree3>();

		return Obj;
	}

	else if (Type == typeid(CMushRoom1).hash_code())
	{
		CMushRoom1* Obj = Scene->LoadGameObject<CMushRoom1>();

		return Obj;
	}

	else if (Type == typeid(CMushRoom2).hash_code())
	{
		CMushRoom2* Obj = Scene->LoadGameObject<CMushRoom2>();

		return Obj;
	}

	else if (Type == typeid(CMushRoom3).hash_code())
	{
		CMushRoom3* Obj = Scene->LoadGameObject<CMushRoom3>();

		return Obj;
	}

	else if (Type == typeid(CGrass1).hash_code())
	{
		CGrass1* Obj = Scene->LoadGameObject<CGrass1>();

		return Obj;
	}

	else if (Type == typeid(CGrass2).hash_code())
	{
		CGrass2* Obj = Scene->LoadGameObject<CGrass2>();

		return Obj;
	}

	else if (Type == typeid(CGrass3).hash_code())
	{
		CGrass3* Obj = Scene->LoadGameObject<CGrass3>();

		return Obj;
	}

	else if (Type == typeid(CGrass4).hash_code())
	{
		CGrass4* Obj = Scene->LoadGameObject<CGrass4>();

		return Obj;
	}

	else if (Type == typeid(CGrass5).hash_code())
	{
		CGrass5* Obj = Scene->LoadGameObject<CGrass5>();

		return Obj;
	}

	else if (Type == typeid(CGrass6).hash_code())
	{
		CGrass6* Obj = Scene->LoadGameObject<CGrass6>();

		return Obj;
	}

	else if (Type == typeid(CGrass7).hash_code())
	{
		CGrass7* Obj = Scene->LoadGameObject<CGrass7>();

		return Obj;
	}

	else if (Type == typeid(CGrass8).hash_code())
	{
		CGrass8* Obj = Scene->LoadGameObject<CGrass8>();

		return Obj;
	}

	else if (Type == typeid(CGrass9).hash_code())
	{
		CGrass9* Obj = Scene->LoadGameObject<CGrass9>();

		return Obj;
	}

	else if (Type == typeid(CVine).hash_code())
	{
		CVine* Obj = Scene->LoadGameObject<CVine>();

		return Obj;
	}

	else if (Type == typeid(CVine2).hash_code())
	{
		CVine2* Obj = Scene->LoadGameObject<CVine2>();

		return Obj;
	}

	else if (Type == typeid(CVine3).hash_code())
	{
		CVine3* Obj = Scene->LoadGameObject<CVine3>();

		return Obj;
	}

	else if (Type == typeid(CVine4).hash_code())
	{
		CVine4* Obj = Scene->LoadGameObject<CVine4>();

		return Obj;
	}

	else if (Type == typeid(CVine5).hash_code())
	{
		CVine5* Obj = Scene->LoadGameObject<CVine5>();

		return Obj;
	}

	else if (Type == typeid(CPrecipice).hash_code())
	{
		CPrecipice* Obj = Scene->LoadGameObject<CPrecipice>();

		return Obj;
	}

	else if (Type == typeid(CPrecipice2).hash_code())
	{
		CPrecipice2* Obj = Scene->LoadGameObject<CPrecipice2>();

		return Obj;
	}

	else if (Type == typeid(CSculpture).hash_code())
	{
		CSculpture* Obj = Scene->LoadGameObject<CSculpture>();

		return Obj;
	}

	else if (Type == typeid(CSmallStone1).hash_code())
	{
		CSmallStone1* Obj = Scene->LoadGameObject<CSmallStone1>();

		return Obj;
	}

	else if (Type == typeid(CGrassRock1).hash_code())
	{
		CSmallStone1* Obj = Scene->LoadGameObject<CSmallStone1>();

		return Obj;
	}

	else if (Type == typeid(CGrassRock2).hash_code())
	{
		CGrassRock2* Obj = Scene->LoadGameObject<CGrassRock2>();

		return Obj;
	}

	else if (Type == typeid(CGrassRock3).hash_code())
	{
		CGrassRock3* Obj = Scene->LoadGameObject<CGrassRock3>();

		return Obj;
	}

	else if (Type == typeid(CGrassRock4).hash_code())
	{
		CGrassRock4* Obj = Scene->LoadGameObject<CGrassRock4>();

		return Obj;
	}

	else if (Type == typeid(CGrassRock5).hash_code())
	{
		CGrassRock5* Obj = Scene->LoadGameObject<CGrassRock5>();

		return Obj;
	}

	else if (Type == typeid(CGrassRock6).hash_code())
	{
		CGrassRock6* Obj = Scene->LoadGameObject<CGrassRock6>();

		return Obj;
	}

	else if (Type == typeid(CGrassRock7).hash_code())
	{
		CGrassRock7* Obj = Scene->LoadGameObject<CGrassRock7>();

		return Obj;
	}

	else if (Type == typeid(CGrassRock8).hash_code())
	{
		CGrassRock8* Obj = Scene->LoadGameObject<CGrassRock8>();

		return Obj;
	}

	else if (Type == typeid(CGrassRock9).hash_code())
	{
		CGrassRock9* Obj = Scene->LoadGameObject<CGrassRock9>();

		return Obj;
	}

	else if (Type == typeid(CWreck1).hash_code())
	{
		CWreck1* Obj = Scene->LoadGameObject<CWreck1>();

		return Obj;
	}

	else if (Type == typeid(CSmallGrass).hash_code())
	{
		CSmallGrass* Obj = Scene->LoadGameObject<CSmallGrass>();

		return Obj;
	}

	else if (Type == typeid(CTent1).hash_code())
	{
		CTent1* Obj = Scene->LoadGameObject<CTent1>();

		return Obj;
	}

	else if (Type == typeid(CTent2).hash_code())
	{
		CTent2* Obj = Scene->LoadGameObject<CTent2>();

		return Obj;
	}

	else if (Type == typeid(CBox1).hash_code())
	{
		CBox1* Obj = Scene->LoadGameObject<CBox1>();

		return Obj;
	}

	else if (Type == typeid(CFar).hash_code())
	{
		CFar* Obj = Scene->LoadGameObject<CFar>();

		return Obj;
	}

	return nullptr;
}

CGameObject* CEditorManager::CreateObj2(CScene* Scene, size_t Type)
{
	CGameObject* Obj = nullptr;

	if (Type == typeid(CDesertPebble).hash_code())
	{
		CDesertPebble* Obj = Scene->LoadGameObject<CDesertPebble>();

		return Obj;
	}

	else if (Type == typeid(CDesertSmallStone).hash_code())
	{
		CDesertSmallStone* Obj = Scene->LoadGameObject<CDesertSmallStone>();

		return Obj;
	}

	else if (Type == typeid(CDesertStone1).hash_code())
	{
		CDesertStone1* Obj = Scene->LoadGameObject<CDesertStone1>();

		return Obj;
	}

	else if (Type == typeid(CDesertStone2).hash_code())
	{
		CDesertStone2* Obj = Scene->LoadGameObject<CDesertStone2>();

		return Obj;
	}

	else if (Type == typeid(CDesertStone3).hash_code())
	{
		CDesertStone3* Obj = Scene->LoadGameObject<CDesertStone3>();

		return Obj;
	}

	else if (Type == typeid(CDesertStone4).hash_code())
	{
		CDesertStone4* Obj = Scene->LoadGameObject<CDesertStone4>();

		return Obj;
	}

	else if (Type == typeid(CDesertStone5).hash_code())
	{
		CDesertStone5* Obj = Scene->LoadGameObject<CDesertStone5>();

		return Obj;
	}

	else if (Type == typeid(CDesertStone6).hash_code())
	{
		CDesertStone6* Obj = Scene->LoadGameObject<CDesertStone6>();

		return Obj;
	}

	else if (Type == typeid(CDesertBigStone).hash_code())
	{
		CDesertBigStone* Obj = Scene->LoadGameObject<CDesertBigStone>();

		return Obj;
	}

	else if (Type == typeid(CDesertRockWall).hash_code())
	{
		CDesertRockWall* Obj = Scene->LoadGameObject<CDesertRockWall>();

		return Obj;
	}

	else if (Type == typeid(CDesertStalactite1).hash_code())
	{
		CDesertStalactite1* Obj = Scene->LoadGameObject<CDesertStalactite1>();

		return Obj;
	}

	else if (Type == typeid(CDesertStalactite2).hash_code())
	{
		CDesertStalactite2* Obj = Scene->LoadGameObject<CDesertStalactite2>();

		return Obj;
	}

	else if (Type == typeid(CDesertStalactite3).hash_code())
	{
		CDesertStalactite3* Obj = Scene->LoadGameObject<CDesertStalactite3>();

		return Obj;
	}

	else if (Type == typeid(CDesertStalactite4).hash_code())
	{
		CDesertStalactite4* Obj = Scene->LoadGameObject<CDesertStalactite4>();

		return Obj;
	}

	else if (Type == typeid(CDesertStalagmite1).hash_code())
	{
		CDesertStalagmite1* Obj = Scene->LoadGameObject<CDesertStalagmite1>();

		return Obj;
	}

	else if (Type == typeid(CDesertStalagmite2).hash_code())
	{
		CDesertStalagmite2* Obj = Scene->LoadGameObject<CDesertStalagmite2>();

		return Obj;
	}

	else if (Type == typeid(CDesertStalagmite3).hash_code())
	{
		CDesertStalagmite3* Obj = Scene->LoadGameObject<CDesertStalagmite3>();

		return Obj;
	}

	else if (Type == typeid(CStonej1).hash_code())
	{
		CStonej1* Obj = Scene->LoadGameObject<CStonej1>();

		return Obj;
	}

	else if (Type == typeid(CStonej2).hash_code())
	{
		CStonej2* Obj = Scene->LoadGameObject<CStonej2>();

		return Obj;
	}

	else if (Type == typeid(CStonej3).hash_code())
	{
		CStonej3* Obj = Scene->LoadGameObject<CStonej3>();

		return Obj;
	}

	else if (Type == typeid(CStonej4).hash_code())
	{
		CStonej4* Obj = Scene->LoadGameObject<CStonej4>();

		return Obj;
	}

	else if (Type == typeid(CStonej5).hash_code())
	{
		CStonej5* Obj = Scene->LoadGameObject<CStonej5>();

		return Obj;
	}

	else if (Type == typeid(CStonej6).hash_code())
	{
		CStonej6* Obj = Scene->LoadGameObject<CStonej6>();

		return Obj;
	}

	else if (Type == typeid(CStonej7).hash_code())
	{
		CStonej7* Obj = Scene->LoadGameObject<CStonej7>();

		return Obj;
	}

	else if (Type == typeid(CStonej8).hash_code())
	{
		CStonej8* Obj = Scene->LoadGameObject<CStonej8>();

		return Obj;
	}

	else if (Type == typeid(CStonej9).hash_code())
	{
		CStonej9* Obj = Scene->LoadGameObject<CStonej9>();

		return Obj;
	}

	else if (Type == typeid(CStonej10).hash_code())
	{
		CStonej10* Obj = Scene->LoadGameObject<CStonej10>();

		return Obj;
	}

	else if (Type == typeid(CStonej11).hash_code())
	{
		CStonej11* Obj = Scene->LoadGameObject<CStonej11>();

		return Obj;
	}

	else if (Type == typeid(CStonej12).hash_code())
	{
		CStonej12* Obj = Scene->LoadGameObject<CStonej12>();

		return Obj;
	}

	else if (Type == typeid(CStonej13).hash_code())
	{
		CStonej13* Obj = Scene->LoadGameObject<CStonej13>();

		return Obj;
	}

	else if (Type == typeid(CStonej14).hash_code())
	{
		CStonej14* Obj = Scene->LoadGameObject<CStonej14>();

		return Obj;
	}

	else if (Type == typeid(CStonej15).hash_code())
	{
		CStonej15* Obj = Scene->LoadGameObject<CStonej15>();

		return Obj;
	}

	else if (Type == typeid(CStonej16).hash_code())
	{
		CStonej16* Obj = Scene->LoadGameObject<CStonej16>();

		return Obj;
	}

	else if (Type == typeid(CStonej17).hash_code())
	{
		CStonej17* Obj = Scene->LoadGameObject<CStonej17>();

		return Obj;
	}

	else if (Type == typeid(CStonej18).hash_code())
	{
		CStonej18* Obj = Scene->LoadGameObject<CStonej18>();

		return Obj;
	}

	else if (Type == typeid(CStonej19).hash_code())
	{
		CStonej19* Obj = Scene->LoadGameObject<CStonej19>();

		return Obj;
	}

	else if (Type == typeid(CStonej20).hash_code())
	{
		CStonej20* Obj = Scene->LoadGameObject<CStonej20>();

		return Obj;
	}

	else if (Type == typeid(CStonej21).hash_code())
	{
		CStonej21* Obj = Scene->LoadGameObject<CStonej21>();

		return Obj;
	}

	else if (Type == typeid(CStonej22).hash_code())
	{
		CStonej22* Obj = Scene->LoadGameObject<CStonej22>();

		return Obj;
	}

	else if (Type == typeid(CStonej23).hash_code())
	{
		CStonej23* Obj = Scene->LoadGameObject<CStonej23>();

		return Obj;
	}

	else if (Type == typeid(CStonej24).hash_code())
	{
		CStonej24* Obj = Scene->LoadGameObject<CStonej24>();

		return Obj;
	}

	else if (Type == typeid(CStonej25).hash_code())
	{
		CStonej25* Obj = Scene->LoadGameObject<CStonej25>();

		return Obj;
	}

	else if (Type == typeid(CStonej26).hash_code())
	{
		CStonej26* Obj = Scene->LoadGameObject<CStonej26>();

		return Obj;
	}

	else if (Type == typeid(CStonej27).hash_code())
	{
		CStonej27* Obj = Scene->LoadGameObject<CStonej27>();

		return Obj;
	}

	else if (Type == typeid(CStonej28).hash_code())
	{
		CStonej28* Obj = Scene->LoadGameObject<CStonej28>();

		return Obj;
	}

	else if (Type == typeid(CStonej29).hash_code())
	{
		CStonej29* Obj = Scene->LoadGameObject<CStonej29>();

		return Obj;
	}

	else if (Type == typeid(CStonej30).hash_code())
	{
		CStonej30* Obj = Scene->LoadGameObject<CStonej30>();

		return Obj;
	}

	else if (Type == typeid(CStonej31).hash_code())
	{
		CStonej31* Obj = Scene->LoadGameObject<CStonej31>();

		return Obj;
	}

	else if (Type == typeid(CStonej32).hash_code())
	{
		CStonej32* Obj = Scene->LoadGameObject<CStonej32>();

		return Obj;
	}

	else if (Type == typeid(CStonej33).hash_code())
	{
		CStonej33* Obj = Scene->LoadGameObject<CStonej33>();

		return Obj;
	}

	else if (Type == typeid(CStonej34).hash_code())
	{
		CStonej34* Obj = Scene->LoadGameObject<CStonej34>();

		return Obj;
	}

	else if (Type == typeid(CStonej35).hash_code())
	{
		CStonej35* Obj = Scene->LoadGameObject<CStonej35>();

		return Obj;
	}

	else if (Type == typeid(CStonej36).hash_code())
	{
		CStonej36* Obj = Scene->LoadGameObject<CStonej36>();

		return Obj;
	}

	else if (Type == typeid(CStonej37).hash_code())
	{
		CStonej37* Obj = Scene->LoadGameObject<CStonej37>();

		return Obj;
	}

	else if (Type == typeid(CTownBarrel).hash_code())
	{
		CTownBarrel* Obj = Scene->LoadGameObject<CTownBarrel>();

		return Obj;
	}

	else if (Type == typeid(CTownCarriage).hash_code())
	{
		CTownCarriage* Obj = Scene->LoadGameObject<CTownCarriage>();

		return Obj;
	}

	else if (Type == typeid(CTownCheckPoint).hash_code())
	{
		CTownCheckPoint* Obj = Scene->LoadGameObject<CTownCheckPoint>();

		return Obj;
	}

	else if (Type == typeid(CTownDragonHead).hash_code())
	{
		CTownDragonHead* Obj = Scene->LoadGameObject<CTownDragonHead>();

		return Obj;
	}

	else if (Type == typeid(CTownPassage).hash_code())
	{
		CTownPassage* Obj = Scene->LoadGameObject<CTownPassage>();

		return Obj;
	}

	else if (Type == typeid(CTownPumpkinMan).hash_code())
	{
		CTownPumpkinMan* Obj = Scene->LoadGameObject<CTownPumpkinMan>();

		return Obj;
	}

	else if (Type == typeid(CTownRampart).hash_code())
	{
		CTownRampart* Obj = Scene->LoadGameObject<CTownRampart>();

		return Obj;
	}

	else if (Type == typeid(CTownShadeScreen).hash_code())
	{
		CTownShadeScreen* Obj = Scene->LoadGameObject<CTownShadeScreen>();

		return Obj;
	}

	else if (Type == typeid(CTownSign).hash_code())
	{
		CTownSign* Obj = Scene->LoadGameObject<CTownSign>();

		return Obj;
	}

	else if (Type == typeid(CTownStructure).hash_code())
	{
		CTownStructure* Obj = Scene->LoadGameObject<CTownStructure>();

		return Obj;
	}

	else if (Type == typeid(CTownSummerHouse).hash_code())
	{
		CTownSummerHouse* Obj = Scene->LoadGameObject<CTownSummerHouse>();

		return Obj;
	}

	else if (Type == typeid(CTownTunnel).hash_code())
	{
		CTownTunnel* Obj = Scene->LoadGameObject<CTownTunnel>();

		return Obj;
	}

	else if (Type == typeid(CDesertMountain1).hash_code())
	{
		CDesertMountain1* Obj = Scene->LoadGameObject<CDesertMountain1>();

		return Obj;
	}

	else if (Type == typeid(CDesertMountain2).hash_code())
	{
		CDesertMountain2* Obj = Scene->LoadGameObject<CDesertMountain2>();

		return Obj;
	}

	return nullptr;
}

const char* CEditorManager::GetHierarchyName(Object_Type Type) const
{
	switch (Type)
	{
	case Object_Type::Player:
		return "플레이어";
	case Object_Type::Monster:
		return "몬스터";
	case Object_Type::LandScape:
		return "지형";
	case Object_Type::FieldObj:
		return "필드";
	}

	return "";
}

void CEditorManager::GetHierarchyNameAll(std::vector<const char*>& vecOutput)
{
	vecOutput.resize((size_t)Object_Type::Max);

	for (int i = 0; i < (int)Object_Type::Max; ++i)
	{
		vecOutput[i] = GetHierarchyName((Object_Type)i);
	}
}

Object_Type CEditorManager::GetHierarchyType(const char* Name) const
{
	if (!strcmp(Name, "플레이어"))
		return Object_Type::Player;

	else if (!strcmp(Name, "몬스터"))
		return Object_Type::Monster;

	else if (!strcmp(Name, "지형"))
		return Object_Type::LandScape;

	else if (!strcmp(Name, "필드"))
		return Object_Type::FieldObj;

	return Object_Type::Max;
}

Object_Type CEditorManager::GetHierarchyType(const std::string& Name) const
{
	if (!Name.compare("플레이어"))
		return Object_Type::Player;

	else if (!Name.compare("몬스터"))
		return Object_Type::Monster;

	else if (!Name.compare("지형"))
		return Object_Type::LandScape;

	else if (!Name.compare("필드"))
		return Object_Type::FieldObj;

	return Object_Type::Max;
}

const char* CEditorManager::GetMonsterName(Monster_Type Type) const
{
	switch (Type)
	{
	case Monster_Type::Barnos:
		return "바르노스";
	case Monster_Type::Jagras:
		return "쟈그라스";
	case Monster_Type::Kestodon:
		return "케스토돈";
	case Monster_Type::Vespoid:
		return "랑고스타";
	case Monster_Type::Anjanath:
		return "안쟈나프";
	case Monster_Type::Rathalos:
		return "리오레우스";
	}

	return "";
}

const char* CEditorManager::GetMonsterNameEng(Monster_Type Type) const
{
	switch (Type)
	{
	case Monster_Type::Barnos:
		return "Barnos";
	case Monster_Type::Jagras:
		return "Jagras";
	case Monster_Type::Kestodon:
		return "Kestodon";
	case Monster_Type::Vespoid:
		return "Vespoid";
	case Monster_Type::Anjanath:
		return "Anjanath";
	case Monster_Type::Rathalos:
		return "Rathalos";
	}

	return "";
}

void CEditorManager::GetMonsterNameAll(std::vector<const char*>& vecOutput)
{
	vecOutput.resize((size_t)Monster_Type::Max);

	for (int i = 0; i < (int)Monster_Type::Max; ++i)
	{
		vecOutput[i] = GetMonsterName((Monster_Type)i);
	}
}

Monster_Type CEditorManager::GetMonsterType(const char* Name) const
{
	if (!strcmp(Name, "바르노스"))
		return Monster_Type::Barnos;

	else if (!strcmp(Name, "쟈그라스"))
		return Monster_Type::Jagras;

	else if (!strcmp(Name, "케스토돈"))
		return Monster_Type::Kestodon;

	else if (!strcmp(Name, "랑고스타"))
		return Monster_Type::Vespoid;

	else if (!strcmp(Name, "안쟈나프"))
		return Monster_Type::Anjanath;

	else if (!strcmp(Name, "리오레우스"))
		return Monster_Type::Rathalos;

	return Monster_Type::Max;
}

Monster_Type CEditorManager::GetMonsterType(const std::string& Name) const
{
	if (!Name.compare("바르노스"))
		return Monster_Type::Barnos;

	else if (!Name.compare("쟈그라스"))
		return Monster_Type::Jagras;

	else if (!Name.compare("케스토돈"))
		return Monster_Type::Kestodon;

	else if (!Name.compare("랑고스타"))
		return Monster_Type::Vespoid;

	else if (!Name.compare("안쟈나프"))
		return Monster_Type::Anjanath;

	else if (!Name.compare("리오레우스"))
		return Monster_Type::Rathalos;

	return Monster_Type::Max;
}

const char* CEditorManager::GetFieldObjName(FieldObj_Type Type) const
{
	switch (Type)
	{
	case FieldObj_Type::SlidingBox:
		return "슬라이딩 박스";
	case FieldObj_Type::HealFlower:
		return "회복꽃";
	case FieldObj_Type::SmallTree:
		return "작은 나무";
	case FieldObj_Type::Tree:
		return "나무";
	case FieldObj_Type::BigTree:
		return "큰 나무";
	case FieldObj_Type::BrokenTree:
		return "부서진 나무";
	case FieldObj_Type::MushRoom:
		return "버섯";
	case FieldObj_Type::SmallGrass:
		return "작은 잔디";
	case FieldObj_Type::Grass:
		return "잔디";
	case FieldObj_Type::Vine:
		return "덩굴";
	case FieldObj_Type::Precipice:
		return "절벽";
	case FieldObj_Type::Sculpture:
		return "조각";
	case FieldObj_Type::SmallStone:
		return "작은 돌";
	case FieldObj_Type::GrassRock:
		return "잔디 돌";
	case FieldObj_Type::Wreck:
		return "잔해";
	case FieldObj_Type::Tent:
		return "텐트";
	case FieldObj_Type::Box:
		return "박스";
	case FieldObj_Type::Far:
		return "원경";
	case FieldObj_Type::Stone:
		return "돌";
	case FieldObj_Type::TownBarrel:
		return "마을 통";
	case FieldObj_Type::TownCarriage:
		return "마을 객차";
	case FieldObj_Type::TownCheckPoint:
		return "마을 체크포인트";
	case FieldObj_Type::TownDragonHead:
		return "마을 용머리";
	case FieldObj_Type::TownPassage:
		return "마을 항로";
	case FieldObj_Type::TownPumpkinMan:
		return "마을 호박인간";
	case FieldObj_Type::TownRampart:
		return "마을 성벽";
	case FieldObj_Type::TownShadeScreen:
		return "마을 그늘막";
	case FieldObj_Type::TownSign:
		return "마을 표지판";
	case FieldObj_Type::TownStructure:
		return "마을 구조물";
	case FieldObj_Type::TownSummerHouse:
		return "마을 정자";
	case FieldObj_Type::TownTunnel:
		return "마을 터널";
	case FieldObj_Type::DesertPebble:
		return "사막 자갈";
	case FieldObj_Type::DesertSmallStone:
		return "사막 작은 돌";
	case FieldObj_Type::DesertStone:
		return "사막 돌";
	case FieldObj_Type::DesertBigStone:
		return "사막 큰 돌";
	case FieldObj_Type::DesertRockWall:
		return "사막 돌벽";
	case FieldObj_Type::DesertStalactite:
		return "사막 종유석";
	case FieldObj_Type::DesertStalagmite:
		return "사막 석순";
	case FieldObj_Type::DesertMountain:
		return "사막 산";
	}

	return "";
}

const char* CEditorManager::GetFieldObjNameEng(FieldObj_Type Type) const
{
	switch (Type)
	{
	case FieldObj_Type::SlidingBox:
		return "SlidingBox";
	case FieldObj_Type::HealFlower:
		return "HealFlower";
	case FieldObj_Type::SmallTree:
		return "SmallTree";
	case FieldObj_Type::Tree:
		return "Tree";
	case FieldObj_Type::BigTree:
		return "BigTree";
	case FieldObj_Type::BrokenTree:
		return "BrokenTree";
	case FieldObj_Type::MushRoom:
		return "MushRoom";
	case FieldObj_Type::SmallGrass:
		return "SmallGrass";
	case FieldObj_Type::Grass:
		return "Grass";
	case FieldObj_Type::Vine:
		return "Vine";
	case FieldObj_Type::Precipice:
		return "Precipice";
	case FieldObj_Type::Sculpture:
		return "Sculpture";
	case FieldObj_Type::SmallStone:
		return "SmallStone";
	case FieldObj_Type::GrassRock:
		return "GrassRock";
	case FieldObj_Type::Wreck:
		return "Wreck";
	case FieldObj_Type::Tent:
		return "Tent";
	case FieldObj_Type::Box:
		return "Box";
	case FieldObj_Type::Far:
		return "Far";
	case FieldObj_Type::Stone:
		return "Stone";
	case FieldObj_Type::TownBarrel:
		return "TownBarrel";
	case FieldObj_Type::TownCarriage:
		return "TownCarriage";
	case FieldObj_Type::TownCheckPoint:
		return "TownCheckPoint";
	case FieldObj_Type::TownDragonHead:
		return "TownDragonHead";
	case FieldObj_Type::TownPassage:
		return "TownPassage";
	case FieldObj_Type::TownPumpkinMan:
		return "TownPumpkinMan";
	case FieldObj_Type::TownRampart:
		return "TownRampart";
	case FieldObj_Type::TownShadeScreen:
		return "TownShadeScreen";
	case FieldObj_Type::TownSign:
		return "TownSign";
	case FieldObj_Type::TownStructure:
		return "TownStructure";
	case FieldObj_Type::TownSummerHouse:
		return "TownSummerHouse";
	case FieldObj_Type::TownTunnel:
		return "TownTunnel";
	case FieldObj_Type::DesertPebble:
		return "DesertPebble";
	case FieldObj_Type::DesertSmallStone:
		return "DesertSmallStone";
	case FieldObj_Type::DesertStone:
		return "DesertStone";
	case FieldObj_Type::DesertBigStone:
		return "DesertBigStone";
	case FieldObj_Type::DesertRockWall:
		return "DesertRockWall";
	case FieldObj_Type::DesertStalactite:
		return "DesertStalactite";
	case FieldObj_Type::DesertStalagmite:
		return "DesertStalagmite";
	case FieldObj_Type::DesertMountain:
		return "DesertMountain";
	}

	return "";
}

void CEditorManager::GetFieldObjNameAll(std::vector<const char*>& vecOutput)
{
	vecOutput.resize((size_t)FieldObj_Type::Max);

	for (int i = 0; i < (int)FieldObj_Type::Max; ++i)
	{
		vecOutput[i] = GetFieldObjName((FieldObj_Type)i);
	}
}

FieldObj_Type CEditorManager::GetFieldObjType(const char* Name) const
{
	if (!strcmp(Name, "슬라이딩 박스"))
		return FieldObj_Type::SlidingBox;

	else if (!strcmp(Name, "회복꽃"))
		return FieldObj_Type::HealFlower;

	else if (!strcmp(Name, "작은 나무"))
		return FieldObj_Type::SmallTree;

	else if (!strcmp(Name, "나무"))
		return FieldObj_Type::Tree;

	else if (!strcmp(Name, "큰 나무"))
		return FieldObj_Type::BigTree;

	else if (!strcmp(Name, "부서진 나무"))
		return FieldObj_Type::BrokenTree;

	else if (!strcmp(Name, "버섯"))
		return FieldObj_Type::MushRoom;

	else if (!strcmp(Name, "작은 잔디"))
		return FieldObj_Type::SmallGrass;

	else if (!strcmp(Name, "잔디"))
		return FieldObj_Type::Grass;

	else if (!strcmp(Name, "덩굴"))
		return FieldObj_Type::Vine;

	else if (!strcmp(Name, "절벽"))
		return FieldObj_Type::Precipice;

	else if (!strcmp(Name, "조각"))
		return FieldObj_Type::Sculpture;

	else if (!strcmp(Name, "작은 돌"))
		return FieldObj_Type::SmallStone;

	else if (!strcmp(Name, "잔디 돌"))
		return FieldObj_Type::GrassRock;

	else if (!strcmp(Name, "잔해"))
		return FieldObj_Type::Wreck;

	else if (!strcmp(Name, "텐트"))
		return FieldObj_Type::Tent;

	else if (!strcmp(Name, "박스"))
		return FieldObj_Type::Box;

	else if (!strcmp(Name, "원경"))
		return FieldObj_Type::Far;

	else if (!strcmp(Name, "돌"))
		return FieldObj_Type::Stone;

	else if (!strcmp(Name, "마을 통"))
		return FieldObj_Type::TownBarrel;

	else if (!strcmp(Name, "마을 객차"))
		return FieldObj_Type::TownCarriage;

	else if (!strcmp(Name, "마을 체크포인트"))
		return FieldObj_Type::TownCheckPoint;

	else if (!strcmp(Name, "마을 용머리"))
		return FieldObj_Type::TownDragonHead;

	else if (!strcmp(Name, "마을 항로"))
		return FieldObj_Type::TownPassage;

	else if (!strcmp(Name, "마을 호박인간"))
		return FieldObj_Type::TownPumpkinMan;

	else if (!strcmp(Name, "마을 성벽"))
		return FieldObj_Type::TownRampart;

	else if (!strcmp(Name, "마을 그늘막"))
		return FieldObj_Type::TownShadeScreen;

	else if (!strcmp(Name, "마을 표지판"))
		return FieldObj_Type::TownSign;

	else if (!strcmp(Name, "마을 구조물"))
		return FieldObj_Type::TownStructure;

	else if (!strcmp(Name, "마을 정자"))
		return FieldObj_Type::TownSummerHouse;

	else if (!strcmp(Name, "마을 터널"))
		return FieldObj_Type::TownTunnel;

	else if (!strcmp(Name, "사막 자갈"))
		return FieldObj_Type::DesertPebble;

	else if (!strcmp(Name, "사막 작은 돌"))
		return FieldObj_Type::DesertSmallStone;

	else if (!strcmp(Name, "사막 돌"))
		return FieldObj_Type::DesertStone;

	else if (!strcmp(Name, "사막 큰 돌"))
		return FieldObj_Type::DesertBigStone;

	else if (!strcmp(Name, "사막 돌벽"))
		return FieldObj_Type::DesertRockWall;

	else if (!strcmp(Name, "사막 종유석"))
		return FieldObj_Type::DesertStalactite;

	else if (!strcmp(Name, "사막 석순"))
		return FieldObj_Type::DesertStalagmite;

	else if (!strcmp(Name, "사막 산"))
	return FieldObj_Type::DesertMountain;

	return FieldObj_Type::Max;
}

FieldObj_Type CEditorManager::GetFieldObjType(const std::string& Name) const
{
	if (!Name.compare("슬라이딩 박스"))
		return FieldObj_Type::SlidingBox;

	else if (!Name.compare("회복꽃"))
		return FieldObj_Type::HealFlower;

	else if (!Name.compare("작은 나무"))
		return FieldObj_Type::SmallTree;

	else if (!Name.compare("나무"))
		return FieldObj_Type::Tree;

	else if (!Name.compare("큰 나무"))
		return FieldObj_Type::BigTree;

	else if (!Name.compare("부서진 나무"))
		return FieldObj_Type::BrokenTree;

	else if (!Name.compare("버섯"))
		return FieldObj_Type::MushRoom;

	else if (!Name.compare("작은 잔디"))
		return FieldObj_Type::SmallGrass;

	else if (!Name.compare("잔디"))
		return FieldObj_Type::Grass;

	else if (!Name.compare("덩굴"))
		return FieldObj_Type::Vine;

	else if (!Name.compare("절벽"))
		return FieldObj_Type::Precipice;

	else if (!Name.compare("조각"))
		return FieldObj_Type::Sculpture;

	else if (!Name.compare("작은 돌"))
		return FieldObj_Type::SmallStone;

	else if (!Name.compare("잔디 돌"))
		return FieldObj_Type::GrassRock;

	else if (!Name.compare("잔해"))
		return FieldObj_Type::Wreck;

	else if (!Name.compare("텐트"))
		return FieldObj_Type::Tent;

	else if (!Name.compare("박스"))
		return FieldObj_Type::Box;

	else if (!Name.compare("원경"))
		return FieldObj_Type::Far;

	else if (!Name.compare("돌"))
		return FieldObj_Type::Stone;

	else if (!Name.compare("마을 통"))
		return FieldObj_Type::TownBarrel;

	else if (!Name.compare("마을 객차"))
		return FieldObj_Type::TownCarriage;

	else if (!Name.compare("마을 체크포인트"))
		return FieldObj_Type::TownCheckPoint;

	else if (!Name.compare("마을 용머리"))
		return FieldObj_Type::TownDragonHead;

	else if (!Name.compare("마을 항로"))
		return FieldObj_Type::TownPassage;

	else if (!Name.compare("마을 호박인간"))
		return FieldObj_Type::TownPumpkinMan;

	else if (!Name.compare("마을 성벽"))
		return FieldObj_Type::TownRampart;

	else if (!Name.compare("마을 그늘막"))
		return FieldObj_Type::TownShadeScreen;

	else if (!Name.compare("마을 표지판"))
		return FieldObj_Type::TownSign;

	else if (!Name.compare("마을 구조물"))
		return FieldObj_Type::TownStructure;

	else if (!Name.compare("마을 정자"))
		return FieldObj_Type::TownSummerHouse;

	else if (!Name.compare("마을 터널"))
		return FieldObj_Type::TownTunnel;

	else if (!Name.compare("사막 자갈"))
		return FieldObj_Type::DesertPebble;

	else if (!Name.compare("사막 작은 돌"))
		return FieldObj_Type::DesertSmallStone;

	else if (!Name.compare("사막 돌"))
		return FieldObj_Type::DesertStone;

	else if (!Name.compare("사막 큰 돌"))
		return FieldObj_Type::DesertBigStone;

	else if (!Name.compare("사막 돌벽"))
		return FieldObj_Type::DesertRockWall;

	else if (!Name.compare("사막 종유석"))
		return FieldObj_Type::DesertStalactite;

	else if (!Name.compare("사막 석순"))
		return FieldObj_Type::DesertStalagmite;

	else if (!Name.compare("사막 산"))
	return FieldObj_Type::DesertMountain;

	return FieldObj_Type::Max;
}

const char* CEditorManager::GetTypeKorToEng(const std::string& KorTypeName)
{
	if (!KorTypeName.compare("플레이어"))
		return "Player";

	else if (!KorTypeName.compare("몬스터"))
		return "Monster";

	else if (!KorTypeName.compare("지형"))
		return "LandScape";

	else if (!KorTypeName.compare("필드"))
		return "FieldObj";

	return "";
}

CEditorScene* CEditorManager::GetEditorScene() const
{
	if (!CSceneManager::GetInst()->GetScene())
		return nullptr;

	CSceneMode* SceneMode = CSceneManager::GetInst()->GetScene()->GetSceneMode();

	return dynamic_cast<CEditorScene*>(SceneMode);
}
