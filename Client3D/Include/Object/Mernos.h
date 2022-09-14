

#pragma once

#include "../Object/Monster.h"
#include "Component/StaticMeshComponent.h"
#include "Component/AnimationMeshComponent.h"
#include "Component/ColliderBox3D.h"
#include "FSM.h"

class CMernos :
    public CMonster
{
    friend class CScene;

protected:
    CMernos();
    CMernos(const CMernos& obj);
    virtual ~CMernos();

private:
    CSharedPtr<CAnimationMeshComponent>    m_Mesh;


    float ActTime;
    Vector3 DestMovePoint;
    class CPlayer* pPlayer;
    float FadeOpacity;

    //�÷��̾� FSM
    FSM<CMernos> FSM;
    float PlayerTime;

    Check_Type m_CheckType;
    Vector3     m_MoveStartPoint;

public:
    void SetCheckToPointType(const Check_Type& Type);

public:
    virtual bool Init();
    virtual void Start();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual CMernos* Clone();

private:


private:
  
    void YPosCorrection();

private:

    void SetNotify();

    //notify
    void PickUpNotify();
    void AscendNotify();


    //fsm
    //ChangeState ���� ��
    //Start�� ù �����ӿ��� ȣ��
    //Stay�� �ٸ� ���·� ChangeState �� ������ �� �����Ӹ��� ȣ��
    //End�� �ٸ� ���·� ChangeState �� �� ������ �����ӿ��� �� �� ȣ��
    void IDLEStart();
    void IDLEStay();
    void IDLEEnd();

    void DESCENDStart();
    void DESCENDStay();
    void DESCENDEnd();

    void PICKUPStart();
    void PICKUPStay();
    void PICKUPEnd();

    void ASCENDStart();
    void ASCENDStay();
    void ASCENDEnd();

    void ARRIVEStart();
    void ARRIVEStay();
    void ARRIVEEnd();

    void LEAVEStart();
    void LEAVEStay();
    void LEAVEEnd();

    void FADEOUTStart();
    void FADEOUTStay();
    void FADEOUTEnd();


private:

};

