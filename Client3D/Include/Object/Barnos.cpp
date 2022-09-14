#include "Barnos.h"
#include "BarnosAnimation.h"
#include "Input.h"
#include "Resource/Animation/AnimationSequence.h"
#include "Engine.h"
#include "Scene/SceneManager.h"
#include "Player.h"
#include "Arrow.h"
#include "DragonArrow.h"
#include "Resource/ResourceManager.h"
#include "Collision/Collision.h"

CBarnos::CBarnos()
{
	SetTypeID<CBarnos>();
	IdleTime = 0.f;
	MoveTime = 0.f;
	AttackTime = 0.f;

	ChaseIdleTime = 0.f;

	HP = 200.f;

	pPlayer = nullptr;

	IsAscending = false;

}

CBarnos::CBarnos(const CBarnos& obj)
{
	m_Mesh = (CAnimationMeshComponent*)FindComponent("Mesh");

}

CBarnos::~CBarnos()
{
}


bool CBarnos::Init()
{




	m_Mesh = CreateComponent<CAnimationMeshComponent>("Mesh");

	ColliderHead = CreateComponent<CColliderBox3D>("ColliderHead");
	ColliderBody1 = CreateComponent<CColliderBox3D>("ColliderBody1");
	ColliderBody2 = CreateComponent<CColliderBox3D>("ColliderBody2");
	ColliderBody3 = CreateComponent<CColliderBox3D>("ColliderBody3");
	ColliderBody4 = CreateComponent<CColliderBox3D>("ColliderBody4");
	ColliderRightWing1 = CreateComponent<CColliderBox3D>("ColliderRightWing1");
	ColliderRightWing2 = CreateComponent<CColliderBox3D>("ColliderRightWing2");
	ColliderRightWing3 = CreateComponent<CColliderBox3D>("ColliderRightWing3");
	ColliderRightWing4 = CreateComponent<CColliderBox3D>("ColliderRightWing4");
	ColliderRightWing5 = CreateComponent<CColliderBox3D>("ColliderRightWing5");
	ColliderLeftWing1 = CreateComponent<CColliderBox3D>("ColliderLeftWing1");
	ColliderLeftWing2 = CreateComponent<CColliderBox3D>("ColliderLeftWing2");
	ColliderLeftWing3 = CreateComponent<CColliderBox3D>("ColliderLeftWing3");
	ColliderLeftWing4 = CreateComponent<CColliderBox3D>("ColliderLeftWing4");
	ColliderLeftWing5 = CreateComponent<CColliderBox3D>("ColliderLeftWing5");

	ColliderLeftFoot = CreateComponent<CColliderBox3D>("ColliderLeftFoot");
	ColliderRightFoot = CreateComponent<CColliderBox3D>("ColliderRightFoot");

	ColliderHeadAttack = CreateComponent<CColliderBox3D>("ColliderHeadAttack");
	ColliderLeftFootAttack = CreateComponent<CColliderBox3D>("ColliderLeftFootAttack");
	ColliderRightFootAttack = CreateComponent<CColliderBox3D>("ColliderRightFootAttack");

	ColliderHead->Set3DExtent(2.5f, 2.5f, 2.5f);
	ColliderBody1->Set3DExtent(1.5f, 1.5f, 1.5f);
	ColliderBody2->Set3DExtent(1.5f, 1.5f, 1.5f);
	ColliderBody3->Set3DExtent(2.f, 2.f, 2.f);
	ColliderBody4->Set3DExtent(1.5f, 1.5f, 1.5f);
	ColliderRightWing1->Set3DExtent(2.3f, 2.3f, 2.3f);
	ColliderRightWing2->Set3DExtent(2.3f, 2.3f, 2.3f);
	ColliderRightWing3->Set3DExtent(2.3f, 2.3f, 2.3f);
	ColliderRightWing4->Set3DExtent(2.3f, 2.3f, 2.3f);
	ColliderRightWing5->Set3DExtent(2.3f, 2.3f, 2.3f);
	ColliderLeftWing1->Set3DExtent(2.3f, 2.3f, 2.3f);
	ColliderLeftWing2->Set3DExtent(2.3f, 2.3f, 2.3f);
	ColliderLeftWing3->Set3DExtent(2.3f, 2.3f, 2.3f);
	ColliderLeftWing4->Set3DExtent(2.3f, 2.3f, 2.3f);
	ColliderLeftWing5->Set3DExtent(2.3f, 2.3f, 2.3f);

	ColliderLeftFoot->Set3DExtent(2.5f, 2.5f, 2.5f);
	ColliderRightFoot->Set3DExtent(2.5f, 2.5f, 2.5f);

	ColliderHeadAttack->Set3DExtent(2.5f, 2.5f, 2.5f);
	ColliderLeftFootAttack->Set3DExtent(2.5f, 2.5f, 2.5f);
	ColliderRightFootAttack->Set3DExtent(2.5f, 2.5f, 2.5f);

	ColliderHead->SetCollisionProfile("Monster");
	ColliderBody1->SetCollisionProfile("Monster");
	ColliderBody2->SetCollisionProfile("Monster");
	ColliderBody3->SetCollisionProfile("Monster");
	ColliderBody4->SetCollisionProfile("Monster");
	ColliderRightWing1->SetCollisionProfile("Monster");
	ColliderRightWing2->SetCollisionProfile("Monster");
	ColliderRightWing3->SetCollisionProfile("Monster");
	ColliderRightWing4->SetCollisionProfile("Monster");
	ColliderRightWing5->SetCollisionProfile("Monster");
	ColliderLeftWing1->SetCollisionProfile("Monster");
	ColliderLeftWing2->SetCollisionProfile("Monster");
	ColliderLeftWing3->SetCollisionProfile("Monster");
	ColliderLeftWing4->SetCollisionProfile("Monster");
	ColliderLeftWing5->SetCollisionProfile("Monster");
	ColliderLeftFoot->SetCollisionProfile("Monster");
	ColliderRightFoot->SetCollisionProfile("Monster");

	ColliderHeadAttack->SetCollisionProfile("MonsterAttack");
	ColliderLeftFootAttack->SetCollisionProfile("MonsterAttack");
	ColliderRightFootAttack->SetCollisionProfile("MonsterAttack");

	//collider callback
	ColliderHead->AddCollisionCallback(Collision_State::Begin, this, &CBarnos::OnCollisionBegin);
	ColliderHead->AddCollisionCallback(Collision_State::End, this, &CBarnos::OnCollisionEnd);
	ColliderBody1->AddCollisionCallback(Collision_State::Begin, this, &CBarnos::OnCollisionBegin);
	ColliderBody1->AddCollisionCallback(Collision_State::End, this, &CBarnos::OnCollisionEnd);
	ColliderBody2->AddCollisionCallback(Collision_State::Begin, this, &CBarnos::OnCollisionBegin);
	ColliderBody2->AddCollisionCallback(Collision_State::End, this, &CBarnos::OnCollisionEnd);
	ColliderBody3->AddCollisionCallback(Collision_State::Begin, this, &CBarnos::OnCollisionBegin);
	ColliderBody3->AddCollisionCallback(Collision_State::End, this, &CBarnos::OnCollisionEnd);
	ColliderBody4->AddCollisionCallback(Collision_State::Begin, this, &CBarnos::OnCollisionBegin);
	ColliderBody4->AddCollisionCallback(Collision_State::End, this, &CBarnos::OnCollisionEnd);
	ColliderRightWing1->AddCollisionCallback(Collision_State::Begin, this, &CBarnos::OnCollisionBegin);
	ColliderRightWing1->AddCollisionCallback(Collision_State::End, this, &CBarnos::OnCollisionEnd);
	ColliderRightWing2->AddCollisionCallback(Collision_State::Begin, this, &CBarnos::OnCollisionBegin);
	ColliderRightWing2->AddCollisionCallback(Collision_State::End, this, &CBarnos::OnCollisionEnd);
	ColliderRightWing3->AddCollisionCallback(Collision_State::Begin, this, &CBarnos::OnCollisionBegin);
	ColliderRightWing3->AddCollisionCallback(Collision_State::End, this, &CBarnos::OnCollisionEnd);
	ColliderRightWing4->AddCollisionCallback(Collision_State::Begin, this, &CBarnos::OnCollisionBegin);
	ColliderRightWing4->AddCollisionCallback(Collision_State::End, this, &CBarnos::OnCollisionEnd);
	ColliderRightWing5->AddCollisionCallback(Collision_State::Begin, this, &CBarnos::OnCollisionBegin);
	ColliderRightWing5->AddCollisionCallback(Collision_State::End, this, &CBarnos::OnCollisionEnd);
	ColliderLeftWing1->AddCollisionCallback(Collision_State::Begin, this, &CBarnos::OnCollisionBegin);
	ColliderLeftWing1->AddCollisionCallback(Collision_State::End, this, &CBarnos::OnCollisionEnd);
	ColliderLeftWing2->AddCollisionCallback(Collision_State::Begin, this, &CBarnos::OnCollisionBegin);
	ColliderLeftWing2->AddCollisionCallback(Collision_State::End, this, &CBarnos::OnCollisionEnd);
	ColliderLeftWing3->AddCollisionCallback(Collision_State::Begin, this, &CBarnos::OnCollisionBegin);
	ColliderLeftWing3->AddCollisionCallback(Collision_State::End, this, &CBarnos::OnCollisionEnd);
	ColliderLeftWing4->AddCollisionCallback(Collision_State::Begin, this, &CBarnos::OnCollisionBegin);
	ColliderLeftWing4->AddCollisionCallback(Collision_State::End, this, &CBarnos::OnCollisionEnd);
	ColliderLeftWing5->AddCollisionCallback(Collision_State::Begin, this, &CBarnos::OnCollisionBegin);
	ColliderLeftWing5->AddCollisionCallback(Collision_State::End, this, &CBarnos::OnCollisionEnd);
	ColliderLeftFoot->AddCollisionCallback(Collision_State::Begin, this, &CBarnos::OnCollisionBegin);
	ColliderLeftFoot->AddCollisionCallback(Collision_State::End, this, &CBarnos::OnCollisionEnd);
	ColliderRightFoot->AddCollisionCallback(Collision_State::Begin, this, &CBarnos::OnCollisionBegin);
	ColliderRightFoot->AddCollisionCallback(Collision_State::End, this, &CBarnos::OnCollisionEnd);

	ColliderHeadAttack->AddCollisionCallback(Collision_State::Begin, this, &CBarnos::AttackOnCollisionBegin);
	ColliderHeadAttack->AddCollisionCallback(Collision_State::End, this, &CBarnos::AttackOnCollisionEnd);
	ColliderLeftFootAttack->AddCollisionCallback(Collision_State::Begin, this, &CBarnos::AttackOnCollisionBegin);
	ColliderLeftFootAttack->AddCollisionCallback(Collision_State::End, this, &CBarnos::AttackOnCollisionEnd);
	ColliderRightFootAttack->AddCollisionCallback(Collision_State::Begin, this, &CBarnos::AttackOnCollisionBegin);
	ColliderRightFootAttack->AddCollisionCallback(Collision_State::End, this, &CBarnos::AttackOnCollisionEnd);





	SetRootComponent(m_Mesh);
	m_Mesh->SetTransformState(Transform_State::None);
	m_State = Transform_State::None;
	m_Mesh->SetMesh("BarnosMesh");
	m_Mesh->CreateAnimationInstance<CBarnosAnimation>();

	m_Mesh->SetRelativeScale(0.05f, 0.05f, 0.05f);
	m_Mesh->SetRelativePos(20.f, 10.f, 10.f);
	m_Mesh->SetRelativeRotation(Vector3(250.f, 180.f, 180.f));

	ColliderCarving = CreateComponent<CColliderBox3D>("ColliderCarving");
	ColliderCarving->Set3DExtent(6.0f, 6.0f, 6.0f);
	ColliderCarving->SetCollisionProfile("Carving");
	m_Mesh->AddChild(ColliderCarving);
	ColliderCarving->Enable(false);

	ColliderSliding = CreateComponent<CColliderBox3D>("ColliderSliding");
	ColliderSliding->Set3DExtent(3.0f, 3.0f, 3.0f);
	ColliderSliding->SetOffset(0.0f, 3.0f, 0.0f);
	ColliderSliding->SetCollisionProfile("MonsterSliding");
	m_Mesh->AddChild(ColliderSliding);
	ColliderSliding->Enable(true);
	ColliderSliding->AddCollisionCallback(Collision_State::Begin, this, &CBarnos::SlidingOnCollisionBegin);
	ColliderSliding->AddCollisionCallback(Collision_State::End, this, &CBarnos::SlidingOnCollisionEnd);

	m_Mesh->AddChild(ColliderHead, "Head");
	m_Mesh->AddChild(ColliderBody1, "Body1");
	m_Mesh->AddChild(ColliderBody2, "Body2");
	m_Mesh->AddChild(ColliderBody3, "Body3");
	m_Mesh->AddChild(ColliderBody4, "Body4");

	m_Mesh->AddChild(ColliderRightWing1, "RightWing1");
	m_Mesh->AddChild(ColliderRightWing2, "RightWing2");
	m_Mesh->AddChild(ColliderRightWing3, "RightWing3");
	m_Mesh->AddChild(ColliderRightWing4, "RightWing4");
	m_Mesh->AddChild(ColliderRightWing5, "RightWing5");

	m_Mesh->AddChild(ColliderLeftWing1, "LeftWing1");
	m_Mesh->AddChild(ColliderLeftWing2, "LeftWing2");
	m_Mesh->AddChild(ColliderLeftWing3, "LeftWing3");
	m_Mesh->AddChild(ColliderLeftWing4, "LeftWing4");
	m_Mesh->AddChild(ColliderLeftWing5, "LeftWing5");

	m_Mesh->AddChild(ColliderLeftFoot, "RightFoot");
	m_Mesh->AddChild(ColliderRightFoot, "LeftFoot");

	m_Mesh->AddChild(ColliderHeadAttack, "Head");
	m_Mesh->AddChild(ColliderLeftFootAttack, "RightFoot");
	m_Mesh->AddChild(ColliderRightFootAttack, "LeftFoot");

	SetNotify();

	//fsm에 함수포인터를 이용해 상태 생성 
	FSM.CreateState("Idle", this, &CBarnos::IDLEStay, &CBarnos::IDLEStart, &CBarnos::IDLEEnd);
	FSM.CreateState("IdleMove", this, &CBarnos::IDLEMOVEStay, &CBarnos::IDLEMOVEStart, &CBarnos::IDLEMOVEEnd);
	FSM.CreateState("Chase", this, &CBarnos::CHASEStay, &CBarnos::CHASEStart, &CBarnos::CHASEEnd);
	FSM.CreateState("GetHit", this, &CBarnos::GETHITStay, &CBarnos::GETHITStart, &CBarnos::GETHITEnd);
	FSM.CreateState("Scream", this, &CBarnos::SCREAMStay, &CBarnos::SCREAMStart, &CBarnos::SCREAMEnd);
	FSM.CreateState("Attack1", this, &CBarnos::ATTACK1Stay, &CBarnos::ATTACK1Start, &CBarnos::ATTACK1End);
	FSM.CreateState("Attack2", this, &CBarnos::ATTACK2Stay, &CBarnos::ATTACK2Start, &CBarnos::ATTACK2End);
	FSM.CreateState("Attack3", this, &CBarnos::ATTACK3Stay, &CBarnos::ATTACK3Start, &CBarnos::ATTACK3End);
	FSM.CreateState("Death", this, &CBarnos::DEATHStay, &CBarnos::DEATHStart, &CBarnos::DEATHEnd);
	FSM.CreateState("FadeOut", this, &CBarnos::FADEOUTStay, &CBarnos::FADEOUTStart, &CBarnos::FADEOUTEnd);

	CResourceManager::GetInst()->LoadSound("Barnos", true, "BarnosWing1" + std::to_string(BarnosCount), "Monster/Barnos/wing1.ogg", SOUND_PATH);
	CResourceManager::GetInst()->LoadSound("Barnos", true, "BarnosWing2" + std::to_string(BarnosCount), "Monster/Barnos/wing2.ogg", SOUND_PATH);
	WingSound1 = CResourceManager::GetInst()->FindSound("BarnosWing1" + std::to_string(BarnosCount));
	WingSound2 = CResourceManager::GetInst()->FindSound("BarnosWing2" + std::to_string(BarnosCount));
	++BarnosCount;

	

	this;

	return true;
}

void CBarnos::Start()
{
	CGameObject::Start();

	pPlayer = (CPlayer*)CSceneManager::GetInst()->GetScene()->GetPlayerObject();

	//상태 변경
	FSM.ChangeState("Idle");
}

void CBarnos::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	Vector3 Dist = pPlayer->GetWorldPos() - GetWorldPos();

	if (Dist.Length() < 40.f && IsIdle && !IsDead)
	{
		CurScreamTime += DeltaTime;
	}

	if (ScreamThreshold < CurScreamTime && IsIdle)
	{
		FSM.ChangeState("Scream");
	}
	



	FSM.Update();

	if (!IsDead)
	{
		YPosCorrection();
	}


	if (IsOnFieldCol)
	{
		FieldCollision(DeltaTime);
		CheckStuck();
	}
}

void CBarnos::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CBarnos* CBarnos::Clone()
{
	return new CBarnos(*this);
}


Vector3 CBarnos::FindNextMovePoint()
{
	Vector3 DestVec;
	srand((unsigned int)time(0) + RandCount++);

	
	//x값
	if (rand() % 2 == 1)
	{
		srand((unsigned int)time(0) + RandCount++);
		DestVec.x = GetWorldPos().x - (rand() % 10 + 8);
	}
	else
	{
		srand((unsigned int)time(0) + RandCount++);
		DestVec.x = GetWorldPos().x + (rand() % 10 + 8);
	}



	//z값
	srand((unsigned int)time(0) + RandCount++);
	if (rand() % 2 == 1)
	{
		srand((unsigned int)time(0) + RandCount++);
		DestVec.z = (GetWorldPos().z) - (rand() % 10 + 8);
	}
	else
	{
		srand((unsigned int)time(0) + RandCount++);
		DestVec.z = GetWorldPos().z + (rand() % 10 + 8);
	}

	//y값

	float y = m_Scene->GetNavigation3DManager()->GetY(DestVec);

	srand((unsigned int)time(0) + RandCount++);
	if (rand() % 2 == 1)
	{
		srand((unsigned int)time(0) + RandCount++);
		DestVec.y = GetWorldPos().y + (rand() % 10);
	}
	else
	{
		srand((unsigned int)time(0) + RandCount++);
		DestVec.y = GetWorldPos().y - (rand() % 10);
	}


	if (DestVec.y <= y + 6)
	{
		DestVec.y = y + 6;
	}


	if (DestVec.y > GetWorldPos().y)
	{
		IsAscending = true;
	}

	return DestVec;
}
Vector3 CBarnos::FindPlayerAroundPos()
{
	Vector3 DestVec;
	srand((unsigned int)time(0) + RandCount++);

	//x값
	if (rand() % 2 == 1)
	{
		srand((unsigned int)time(0) + RandCount++);
		DestVec.x = pPlayer->GetWorldPos().x - (rand() % 5 + 2);
	}
	else
	{
		srand((unsigned int)time(0) + RandCount++);
		DestVec.x = pPlayer->GetWorldPos().x + (rand() % 5 + 2);
	}


	srand((unsigned int)time(0) + RandCount++);
	//z값
	if (rand() % 2 == 1)
	{
		srand((unsigned int)time(0) + RandCount++);
		DestVec.z = (pPlayer->GetWorldPos().z) - (rand() % 5 + 2);
	}
	else
	{
		srand((unsigned int)time(0) + RandCount++);
		DestVec.z = pPlayer->GetWorldPos().z + (rand() % 5 + 2);
	}

	//y값
	srand((unsigned int)time(0) + RandCount++);
	DestVec.y = pPlayer->GetWorldPos().y + (rand() % 2);

	float y = m_Scene->GetNavigation3DManager()->GetY(DestVec);
	if (DestVec.y <= y + 6)
	{
		DestVec.y = y + 6;
	}
	return DestVec;
}

void CBarnos::YPosCorrection()
{
	Vector3 DestVec = GetWorldPos();
	DestVec.y = 0;
	float y = m_Scene->GetNavigation3DManager()->GetY(DestVec) + 5;

	if (GetWorldPos().y <= y)
	{
		Vector3 t = GetWorldPos();
		t.y = y;
		SetWorldPos(t);
	}
}

void CBarnos::FieldCollision(float DeltaTime)
{
	Vector3 Dir = Vector3(pFieldObj->GetWorldPos() - GetWorldPos());
	Dir.Normalize();
	Dir *= -1;
	AddWorldPos(Dir * CurSpeed *2* DeltaTime);

	Vector3 MyPos = m_Mesh->GetWorldPos();

	CGameObject* FieldObj = m_Scene->FindObject(m_FieldObjName);

	CSharedPtr<CColliderBox3D> Box = FieldObj->FindComponentFromType<CColliderBox3D>();

	// 충돌체가 정육면체일 경우
	if (((int)Box->GetInfo().Length.x == (int)Box->GetInfo().Length.y) &&
		((int)Box->GetInfo().Length.y == (int)Box->GetInfo().Length.z))
	{

		Vector3 MyDir = m_Mesh->GetWorldAxis(AXIS_Y);
		MyDir.y = 0;

		if (FieldObj->GetRootComponent()->GetTransformState() == Transform_State::None)
		{

		}

		MyPos.y += 1.f;

		std::vector<CollisionBoxInfo>	vecInfo;

		CollisionBoxInfo Info = {};

		for (int i = 0; i < 8; ++i)
		{
			float Dist = (MyPos.Distance(Box->GetInfo().Pos[i]));
			Info.Dist = Dist;
			Info.Numb = i;

			vecInfo.push_back(Info);
		}

		std::sort(vecInfo.begin(), vecInfo.end(), SortPos);

		if (vecInfo[0].Numb == 0 || vecInfo[0].Numb == 1 ||
			vecInfo[0].Numb == 2 || vecInfo[0].Numb == 3)
		{
			if (vecInfo[1].Numb == 0 || vecInfo[1].Numb == 1 ||
				vecInfo[1].Numb == 2 || vecInfo[1].Numb == 3)
			{
				if (vecInfo[2].Numb == 0 || vecInfo[2].Numb == 1 ||
					vecInfo[2].Numb == 2 || vecInfo[2].Numb == 3)
				{
					if (vecInfo[3].Numb == 0 || vecInfo[3].Numb == 1 ||
						vecInfo[3].Numb == 2 || vecInfo[3].Numb == 3)
					{
						float PlayerAngle = MyDir.Angle(Box->GetInfo().NearNormal);
						if ((PlayerAngle < 90.f) && (PlayerAngle > -90.f))
						{
							float PDotN = MyDir.Dot(Box->GetInfo().NearNormal);
							m_SlidingVec = MyDir - Box->GetInfo().NearNormal * PDotN;
						}
						else
						{
							m_SlidingVec = Vector3(0.f, 0.f, 0.f);
						}
					}
				}
			}
		}

		if (vecInfo[0].Numb == 4 || vecInfo[0].Numb == 5 ||
			vecInfo[0].Numb == 6 || vecInfo[0].Numb == 7)
		{
			if (vecInfo[1].Numb == 4 || vecInfo[1].Numb == 5 ||
				vecInfo[1].Numb == 6 || vecInfo[1].Numb == 7)
			{
				if (vecInfo[2].Numb == 4 || vecInfo[2].Numb == 5 ||
					vecInfo[2].Numb == 6 || vecInfo[2].Numb == 7)
				{
					if (vecInfo[3].Numb == 4 || vecInfo[3].Numb == 5 ||
						vecInfo[3].Numb == 6 || vecInfo[3].Numb == 7)
					{
						float PlayerAngle = MyDir.Angle(Box->GetInfo().FarNormal);
						if ((PlayerAngle < 90.f) && (PlayerAngle > -90.f))
						{
							float PDotN = MyDir.Dot(Box->GetInfo().FarNormal);
							m_SlidingVec = MyDir - Box->GetInfo().FarNormal * PDotN;
						}
						else
						{
							m_SlidingVec = Vector3(0.f, 0.f, 0.f);
						}
					}
				}
			}
		}

		if (vecInfo[0].Numb == 1 || vecInfo[0].Numb == 5 ||
			vecInfo[0].Numb == 3 || vecInfo[0].Numb == 7)
		{
			if (vecInfo[1].Numb == 1 || vecInfo[1].Numb == 5 ||
				vecInfo[1].Numb == 3 || vecInfo[1].Numb == 7)
			{
				if (vecInfo[2].Numb == 1 || vecInfo[2].Numb == 5 ||
					vecInfo[2].Numb == 3 || vecInfo[2].Numb == 7)
				{
					if (vecInfo[3].Numb == 1 || vecInfo[3].Numb == 5 ||
						vecInfo[3].Numb == 3 || vecInfo[3].Numb == 7)
					{
						float PlayerAngle = MyDir.Angle(Box->GetInfo().RightNormal);
						if ((PlayerAngle < 90.f) && (PlayerAngle > -90.f))
						{
							float PDotN = MyDir.Dot(Box->GetInfo().RightNormal);
							m_SlidingVec = MyDir - Box->GetInfo().RightNormal * PDotN;
						}
						else
						{
							m_SlidingVec = Vector3(0.f, 0.f, 0.f);
						}
					}
				}
			}
		}

		if (vecInfo[0].Numb == 4 || vecInfo[0].Numb == 0 ||
			vecInfo[0].Numb == 2 || vecInfo[0].Numb == 6)
		{
			if (vecInfo[1].Numb == 4 || vecInfo[1].Numb == 0 ||
				vecInfo[1].Numb == 2 || vecInfo[1].Numb == 6)
			{
				if (vecInfo[2].Numb == 4 || vecInfo[2].Numb == 0 ||
					vecInfo[2].Numb == 2 || vecInfo[2].Numb == 6)
				{
					if (vecInfo[3].Numb == 4 || vecInfo[3].Numb == 0 ||
						vecInfo[3].Numb == 2 || vecInfo[3].Numb == 6)
					{
						float PlayerAngle = MyDir.Angle(Box->GetInfo().LeftNormal);
						if ((PlayerAngle < 90.f) && (PlayerAngle > -90.f))
						{
							float PDotN = MyDir.Dot(Box->GetInfo().LeftNormal);
							m_SlidingVec = MyDir - Box->GetInfo().LeftNormal * PDotN;
						}
						else
						{
							m_SlidingVec = Vector3(0.f, 0.f, 0.f);
						}
					}
				}
			}
		}

		if (vecInfo[0].Numb == 4 || vecInfo[0].Numb == 5 ||
			vecInfo[0].Numb == 0 || vecInfo[0].Numb == 1)
		{
			if (vecInfo[1].Numb == 4 || vecInfo[1].Numb == 5 ||
				vecInfo[1].Numb == 0 || vecInfo[1].Numb == 1)
			{
				if (vecInfo[2].Numb == 4 || vecInfo[2].Numb == 5 ||
					vecInfo[2].Numb == 0 || vecInfo[2].Numb == 1)
				{
					if (vecInfo[3].Numb == 4 || vecInfo[3].Numb == 5 ||
						vecInfo[3].Numb == 0 || vecInfo[3].Numb == 1)
					{
						float PlayerAngle = MyDir.Angle(Box->GetInfo().TopNormal);
						if ((PlayerAngle < 90.f) && (PlayerAngle > -90.f))
						{
							float PDotN = MyDir.Dot(Box->GetInfo().TopNormal);
							m_SlidingVec = MyDir - Box->GetInfo().TopNormal * PDotN;
						}
						else
						{
							m_SlidingVec = Vector3(0.f, 0.f, 0.f);
						}
					}
				}
			}
		}

		if (vecInfo[0].Numb == 6 || vecInfo[0].Numb == 7 ||
			vecInfo[0].Numb == 2 || vecInfo[0].Numb == 3)
		{
			if (vecInfo[1].Numb == 6 || vecInfo[1].Numb == 7 ||
				vecInfo[1].Numb == 2 || vecInfo[1].Numb == 3)
			{
				if (vecInfo[2].Numb == 6 || vecInfo[2].Numb == 7 ||
					vecInfo[2].Numb == 2 || vecInfo[2].Numb == 3)
				{
					if (vecInfo[3].Numb == 6 || vecInfo[3].Numb == 7 ||
						vecInfo[3].Numb == 2 || vecInfo[3].Numb == 3)
					{
						float PlayerAngle = MyDir.Angle(Box->GetInfo().BottomNormal);
						if ((PlayerAngle < 90.f) && (PlayerAngle > -90.f))
						{
							float PDotN = MyDir.Dot(Box->GetInfo().BottomNormal);
							m_SlidingVec = MyDir - Box->GetInfo().BottomNormal * PDotN;
						}
						else
						{
							m_SlidingVec = Vector3(0.f, 0.f, 0.f);
						}
					}
				}
			}
		}
	}
	else
	{
		Vector3 MyDir = m_Mesh->GetWorldAxis(AXIS_Y);
		MyDir.y = 0;

		Vector3 AxisDir = m_Mesh->GetWorldAxis(AXIS_Y) * -1.f;
		AxisDir.y = 0;

		if (((FieldObj->GetWorldRot().x <= -89.f) && (FieldObj->GetWorldRot().x >= -91.f))
			|| ((FieldObj->GetWorldRot().x >= 269.f) && (FieldObj->GetWorldRot().x <= 271.f)))
		{
			if ((MyDir.z > 0.f) && (Box->GetInfo().Pos[0].x < MyPos.x) &&
				(Box->GetInfo().Pos[1].x > MyPos.x) && (MyPos.z < Box->GetInfo().Center.z))
			{
				int PlayerAngle = (int)AxisDir.Angle(Box->GetInfo().TopNormal);
				if ((PlayerAngle <= 90) && (PlayerAngle >= -90))
				{

					float PDotN = AxisDir.Dot(Box->GetInfo().TopNormal);
					m_SlidingVec = AxisDir - Box->GetInfo().TopNormal * PDotN;
				}
				else
				{
					m_SlidingVec = Vector3(0.f, 0.f, 0.f);
				}
			}

			else if ((MyDir.z < 0.f) && (Box->GetInfo().Pos[2].x < MyPos.x) &&
				(Box->GetInfo().Pos[3].x > MyPos.x) && (MyPos.z > Box->GetInfo().Center.z))
			{
				int PlayerAngle = (int)AxisDir.Angle(Box->GetInfo().BottomNormal);
				if ((PlayerAngle <= 90) && (PlayerAngle >= -90))
				{
					float PDotN = AxisDir.Dot(Box->GetInfo().BottomNormal);
					m_SlidingVec = AxisDir - Box->GetInfo().BottomNormal * PDotN;
				}
				else
				{
					m_SlidingVec = Vector3(0.f, 0.f, 0.f);
				}
			}

			else if ((MyDir.x > 0.f) && (Box->GetInfo().Pos[0].z < MyPos.z) &&
				(Box->GetInfo().Pos[2].z > MyPos.z) && (MyPos.x < Box->GetInfo().Center.x))
			{
				int PlayerAngle = (int)AxisDir.Angle(Box->GetInfo().LeftNormal);
				if ((PlayerAngle <= 90) && (PlayerAngle >= -90))
				{
					float PDotN = AxisDir.Dot(Box->GetInfo().LeftNormal);
					m_SlidingVec = AxisDir - Box->GetInfo().LeftNormal * PDotN;
				}
				else
				{
					m_SlidingVec = Vector3(0.f, 0.f, 0.f);
				}
			}

			else if ((MyDir.x < 0.f) && (Box->GetInfo().Pos[1].z < MyPos.z) &&
				(Box->GetInfo().Pos[3].z > MyPos.z) && (MyPos.x > Box->GetInfo().Center.x))
			{
				int PlayerAngle = (int)AxisDir.Angle(Box->GetInfo().RightNormal);
				if ((PlayerAngle <= 90) && (PlayerAngle >= -90))
				{
					float PDotN = AxisDir.Dot(Box->GetInfo().RightNormal);
					m_SlidingVec = AxisDir - Box->GetInfo().RightNormal * PDotN;
				}
				else
				{
					m_SlidingVec = Vector3(0.f, 0.f, 0.f);
				}
			}
			else
			{
				m_SlidingVec = Vector3(0.f, 0.f, 0.f);
			}

		}
		else if (((FieldObj->GetWorldRot().x >= 89.f) && (FieldObj->GetWorldRot().x <= 91.f))
			|| ((FieldObj->GetWorldRot().x <= -269.f) && (FieldObj->GetWorldRot().x >= -271.f)))
		{
			if ((MyDir.z > 0.f) && (Box->GetInfo().Pos[2].x < MyPos.x) &&
				(Box->GetInfo().Pos[3].x > MyPos.x) && (MyPos.z < Box->GetInfo().Center.z))
			{
				int PlayerAngle = (int)AxisDir.Angle(Box->GetInfo().BottomNormal);
				if ((PlayerAngle <= 90) && (PlayerAngle >= -90))
				{
					float PDotN = AxisDir.Dot(Box->GetInfo().BottomNormal);
					m_SlidingVec = AxisDir - Box->GetInfo().BottomNormal * PDotN;
				}
				else
				{
					m_SlidingVec = Vector3(0.f, 0.f, 0.f);
				}
			}

			else if ((MyDir.z < 0.f) && (Box->GetInfo().Pos[0].x < MyPos.x) &&
				(Box->GetInfo().Pos[1].x > MyPos.x) && (MyPos.z > Box->GetInfo().Center.z))
			{
				int PlayerAngle = (int)AxisDir.Angle(Box->GetInfo().TopNormal);
				if ((PlayerAngle <= 90) && (PlayerAngle >= -90))
				{
					float PDotN = AxisDir.Dot(Box->GetInfo().TopNormal);
					m_SlidingVec = AxisDir - Box->GetInfo().TopNormal * PDotN;
				}
				else
				{
					m_SlidingVec = Vector3(0.f, 0.f, 0.f);
				}
			}

			else if ((MyDir.x > 0.f) && (Box->GetInfo().Pos[2].z < MyPos.z) &&
				(Box->GetInfo().Pos[0].z > MyPos.z) && (MyPos.x < Box->GetInfo().Center.x))
			{
				int PlayerAngle = (int)AxisDir.Angle(Box->GetInfo().LeftNormal);
				if ((PlayerAngle <= 90) && (PlayerAngle >= -90))
				{
					float PDotN = AxisDir.Dot(Box->GetInfo().LeftNormal);
					m_SlidingVec = AxisDir - Box->GetInfo().LeftNormal * PDotN;
				}
				else
				{
					m_SlidingVec = Vector3(0.f, 0.f, 0.f);
				}
			}

			else if ((MyDir.x < 0.f) && (Box->GetInfo().Pos[2].z < MyPos.z) &&
				(Box->GetInfo().Pos[0].z > MyPos.z) && (MyPos.x > Box->GetInfo().Center.x))
			{
				int PlayerAngle = (int)AxisDir.Angle(Box->GetInfo().RightNormal);
				if ((PlayerAngle <= 90) && (PlayerAngle >= -90))
				{
					float PDotN = AxisDir.Dot(Box->GetInfo().RightNormal);
					m_SlidingVec = AxisDir - Box->GetInfo().RightNormal * PDotN;
				}
				else
				{
					m_SlidingVec = Vector3(0.f, 0.f, 0.f);
				}
			}
			else
			{
				m_SlidingVec = Vector3(0.f, 0.f, 0.f);
			}
		}
		else if (FieldObj->GetWorldRot().x == 0.f || FieldObj->GetWorldRot().x == 360.f)
		{
			if ((MyDir.z > 0.f) && (Box->GetInfo().Pos[2].x - 0.1f < MyPos.x) &&
				(Box->GetInfo().Pos[3].x + 0.1f > MyPos.x) && (MyPos.z < Box->GetInfo().Center.z))
			{
				int PlayerAngle = (int)AxisDir.Angle(Box->GetInfo().NearNormal);
				if ((PlayerAngle <= 90) && (PlayerAngle >= -90))
				{
					float PDotN = AxisDir.Dot(Box->GetInfo().NearNormal);
					m_SlidingVec = AxisDir - Box->GetInfo().NearNormal * PDotN;
				}
				else
				{
					m_SlidingVec = Vector3(0.f, 0.f, 0.f);
				}
			}
			else if ((MyDir.z < 0.f) && (Box->GetInfo().Pos[6].x - 0.1f < MyPos.x) &&
				(Box->GetInfo().Pos[7].x + 0.1f > MyPos.x) && (MyPos.z > Box->GetInfo().Center.z))
			{
				int PlayerAngle = (int)AxisDir.Angle(Box->GetInfo().FarNormal);
				if ((PlayerAngle <= 90) && (PlayerAngle >= -90))
				{
					float PDotN = AxisDir.Dot(Box->GetInfo().FarNormal);
					m_SlidingVec = AxisDir - Box->GetInfo().FarNormal * PDotN;
				}
				else
				{
					m_SlidingVec = Vector3(0.f, 0.f, 0.f);
				}
			}
			else if ((MyDir.x > 0.f) && (Box->GetInfo().Pos[2].z - 0.1f < MyPos.z) &&
				(Box->GetInfo().Pos[6].z + 0.1f > MyPos.z) && (MyPos.x < Box->GetInfo().Center.x))
			{
				int PlayerAngle = (int)AxisDir.Angle(Box->GetInfo().LeftNormal);
				if ((PlayerAngle <= 90) && (PlayerAngle >= -90))
				{
					float PDotN = AxisDir.Dot(Box->GetInfo().LeftNormal);
					m_SlidingVec = AxisDir - Box->GetInfo().LeftNormal * PDotN;
				}
				else
				{
					m_SlidingVec = Vector3(0.f, 0.f, 0.f);
				}
			}
			else if ((MyDir.x < 0.f) && (Box->GetInfo().Pos[3].z - 0.1f < MyPos.z) &&
				(Box->GetInfo().Pos[7].z + 0.1f > MyPos.z) && (MyPos.x > Box->GetInfo().Center.x))
			{
				int PlayerAngle = (int)AxisDir.Angle(Box->GetInfo().RightNormal);
				if ((PlayerAngle <= 90) && (PlayerAngle >= -90))
				{
					float PDotN = AxisDir.Dot(Box->GetInfo().RightNormal);
					m_SlidingVec = AxisDir - Box->GetInfo().RightNormal * PDotN;
				}
				else
				{
					m_SlidingVec = Vector3(0.f, 0.f, 0.f);
				}
			}
			else
			{
				m_SlidingVec = Vector3(0.f, 0.f, 0.f);
			}

		}

		else if (((FieldObj->GetWorldRot().z <= -89.f) && (FieldObj->GetWorldRot().z >= -91.f))
			|| ((FieldObj->GetWorldRot().z >= 269.f) && (FieldObj->GetWorldRot().z <= 271.f)))
		{
			if ((MyDir.z > 0.f) && (Box->GetInfo().Pos[0].x < MyPos.x) &&
				(Box->GetInfo().Pos[2].x > MyPos.x) && (MyPos.z < Box->GetInfo().Center.z))
			{
				int PlayerAngle = (int)AxisDir.Angle(Box->GetInfo().NearNormal);
				if ((PlayerAngle <= 90) && (PlayerAngle >= -90))
				{
					float PDotN = AxisDir.Dot(Box->GetInfo().NearNormal);
					m_SlidingVec = AxisDir - Box->GetInfo().NearNormal * PDotN;
				}
				else
				{
					m_SlidingVec = Vector3(0.f, 0.f, 0.f);
				}
			}
			else if ((MyDir.z < 0.f) && (Box->GetInfo().Pos[0].x < MyPos.x) &&
				(Box->GetInfo().Pos[2].x > MyPos.x) && (MyPos.z > Box->GetInfo().Center.z))
			{
				int PlayerAngle = (int)AxisDir.Angle(Box->GetInfo().FarNormal);
				if ((PlayerAngle <= 90) && (PlayerAngle >= -90))
				{
					float PDotN = AxisDir.Dot(Box->GetInfo().FarNormal);
					m_SlidingVec = AxisDir - Box->GetInfo().FarNormal * PDotN;
				}
				else
				{
					m_SlidingVec = Vector3(0.f, 0.f, 0.f);
				}
			}
			else if ((MyDir.x > 0.f) && (Box->GetInfo().Pos[0].z < MyPos.z) &&
				(Box->GetInfo().Pos[4].z > MyPos.z) && (MyPos.x < Box->GetInfo().Center.x))
			{
				int PlayerAngle = (int)AxisDir.Angle(Box->GetInfo().TopNormal);
				if ((PlayerAngle <= 90) && (PlayerAngle >= -90))
				{
					float PDotN = AxisDir.Dot(Box->GetInfo().TopNormal);
					m_SlidingVec = AxisDir - Box->GetInfo().TopNormal * PDotN;
				}
				else
				{
					m_SlidingVec = Vector3(0.f, 0.f, 0.f);
				}
			}
			else if ((MyDir.x < 0.f) && (Box->GetInfo().Pos[0].z < MyPos.z) &&
				(Box->GetInfo().Pos[4].z > MyPos.z) && (MyPos.x > Box->GetInfo().Center.x))
			{
				int PlayerAngle = (int)AxisDir.Angle(Box->GetInfo().BottomNormal);
				if ((PlayerAngle <= 90) && (PlayerAngle >= -90))
				{
					float PDotN = AxisDir.Dot(Box->GetInfo().BottomNormal);
					m_SlidingVec = AxisDir - Box->GetInfo().BottomNormal * PDotN;
				}
				else
				{
					m_SlidingVec = Vector3(0.f, 0.f, 0.f);
				}
			}
			else
			{
				m_SlidingVec = Vector3(0.f, 0.f, 0.f);
			}
		}

		else if (((FieldObj->GetWorldRot().z >= 89.f) && (FieldObj->GetWorldRot().z <= 91.f))
			|| ((FieldObj->GetWorldRot().z <= -269.f) && (FieldObj->GetWorldRot().z >= -271.f)))
		{
			if ((MyDir.z > 0.f) && (Box->GetInfo().Pos[3].x < MyPos.x) &&
				(Box->GetInfo().Pos[1].x > MyPos.x) && (MyPos.z < Box->GetInfo().Center.z))
			{
				int PlayerAngle = (int)AxisDir.Angle(Box->GetInfo().NearNormal);
				if ((PlayerAngle <= 90) && (PlayerAngle >= -90))
				{
					float PDotN = AxisDir.Dot(Box->GetInfo().NearNormal);
					m_SlidingVec = AxisDir - Box->GetInfo().NearNormal * PDotN;
				}
				else
				{
					m_SlidingVec = Vector3(0.f, 0.f, 0.f);
				}
			}
			else if ((MyDir.z < 0.f) && (Box->GetInfo().Pos[3].x < MyPos.x) &&
				(Box->GetInfo().Pos[1].x > MyPos.x) && (MyPos.z > Box->GetInfo().Center.z))
			{
				int PlayerAngle = (int)AxisDir.Angle(Box->GetInfo().FarNormal);
				if ((PlayerAngle <= 90) && (PlayerAngle >= -90))
				{
					float PDotN = AxisDir.Dot(Box->GetInfo().FarNormal);
					m_SlidingVec = AxisDir - Box->GetInfo().FarNormal * PDotN;
				}
				else
				{
					m_SlidingVec = Vector3(0.f, 0.f, 0.f);
				}
			}
			else if ((MyDir.x > 0.f) && (Box->GetInfo().Pos[3].z < MyPos.z) &&
				(Box->GetInfo().Pos[7].z > MyPos.z) && (MyPos.x < Box->GetInfo().Center.x))
			{
				int PlayerAngle = (int)AxisDir.Angle(Box->GetInfo().BottomNormal);
				if ((PlayerAngle <= 90) && (PlayerAngle >= -90))
				{
					float PDotN = AxisDir.Dot(Box->GetInfo().BottomNormal);
					m_SlidingVec = AxisDir - Box->GetInfo().BottomNormal * PDotN;
				}
				else
				{
					m_SlidingVec = Vector3(0.f, 0.f, 0.f);
				}
			}
			else if ((MyDir.x < 0.f) && (Box->GetInfo().Pos[3].z < MyPos.z) &&
				(Box->GetInfo().Pos[7].z > MyPos.z) && (MyPos.x > Box->GetInfo().Center.x))
			{
				int PlayerAngle = (int)AxisDir.Angle(Box->GetInfo().TopNormal);
				if ((PlayerAngle <= 90) && (PlayerAngle >= -90))
				{
					float PDotN = AxisDir.Dot(Box->GetInfo().TopNormal);
					m_SlidingVec = AxisDir - Box->GetInfo().TopNormal * PDotN;
				}
				else
				{
					m_SlidingVec = Vector3(0.f, 0.f, 0.f);
				}
			}
			else
			{
				m_SlidingVec = Vector3(0.f, 0.f, 0.f);
			}
		}

		else if (((FieldObj->GetWorldRot().y >= 89.f) && (FieldObj->GetWorldRot().y <= 91.f))
			|| ((FieldObj->GetWorldRot().y <= -269.f) && (FieldObj->GetWorldRot().y >= -271.f)))
		{
			if ((MyDir.z > 0.f) && (Box->GetInfo().Pos[7].x < MyPos.x) &&
				(Box->GetInfo().Pos[3].x > MyPos.x) && (MyPos.z < Box->GetInfo().Center.z))
			{
				int PlayerAngle = (int)AxisDir.Angle(Box->GetInfo().LeftNormal);
				if ((PlayerAngle <= 90) && (PlayerAngle >= -90))
				{
					float PDotN = AxisDir.Dot(Box->GetInfo().LeftNormal);
					m_SlidingVec = AxisDir - Box->GetInfo().LeftNormal * PDotN;
				}
				else
				{
					m_SlidingVec = Vector3(0.f, 0.f, 0.f);
				}
			}
			else if ((MyDir.z < 0.f) && (Box->GetInfo().Pos[7].x < MyPos.x) &&
				(Box->GetInfo().Pos[3].x > MyPos.x) && (MyPos.z > Box->GetInfo().Center.z))
			{
				int PlayerAngle = (int)AxisDir.Angle(Box->GetInfo().RightNormal);
				if ((PlayerAngle <= 90) && (PlayerAngle >= -90))
				{
					float PDotN = AxisDir.Dot(Box->GetInfo().RightNormal);
					m_SlidingVec = AxisDir - Box->GetInfo().RightNormal * PDotN;
				}
				else
				{
					m_SlidingVec = Vector3(0.f, 0.f, 0.f);
				}
			}
			else if ((MyDir.x > 0.f) && (Box->GetInfo().Pos[2].z < MyPos.z) &&
				(Box->GetInfo().Pos[3].z > MyPos.z) && (MyPos.x < Box->GetInfo().Center.x))
			{
				int PlayerAngle = (int)AxisDir.Angle(Box->GetInfo().FarNormal);
				if ((PlayerAngle <= 90) && (PlayerAngle >= -90))
				{
					float PDotN = AxisDir.Dot(Box->GetInfo().FarNormal);
					m_SlidingVec = AxisDir - Box->GetInfo().FarNormal * PDotN;
				}
				else
				{
					m_SlidingVec = Vector3(0.f, 0.f, 0.f);
				}
			}
			else if ((MyDir.x < 0.f) && (Box->GetInfo().Pos[2].z < MyPos.z) &&
				(Box->GetInfo().Pos[3].z > MyPos.z) && (MyPos.x > Box->GetInfo().Center.x))
			{
				int PlayerAngle = (int)AxisDir.Angle(Box->GetInfo().NearNormal);
				if ((PlayerAngle <= 90) && (PlayerAngle >= -90))
				{
					float PDotN = AxisDir.Dot(Box->GetInfo().NearNormal);
					m_SlidingVec = AxisDir - Box->GetInfo().NearNormal * PDotN;
				}
				else
				{
					m_SlidingVec = Vector3(0.f, 0.f, 0.f);
				}
			}
			else
			{
				m_SlidingVec = Vector3(0.f, 0.f, 0.f);
			}
		}

		else if (((FieldObj->GetWorldRot().y <= -89.f) && (FieldObj->GetWorldRot().y >= -91.f))
			|| ((FieldObj->GetWorldRot().y >= 269.f) && (FieldObj->GetWorldRot().y <= 271.f)))
		{
			if ((MyDir.z > 0.f) && (Box->GetInfo().Pos[2].x < MyPos.x) &&
				(Box->GetInfo().Pos[6].x > MyPos.x) && (MyPos.z < Box->GetInfo().Center.z))
			{
				int PlayerAngle = (int)AxisDir.Angle(Box->GetInfo().RightNormal);
				if ((PlayerAngle <= 90) && (PlayerAngle >= -90))
				{
					float PDotN = AxisDir.Dot(Box->GetInfo().RightNormal);
					m_SlidingVec = AxisDir - Box->GetInfo().RightNormal * PDotN;
				}
				else
				{
					m_SlidingVec = Vector3(0.f, 0.f, 0.f);
				}
			}
			else if ((MyDir.z < 0.f) && (Box->GetInfo().Pos[26].x < MyPos.x) &&
				(Box->GetInfo().Pos[6].x > MyPos.x) && (MyPos.z > Box->GetInfo().Center.z))
			{
				int PlayerAngle = (int)AxisDir.Angle(Box->GetInfo().LeftNormal);
				if ((PlayerAngle <= 90) && (PlayerAngle >= -90))
				{
					float PDotN = AxisDir.Dot(Box->GetInfo().LeftNormal);
					m_SlidingVec = AxisDir - Box->GetInfo().LeftNormal * PDotN;
				}
				else
				{
					m_SlidingVec = Vector3(0.f, 0.f, 0.f);
				}
			}
			else if ((MyDir.x > 0.f) && (Box->GetInfo().Pos[7].z < MyPos.z) &&
				(Box->GetInfo().Pos[6].z > MyPos.z) && (MyPos.x < Box->GetInfo().Center.x))
			{
				int PlayerAngle = (int)AxisDir.Angle(Box->GetInfo().NearNormal);
				if ((PlayerAngle <= 90) && (PlayerAngle >= -90))
				{
					float PDotN = AxisDir.Dot(Box->GetInfo().NearNormal);
					m_SlidingVec = AxisDir - Box->GetInfo().NearNormal * PDotN;
				}
				else
				{
					m_SlidingVec = Vector3(0.f, 0.f, 0.f);
				}
			}
			else if ((MyDir.x < 0.f) && (Box->GetInfo().Pos[7].z < MyPos.z) &&
				(Box->GetInfo().Pos[6].z > MyPos.z) && (MyPos.x > Box->GetInfo().Center.x))
			{
				int PlayerAngle = (int)AxisDir.Angle(Box->GetInfo().FarNormal);
				if ((PlayerAngle <= 90) && (PlayerAngle >= -90))
				{
					float PDotN = AxisDir.Dot(Box->GetInfo().FarNormal);
					m_SlidingVec = AxisDir - Box->GetInfo().FarNormal * PDotN;
				}
				else
				{
					m_SlidingVec = Vector3(0.f, 0.f, 0.f);
				}
			}
			else
			{
				m_SlidingVec = Vector3(0.f, 0.f, 0.f);
			}
		}
		else
		{
			Vector3 Dir = Vector3(m_Mesh->GetWorldPos() - FieldObj->GetWorldPos());
			Dir.Normalize();
			Dir *= -1;
			m_Mesh->AddWorldPos(Dir * CurSpeed * DeltaTime * 2.f);
		}

	}
}

void CBarnos::CheckStuck()
{
	float t1 = Vector3(DestMovePoint - pFieldObj->GetWorldPos()).Length();
	float t2 = (float)sqrt(pow(FieldColInfo.Length.x, 2) + pow(FieldColInfo.Length.y, 2) + pow(FieldColInfo.Length.z, 2));

	if (t1 < t2)
	{
		if (IsChase)
		{

			DestMovePoint = FindPlayerAroundPos();
			RotateTo(DestMovePoint);
		}
		else
		{

			DestMovePoint = FindNextMovePoint();
			RotateTo(DestMovePoint);

		}
	}
}

void CBarnos::SetNotify()
{
	m_Mesh->GetAnimationInstance()->SetEndFunction<CBarnos>("barnosgliding", this, &CBarnos::FlyNotify);
	m_Mesh->GetAnimationInstance()->SetEndFunction<CBarnos>("barnoshitdead", this, &CBarnos::DeadNotify1);
	m_Mesh->GetAnimationInstance()->SetEndFunction<CBarnos>("barnosroll", this, &CBarnos::DeadNotify2);
	m_Mesh->GetAnimationInstance()->SetEndFunction<CBarnos>("barnoshit", this, &CBarnos::GetHitEndNotify);
	m_Mesh->GetAnimationInstance()->SetEndFunction<CBarnos>("barnosscream", this, &CBarnos::ScreamEndNotify);
	m_Mesh->GetAnimationInstance()->SetEndFunction<CBarnos>("barnosattack1", this, &CBarnos::AttackEndNotify);
	m_Mesh->GetAnimationInstance()->SetEndFunction<CBarnos>("barnosattack2", this, &CBarnos::AttackEndNotify);
	m_Mesh->GetAnimationInstance()->SetEndFunction<CBarnos>("barnosattack3", this, &CBarnos::AttackEndNotify);

}

void CBarnos::FlyNotify()
{
	if (IsIdle)
	{
		m_Mesh->GetAnimationInstance()->ChangeAnimation("barnosfly1");
	}
	else
	{
		m_Mesh->GetAnimationInstance()->ChangeAnimation("barnosfly2");
	}




}

void CBarnos::DeadNotify1()
{
	m_Mesh->GetAnimationInstance()->ChangeAnimation("barnosroll");

}

void CBarnos::DeadNotify2()
{
	AddWorldRotationX(20);
	AddWorldRotationY(80.f);
	m_Mesh->GetAnimationInstance()->ChangeAnimation("barnosdead");
	CResourceManager::GetInst()->SoundPlay("BarnosDeath");

}

void CBarnos::ToIdleNotify()
{
	FSM.ChangeState("Idle");
}

void CBarnos::ScreamEndNotify()
{
	FSM.ChangeState("Chase");
}

void CBarnos::AttackEndNotify()
{
	FSM.ChangeState("IdleMove");
}

void CBarnos::GetHitEndNotify()
{
	if (IsIdle)
	{
		FSM.ChangeState("Scream");
	}
	else
	{
		FSM.ChangeState("Chase");
	}

}




void CBarnos::OnCollisionBegin(const CollisionResult& result)
{
	if (result.Dest->GetGameObject()->CheckType<CArrow>())
	{
		if (IsDead)
			return;

		if (HP <= 0)
		{
			FSM.ChangeState("Death");
		}
		else
		{
			if (AccDamage >= Threshold)
			{
				FSM.ChangeState("GetHit");
				AccDamage = 0.f;
			}
		}


	}
	if (result.Dest->GetGameObject()->CheckType<CDragonArrow>())
	{
		if (IsDead)
			return;

		CDragonArrow* dragonarrow = (CDragonArrow*)result.Dest->GetGameObject();

		if (2 != (int)dragonarrow->GetDragonArrowState())
			return;

		
		if (HP <= 0)
		{
			FSM.ChangeState("Death");
		}
		else
		{
			if (!IsStun)
			{
				FSM.ChangeState("GetHit");
			}
			
		}
	}




}

void CBarnos::OnCollisionEnd(const CollisionResult& result)
{
}

void CBarnos::AttackOnCollisionBegin(const CollisionResult& result)
{
	std::string t = result.Dest->GetGameObject()->GetName();
	if (result.Dest->GetGameObject()->GetName() == "Player")
	{
		if (IsAttacking)
		{

		}
	}
}

void CBarnos::AttackOnCollisionEnd(const CollisionResult& result)
{
}

void CBarnos::SlidingOnCollisionBegin(const CollisionResult& result)
{	
	if (result.Dest->GetCollisionProfile()->Name == "FieldObj")
	{
		IsOnFieldCol = true;

		pFieldObj = result.Dest->GetGameObject();
		FieldColInfo = ((CColliderBox3D*)result.Dest)->GetInfo();
		strcpy_s(m_FieldObjName, result.Dest->GetGameObject()->GetName().c_str());

	}
}

void CBarnos::SlidingOnCollisionEnd(const CollisionResult& result)
{
	if (result.Dest->GetCollisionProfile()->Name == "FieldObj")
	{
		pFieldObj = nullptr;
		IsOnFieldCol = false;

		memset(m_FieldObjName, 0, sizeof(char) * 32);
		m_SlidingVec = Vector3(0.f, 0.f, 0.f);
	}
}

