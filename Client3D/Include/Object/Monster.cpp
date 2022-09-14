#include "Monster.h"
#include "Engine.h"

int CMonster::RandCount = 0;
int CMonster::KestodonCount = 0;
int CMonster::BarnosCount = 0;
int CMonster::VespoidCount = 0;
void CMonster::RotateTo(Vector3 v)
{
	int TargetDimension = 0;
	int MyX = (int)GetWorldPos().x;
	int MyZ = (int)GetWorldPos().z;
	int TX = (int)v.x;
	int TZ = (int)v.z;

	if (TX > MyX && TZ > MyZ)
	{
		TargetDimension = 1;
	}
	else if (TX > MyX && TZ < MyZ)
	{
		TargetDimension = 2;
	}
	else if (TX < MyX && TZ < MyZ)
	{
		TargetDimension = 3;
	}
	else if (TX < MyX && TZ > MyZ)
	{
		TargetDimension = 4;
	}
	else if (TX == MyX && TZ > MyZ)//5, 6, 7, 8�� z���, x���, z����, x����
	{
		TargetDimension = 5;
	}
	else if (TX > MyX && TZ == MyZ)
	{
		TargetDimension = 6;
	}
	else if (TX == MyX && TZ < MyZ)
	{
		TargetDimension = 7;
	}
	else if (TX < MyX && TZ == MyZ)
	{
		TargetDimension = 8;
	}

	Vector3 DestVec;
	Vector3 StartVec;
	DestVec.x = v.x;
	DestVec.y = 0;
	DestVec.z = v.z;

	StartVec.x = GetWorldPos().x;
	StartVec.y = 0;
	StartVec.z = GetWorldPos().z;

	int RotAngle = (int)Vector3(0, 0, -1).Angle(DestVec - StartVec);
	if (RotAngle > 90)
	{
		RotAngle %= 91;
	}

	if (1 == TargetDimension)
	{
		RotAngle = 90 - RotAngle;
		AddWorldRotationY(-CurYRot);
		AddWorldRotationY((float)RotAngle);
		CurYRot = (float)RotAngle;

	}
	else if (2 == TargetDimension)
	{
		RotAngle = 90 - RotAngle;
		AddWorldRotationY(-CurYRot);
		AddWorldRotationY(RotAngle + 90.f);
		CurYRot = RotAngle + 90.f;
	}
	else if (3 == TargetDimension)
	{
		AddWorldRotationY(-CurYRot);
		AddWorldRotationY(RotAngle + 180.f);
		CurYRot = RotAngle + 180.f;
	}
	else if (4 == TargetDimension)
	{
		AddWorldRotationY(-CurYRot);
		AddWorldRotationY(RotAngle + 270.f);
		CurYRot = RotAngle + 270.f;
	}
	else if (5 == TargetDimension)
	{
		AddWorldRotationY(-CurYRot);
		AddWorldRotationY(0);
		CurYRot = 0;
	}
	else if (6 == TargetDimension)
	{
		AddWorldRotationY(-CurYRot);
		AddWorldRotationY(90);
		CurYRot = 90;
	}
	else if (7 == TargetDimension)
	{
		AddWorldRotationY(-CurYRot);
		AddWorldRotationY(180);
		CurYRot = 180;
	}
	else if (8 == TargetDimension)
	{
		AddWorldRotationY(-CurYRot);
		AddWorldRotationY(270.f);
		CurYRot = 270.f;
	}
}


void CMonster::Move(Vector3 Dest)
{
	float DeltaTime = CEngine::GetInst()->GetDeltaTime();
		
	if (Transform_State::Ground == m_State)
	{
		Vector3 tDest = Dest;
		Vector3 tMyPos = GetWorldPos();

		tDest.y = 0;
		tMyPos.y = 0;


		Vector3 DirVec = tDest - tMyPos;
		DirVec.Normalize();
		Vector3 TargetPos = tDest;
		Vector3 Vec = GetWorldPos();

		static float aStep;
		static Vector3 EndV;

		// ������ ���⿡ �ð� ���� ���ؼ� ���ݾ� �̵��ϰ� �Ѵ�
		aStep = DeltaTime * MoveSpeed; //�̹��� �Ѱ��� ���� (����)

		EndV = TargetPos - tMyPos;
		if (EndV.Length() <= aStep)  //��ǥ�������� �Ÿ����� ������ ũ�ų� ������ �������� ����.
		{
			IsMoving = false;

		}
		else
		{
			Vector3 temp = DirVec * aStep;

			if (0 == m_SlidingVec.x && 0 == m_SlidingVec.y && 0 == m_SlidingVec.z)
			{
				AddRelativePos(temp);
			}
			else
			{
				AddRelativePos(m_SlidingVec*aStep);
			}
			
		}
	}
	else
	{
		Vector3 DirVec = Dest - GetWorldPos();
		DirVec.Normalize();
		Vector3 TargetPos = Dest;
		Vector3 Vec = GetWorldPos();

		static float aStep;
		static Vector3 EndV;

		// ������ ���⿡ �ð� ���� ���ؼ� ���ݾ� �̵��ϰ� �Ѵ�
		aStep = DeltaTime * MoveSpeed; //�̹��� �Ѱ��� ���� (����)

		EndV = TargetPos - GetWorldPos();
		if (EndV.Length() <= aStep)  //��ǥ�������� �Ÿ����� ������ ũ�ų� ������ �������� ����.
		{
			IsMoving = false;

		}
		else
		{
			if (0 == m_SlidingVec.x && 0 == m_SlidingVec.y && 0 == m_SlidingVec.z)
			{
				Vector3 temp = DirVec * aStep;
				AddRelativePos(temp);
			}
			else
			{
				AddRelativePos(m_SlidingVec * aStep);
			}			
		}
	}
}

bool CMonster::SortPos(const CollisionBoxInfo& Begin, const CollisionBoxInfo& End)
{
	return Begin.Dist < End.Dist;
}