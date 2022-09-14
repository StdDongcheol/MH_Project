#pragma once

#include "SceneComponent.h"

class CCameraComponent :
	public CSceneComponent
{
	friend class CGameObject;
	friend class CCameraManager;

protected:
	CCameraComponent();
	CCameraComponent(const CCameraComponent& com);
	virtual ~CCameraComponent();

protected:
	Camera_Type m_CameraType;
	Matrix      m_matView;
	Matrix      m_matProj;
	Matrix      m_matShadowView;
	Matrix      m_matShadowProj;
	float		m_ViewAngle;
	float		m_Distance;
	Resolution	m_RS;
	Vector2		m_Ratio;
	class CFrustum* m_Frustum;

private:
	bool		m_LerpStrength;
	bool		m_CamShake;
	float		m_ShakeTime;
	float		m_ShakeTimeAcc;
	float		m_ShakeStrength;
	float		m_ShakeStrengthAcc;
	float		m_ShakeLength;
	float		m_ShakeLengthAcc;
	Vector3		m_OriginPos;

private:
	bool		m_TargetMode;

public:
	Resolution GetResolution()	const
	{
		return m_RS;
	}

	Camera_Type GetCameraType()	const
	{
		return m_CameraType;
	}

	Matrix GetViewMatrix()	const
	{
		return m_matView;
	}

	Matrix GetProjMatrix()	const
	{
		return m_matProj;
	}

	Matrix GetShadowViewMatrix()	const
	{
		return m_matShadowView;
	}

	Matrix GetShadowProjMatrix()	const
	{
		return m_matShadowProj;
	}

	Vector2 GetLeftBottom()	const
	{
		Vector2	LB;

		LB.x = GetWorldPos().x;// - m_Ratio.x * m_RS.Width;
		LB.y = GetWorldPos().y;// - m_Ratio.y * m_RS.Height;

		return LB;
	}

public:
	void SetViewMatrix(const Matrix& mat)
	{
		m_matView = mat;
	}

	void SetProjMatrix(const Matrix& mat)
	{
		m_matProj = mat;
	}

	void SetViewAngle(float Angle)
	{
		m_ViewAngle = Angle;

		if (m_CameraType == Camera_Type::Camera3D)
			CreateProjectionMatrix();
	}

	void SetDistance(float Distance)
	{
		m_Distance = Distance;

		CreateProjectionMatrix();
	}

	void SetCameraType(Camera_Type Type)
	{
		m_CameraType = Type;

		CreateProjectionMatrix();
	}

	// 2D 전용
	void OnViewportCenter()
	{
		if (m_CameraType == Camera_Type::Camera2D)
		{
			float	z = GetRelativePos().z;
			SetRelativePos(m_RS.Width / -2.f, m_RS.Height / -2.f, z);

			m_Ratio.x = 0.5f;
			m_Ratio.y = 0.5f;
		}
	}

	// 2D 전용
	void SetViewportRatio(float x, float y)
	{
		if (m_CameraType == Camera_Type::Camera2D)
		{
			float	z = GetRelativePos().z;
			SetRelativePos(m_RS.Width * -x, m_RS.Height * -y, z);

			m_Ratio.x = x;
			m_Ratio.y = y;
		}
	}

	// 카메라 쉐이크 효과 시작.
	void ShakeOn(float Strength = 0.1f, float Time = 1.f, bool StrengthOn = false)
	{
		if (StrengthOn)
		{
			m_ShakeLength = 2000.f;
			m_LerpStrength = true;
		}

		m_ShakeStrength = Strength;
		m_ShakeTime = Time;
		m_CamShake = true;
	}

	// 카메라 강도 효과 시작.
	void SetStrengthOn()
	{
		m_ShakeTime = 4.f;
		m_ShakeStrength = 0.0001f;
		m_ShakeLength = 2000.f;
		m_LerpStrength = true;
	}

	// 카메라 쉐이크 시간 설정. (초 단위)
	void SetShakeTime(float Time)
	{
		m_ShakeTime = Time;
	}

	// 값 올릴수록 진동 흔들리는 범위가 넓어짐.
	void SetShakeStrength(float Strength = 1.f)
	{
		m_ShakeStrength = Strength;
	}

	// 값 올릴수록 진동하는 횟수가 줄어듦.
	void SetShakeLength(float Length = 0.00001f)
	{
		m_ShakeLength = Length;
	}
	
	// 타겟 추적상태로 전환
	void SetTargetMode(bool	bEnable)
	{
		m_TargetMode = bEnable;
	}

private:
	void CreateProjectionMatrix();

public:
	bool FrustumInPoint(const Vector3& Point);
	bool FrustumInSphere(const SphereInfo& Sphere);

public:
	void ComputeShadowView();


public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void PrevRender();
	virtual void Render();
	virtual void PostRender();
	virtual CCameraComponent* Clone();
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);
};

