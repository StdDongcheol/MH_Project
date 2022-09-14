#pragma once

#include "../Object/Monster.h"
#include "Component/StaticMeshComponent.h"
#include "Component/AnimationMeshComponent.h"
#include "Component/ColliderBox3D.h"
#include "FSM.h"

class CVespoid :
    public CMonster
{
    friend class CScene;

protected:
    CVespoid();
    CVespoid(const CVespoid& obj);
    virtual ~CVespoid();

private:
    CSharedPtr<CAnimationMeshComponent>    m_Mesh;
 
  
  
    CSharedPtr<CColliderBox3D>		ColliderUpperBody;
    CSharedPtr<CColliderBox3D>		ColliderLowerBody;

    CSharedPtr<CColliderBox3D>	    ColliderAttack;
    
    CSharedPtr<CColliderBox3D>          ColliderCarving;

    CSharedPtr<CColliderBox3D>          ColliderSliding;

    CSharedPtr<class CSound> WingSound;

    float IdleTime;
    float MoveTime;
    float AttackTime;
    float ChaseIdleTime;
    float MoveDist;
    float StartAttackTime;
    float EndAttackTime;
 
    float ChaseAccTime;


 

 
    class CPlayer* pPlayer;
  

  
    Vector3 TargetPos;
 
  
    
    int attacktype;


   
  
    bool IsLegUp;
    //�÷��̾� FSM
    FSM<CVespoid> FSM;
   
public:
    virtual bool Init();
    virtual void Start();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual CVespoid* Clone();

private:
   

private:
    Vector3 FindNextMovePoint();
    Vector3 FindPlayerAroundPos();
    void YPosCorrection();
    void FieldCollision(float DeltaTIme);
    void CheckStuck();

private:
  
    void SetNotify();

    //notify
    void LegUpEndNotify(); 
    void Death1EndNotify();
    void ToIdleNotify();
    void ScreamEndNotify();
    void GetHitEndNotify();
  

    //fsm
    //ChangeState ���� ��
    //Start�� ù �����ӿ��� ȣ��
    //Stay�� �ٸ� ���·� ChangeState �� ������ �� �����Ӹ��� ȣ��
    //End�� �ٸ� ���·� ChangeState �� �� ������ �����ӿ��� �� �� ȣ��
    void IDLEStart();
    void IDLEStay();
    void IDLEEnd();

 

    void MOVEStart();
    void MOVEStay();
    void MOVEEnd();

    void SCREAMStart();
    void SCREAMStay();
    void SCREAMEnd();

    void ATTACKStart();
    void ATTACKStay();
    void ATTACKEnd();

    void CHASEStart();
    void CHASEStay();
    void CHASEEnd();


    void GETHITStart();
    void GETHITStay();
    void GETHITEnd();

    void DEATHStart();
    void DEATHStay();
    void DEATHEnd();

    void FADEOUTStart();
    void FADEOUTStay();
    void FADEOUTEnd();

private:
    void OnCollisionBegin(const CollisionResult& result);
    void OnCollisionEnd(const CollisionResult& result);

    void AttackOnCollisionBegin(const CollisionResult& result);
    void AttackOnCollisionEnd(const CollisionResult& result);

    void SlidingOnCollisionBegin(const CollisionResult& result);
    void SlidingOnCollisionEnd(const CollisionResult& result);
};

