
#include "Scene.h"
#include "SceneManager.h"
#include "../Input.h"
#include "../PathManager.h"
#include "../GameObject/SkyObject.h"
#include "../Component/CameraComponent.h"
#include "../Component/WidgetComponent.h"
#include "../Component/AnimationMeshComponent.h"
#include "../Component/StaticMeshComponent.h"
#include "../Component/CameraComponent.h"
#include "../Component/LandScape.h"
#include "../Collision/Collision.h"
#include "../Component/ColliderBox3D.h"

CScene::CScene()
{
	m_Mode = DBG_NEW CSceneMode;
	m_Resource = DBG_NEW CSceneResource;
	m_Collision = DBG_NEW CSceneCollision;
	m_CameraManager = DBG_NEW CCameraManager;
	m_Viewport = DBG_NEW CViewport;
	m_NavManager = DBG_NEW CNavigationManager;
	m_Nav3DManager = DBG_NEW CNavigation3DManager;
	m_LightManager = DBG_NEW CLightManager;

	m_Mode->m_Scene = this;
	m_Resource->m_Scene = this;
	m_Collision->m_Scene = this;
	m_CameraManager->m_Scene = this;
	m_Viewport->m_Scene = this;
	m_NavManager->m_Scene = this;
	m_Nav3DManager->m_Scene = this;
	m_LightManager->m_Scene = this;

	m_Start = false;

	m_Collision->Init();
	m_CameraManager->Init();
	m_Viewport->Init();
	m_NavManager->Init();
	m_Nav3DManager->Init();
	m_LightManager->Init();

	m_Change = true;

	m_SkyObject = DBG_NEW CSkyObject;

	m_SkyObject->SetName("Sky");
	m_SkyObject->SetScene(this);

	m_SkyObject->Init();
}

CScene::~CScene()
{
	m_ObjList.clear();
	SAFE_DELETE(m_Nav3DManager);
	SAFE_DELETE(m_NavManager);
	SAFE_DELETE(m_Viewport);
	SAFE_DELETE(m_CameraManager);
	SAFE_DELETE(m_Collision);
	SAFE_DELETE(m_Resource);
	m_LightManager->Destroy();
	SAFE_DELETE(m_LightManager);
}

bool CScene::Picking(CGameObject*& result)
{
	CCameraComponent* Camera = m_CameraManager->GetCurrentCamera();

	Ray	ray = CInput::GetInst()->GetRay(Camera->GetViewMatrix());

	auto	iter = m_RenderComponentList.begin();
	auto	iterEnd = m_RenderComponentList.end();

	Vector3	HitPoint;

	for (; iter != iterEnd; ++iter)
	{
		SphereInfo	Info = (*iter)->GetSphereInfo();

		if (CCollision::CollisionRayToSphere(HitPoint, ray, Info))
		{
			if (FindIgnoreTypeID((*iter)->GetGameObject()->GetTypeID()))
				continue;

			result = (*iter)->GetGameObject();
			return true;
		}
	}

	result = nullptr;

	return false;
}

bool CScene::PickingBox(CGameObject*& result)
{
	CCameraComponent* Camera = m_CameraManager->GetCurrentCamera();

	Ray	ray = CInput::GetInst()->GetRay(Camera->GetViewMatrix());

	auto	iter = m_ColliderList.begin();
	auto	iterEnd = m_ColliderList.end();

	Vector3	HitPoint;

	for (; iter != iterEnd; ++iter)
	{
		Box3DInfo	Info = ((CColliderBox3D*)(*iter))->GetInfo();

		if (CCollision::CollisionRayToBox3D(HitPoint, ray, Info))
		{
			if (FindIgnoreTypeID((*iter)->GetGameObject()->GetTypeID()))
				continue;

			result = (*iter)->GetGameObject();
			return true;
		}
	}

	result = nullptr;

	return false;
}

bool CScene::ForwardRayCollision(CGameObject*& result)
{
	
	CGameObject* Player = FindObject("Player");

	Vector3 PlayerPos = Player->GetWorldPos();

	Vector3 AxisZ = Player->GetRootComponent()->GetWorldAxis(AXIS::AXIS_Z);
	AxisZ.Normalize();
	PlayerPos.y += 3.f;

	Ray ForwardRay = {};
	ForwardRay.Pos = PlayerPos;

	ForwardRay.Dir = AxisZ;

	auto	iter = m_ColliderList.begin();
	auto	iterEnd = m_ColliderList.end();

	Vector3	HitPoint;

	for (; iter != iterEnd; ++iter)
	{
		Box3DInfo	Info = ((CColliderBox3D*)(*iter))->GetInfo();

		if (CCollision::CollisionRayToBox3D(HitPoint, ForwardRay, Info))
		{
			if (FindIgnoreTypeID((*iter)->GetGameObject()->GetTypeID()))
				continue;

			result = (*iter)->GetGameObject();

			if (result->GetName() == "Player")
			{
				result = nullptr;
				return false;
			}
			return true;
		}
	}

	result = nullptr;

	return false;
}

bool CScene::FindIgnoreTypeID(size_t TypeID)
{
	size_t Size = m_vecIgnoreObject.size();

	for (size_t i = 0; i < Size; ++i)
	{
		if (m_vecIgnoreObject[i] == TypeID)
			return true;
	}

	return false;
}

void CScene::AddIgnoreTypeID(size_t TypeID)
{
	if (FindIgnoreTypeID(TypeID))
		return;

	m_vecIgnoreObject.push_back(TypeID);
}

void CScene::Start()
{
	m_Mode->Start();

	auto	iter = m_ObjList.begin();
	auto	iterEnd = m_ObjList.end();

	for (; iter != iterEnd; ++iter)
	{
		(*iter)->Start();
	}

	m_Start = true;

	m_SkyObject->Start();

	m_CameraManager->Start();
	m_Collision->Start();
	m_Viewport->Start();
	m_LightManager->Start();

	if (m_Mode->GetPlayerObject())
	{
		CCameraComponent* Camera = m_Mode->GetPlayerObject()->FindComponentFromType<CCameraComponent>();

		if (Camera)
		{
			m_CameraManager->SetCurrentCamera(Camera);
		}
	}

	m_NavManager->Start();

	m_Nav3DManager->Start();
}

void CScene::Update(float DeltaTime)
{
	m_Mode->Update(DeltaTime);

	//m_SkyObject->Update(DeltaTime);

	auto	iter = m_ObjList.begin();
	auto	iterEnd = m_ObjList.end();

	for (; iter != iterEnd;)
	{
		if (!(*iter)->IsActive())
		{
			iter = m_ObjList.erase(iter);
			iterEnd = m_ObjList.end();
			continue;
		}

		else if (!(*iter)->IsEnable())
		{
			++iter;
			continue;
		}

		(*iter)->Update(DeltaTime);
		++iter;
	}

	m_CameraManager->Update(DeltaTime);

	m_Viewport->Update(DeltaTime);

	m_NavManager->Update(DeltaTime);

	m_Nav3DManager->Update(DeltaTime);

	m_LightManager->Update(DeltaTime);
}

void CScene::PostUpdate(float DeltaTime)
{
	m_Mode->PostUpdate(DeltaTime);

	m_SkyObject->PostUpdate(DeltaTime);

	auto	iter = m_ObjList.begin();
	auto	iterEnd = m_ObjList.end();

	for (; iter != iterEnd;)
	{
		if (!(*iter)->IsActive())
		{
			iter = m_ObjList.erase(iter);
			iterEnd = m_ObjList.end();
			continue;
		}

		else if (!(*iter)->IsEnable())
		{
			++iter;
			continue;
		}

		(*iter)->PostUpdate(DeltaTime);
		++iter;
	}

	m_CameraManager->PostUpdate(DeltaTime);

	m_Viewport->PostUpdate(DeltaTime);

	// 충돌체들을 충돌 영역에 포함시킨다.
	iter = m_ObjList.begin();
	iterEnd = m_ObjList.end();

	m_RenderComponentList.clear();
	m_ColliderList.clear();

	for (; iter != iterEnd; ++iter)
	{
		(*iter)->AddCollision();

		const std::list<CSceneComponent*>& List = (*iter)->GetSceneComponents();

		auto	iter1 = List.begin();
		auto	iter1End = List.end();

		for (; iter1 != iter1End; ++iter1)
		{
			if ((*iter1)->GetRender() && !(*iter1)->GetCulling() &&
				((*iter1)->CheckType<CAnimationMeshComponent>() || 
				(*iter1)->CheckType<CStaticMeshComponent>()))
			{
				m_RenderComponentList.push_back(*iter1);
			}
			if ((*iter1)->GetRender() && !(*iter1)->GetCulling() &&
				(*iter1)->CheckType<CColliderBox3D>())
			{
				m_ColliderList.push_back((CColliderBox3D*)*iter1);
			}
		}
	}

	// 출력되는 물체를 정렬한다.
	if (m_RenderComponentList.size() >= 2)
	{
		m_RenderComponentList.sort(SortRenderList);
	}
	if (m_ColliderList.size() >= 2)
	{
		m_ColliderList.sort(SortColliderRenderList);
	}


	// 포함된 충돌체들을 이용해서 충돌처리를 진행한다.
	m_Collision->Collision(DeltaTime);
}

void CScene::Save(const char* FileName, const std::string& PathName)
{
	const PathInfo* Info = CPathManager::GetInst()->FindPath(PathName);

	char	FullPath[MAX_PATH] = {};

	if (Info)
		strcpy_s(FullPath, Info->PathMultibyte);

	strcat_s(FullPath, FileName);

	SaveFullPath(FullPath);
}

void CScene::SaveFullPath(const char* FullPath)
{
	FILE* File = nullptr;

	fopen_s(&File, FullPath, "wb");

	if (!File)
		return;

	size_t	SceneModeType = m_Mode->GetTypeID();

	fwrite(&SceneModeType, sizeof(size_t), 1, File);

	size_t	ObjCount = m_ObjList.size();

	fwrite(&ObjCount, sizeof(size_t), 1, File);

	auto	iter = m_ObjList.begin();
	auto	iterEnd = m_ObjList.end();

	for (; iter != iterEnd; ++iter)
	{
		size_t	ObjType = (*iter)->GetTypeID();

		fwrite(&ObjType, sizeof(size_t), 1, File);

		(*iter)->Save(File);
	}


	fclose(File);
}

void CScene::Load(const char* FileName, const std::string& PathName)
{
	const PathInfo* Info = CPathManager::GetInst()->FindPath(PathName);

	char	FullPath[MAX_PATH] = {};

	if (Info)
		strcpy_s(FullPath, Info->PathMultibyte);

	strcat_s(FullPath, FileName);

	LoadFullPath(FullPath);
}

void CScene::LoadFullPath(const char* FullPath)
{
	FILE* File = nullptr;

	fopen_s(&File, FullPath, "rb");

	if (!File)
		return;

	m_ObjList.clear();

	size_t	SceneModeType = 0;

	fread(&SceneModeType, sizeof(size_t), 1, File);

	// SceneMode 생성
	CSceneManager::GetInst()->CallCreateSceneMode(this, SceneModeType);

	size_t	ObjCount = m_ObjList.size();

	fread(&ObjCount, sizeof(size_t), 1, File);

	for (size_t i = 0; i < ObjCount; ++i)
	{
		size_t	ObjType = 0;
		fread(&ObjType, sizeof(size_t), 1, File);

		CGameObject* Obj = CSceneManager::GetInst()->CallCreateObject(this, ObjType);

		Obj->Load(File);
	}

	fclose(File);
}

bool CScene::SortRenderList(CSceneComponent* Src, CSceneComponent* Dest)
{
	SphereInfo	SrcInfo = Src->GetSphereInfoViewSpace();
	SphereInfo	DestInfo = Dest->GetSphereInfoViewSpace();

	return SrcInfo.Center.Length() - SrcInfo.Radius > DestInfo.Center.Length() - DestInfo.Radius;
}

bool CScene::SortColliderRenderList(CColliderBox3D* Src, CColliderBox3D* Dest)
{
	Box3DInfo SrcInfo = Src->GetBox3DInfoViewSpace();
	Box3DInfo DestInfo = Dest->GetBox3DInfoViewSpace();

	float SrcValue = SrcInfo.Center.Length() - SrcInfo.Length.x +
		SrcInfo.Center.Length() - SrcInfo.Length.y +
		SrcInfo.Center.Length() - SrcInfo.Length.z;
	float DestValue = DestInfo.Center.Length() - DestInfo.Length.x +
		DestInfo.Center.Length() - DestInfo.Length.y +
		DestInfo.Center.Length() - DestInfo.Length.z;


	return SrcValue > DestValue;
}
