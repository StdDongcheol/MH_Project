
#pragma once

#include "GameObject/GameObject.h"
#include "Component/CameraComponent.h"
#include "Component/Arm.h"

class CFlightCamera :
	public CGameObject
{
	friend class CScene;

protected:
	CFlightCamera();
	CFlightCamera(const CFlightCamera& obj);
	virtual ~CFlightCamera();

private:
	bool       m_UseCam;
	CSharedPtr<CCameraComponent>        m_Camera;
	CSharedPtr<CArm>                    m_Arm;
	class CIMGUIGizmo* m_Gizmo;

private:
	Vector2     m_MouseMove;
	POINT       m_CenterPoint;
	float       m_FlightSpeed;

public:
	void SetUseCam(bool Use)
	{
		m_UseCam = Use;
	}

	void SetCameraSpeed(float Speed)
	{
		m_FlightSpeed = Speed;
	}

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CFlightCamera* Clone();

private:
	void MoveFront(float DeltaTime);
	void MoveBack(float DeltaTime);
	void MoveLeft(float DeltaTime);
	void MoveRight(float DeltaTime);
	void MoveUp(float DeltaTime);
	void MoveDown(float DeltaTime);
	void RotationX(float DeltaTime);

};

