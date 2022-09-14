
#include "LandScapeObj.h"
#include "Engine.h"
#include "Input.h"
#include "Scene/Scene.h"
#include "Scene/Navigation3DManager.h"
#include "Component/LandScape.h"
#include "Component/CameraComponent.h"
#include "../../EditorManager.h"
#include "../../EditorManager.h"
#include "../../Scene/EditorScene.h"
#include "../../Window/InfoWindow.h"
#include "../../Window/ObjectWindow.h"

CLandScapeObj::CLandScapeObj()	:
	m_CountX(100),
	m_CountZ(100),
	m_First(false)
{
	SetTypeID<CLandScapeObj>();
}

CLandScapeObj::CLandScapeObj(const CLandScapeObj& obj) :
	CGameObject(obj)
{
	m_LandScape	 = (CLandScape*)FindComponent("LandScape");

	m_CountX = obj.m_CountX;
	m_CountZ = obj.m_CountZ;

	m_First = false;
}

CLandScapeObj::~CLandScapeObj()
{
}

void CLandScapeObj::Start()
{
	CGameObject::Start();
}

bool CLandScapeObj::Init()
{
	m_LandScape = CreateComponent<CLandScape>("LandScape");
	m_LandScape->AddMaterial("LandScape");
	m_LandScape->SetDetailLevel(30.f);
	m_LandScape->SetSplatCount(4);

	return true;
}

void CLandScapeObj::Update(float DeltaTime)
{
	if (!m_First)
	{
		m_First = true;

		m_LandScape->CreateLandScape("LandScape", m_CountX, m_CountZ);

		SetNavData();
	}

	CGameObject::Update(DeltaTime);

	CEditorManager::GetInst()->GetInfoWindow()->SetDDTPos(m_LandScape->GetDDTPos());
}

void CLandScapeObj::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CLandScapeObj* CLandScapeObj::Clone()
{
	return DBG_NEW CLandScapeObj(*this);
}

void CLandScapeObj::Save(FILE* File)
{
	fwrite(&m_CountX, sizeof(int), 1, File);
	fwrite(&m_CountZ, sizeof(int), 1, File);

	m_LandScape->Save(File);
}

void CLandScapeObj::Load(FILE* File)
{
	fread(&m_CountX, sizeof(int), 1, File);
	fread(&m_CountZ, sizeof(int), 1, File);

	m_LandScape->Load(File);

	m_First = true;
}

void CLandScapeObj::ReleaseMesh()
{
	m_LandScape->ReleaseMesh();
}

Vector3 CLandScapeObj::GetDDTPos() const
{
	if (m_LandScape)
		return m_LandScape->GetDDTPos();

	return Vector3();
}

void CLandScapeObj::SelectMap(int Map)
{
	if (m_LandScape)
		m_LandScape->SelectMap(Map);
}

void CLandScapeObj::SetBrushType(int Type)
{
	if (m_LandScape)
		m_LandScape->SetBrushType(Type);
}

void CLandScapeObj::SetBrushType(Brush_Type Type)
{
	if (m_LandScape)
		m_LandScape->SetBrushType(Type);
}

void CLandScapeObj::SetBrushLocation(const Vector3& Location)
{
	if (m_LandScape)
		m_LandScape->SetBrushLocation(Location);
}

void CLandScapeObj::SetBrushRange(float Range)
{
	if (m_LandScape)
		m_LandScape->SetBrushRange(Range);
}

void CLandScapeObj::SetBrushColor(const Vector3& Color)
{
	if (m_LandScape)
		m_LandScape->SetBrushColor(Color);
}

int CLandScapeObj::GetBrushType() const
{
	if (m_LandScape)
		return m_LandScape->GetBrushType();

	return -1;
}

Vector3 CLandScapeObj::GetBrushLocation() const
{
	if (m_LandScape)
		return m_LandScape->GetBrushLocation();

	return Vector3();
}

float CLandScapeObj::GetBrushRange() const
{
	if (m_LandScape)
		return m_LandScape->GetBrushRange();

	return 0.0f;
}

Vector3 CLandScapeObj::GetBrushColor() const
{
	if (m_LandScape)
		return m_LandScape->GetBrushColor();

	return Vector3();
}

void CLandScapeObj::PlayBrush(float DeltaTime, bool Up)
{
	if (m_LandScape)
		m_LandScape->PlayBrush(DeltaTime, Up);
}

void CLandScapeObj::PlaySplatting(float DeltaTime, bool Draw, int TypeNumb)
{
	if (m_LandScape)
		m_LandScape->PlaySplatting(DeltaTime, Draw, TypeNumb);
}

void CLandScapeObj::SetNavData()
{
	m_Scene->GetNavigation3DManager()->SetNavData(m_LandScape);
}
