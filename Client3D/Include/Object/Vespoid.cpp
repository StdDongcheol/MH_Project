#include "Vespoid.h"
#include "VespoidAnimation.h"
#include "Input.h"
#include "Resource/Animation/AnimationSequence.h"
#include "Engine.h"
#include "Scene/SceneManager.h"
#include "Player.h"
#include "Arrow.h"
#include "DragonArrow.h"
#include "Collision/Collision.h"
#include "../ClientManager3D.h"

CVespoid::CVespoid()
{
	SetTypeID<CVespoid>();
	IdleTime = 0.f;
	MoveTime= 0.f;
	AttackTime= 0.f;
	StartAttackTime= 0.f;
	EndAttackTime= 0.f;

	attacktype = 0;
	MoveDist = 0.f;
	ChaseAccTime = 0.f;
	ChaseIdleTime = 0.f;

	HP = 150;

	pPlayer = nullptr;

	IsLegUp = false;

}

CVespoid::CVespoid(const CVespoid& obj)
{
	m_Mesh = (CAnimationMeshComponent*)FindComponent("Mesh");

}

CVespoid::~CVespoid()
{
}

bool CVespoid::Init()
{


	


	m_Mesh = CreateComponent<CAnimationMeshComponent>("Mesh");
	

	ColliderUpperBody = CreateComponent<CColliderBox3D>("ColliderUpperBody");
	ColliderLowerBody = CreateComponent<CColliderBox3D>("ColliderLowerBody");

	ColliderAttack = CreateComponent<CColliderBox3D>("ColliderAttack");


	ColliderUpperBody->Set3DExtent(2.0f, 1.0f, 2.0f);
	ColliderLowerBody->Set3DExtent(1.0f, 1.0f, 1.0f);
	
	ColliderAttack->Set3DExtent(0.5f, 1.5f, 0.5f);	

	ColliderUpperBody->SetCollisionProfile("Monster");
	ColliderLowerBody->SetCollisionProfile("Monster");
	
	ColliderAttack->SetCollisionProfile("MonsterAttack");

	ColliderUpperBody->AddCollisionCallback(Collision_State::Begin, this, &CVespoid::OnCollisionBegin);
	ColliderUpperBody->AddCollisionCallback(Collision_State::End, this, &CVespoid::OnCollisionEnd);
	ColliderLowerBody->AddCollisionCallback(Collision_State::Begin, this, &CVespoid::OnCollisionBegin);
	ColliderLowerBody->AddCollisionCallback(Collision_State::End, this, &CVespoid::OnCollisionEnd);
	
	ColliderAttack->AddCollisionCallback(Collision_State::Begin, this, &CVespoid::AttackOnCollisionBegin);
	ColliderAttack->AddCollisionCallback(Collision_State::End, this, &CVespoid::AttackOnCollisionEnd);








	SetRootComponent(m_Mesh);
	m_Mesh->SetTransformState(Transform_State::None);
	m_State = Transform_State::None;
	m_Mesh->SetMesh("VespoidMesh");
	m_Mesh->CreateAnimationInstance<CVespoidAnimation>();

	m_Mesh->SetRelativeScale(0.05f, 0.05f, 0.05f);
	m_Mesh->SetRelativePos(10.f, 10.f, 10.f);
	m_Mesh->SetRelativeRotation(Vector3(250.f, 180.f, 180.f));

	m_Mesh->AddChild(ColliderUpperBody, "UpperBody");
	m_Mesh->AddChild(ColliderLowerBody, "LowerBody");	
	m_Mesh->AddChild(ColliderAttack, "Attack");

	
	ColliderCarving = CreateComponent<CColliderBox3D>("ColliderCarving");
	ColliderCarving->Set3DExtent(4.0f, 4.0f, 4.0f);
	ColliderCarving->SetCollisionProfile("Carving");
	m_Mesh->AddChild(ColliderCarving);
	ColliderCarving->Enable(false);

	ColliderSliding = CreateComponent<CColliderBox3D>("ColliderSliding");
	ColliderSliding->Set3DExtent(2.0f, 2.0f, 2.0f);
	ColliderSliding->SetOffset(0.0f, 2.0f, 0.0f);
	ColliderSliding->SetCollisionProfile("MonsterSliding");
	m_Mesh->AddChild(ColliderSliding);
	ColliderSliding->Enable(true);
	ColliderSliding->AddCollisionCallback(Collision_State::Begin, this, &CVespoid::SlidingOnCollisionBegin);
	ColliderSliding->AddCollisionCallback(Collision_State::End, this, &CVespoid::SlidingOnCollisionEnd);
	
	SetNotify();



	//fsm에 함수포인터를 이용해 상태 생성 
	FSM.CreateState("Idle", this, &CVespoid::IDLEStay, &CVespoid::IDLEStart, &CVespoid::IDLEEnd);
	FSM.CreateState("Move", this, &CVespoid::MOVEStay, &CVespoid::MOVEStart, &CVespoid::MOVEEnd);	
	FSM.CreateState("GetHit", this, &CVespoid::GETHITStay, &CVespoid::GETHITStart, &CVespoid::GETHITEnd);
	FSM.CreateState("Attack", this, &CVespoid::ATTACKStay, &CVespoid::ATTACKStart, &CVespoid::ATTACKEnd);
	FSM.CreateState("Death", this, &CVespoid::DEATHStay, &CVespoid::DEATHStart, &CVespoid::DEATHEnd);
	FSM.CreateState("Scream", this, &CVespoid::SCREAMStay, &CVespoid::SCREAMStart, &CVespoid::SCREAMEnd);
	FSM.CreateState("Chase", this, &CVespoid::CHASEStay, &CVespoid::CHASEStart, &CVespoid::CHASEEnd);
	FSM.CreateState("FadeOut", this, &CVespoid::FADEOUTStay, &CVespoid::FADEOUTStart, &CVespoid::FADEOUTEnd);

	
	CResourceManager::GetInst()->LoadSound("Vespoid", true, "VespoidWing" + std::to_string(VespoidCount), "Monster/Vespoid/wing.ogg", SOUND_PATH);
	WingSound = CResourceManager::GetInst()->FindSound("VespoidWing" + std::to_string(VespoidCount));
	
	++VespoidCount;


	
	
	this;

	return true;
}

void CVespoid::Start()
{
	CGameObject::Start();

	pPlayer = (CPlayer*)CSceneManager::GetInst()->GetScene()->GetPlayerObject();
	//상태 변경
	FSM.ChangeState("Idle");
}

void CVespoid::Update(float DeltaTime)
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

void CVespoid::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);



	
}

CVespoid* CVespoid::Clone()
{
	return new CVespoid(*this);
}



Vector3 CVespoid::FindNextMovePoint()
{
	Vector3 DestVec;
	srand((unsigned int)time(0) + RandCount++);


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


	MoveDist = Vector3(DestVec - GetWorldPos()).Length();



	return DestVec;

}

Vector3 CVespoid::FindPlayerAroundPos()
{
	Vector3 DestVec;
	srand((unsigned int)time(0) + RandCount++);


	if (rand() % 2 == 1)
	{
		srand((unsigned int)time(0) + RandCount++);
		DestVec.x = pPlayer->GetWorldPos().x - (rand() % 2 + 1);
	}
	else
	{
		srand((unsigned int)time(0) + RandCount++);
		DestVec.x = pPlayer->GetWorldPos().x + (rand() % 2 + 1);
	}



	srand((unsigned int)time(0) + RandCount++);
	if (rand() % 2 == 1)
	{
		srand((unsigned int)time(0) + RandCount++);
		DestVec.z = (pPlayer->GetWorldPos().z) - (rand() % 2 + 1);
	}
	else
	{
		srand((unsigned int)time(0) + RandCount++);
		DestVec.z = pPlayer->GetWorldPos().z + (rand() % 2 + 1);
	}

	DestVec.y = pPlayer->GetWorldPos().y + (rand() % 2)+2;

	float y = m_Scene->GetNavigation3DManager()->GetY(DestVec);
	if (DestVec.y <= y + 6)
	{
		DestVec.y = y + 6;
	}

	MoveDist = Vector3(DestVec - GetWorldPos()).Length();

	return DestVec;
}

void CVespoid::YPosCorrection()
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

void CVespoid::FieldCollision(float DeltaTime)
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

void CVespoid::CheckStuck()
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



void CVespoid::SetNotify()
{
	m_Mesh->GetAnimationInstance()->SetEndFunction<CVespoid>("vespoidlegup", this, &CVespoid::LegUpEndNotify);
	m_Mesh->GetAnimationInstance()->SetEndFunction<CVespoid>("vespoidattack1", this, &CVespoid::ToIdleNotify);
	m_Mesh->GetAnimationInstance()->SetEndFunction<CVespoid>("vespoidattack2", this, &CVespoid::ToIdleNotify);
	m_Mesh->GetAnimationInstance()->SetEndFunction<CVespoid>("vespoiddeath1", this, &CVespoid::Death1EndNotify);
	m_Mesh->GetAnimationInstance()->SetEndFunction<CVespoid>("vespoidscream", this, &CVespoid::ScreamEndNotify);
	m_Mesh->GetAnimationInstance()->SetEndFunction<CVespoid>("vespoidhit1", this, &CVespoid::GetHitEndNotify);
}

void CVespoid::LegUpEndNotify()
{
	m_Mesh->GetAnimationInstance()->ChangeAnimation("vespoidfly3");
}


void CVespoid::Death1EndNotify()
{
	m_Mesh->GetAnimationInstance()->ChangeAnimation("vespoiddeath2");
	AddWorldPos(Vector3(0, -1, 0));
}

void CVespoid::ToIdleNotify()
{
	FSM.ChangeState("Idle");
}

void CVespoid::ScreamEndNotify()
{
	FSM.ChangeState("Chase");
}

void CVespoid::GetHitEndNotify()
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

void CVespoid::OnCollisionBegin(const CollisionResult& result)
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

				CClientManager3D::GetInst()->PlayBattleBGM(BGM_Type::MonsterBattle);
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

void CVespoid::OnCollisionEnd(const CollisionResult& result)
{
}

void CVespoid::AttackOnCollisionBegin(const CollisionResult& result)
{
	std::string t = result.Dest->GetGameObject()->GetName();
	if (result.Dest->GetGameObject()->GetName() == "Player")
	{
		if (IsAttacking)
		{

		}
	}
}

void CVespoid::AttackOnCollisionEnd(const CollisionResult& result)
{
}

void CVespoid::SlidingOnCollisionBegin(const CollisionResult& result)
{
	if (result.Dest->GetCollisionProfile()->Name == "FieldObj")
	{
		IsOnFieldCol = true;
		pFieldObj = result.Dest->GetGameObject();
		FieldColInfo = ((CColliderBox3D*)result.Dest)->GetInfo();
		strcpy_s(m_FieldObjName, result.Dest->GetGameObject()->GetName().c_str());

	}
}

void CVespoid::SlidingOnCollisionEnd(const CollisionResult& result)
{
	if (result.Dest->GetCollisionProfile()->Name == "FieldObj")
	{
		pFieldObj = nullptr;
		IsOnFieldCol = false;
		memset(m_FieldObjName, 0, sizeof(char) * 32);
		m_SlidingVec = Vector3(0.f, 0.f, 0.f);
	}
}


