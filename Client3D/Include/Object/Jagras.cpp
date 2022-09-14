#include "Jagras.h"
#include "JagrasAnimation.h"
#include "Input.h"
#include "Resource/Animation/AnimationSequence.h"
#include "Engine.h"
#include "Scene/SceneManager.h"
#include "Player.h"
#include "Arrow.h"
#include "DragonArrow.h"
#include "Collision/Collision.h"

CJagras::CJagras()	
{
	SetTypeID<CJagras>();
	IdleTime = 0.f;
	MoveTime = 0.f;
	AttackTime = 0.f;
	DodgeTime = 0.f;

	Attack1Move = false;	
	IsDodged = false;
	
	pPlayer = nullptr;

	MoveSpeed = 5;
	HP = 200.f;	
}

CJagras::CJagras(const CJagras& obj)
{
	m_Mesh = (CAnimationMeshComponent*)FindComponent("Mesh");
	
}

CJagras::~CJagras()
{
}

bool CJagras::Init()
{




	m_Mesh = CreateComponent<CAnimationMeshComponent>("Mesh");
	

	ColliderHead = CreateComponent<CColliderBox3D>("ColliderHead");
	ColliderBody1= CreateComponent<CColliderBox3D>("ColliderBody1");
	ColliderBody2= CreateComponent<CColliderBox3D>("ColliderBody2");
	ColliderBody3= CreateComponent<CColliderBox3D>("ColliderBody3");
	ColliderBody4= CreateComponent<CColliderBox3D>("ColliderBody4");
	ColliderBody5 = CreateComponent<CColliderBox3D>("ColliderBody5");
	ColliderTail1= CreateComponent<CColliderBox3D>("ColliderTail1");
	ColliderTail2= CreateComponent<CColliderBox3D>("ColliderTail2");
	ColliderRightFrontLeg = CreateComponent<CColliderBox3D>("ColliderRightFrontLeg");
	ColliderLeftFrontLeg = CreateComponent<CColliderBox3D>("ColliderLeftFrontLeg");
	ColliderRightBackLeg = CreateComponent<CColliderBox3D>("ColliderRightBackLeg");
	ColliderLeftBackLeg = CreateComponent<CColliderBox3D>("ColliderLeftBackLeg");


	ColliderHeadAttack = CreateComponent<CColliderBox3D>("ColliderHeadAttack");
	ColliderLeftArmAttack = CreateComponent<CColliderBox3D>("ColliderLeftArmAttack");
	ColliderRightArmAttack = CreateComponent<CColliderBox3D>("ColliderRightArmAttack");

	ColliderHead->Set3DExtent(1.0f, 1.0f, 1.0f);
	ColliderBody1->Set3DExtent(1.5f, 1.5f, 1.5f);
	ColliderBody2->Set3DExtent(1.5f, 1.5f, 1.5f);
	ColliderBody3->Set3DExtent(1.5f, 1.5f, 1.5f);
	ColliderBody4->Set3DExtent(1.5f, 1.5f, 1.5f);
	ColliderBody5->Set3DExtent(1.5f, 1.5f, 1.5f);
	ColliderTail1->Set3DExtent(1.5f, 1.5f, 1.5f);
	ColliderTail2->Set3DExtent(1.0f, 1.0f, 1.0f);
	ColliderRightFrontLeg->Set3DExtent(1.0f, 1.5f, 1.0f);
	ColliderLeftFrontLeg->Set3DExtent(1.0f, 1.5f, 1.0f);
	ColliderRightBackLeg->Set3DExtent(1.0f, 1.5f, 1.0f);
	ColliderLeftBackLeg->Set3DExtent(1.0f, 1.5f, 1.0f);

	ColliderHeadAttack->Set3DExtent(1.0f, 1.0f, 1.0f);
	ColliderLeftArmAttack->Set3DExtent(1.0f, 1.0f, 1.0f);
	ColliderRightArmAttack->Set3DExtent(1.0f, 1.0f, 1.0f);

	ColliderHead->SetCollisionProfile("Monster");
	ColliderBody1->SetCollisionProfile("Monster");
	ColliderBody2->SetCollisionProfile("Monster");
	ColliderBody3->SetCollisionProfile("Monster");
	ColliderBody4->SetCollisionProfile("Monster");
	ColliderBody5->SetCollisionProfile("Monster");
	ColliderTail1->SetCollisionProfile("Monster");
	ColliderTail2->SetCollisionProfile("Monster");	
	ColliderRightFrontLeg->SetCollisionProfile("Monster");
	ColliderLeftFrontLeg->SetCollisionProfile("Monster");
	ColliderRightBackLeg->SetCollisionProfile("Monster");
	ColliderLeftBackLeg->SetCollisionProfile("Monster");

	ColliderHeadAttack->SetCollisionProfile("MonsterAttack");
	ColliderLeftArmAttack->SetCollisionProfile("MonsterAttack");
	ColliderRightArmAttack->SetCollisionProfile("MonsterAttack");

	ColliderHead->AddCollisionCallback(Collision_State::Begin, this, &CJagras::OnCollisionBegin);
	ColliderHead->AddCollisionCallback(Collision_State::End, this, &CJagras::OnCollisionEnd);
	ColliderBody1->AddCollisionCallback(Collision_State::Begin, this, &CJagras::OnCollisionBegin);
	ColliderBody1->AddCollisionCallback(Collision_State::End, this, &CJagras::OnCollisionEnd);
	ColliderBody2->AddCollisionCallback(Collision_State::Begin, this, &CJagras::OnCollisionBegin);
	ColliderBody2->AddCollisionCallback(Collision_State::End, this, &CJagras::OnCollisionEnd);
	ColliderBody3->AddCollisionCallback(Collision_State::Begin, this, &CJagras::OnCollisionBegin);
	ColliderBody3->AddCollisionCallback(Collision_State::End, this, &CJagras::OnCollisionEnd);
	ColliderBody4->AddCollisionCallback(Collision_State::Begin, this, &CJagras::OnCollisionBegin);
	ColliderBody4->AddCollisionCallback(Collision_State::End, this, &CJagras::OnCollisionEnd);
	ColliderBody5->AddCollisionCallback(Collision_State::Begin, this, &CJagras::OnCollisionBegin);
	ColliderBody5->AddCollisionCallback(Collision_State::End, this, &CJagras::OnCollisionEnd);
	ColliderTail1->AddCollisionCallback(Collision_State::Begin, this, &CJagras::OnCollisionBegin);
	ColliderTail1->AddCollisionCallback(Collision_State::End, this, &CJagras::OnCollisionEnd);
	ColliderTail2->AddCollisionCallback(Collision_State::Begin, this, &CJagras::OnCollisionBegin);
	ColliderTail2->AddCollisionCallback(Collision_State::End, this, &CJagras::OnCollisionEnd);
	ColliderRightFrontLeg->AddCollisionCallback(Collision_State::Begin, this, &CJagras::OnCollisionBegin);
	ColliderRightFrontLeg->AddCollisionCallback(Collision_State::End, this, &CJagras::OnCollisionEnd);
	ColliderLeftFrontLeg->AddCollisionCallback(Collision_State::Begin, this, &CJagras::OnCollisionBegin);
	ColliderLeftFrontLeg->AddCollisionCallback(Collision_State::End, this, &CJagras::OnCollisionEnd);
	ColliderRightBackLeg->AddCollisionCallback(Collision_State::Begin, this, &CJagras::OnCollisionBegin);
	ColliderRightBackLeg->AddCollisionCallback(Collision_State::End, this, &CJagras::OnCollisionEnd);
	ColliderLeftBackLeg->AddCollisionCallback(Collision_State::Begin, this, &CJagras::OnCollisionBegin);
	ColliderLeftBackLeg->AddCollisionCallback(Collision_State::End, this, &CJagras::OnCollisionEnd);
	ColliderHeadAttack->AddCollisionCallback(Collision_State::Begin, this, &CJagras::AttackOnCollisionBegin);
	ColliderHeadAttack->AddCollisionCallback(Collision_State::End, this, &CJagras::AttackOnCollisionEnd);
	ColliderLeftArmAttack->AddCollisionCallback(Collision_State::Begin, this, &CJagras::AttackOnCollisionBegin);
	ColliderLeftArmAttack->AddCollisionCallback(Collision_State::End, this, &CJagras::AttackOnCollisionEnd);
	ColliderRightArmAttack->AddCollisionCallback(Collision_State::Begin, this, &CJagras::AttackOnCollisionBegin);
	ColliderRightArmAttack->AddCollisionCallback(Collision_State::End, this, &CJagras::AttackOnCollisionEnd);

	ColliderCarving = CreateComponent<CColliderBox3D>("ColliderCarving");
	ColliderCarving->Set3DExtent(5.0f, 5.0f, 5.0f);
	ColliderCarving->SetCollisionProfile("Carving");
	m_Mesh->AddChild(ColliderCarving);
	ColliderCarving->Enable(false);

	ColliderSliding = CreateComponent<CColliderBox3D>("ColliderSliding");
	ColliderSliding->Set3DExtent(3.0f, 3.0f, 3.0f);
	ColliderSliding->SetOffset(0.0f, 3.0f, 0.0f);
	ColliderSliding->SetCollisionProfile("MonsterSliding");
	m_Mesh->AddChild(ColliderSliding);
	ColliderSliding->Enable(true);
	ColliderSliding->AddCollisionCallback(Collision_State::Begin, this, &CJagras::SlidingOnCollisionBegin);
	ColliderSliding->AddCollisionCallback(Collision_State::End, this, &CJagras::SlidingOnCollisionEnd);
	

	SetRootComponent(m_Mesh);
	m_Mesh->SetTransformState(Transform_State::Ground);
	m_State = Transform_State::Ground;
	m_Mesh->SetMesh("JagrasMesh");
	m_Mesh->CreateAnimationInstance<CJagrasAnimation>();

	m_Mesh->SetRelativeScale(0.05f, 0.05f, 0.05f);
	m_Mesh->SetRelativePos(50.f, 0.f, 60.f);
	m_Mesh->SetRelativeRotation(Vector3(270.f, 180.f, 180.f));

	m_Mesh->AddChild(ColliderHead, "Head");
	m_Mesh->AddChild(ColliderBody1, "Body1");
	m_Mesh->AddChild(ColliderBody2, "Body2");
	m_Mesh->AddChild(ColliderBody3, "Body3");
	m_Mesh->AddChild(ColliderBody4, "Body4");
	m_Mesh->AddChild(ColliderBody5, "Body5");
	m_Mesh->AddChild(ColliderTail1, "Tail1");
	m_Mesh->AddChild(ColliderTail2, "Tail2");	
	m_Mesh->AddChild(ColliderRightFrontLeg, "RightFrontLeg");
	m_Mesh->AddChild(ColliderLeftFrontLeg, "LeftFrontLeg");
	m_Mesh->AddChild(ColliderRightBackLeg, "RightBackLeg");
	m_Mesh->AddChild(ColliderLeftBackLeg, "LeftBackLeg");
	m_Mesh->AddChild(ColliderHeadAttack, "Head");
	m_Mesh->AddChild(ColliderLeftArmAttack, "LeftFoot");
	m_Mesh->AddChild(ColliderRightArmAttack, "RightFoot");
		
	SetNotify();

	//fsm에 함수포인터를 이용해 상태 생성 
	FSM.CreateState("Idle", this, &CJagras::IDLEStay, &CJagras::IDLEStart, &CJagras::IDLEEnd);
	FSM.CreateState("Move", this, &CJagras::MOVEStay, &CJagras::MOVEStart, &CJagras::MOVEEnd);
	FSM.CreateState("AttackLong", this, &CJagras::ATTACK1Stay, &CJagras::ATTACK1Start, &CJagras::ATTACK1End);
	FSM.CreateState("AttackMid", this, &CJagras::ATTACK2Stay, &CJagras::ATTACK2Start, &CJagras::ATTACK2End);
	FSM.CreateState("AttackShort", this, &CJagras::ATTACK3Stay, &CJagras::ATTACK3Start, &CJagras::ATTACK3End);
	FSM.CreateState("Death", this, &CJagras::DEATHStay, &CJagras::DEATHStart, &CJagras::DEATHEnd);
	FSM.CreateState("Dodge", this, &CJagras::DODGEStay, &CJagras::DODGEStart, &CJagras::DODGEEnd);
	
	FSM.CreateState("Scream", this, &CJagras::SCREAMStay, &CJagras::SCREAMStart, &CJagras::SCREAMEnd);
	FSM.CreateState("GetHit", this, &CJagras::GETHITStay, &CJagras::GETHITStart, &CJagras::GETHITEnd);
	FSM.CreateState("FadeOut", this, &CJagras::FADEOUTStay, &CJagras::FADEOUTStart, &CJagras::FADEOUTEnd);



	this;

	return true;
}

void CJagras::Start()
{
	CGameObject::Start();

	pPlayer = (CPlayer*)CSceneManager::GetInst()->GetScene()->GetPlayerObject();

	//상태 변경
	FSM.ChangeState("Idle");
}
	

void CJagras::Update(float DeltaTime)
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

	FSM.Update();//Update에서 매 프레임마다 fsm 상태 갱신

	if (IsOnFieldCol)
	{
		FieldCollision(DeltaTime);
		CheckStuck();
	}
}

void CJagras::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CJagras* CJagras::Clone()
{
	return new CJagras(*this);
}


Vector3 CJagras::FindNextMovePoint()
{
	Vector3 DestVec= GetWorldPos();
	srand((unsigned int)time(0)+ RandCount++);
	
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

	srand((unsigned int)time(0) + RandCount++);
	if (rand() % 2 == 1)
	{
		srand((unsigned int)time(0) + RandCount++);
		DestVec.z = GetWorldPos().z - (rand() % 10 + 8);
	}
	else
	{
		srand((unsigned int)time(0) + RandCount++);
		DestVec.z = GetWorldPos().z + (rand() % 10 + 8);
	}

	return DestVec;
}

Vector3 CJagras::FindPlayerAroundPos()
{
	Vector3 DestVec;
	srand((unsigned int)time(0) + RandCount++);


	if (rand() % 2 == 1)
	{
		DestVec.x = pPlayer->GetWorldPos().x - (rand() % 15 );
	}
	else
	{
		DestVec.x = pPlayer->GetWorldPos().x + (rand() % 15 );
	}
		
	srand((unsigned int)time(0) + RandCount++);

	if (rand() % 2 == 1)
	{
		DestVec.z = pPlayer->GetWorldPos().z - (rand() % 15);
	}
	else
	{
		DestVec.z = pPlayer->GetWorldPos().z + (rand() % 15 );
	}
	return DestVec;
}

void CJagras::TakeNestAction()
{
	srand((unsigned int)time(0) + RandCount++);
	int t = rand() % 4;
	if (0 == t)
	{
		if (true == IsDodged)
		{
			FSM.ChangeState("Move");
			IsDodged = false;
		}
		else
		{
			FSM.ChangeState("Dodge");
		}		
	}
	else
	{
		FSM.ChangeState("Move");
		IsDodged = false;
	}
}

void CJagras::TakeAttack()
{
	Vector3 Dist = pPlayer->GetWorldPos() - GetWorldPos();
	float Distf = Dist.Length();
	if (Distf < 12.f)
	{
		FSM.ChangeState("AttackShort");
	}
	else if (Distf >= 12.f && Distf <20.f)
	{
		FSM.ChangeState("AttackMid");
	}
	else if (Distf >= 20.f)
	{
		FSM.ChangeState("AttackLong");
	}	
}

void CJagras::FieldCollision(float DeltaTime)
{
	Vector3 Dir = Vector3(pFieldObj->GetWorldPos() - GetWorldPos());
	Dir.Normalize();
	Dir *= -1;
	AddWorldPos(Dir * CurSpeed * DeltaTime * 2);

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

void CJagras::CheckStuck()
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


void CJagras::SetNotify()
{
	m_Mesh->GetAnimationInstance()->SetEndFunction<CJagras>("jagrasattack1", this, &CJagras::Attack1EndNotify);
	m_Mesh->GetAnimationInstance()->SetEndFunction<CJagras>("jagrasattack2", this, &CJagras::Attack2EndNotify);
	m_Mesh->GetAnimationInstance()->SetEndFunction<CJagras>("jagrasattack3", this, &CJagras::Attack3EndNotify);

	m_Mesh->GetAnimationInstance()->SetEndFunction<CJagras>("jagrasroll", this, &CJagras::RollEndNotify);
	m_Mesh->GetAnimationInstance()->SetEndFunction<CJagras>("jagrasscream", this, &CJagras::ScreamEndNotify);
	
	m_Mesh->GetAnimationInstance()->SetEndFunction<CJagras>("jagrasattackb", this, &CJagras::TakeNestAction);
	m_Mesh->GetAnimationInstance()->SetEndFunction<CJagras>("jagrasattackc", this, &CJagras::TakeNestAction);
	m_Mesh->GetAnimationInstance()->SetEndFunction<CJagras>("jagrasdodgeback", this, &CJagras::TakeNestAction);

	m_Mesh->GetAnimationInstance()->SetEndFunction<CJagras>("jagrashit1", this, &CJagras::GetHitEndNotify);
	m_Mesh->GetAnimationInstance()->SetEndFunction<CJagras>("jagrashit2", this, &CJagras::GetHitEndNotify);


}

void CJagras::Attack1EndNotify()
{
	Attack1Move = true;
	IsAttacking = true;
	m_Mesh->GetAnimationInstance()->ChangeAnimation("jagrasattack2");
}

void CJagras::Attack2EndNotify()
{
	Attack1Move = false;
	m_Mesh->GetAnimationInstance()->ChangeAnimation("jagrasattack3");
}

void CJagras::Attack3EndNotify()
{
	
	m_Mesh->GetAnimationInstance()->ChangeAnimation("jagrasattack1");
	AddWorldPos(GetWorldAxis(AXIS_Y) * 4.5);
	TakeNestAction();
}

void CJagras::RollEndNotify()
{
	m_Mesh->GetAnimationInstance()->ChangeAnimation("jagrasstandup");
}

void CJagras::ScreamEndNotify()
{
	FSM.ChangeState("Move");
}

void CJagras::AttackEndNotify()
{
}

void CJagras::GetHitEndNotify()
{
	if (IsChase)
	{
		TakeNestAction();
	}
	else
	{
		FSM.ChangeState("Scream");
	}
}

void CJagras::OnCollisionBegin(const CollisionResult& result)
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

void CJagras::OnCollisionEnd(const CollisionResult& result)
{
}

void CJagras::AttackOnCollisionBegin(const CollisionResult& result)
{
	std::string t = result.Dest->GetGameObject()->GetName();
	if (result.Dest->GetGameObject()->GetName() == "Player")
	{
		if (IsAttacking)
		{

		}
	}
}

void CJagras::AttackOnCollisionEnd(const CollisionResult& result)
{
}

void CJagras::SlidingOnCollisionBegin(const CollisionResult& result)
{
	if (result.Dest->GetCollisionProfile()->Name == "FieldObj")
	{
		IsOnFieldCol = true;

		FieldColInfo = ((CColliderBox3D*)result.Dest)->GetInfo();
		pFieldObj = result.Dest->GetGameObject();
		strcpy_s(m_FieldObjName, result.Dest->GetGameObject()->GetName().c_str());

	}
	
}

void CJagras::SlidingOnCollisionEnd(const CollisionResult& result)
{
	if (result.Dest->GetCollisionProfile()->Name == "FieldObj")
	{
		pFieldObj = nullptr;
		IsOnFieldCol = false;

		memset(m_FieldObjName, 0, sizeof(char) * 32);
		m_SlidingVec = Vector3(0.f, 0.f, 0.f);
	}
}

