#include "ColliderBox3D.h"
#include "../Collision/Collision.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Resource/Shader/ColliderConstantBuffer.h"
#include "../Scene/Scene.h"
#include "../Scene/CameraManager.h"
#include "CameraComponent.h"

CColliderBox3D::CColliderBox3D()
{
	SetTypeID<CColliderBox3D>();
	m_ComponentType = Component_Type::SceneComponent;
	m_Render = true;

	m_ColliderType = Collider_Type::Box3D;
}

CColliderBox3D::CColliderBox3D(const CColliderBox3D& com) :
	CColliderComponent(com)
{
	m_Info = com.m_Info;
}

CColliderBox3D::~CColliderBox3D()
{
}

Box3DInfo CColliderBox3D::GetBox3DInfoViewSpace() const
{
	Box3DInfo	Info = {};

	CCameraComponent* Camera = m_Scene->GetCameraManager()->GetCurrentCamera();

	Info.Center = m_Info.Center;
	Info.Center = Info.Center.TransformCoord(Camera->GetViewMatrix()); Vector3 Pos[8] = {};
	Info.Length = m_Info.Length;

	// 센터를 중심으로 각 꼭지점의 위치를 설정한다.
	Pos[0] = Info.Center - m_Info.Axis[0] * m_Info.Length.x + m_Info.Axis[1] * m_Info.Length.y - m_Info.Axis[2] * m_Info.Length.z;
	Pos[1] = Info.Center + m_Info.Axis[0] * m_Info.Length.x + m_Info.Axis[1] * m_Info.Length.y - m_Info.Axis[2] * m_Info.Length.z;
	Pos[2] = Info.Center - m_Info.Axis[0] * m_Info.Length.x - m_Info.Axis[1] * m_Info.Length.y - m_Info.Axis[2] * m_Info.Length.z;
	Pos[3] = Info.Center + m_Info.Axis[0] * m_Info.Length.x - m_Info.Axis[1] * m_Info.Length.y - m_Info.Axis[2] * m_Info.Length.z;

	Pos[4] = Info.Center - m_Info.Axis[0] * m_Info.Length.x + m_Info.Axis[1] * m_Info.Length.y + m_Info.Axis[2] * m_Info.Length.z;
	Pos[5] = Info.Center + m_Info.Axis[0] * m_Info.Length.x + m_Info.Axis[1] * m_Info.Length.y + m_Info.Axis[2] * m_Info.Length.z;
	Pos[6] = Info.Center - m_Info.Axis[0] * m_Info.Length.x - m_Info.Axis[1] * m_Info.Length.y + m_Info.Axis[2] * m_Info.Length.z;
	Pos[7] = Info.Center + m_Info.Axis[0] * m_Info.Length.x - m_Info.Axis[1] * m_Info.Length.y + m_Info.Axis[2] * m_Info.Length.z;

	// 일단 기본적으로 Pos[0]으로 대입을 한다
	Info.Min.x = Pos[0].x;
	Info.Min.y = Pos[0].y;
	Info.Min.z = Pos[0].z;

	Info.Max.x = Pos[0].x;
	Info.Max.y = Pos[0].y;
	Info.Max.z = Pos[0].z;

	// Pos[0]은 위에서 대입했으니
	// 나머지 값의 포문을 돌면서 해당하는 값으로 저장한다.
	for (int i = 1; i < 8; ++i)
	{
		if (Info.Min.x > Pos[i].x)
			Info.Min.x = Pos[i].x;

		if (Info.Min.y > Pos[i].y)
			Info.Min.y = Pos[i].y;

		if (Info.Min.z > Pos[i].z)
			Info.Min.z = Pos[i].z;

		if (Info.Max.x < Pos[i].x)
			Info.Max.x = Pos[i].x;

		if (Info.Max.y < Pos[i].y)
			Info.Max.y = Pos[i].y;

		if (Info.Max.z < Pos[i].z)
			Info.Max.z = Pos[i].z;
	}

	return Info;
}

void CColliderBox3D::Start()
{
	CColliderComponent::Start();
}

bool CColliderBox3D::Init()
{
	if (!CColliderComponent::Init())
		return false;

	m_Info.Axis[0] = Vector3(1.f, 0.f, 0.f);
	m_Info.Axis[1] = Vector3(0.f, 1.f, 0.f);
	m_Info.Axis[2] = Vector3(0.f, 0.f, 1.f);

	//m_Info.Length = Vector3(50.f, 50.f, 50.f);

	// 충돌체박스는 무조건 부모의 z회전에 영향을 받아야한다.
	SetInheritRotX(true);
	SetInheritRotY(true);
	SetInheritRotZ(true);

	m_Mesh = m_Scene->GetResource()->FindMesh("Box3DLinePos");

	return true;
}

void CColliderBox3D::Update(float DeltaTime)
{
	CColliderComponent::Update(DeltaTime);
}

void CColliderBox3D::PostUpdate(float DeltaTime)
{
	CColliderComponent::PostUpdate(DeltaTime);

	if (GetTransform()->GetSocket())
	{
		m_Info.Center.x = GetTransform()->GetSocketPos().x;
		m_Info.Center.y = GetTransform()->GetSocketPos().y;
		m_Info.Center.z = GetTransform()->GetSocketPos().z;
	}
	else
	{
		m_Info.Center.x = GetWorldPos().x + m_Offset.x;
		m_Info.Center.y = GetWorldPos().y + m_Offset.y;
		m_Info.Center.z = GetWorldPos().z + m_Offset.z;
	}

	// X축
	m_Info.Axis[0] = GetWorldAxis(AXIS_X);
	// Y축
	m_Info.Axis[1] = GetWorldAxis(AXIS_Y);
	// Z축
	m_Info.Axis[2] = GetWorldAxis(AXIS_Z);

	//Vector3 Pos[8] = {};

	// 센터를 중심으로 각 꼭지점의 위치를 설정한다.
	m_Info.Pos[0] = m_Info.Center - m_Info.Axis[0] * m_Info.Length.x + m_Info.Axis[1] * m_Info.Length.y - m_Info.Axis[2] * m_Info.Length.z;
	m_Info.Pos[1] = m_Info.Center + m_Info.Axis[0] * m_Info.Length.x + m_Info.Axis[1] * m_Info.Length.y - m_Info.Axis[2] * m_Info.Length.z;
	m_Info.Pos[2] = m_Info.Center - m_Info.Axis[0] * m_Info.Length.x - m_Info.Axis[1] * m_Info.Length.y - m_Info.Axis[2] * m_Info.Length.z;
	m_Info.Pos[3] = m_Info.Center + m_Info.Axis[0] * m_Info.Length.x - m_Info.Axis[1] * m_Info.Length.y - m_Info.Axis[2] * m_Info.Length.z;

	m_Info.Pos[4] = m_Info.Center - m_Info.Axis[0] * m_Info.Length.x + m_Info.Axis[1] * m_Info.Length.y + m_Info.Axis[2] * m_Info.Length.z;
	m_Info.Pos[5] = m_Info.Center + m_Info.Axis[0] * m_Info.Length.x + m_Info.Axis[1] * m_Info.Length.y + m_Info.Axis[2] * m_Info.Length.z;
	m_Info.Pos[6] = m_Info.Center - m_Info.Axis[0] * m_Info.Length.x - m_Info.Axis[1] * m_Info.Length.y + m_Info.Axis[2] * m_Info.Length.z;
	m_Info.Pos[7] = m_Info.Center + m_Info.Axis[0] * m_Info.Length.x - m_Info.Axis[1] * m_Info.Length.y + m_Info.Axis[2] * m_Info.Length.z;
	
	/*m_Info.LeftNormal = XMPlaneFromPoints(m_Info.Pos[4].Convert(), m_Info.Pos[0].Convert(),
		m_Info.Pos[2].Convert());

	m_Info.RightNormal = XMPlaneFromPoints(m_Info.Pos[1].Convert(), m_Info.Pos[5].Convert(),
		m_Info.Pos[7].Convert());

	m_Info.NearNormal = XMPlaneFromPoints(m_Info.Pos[0].Convert(), m_Info.Pos[1].Convert(),
		m_Info.Pos[3].Convert());

	m_Info.FarNormal = XMPlaneFromPoints(m_Info.Pos[5].Convert(), m_Info.Pos[4].Convert(),
		m_Info.Pos[6].Convert());

	m_Info.BottomNormal = XMPlaneFromPoints(m_Info.Pos[2].Convert(), m_Info.Pos[3].Convert(),
		m_Info.Pos[7].Convert());

	m_Info.TopNormal = XMPlaneFromPoints(m_Info.Pos[4].Convert(), m_Info.Pos[5].Convert(),
		m_Info.Pos[1].Convert());*/

	if ((m_Info.Length.x == m_Info.Length.y) && (m_Info.Length.y == m_Info.Length.z))
	{
		m_Info.LeftNormal = XMPlaneFromPoints(m_Info.Pos[4].Convert(), m_Info.Pos[0].Convert(),
			m_Info.Pos[2].Convert());

		m_Info.RightNormal = XMPlaneFromPoints(m_Info.Pos[1].Convert(), m_Info.Pos[5].Convert(),
			m_Info.Pos[7].Convert());

		m_Info.NearNormal = XMPlaneFromPoints(m_Info.Pos[0].Convert(), m_Info.Pos[1].Convert(),
			m_Info.Pos[3].Convert());

		m_Info.FarNormal = XMPlaneFromPoints(m_Info.Pos[5].Convert(), m_Info.Pos[4].Convert(),
			m_Info.Pos[6].Convert());

		m_Info.BottomNormal = XMPlaneFromPoints(m_Info.Pos[2].Convert(), m_Info.Pos[3].Convert(),
			m_Info.Pos[7].Convert());

		m_Info.TopNormal = XMPlaneFromPoints(m_Info.Pos[4].Convert(), m_Info.Pos[5].Convert(),
			m_Info.Pos[1].Convert());
	}
	else
	{
		Vector3 Dir1 = m_Info.Pos[1] - m_Info.Pos[0];
		Vector3 Dir2 = m_Info.Pos[2] - m_Info.Pos[0];

		Dir1.Normalize();
		Dir2.Normalize();

		m_Info.NearNormal = Dir1.Cross(Dir2);

		Dir1 = m_Info.Pos[4] - m_Info.Pos[5];
		Dir2 = m_Info.Pos[7] - m_Info.Pos[5];

		Dir1.Normalize();
		Dir2.Normalize();

		m_Info.FarNormal = Dir1.Cross(Dir2);

		Dir1 = m_Info.Pos[0] - m_Info.Pos[4];
		Dir2 = m_Info.Pos[6] - m_Info.Pos[4];

		Dir1.Normalize();
		Dir2.Normalize();

		m_Info.LeftNormal = Dir1.Cross(Dir2);

		Dir1 = m_Info.Pos[5] - m_Info.Pos[1];
		Dir2 = m_Info.Pos[3] - m_Info.Pos[1];

		Dir1.Normalize();
		Dir2.Normalize();

		m_Info.RightNormal = Dir1.Cross(Dir2);

		Dir1 = m_Info.Pos[3] - m_Info.Pos[2];
		Dir2 = m_Info.Pos[6] - m_Info.Pos[2];

		Dir1.Normalize();
		Dir2.Normalize();

		m_Info.BottomNormal = Dir1.Cross(Dir2);

		Dir1 = m_Info.Pos[5] - m_Info.Pos[4];
		Dir2 = m_Info.Pos[0] - m_Info.Pos[4];

		Dir1.Normalize();
		Dir2.Normalize();

		m_Info.TopNormal = Dir1.Cross(Dir2);

		ResultNormalVec(m_Info.NearNormal);

		ResultNormalVec(m_Info.FarNormal);

		ResultNormalVec(m_Info.LeftNormal);

		ResultNormalVec(m_Info.RightNormal);

		ResultNormalVec(m_Info.BottomNormal);

		ResultNormalVec(m_Info.TopNormal);
	}
	

	// 일단 기본적으로 Pos[0]으로 대입을 한다
	m_Min.x = m_Info.Pos[0].x;
	m_Min.y = m_Info.Pos[0].y;
	m_Min.z = m_Info.Pos[0].z;

	m_Max.x = m_Info.Pos[0].x;
	m_Max.y = m_Info.Pos[0].y;
	m_Max.z = m_Info.Pos[0].z;

	// Pos[0]은 위에서 대입했으니
	// 나머지 값의 포문을 돌면서 해당하는 값으로 저장한다.
	for (int i = 1; i < 8; ++i)
	{
		if (m_Min.x > m_Info.Pos[i].x)
			m_Min.x = m_Info.Pos[i].x;

		if (m_Min.y > m_Info.Pos[i].y)
			m_Min.y = m_Info.Pos[i].y;

		if (m_Min.z > m_Info.Pos[i].z)
			m_Min.z = m_Info.Pos[i].z;

		if (m_Max.x < m_Info.Pos[i].x)
			m_Max.x = m_Info.Pos[i].x;

		if (m_Max.y < m_Info.Pos[i].y)
			m_Max.y = m_Info.Pos[i].y;

		if (m_Max.z < m_Info.Pos[i].z)
			m_Max.z = m_Info.Pos[i].z;
	}

	// 해당 값을 찾았으면 Info에 값을 저장한다.
	m_Info.Min.x = m_Min.x;
	m_Info.Min.y = m_Min.y;
	m_Info.Min.z = m_Min.z;

	m_Info.Max.x = m_Max.x;
	m_Info.Max.y = m_Max.y;
	m_Info.Max.z = m_Max.z;

	if ((m_Info.Length.x == m_Info.Length.y) &&
		(m_Info.Length.y == m_Info.Length.z))
	{
		m_Info.BoxType = Box_Type::Cube;
	}
	else
	{
		m_Info.BoxType = Box_Type::Cuboid;
	}
}

void CColliderBox3D::PrevRender()
{
	CColliderComponent::PrevRender();
}

void CColliderBox3D::Render()
{
	CColliderComponent::Render();

	CCameraComponent* Camera = m_Scene->GetCameraManager()->GetCurrentCamera();

	Matrix matWorld, matView, matProj, matWVP;

	matView = Camera->GetViewMatrix();
	matProj = Camera->GetProjMatrix();

	Matrix matScale, matRot, matTrans;

	matScale.Scaling(m_Info.Length * 2.f);
	matRot.Rotation(GetWorldRot());
	matTrans.Translation(m_Info.Center);

	matWorld = matScale * matRot * matTrans;

	matWVP = matWorld * matView * matProj;

	matWVP.Transpose();

	m_CBuffer->SetWVP(matWVP);

	if (m_PrevCollisionList.empty())
		m_CBuffer->SetColliderColor(Vector4(0.f, 1.f, 0.f, 1.f));

	else
		m_CBuffer->SetColliderColor(Vector4(1.f, 0.f, 0.f, 1.f));

	if (m_MouseCollision)
		m_CBuffer->SetColliderColor(Vector4(1.f, 0.f, 0.f, 1.f));

	m_CBuffer->UpdateCBuffer();

	m_Shader->SetShader();

	if (IsEnable())
		m_Mesh->Render();
}

void CColliderBox3D::PostRender()
{
	CColliderComponent::PostRender();
}

CColliderBox3D* CColliderBox3D::Clone()
{
	return new CColliderBox3D(*this);
}

void CColliderBox3D::Save(FILE* File)
{
	CColliderComponent::Save(File);

	fwrite(&m_Info, sizeof(Box3DInfo), 1, File);
}

void CColliderBox3D::Load(FILE* File)
{
	CColliderComponent::Load(File);

	fread(&m_Info, sizeof(Box3DInfo), 1, File);

	m_Mesh = m_Scene->GetResource()->FindMesh("Box3DLinePos");
}

bool CColliderBox3D::Collision(CColliderComponent* Dest)
{
	switch (Dest->GetColliderType())
	{
	case Collider_Type::Box3D:
		return CCollision::CollisionBox3DToBox3D(this, (CColliderBox3D*)Dest);
		break;
	}

	return false;
}

bool CColliderBox3D::CollisionMouse(const Vector2& MousePos)
{
	return m_MouseCollision;
}

bool CColliderBox3D::CollisionRay(const Ray& ray)
{
	return false;
}

void CColliderBox3D::ResultNormalVec(Vector3& NormalVec)
{
	if (NormalVec.x > 1.f && NormalVec.x < -1.f)
	{
		NormalVec.x = 0.f;
	}

	if (NormalVec.y > 1.f && NormalVec.y < -1.f)
	{
		NormalVec.y = 0.f;
	}

	if (NormalVec.z > 1.f && NormalVec.z < -1.f)
	{
		NormalVec.z = 0.f;
	}
}
