
#include "CameraComponent.h"
#include "../Device.h"
#include "Frustum.h"
#include "../Scene/Scene.h"
#include "../Scene/LightManager.h"
#include "LightComponent.h"
#include "../Render/RenderManager.h"
#include "Arm.h"

CCameraComponent::CCameraComponent()
{
	SetTypeID<CCameraComponent>();
	m_Render = false;

	m_CameraType = Camera_Type::Camera3D;
	m_ViewAngle = 90.f;
	m_Distance = 1000.f;

	m_Frustum = DBG_NEW CFrustum;

	m_CamShake = false;
	m_ShakeTime = 1.f;
	m_ShakeTimeAcc = 0.f;
	m_ShakeStrength = 1.f;
	m_ShakeLength = 0.00001f;
	m_TargetMode = false;
}

CCameraComponent::CCameraComponent(const CCameraComponent& com) :
	CSceneComponent(com)
{
	m_CameraType = com.m_CameraType;
	m_matView = com.m_matView;
	m_matProj = com.m_matProj;
	m_ViewAngle = com.m_ViewAngle;
	m_Distance = com.m_Distance;
	m_RS = com.m_RS;

	m_Frustum = DBG_NEW CFrustum;
}

CCameraComponent::~CCameraComponent()
{
	SAFE_DELETE(m_Frustum);
}

void CCameraComponent::CreateProjectionMatrix()
{
	switch (m_CameraType)
	{
	case Camera_Type::Camera2D:
		m_matProj = XMMatrixOrthographicOffCenterLH(0.f, (float)m_RS.Width, 0.f, (float)m_RS.Height, 0.f, 1000.f);
		break;
	case Camera_Type::Camera3D:
		m_matProj = XMMatrixPerspectiveFovLH(DegreeToRadian(m_ViewAngle),
			m_RS.Width / (float)m_RS.Height, 0.1f, m_Distance);
		break;
	case Camera_Type::CameraUI:
		m_matProj = XMMatrixOrthographicOffCenterLH(0.f, (float)m_RS.Width, 0.f, (float)m_RS.Height, 0.f, 1000.f);
		break;
	}
	
	m_matShadowProj = XMMatrixPerspectiveFovLH(DegreeToRadian(m_ViewAngle),
		SHADOWMAP_WIDTH / SHADOWMAP_HEIGHT, 0.1f, m_Distance);
	//m_matShadowProj = XMMatrixOrthographicLH((float)m_RS.Width, (float)m_RS.Height, 0.f, 1000.f);
}

bool CCameraComponent::FrustumInPoint(const Vector3& Point)
{
	return m_Frustum->FrustumInPoint(Point);
}

bool CCameraComponent::FrustumInSphere(const SphereInfo& Sphere)
{
	return m_Frustum->FrustumInSphere(Sphere);
}

void CCameraComponent::ComputeShadowView()
{
	if (!m_Parent)
		return;

	CLightComponent* GlobalLight = m_Scene->GetLightManager()->GetGlobalLightComponent();

	m_matShadowView.Identity();

	for (int i = 0; i < AXIS_MAX; ++i)
	{
		Vector3	Axis = GlobalLight->GetWorldAxis((AXIS)i);
		memcpy(&m_matShadowView[i][0], &Axis, sizeof(Vector3));
	}

	m_matShadowView.Transpose();

	Vector3	TargetPos;

	if (m_Parent->CheckType<CArm>())
	{
		CArm* Parent = (CArm*)m_Parent;

		TargetPos = GetWorldPos() + GetWorldAxis(AXIS_Z) * Parent->GetTargetDistance();
	}

	float ShadowLightDistance = CRenderManager::GetInst()->GetShadowLightDistance();

	Vector3	Pos = TargetPos - GlobalLight->GetWorldAxis(AXIS_Z) * ShadowLightDistance;

	Pos *= -1.f;

	for (int i = 0; i < AXIS_MAX; ++i)
	{
		Vector3	Axis = GlobalLight->GetWorldAxis((AXIS)i);

		m_matShadowView[3][i] = Pos.Dot(Axis);
	}
}

void CCameraComponent::Start()
{
	CSceneComponent::Start();

	CreateProjectionMatrix();

	// m_TargetMode???? ?????????? ???? ViewMat???? ?????? ????.
	if (m_TargetMode)
	{
		for (int i = 0; i < AXIS_MAX; ++i)
		{
			Vector3	Axis = GetWorldAxis((AXIS)i);
			memcpy(&m_matView[i][0], &Axis, sizeof(Vector3));
		}

		m_matView.Transpose();

		Vector3	Pos = GetWorldPos() * -1.f;

		for (int i = 0; i < AXIS_MAX; ++i)
		{
			Vector3	Axis = GetWorldAxis((AXIS)i);

			m_matView[3][i] = Pos.Dot(Axis);
		}

		m_Frustum->Update(m_matView * m_matProj);
	}
}

bool CCameraComponent::Init()
{
	m_RS = CDevice::GetInst()->GetResolution();

	return true;
}

void CCameraComponent::Update(float DeltaTime)
{
	CSceneComponent::Update(DeltaTime);

	/*
	???????? ?????????? ?????? ???? ???????? ???????? x, y, z ???? ?????? ???? ????????
	????. ??, ???? x : 1, 0, 0  y : 0, 1, 0  z : 0, 0, 1 ?? ?????? ?????? ??????.
	???????? : ?????? ???????? 3???? ???? ???? ?????? ???? ?????? ???? ?????? ??????.
	1 0 0
	0 1 0
	0 0 1

	?????????? ???? ?????? ???????? ????.

	?????? X?? * ?????? = 1, 0, 0
	?????? y?? * ?????? = 0, 1, 0
	?????? z?? * ?????? = 0, 0, 1
	x, y, z   0 0 0   1 0 0
	x, y, z * 0 0 0 = 0 1 0
	x, y, z	  0 0 0   0 0 1

	???? ???? ????
	Xx Yx Zx 0
	Xy Yy Zy 0
	Xz Yz Zz 0
	0  0  0  1

	???? ???? ????
	1   0  0 0
	0   1  0 0
	0   0  1 0
	-x -y -z 1

	1   0  0 0   Xx Yx Zx 0
	0   1  0 0 * Xy Yy Zy 0
	0   0  1 0   Xz Yz Zz 0
	-x -y -z 1   0  0  0  1

	???? ?? ????
	Xx    Yx   Zx  0
	Xy    Yy   Zy  0
	Xz    Yz   Zz  0
	-X.P -Y.P -Z.P 1
	*/
}

void CCameraComponent::PostUpdate(float DeltaTime)
{
	CSceneComponent::PostUpdate(DeltaTime);

	if (m_TargetMode)
		return;

	m_matView.Identity();


	/*
	i?? 0????
	Xx Xy Xz 0
	0  1  0  0
	0  0  1  0
	0  0  0  1

	i?? 1????
	Xx Xy Xz 0
	Yx Yy Yz 0
	0  0  1  0
	0  0  0  1

	i?? 2????
	Xx Xy Xz 0
	Yx Yy Yz 0
	Zx Zy Zz 0
	0  0  0  1
	*/
	for (int i = 0; i < AXIS_MAX; ++i)
	{
		Vector3	Axis = GetWorldAxis((AXIS)i);
		memcpy(&m_matView[i][0], &Axis, sizeof(Vector3));
	}

	/*
	Xx Xy Xz 0
	Yx Yy Yz 0
	Zx Zy Zz 0
	0  0  0  1

	????????
	Xx Yx Zx 0
	Xy Yy Zy 0
	Xz Yz Zz 0
	0  0  0  1
	*/
	m_matView.Transpose();

	// ?????????? ??????, 
	if (m_CamShake)
	{
		m_ShakeTimeAcc += DeltaTime;

		m_OriginPos = GetWorldPos() * -1.f;

		float Radian = 0.f;

		if (m_LerpStrength)
		{
			m_ShakeLengthAcc += m_ShakeLength * DeltaTime;

			// DeltaTime?? ???????? m_ShakeStrength?? ?????? ?????? ???? ??????.
			// 0.1f???? DeltaTime?? ????.
			m_ShakeStrength += 0.1f * DeltaTime;

			// DeltaTime?? ???????? m_ShakeLengthAcc ?? ?????? ?????? ????.
			Radian = cosf(DegreeToRadian(m_ShakeTimeAcc * m_ShakeLengthAcc));
		}

		else
		{			
			// ?????? m_ShakeLength ?? ?????? ?????? ????.
			Radian = cosf(DegreeToRadian(m_ShakeTimeAcc * m_ShakeLength));
		}

		Vector3 ShakePos = Vector3(m_OriginPos.x, 
			m_OriginPos.y + Radian * m_ShakeStrength, m_OriginPos.z);

		if (m_ShakeTimeAcc >= m_ShakeTime)
		{
			m_ShakeTimeAcc = 0.f;
			m_CamShake = false;
		}

		for (int i = 0; i < AXIS_MAX; ++i)
		{
			Vector3	Axis = GetWorldAxis((AXIS)i);

			m_matView[3][i] = ShakePos.Dot(Axis);
		}

		m_Frustum->Update(m_matView * m_matProj);

		if (m_ShakeTimeAcc >= m_ShakeTime)
		{
			m_ShakeTimeAcc = 0.f;
			m_CamShake = false;
		}
	}

	// ???? ???? ??????
	else
	{
		Vector3	Pos = GetWorldPos() * -1.f;

		/*
		Xx    Yx   Zx  0
		Xy    Yy   Zy  0
		Xz    Yz   Zz  0
		-X.P -Y.P -Z.P 1
		*/
		for (int i = 0; i < AXIS_MAX; ++i)
		{
			Vector3	Axis = GetWorldAxis((AXIS)i);

			m_matView[3][i] = Pos.Dot(Axis);
		}

		m_Frustum->Update(m_matView * m_matProj);
	}
}

void CCameraComponent::PrevRender()
{
	CSceneComponent::PrevRender();
}

void CCameraComponent::Render()
{
	CSceneComponent::Render();
}

void CCameraComponent::PostRender()
{
	CSceneComponent::PostRender();
}

CCameraComponent* CCameraComponent::Clone()
{
	return new CCameraComponent(*this);
}

void CCameraComponent::Save(FILE* File)
{
	fwrite(&m_CameraType, sizeof(Camera_Type), 1, File);
	fwrite(&m_matView, sizeof(Matrix), 1, File);
	fwrite(&m_matProj, sizeof(Matrix), 1, File);
	fwrite(&m_ViewAngle, sizeof(float), 1, File);
	fwrite(&m_Distance, sizeof(float), 1, File);
	fwrite(&m_RS, sizeof(Resolution), 1, File);

	CSceneComponent::Save(File);
}

void CCameraComponent::Load(FILE* File)
{
	fread(&m_CameraType, sizeof(Camera_Type), 1, File);
	fread(&m_matView, sizeof(Matrix), 1, File);
	fread(&m_matProj, sizeof(Matrix), 1, File);
	fread(&m_ViewAngle, sizeof(float), 1, File);
	fread(&m_Distance, sizeof(float), 1, File);
	fread(&m_RS, sizeof(Resolution), 1, File);

	CSceneComponent::Load(File);
}
