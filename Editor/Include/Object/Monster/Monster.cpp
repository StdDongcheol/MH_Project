#include "Monster.h"
#include "Engine.h"

void CMonster::RotateTo(Vector3 v)
{
	int TargetDimension = 0;
	float MyX = GetWorldPos().x;
	float MyZ = GetWorldPos().z;
	float TX = v.x;
	float TZ = v.z;

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
	else if (TX == MyX && TZ > MyZ)//5, 6, 7, 8은 z축양, x축양, z축음, x축음
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
		AddWorldRotationY((float)RotAngle + 90.f);
		CurYRot = (float)RotAngle + 90.f;
	}
	else if (3 == TargetDimension)
	{
		AddWorldRotationY(-CurYRot);
		AddWorldRotationY((float)RotAngle + 180.f);
		CurYRot = (float)RotAngle + 180.f;
	}
	else if (4 == TargetDimension)
	{
		AddWorldRotationY(-CurYRot);
		AddWorldRotationY((float)RotAngle + 270.f);
		CurYRot = (float)RotAngle + 270.f;
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

		// 가야할 방향에 시간 값을 곱해서 조금씩 이동하게 한다
		aStep = DeltaTime * 10; //이번에 한걸음 길이 (보폭)

		EndV = TargetPos - tMyPos;
		if (EndV.Length() <= aStep)  //목표점까지의 거리보다 보폭이 크거나 같으면 도착으로 본다.
		{
			IsMoving = false;

		}
		else
		{
			Vector3 temp = DirVec * aStep;
			AddRelativePos(temp);
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

		// 가야할 방향에 시간 값을 곱해서 조금씩 이동하게 한다
		aStep = DeltaTime * 10; //이번에 한걸음 길이 (보폭)

		EndV = TargetPos - GetWorldPos();
		if (EndV.Length() <= aStep)  //목표점까지의 거리보다 보폭이 크거나 같으면 도착으로 본다.
		{
			IsMoving = false;

		}
		else
		{
			Vector3 temp = DirVec * aStep;
			AddRelativePos(temp);
		}
	}
	
	

}