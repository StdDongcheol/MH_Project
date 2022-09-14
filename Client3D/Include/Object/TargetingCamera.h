
#pragma once

#include "GameObject/GameObject.h"
#include "Component/CameraComponent.h"
#include "Component/Arm.h"

class CTargetingCamera :
    public CGameObject
{
public:
    CTargetingCamera();
    virtual ~CTargetingCamera();

private:
    CSharedPtr<CCameraComponent>        m_Camera;
    CSharedPtr<CArm>                    m_Arm;
    CSharedPtr<CGameObject>             m_TargetObj;

private:
    std::string m_TargetSocketName;
    Vector3     m_TargetOffset;
    Vector3     m_TargetPos;
    Vector3     m_CamFixedPos;
    Vector3     m_Dir;
    float       m_CamDist;
    float       m_CamRotSpeed;
    float       m_MoveSpeed;
    float       m_CameraAliveTime;
    float       m_CameraAliveTimeAcc;
    bool        m_IsBossDeadCam;
    bool        m_RotateCamStart;

public:
    // ������ ������Ʈ�� ������ BoneSocket �̸��� �Է�.
    // ���� ī�޶� LootAt�ϴ� ����� BoneSocket�� Position.
    void SetLookAtTarget(CGameObject* Obj, const std::string& SocketName)
    {
        m_IsBossDeadCam = true;

        m_TargetObj = Obj;

        m_TargetSocketName = SocketName;
    }

    void SetLookAtTarget(Vector3 Pos, CGameObject* Obj)
    {
        m_TargetPos = Pos;

        m_TargetObj = Obj;

        Vector3 CamPos = GetWorldPos();

        //// �ǵ����̸� z�������� ���� �̰ݵǵ��� �ϱ����� �Ϻ� Offset����.
        //CamPos.x -= m_CamDist / 2.f;
        //CamPos.y -= m_CamDist / 2.f;

        Vector3 CamUpVector = GetRelativeAxis(AXIS::AXIS_Y);

        Matrix ViewMat;

        ViewMat.m = XMMatrixLookAtLH(CamPos.Convert(), m_TargetPos.Convert(), CamUpVector.Convert());

        if (m_Camera)
        {
            m_Camera->SetViewMatrix(ViewMat);
        }
    }

    // �⺻ �����ð� 4��
    void SetAliveTime(float Time)
    {
        m_CameraAliveTime = Time;
    }
    
    // LookAt Target�� Offset����
    void SetLootAtOffset(Vector3 Offset)
    {
        m_TargetOffset = Offset;
    }
    
    // ��ġ�� CameraPos�κ��� Offset����
    // �⺻ Distance �� 15.f
    void SetCameraDistance(float Dist)
    {
        m_CamDist = Dist;
    }

    // �⺻�ӵ� 2.f.
    void SetMoveSpeed(float Speed)
    {
        m_MoveSpeed = Speed;
    }

    // Zero ���ͼ�����, �������� ����.
    void SetMoveDir(Vector3 Dir)
    {
        m_Dir = Dir;
    }

    void SetCameraFixedPos(Vector3 Pos)
    {
        m_CamFixedPos = Pos;
    }
   
    // ī�޶� Rotation �����ϸ� FadeOut Eventȣ��.
    void RotationStart();


public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render();

private:
    void LookAt(float DeltaTime);
    void Move(float DeltaTime);

};

