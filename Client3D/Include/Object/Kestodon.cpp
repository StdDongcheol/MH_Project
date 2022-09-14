#include "Kestodon.h"
#include "KestodonAnimation.h"
#include "Input.h"
#include "Resource/Animation/AnimationSequence.h"
#include "Engine.h"
#include "Scene/SceneManager.h"
#include "Player.h"
#include "Arrow.h"
#include "DragonArrow.h"
#include "Collision/Collision.h"

CKestodon::CKestodon() 
{
	SetTypeID<CKestodon>();
	IdleTime = 0.f;
	MoveTime = 0.f;
	AttackTime = 0.f;
	DodgeTime = 0.f;
	
	pPlayer = nullptr;

	IsCharging = false;
	IsDodged = false;
	
	MoveSpeed = 5;
	HP = 250.f;	
}

CKestodon::CKestodon(const CKestodon& obj)
{
	m_Mesh = (CAnimationMeshComponent*)FindComponent("Mesh");
	
}

CKestodon::~CKestodon()
{
}

bool CKestodon::Init()
{
	m_Mesh = CreateComponent<CAnimationMeshComponent>("Mesh");
	
	ColliderHead = CreateComponent<CColliderBox3D>("ColliderHead");
	ColliderUpperBody = CreateComponent<CColliderBox3D>("ColliderUpperBody");
	ColliderLowerBody = CreateComponent<CColliderBox3D>("ColliderLowerBody");
	ColliderLowerLowerBody = CreateComponent<CColliderBox3D>("ColliderLowerLowerBody");
	ColliderTail = CreateComponent<CColliderBox3D>("ColliderTail");
	ColliderLeftLeg = CreateComponent<CColliderBox3D>("ColliderLeftLeg");
	ColliderRightLeg = CreateComponent<CColliderBox3D>("ColliderRightLeg");
	ColliderHeadAttack = CreateComponent<CColliderBox3D>("ColliderHeadAttack");

	ColliderHead->Set3DExtent(2.5f, 2.5f, 2.5f);
	ColliderUpperBody->Set3DExtent(2.f, 2.f, 2.f);
	ColliderLowerBody->Set3DExtent(3.f, 3.f, 3.f);
	ColliderLowerLowerBody->Set3DExtent(2.f, 2.f, 2.f);
	ColliderTail->Set3DExtent(2.f, 2.f, 2.f);
	ColliderLeftLeg->Set3DExtent(1.2f, 1.8f, 1.2f);
	ColliderRightLeg->Set3DExtent(1.2f, 1.8f, 1.2f);
	ColliderHeadAttack->Set3DExtent(2.5f, 2.5f, 2.5f);
	
	ColliderHead->SetCollisionProfile("Monster");
	ColliderUpperBody->SetCollisionProfile("Monster");
	ColliderLowerBody->SetCollisionProfile("Monster");
	ColliderLowerLowerBody->SetCollisionProfile("Monster");
	ColliderTail->SetCollisionProfile("Monster");
	ColliderLeftLeg->SetCollisionProfile("Monster");
	ColliderRightLeg->SetCollisionProfile("Monster");
	ColliderHeadAttack->SetCollisionProfile("MonsterAttack");
	
	ColliderHead->AddCollisionCallback(Collision_State::Begin, this, &CKestodon::OnCollisionBegin);
	ColliderHead->AddCollisionCallback(Collision_State::End, this, &CKestodon::OnCollisionEnd);
	ColliderUpperBody->AddCollisionCallback(Collision_State::Begin, this, &CKestodon::OnCollisionBegin);
	ColliderUpperBody->AddCollisionCallback(Collision_State::End, this, &CKestodon::OnCollisionEnd);
	ColliderLowerBody->AddCollisionCallback(Collision_State::Begin, this, &CKestodon::OnCollisionBegin);
	ColliderLowerBody->AddCollisionCallback(Collision_State::End, this, &CKestodon::OnCollisionEnd);
	ColliderLowerLowerBody->AddCollisionCallback(Collision_State::Begin, this, &CKestodon::OnCollisionBegin);
	ColliderLowerLowerBody->AddCollisionCallback(Collision_State::End, this, &CKestodon::OnCollisionEnd);
	ColliderTail->AddCollisionCallback(Collision_State::Begin, this, &CKestodon::OnCollisionBegin);
	ColliderTail->AddCollisionCallback(Collision_State::End, this, &CKestodon::OnCollisionEnd);
	ColliderLeftLeg->AddCollisionCallback(Collision_State::Begin, this, &CKestodon::OnCollisionBegin);
	ColliderLeftLeg->AddCollisionCallback(Collision_State::End, this, &CKestodon::OnCollisionEnd);
	ColliderRightLeg->AddCollisionCallback(Collision_State::Begin, this, &CKestodon::OnCollisionBegin);
	ColliderRightLeg->AddCollisionCallback(Collision_State::End, this, &CKestodon::OnCollisionEnd);
	ColliderHeadAttack->AddCollisionCallback(Collision_State::Begin, this, &CKestodon::AttackOnCollisionBegin);
	ColliderHeadAttack->AddCollisionCallback(Collision_State::End, this, &CKestodon::AttackOnCollisionEnd);
	

	SetRootComponent(m_Mesh);
	m_Mesh->SetTransformState(Transform_State::Ground);
	m_State = Transform_State::Ground;
	m_Mesh->SetMesh("KestodonMesh");
	m_Mesh->CreateAnimationInstance<CKestodonAnimation>();

	m_Mesh->SetRelativeScale(0.05f, 0.05f, 0.05f);
	m_Mesh->SetRelativePos(40.f, 0.f, 10.f);
	m_Mesh->SetRelativeRotation(Vector3(270.f, 180.f, 180.f));
	m_Mesh->SetRelativePos(60.f, 0.f, 60.f);

	m_Mesh->AddChild(ColliderHead, "Head");
	m_Mesh->AddChild(ColliderUpperBody, "UpperBody");
	m_Mesh->AddChild(ColliderLowerBody, "LowerBody");
	m_Mesh->AddChild(ColliderLowerLowerBody, "LowerLowerBody");
	m_Mesh->AddChild(ColliderTail, "Tail");
	m_Mesh->AddChild(ColliderLeftLeg, "LeftLeg");
	m_Mesh->AddChild(ColliderRightLeg, "RightLeg");
	m_Mesh->AddChild(ColliderHeadAttack, "Head");

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
	ColliderSliding->AddCollisionCallback(Collision_State::Begin, this, &CKestodon::SlidingOnCollisionBegin);
	ColliderSliding->AddCollisionCallback(Collision_State::End, this, &CKestodon::SlidingOnCollisionEnd);
	

	SetNotify();

	

	//fsm에 함수포인터를 이용해 상태 생성 
	FSM.CreateState("Idle", this, &CKestodon::IDLEStay, &CKestodon::IDLEStart, &CKestodon::IDLEEnd);
	FSM.CreateState("Move", this, &CKestodon::MOVEStay, &CKestodon::MOVEStart, &CKestodon::MOVEEnd);
	FSM.CreateState("Attack1", this, &CKestodon::ATTACK1Stay, &CKestodon::ATTACK1Start, &CKestodon::ATTACK1End);
	FSM.CreateState("Attack2", this, &CKestodon::ATTACK2Stay, &CKestodon::ATTACK2Start, &CKestodon::ATTACK2End);
	FSM.CreateState("Death", this, &CKestodon::DEATHStay, &CKestodon::DEATHStart, &CKestodon::DEATHEnd);

	FSM.CreateState("Dodge", this, &CKestodon::DODGEStay, &CKestodon::DODGEStart, &CKestodon::DODGEEnd);
	FSM.CreateState("Scream", this, &CKestodon::SCREAMStay, &CKestodon::SCREAMStart, &CKestodon::SCREAMEnd);
	FSM.CreateState("GetHit", this, &CKestodon::GETHITStay, &CKestodon::GETHITStart, &CKestodon::GETHITEnd);
	FSM.CreateState("FadeOut", this, &CKestodon::FADEOUTStay, &CKestodon::FADEOUTStart, &CKestodon::FADEOUTEnd);



	CResourceManager::GetInst()->LoadSound("Kestodon", true, "KestodonCharge"+std::to_string(KestodonCount), "Monster/Kestodon/charge.ogg", SOUND_PATH);
	AttackSound = CResourceManager::GetInst()->FindSound("KestodonCharge" + std::to_string(KestodonCount));
	++KestodonCount;
	

	this;

	return true;
}

void CKestodon::Start()
{
	CGameObject::Start();

	pPlayer = (CPlayer*)CSceneManager::GetInst()->GetScene()->GetPlayerObject();
	//상태 변경
	FSM.ChangeState("Idle");

}

void CKestodon::Update(float DeltaTime)
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

void CKestodon::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CKestodon* CKestodon::Clone()
{
	return new CKestodon(*this);
}

Vector3 CKestodon::FindNextMovePoint()
{
	Vector3 DestVec = GetWorldPos();
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
		DestVec.z = GetWorldPos().z - (rand() % 10 + 8);
	}
	else
	{
		srand((unsigned int)time(0) + RandCount++);
		DestVec.z = GetWorldPos().z + (rand() % 10 + 8);
	}

	return DestVec;
}

Vector3 CKestodon::FindPlayerAroundPos()
{
	Vector3 DestVec;
	srand((unsigned int)time(0) + RandCount++);


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
	return DestVec;
}

void CKestodon::TakeNestAction()
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

void CKestodon::TakeAttack()
{
	
	FSM.ChangeState("Attack2");

	srand((unsigned int)time(NULL));
	int r = rand() % 2;
	if (r == 0)
	{
		FSM.ChangeState("Attack1");
	}
	else if (r == 1)
	{
		FSM.ChangeState("Attack2");
	}

	
}

void CKestodon::FieldCollision(float DeltaTime)
{
	Vector3 Dir=Vector3(pFieldObj->GetWorldPos()-GetWorldPos());
	Dir.Normalize();
	Dir *= -1;
	AddWorldPos(Dir * CurSpeed * DeltaTime*2);

	
	
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

void CKestodon::CheckStuck()
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


void CKestodon::SetNotify()
{
	m_Mesh->GetAnimationInstance()->SetEndFunction<CKestodon>("kestodonattack1", this, &CKestodon::Attack1EndNotify);
	m_Mesh->GetAnimationInstance()->SetEndFunction<CKestodon>("kestodonattack2", this, &CKestodon::Attack2EndNotify);
	m_Mesh->GetAnimationInstance()->SetEndFunction<CKestodon>("kestodonattack3", this, &CKestodon::Attack3EndNotify);

	m_Mesh->GetAnimationInstance()->SetEndFunction<CKestodon>("kestodonscream2", this, &CKestodon::ScreamEndNotify);

	m_Mesh->GetAnimationInstance()->SetEndFunction<CKestodon>("kestodonattack4", this, &CKestodon::TakeNestAction);
	m_Mesh->GetAnimationInstance()->SetEndFunction<CKestodon>("kestodonattackc", this, &CKestodon::TakeNestAction);
	m_Mesh->GetAnimationInstance()->SetEndFunction<CKestodon>("kestodondodgeback1", this, &CKestodon::TakeNestAction);

	m_Mesh->GetAnimationInstance()->SetEndFunction<CKestodon>("kestodongethit1", this, &CKestodon::GetHitEndNotify);
	m_Mesh->GetAnimationInstance()->SetEndFunction<CKestodon>("kestodongethit2", this, &CKestodon::GetHitEndNotify);
}
void CKestodon::Attack1EndNotify()
{
	m_Mesh->GetAnimationInstance()->ChangeAnimation("kestodonattack2");
	
}
void CKestodon::Attack2EndNotify()
{
	m_Mesh->GetAnimationInstance()->ChangeAnimation("kestodonattack3");
	
}
void CKestodon::Attack3EndNotify()
{
	m_Mesh->GetAnimationInstance()->ChangeAnimation("kestodonattack4");
	
}

void CKestodon::ToIdleNotify()
{
	FSM.ChangeState("Idle");
}

void CKestodon::ScreamEndNotify()
{
	FSM.ChangeState("Move");
}



void CKestodon::GetHitEndNotify()
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

void CKestodon::OnCollisionBegin(const CollisionResult& result)
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

void CKestodon::OnCollisionEnd(const CollisionResult& result)
{
	
}

void CKestodon::AttackOnCollisionBegin(const CollisionResult& result)
{
	
	if (result.Dest->GetGameObject()->GetName() == "Player")
	{
		if (IsAttacking)
		{

		}
	}
}

void CKestodon::AttackOnCollisionEnd(const CollisionResult& result)
{
}

void CKestodon::SlidingOnCollisionBegin(const CollisionResult& result)
{
	/*if ("FieldObj" == result.Dest->GetCollisionProfile()->Name)
	{
		
		pTestObj = result.Dest->GetGameObject();
		IsOnFieldCol = true;
		FieldColInfo = ((CColliderBox3D*)result.Dest)->GetInfo();

	}*/

	if (result.Dest->GetCollisionProfile()->Name == "FieldObj")
	{
		IsOnFieldCol = true;
		FieldColInfo = ((CColliderBox3D*)result.Dest)->GetInfo();
		pFieldObj = result.Dest->GetGameObject();
		strcpy_s(m_FieldObjName, result.Dest->GetGameObject()->GetName().c_str());
		
	}
}

void CKestodon::SlidingOnCollisionEnd(const CollisionResult& result)
{
	/*if ("FieldObj" == result.Dest->GetCollisionProfile()->Name)
	{		
		pTestObj = nullptr;
		IsOnFieldCol = false;
	}*/

	if (result.Dest->GetCollisionProfile()->Name == "FieldObj")
	{
		pFieldObj = nullptr;
		IsOnFieldCol = false;

		memset(m_FieldObjName, 0, sizeof(char) * 32);
		m_SlidingVec = Vector3(0.f, 0.f, 0.f);
	}
}
