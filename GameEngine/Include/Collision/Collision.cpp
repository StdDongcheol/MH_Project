#include "Collision.h"
#include "../Component/ColliderBox2D.h"
#include "../Component/ColliderCircle.h"
#include "../Component/ColliderPixel.h"
#include "../Component/ColliderSphere.h"
#include "../Component/ColliderBox3D.h"

bool CCollision::CollisionBox2DToBox2D(CColliderBox2D* Src, CColliderBox2D* Dest)
{
	CollisionResult srcResult, destResult;

	// �浹�� �Ǿ������ ���´�.
	if (CollisionBox2DToBox2D(srcResult, destResult, Src->GetInfo(), Dest->GetInfo()))
	{
		// srcResult�� �ڱ� �ڽ��� �浹 ����̱⶧����
		// Src�� Src���� �ְ�
		// Dest�� Dest �� �ִ´�
		srcResult.Src = Src;
		srcResult.Dest = Dest;

		// destResult�� ������ �浹 ����̱� ������
		// Src�� Dest �ڽ��� �ְ�
		// Dest�� ������ Src�� �ִ´�.
		destResult.Src = Dest;
		destResult.Dest = Src;

		Src->m_Result = srcResult;
		Dest->m_Result = destResult;


		return true;
	}

	return false;
}

bool CCollision::CollisionCircleToCircle(CColliderCircle* Src, CColliderCircle* Dest)
{
	CollisionResult srcResult, destResult;

	// �浹�� �Ǿ������ ���´�.
	if (CollisionCircleToCircle(srcResult, destResult, Src->GetInfo(), Dest->GetInfo()))
	{
		// srcResult�� �ڱ� �ڽ��� �浹 ����̱⶧����
		// Src�� Src���� �ְ�
		// Dest�� Dest �� �ִ´�
		srcResult.Src = Src;
		srcResult.Dest = Dest;

		// destResult�� ������ �浹 ����̱� ������
		// Src�� Dest �ڽ��� �ְ�
		// Dest�� ������ Src�� �ִ´�.
		destResult.Src = Dest;
		destResult.Dest = Src;

		Src->m_Result = srcResult;
		Dest->m_Result = destResult;

		return true;
	}

	return false;
}

bool CCollision::CollisionBox2DToCircle(CColliderBox2D* Src, CColliderCircle* Dest)
{
	CollisionResult srcResult, destResult;

	// �浹�� �Ǿ������ ���´�.
	if (CollisionBox2DToCircle(srcResult, destResult, Src->GetInfo(), Dest->GetInfo()))
	{
		// srcResult�� �ڱ� �ڽ��� �浹 ����̱⶧����
		// Src�� Src���� �ְ�
		// Dest�� Dest �� �ִ´�
		srcResult.Src = Src;
		srcResult.Dest = Dest;

		// destResult�� ������ �浹 ����̱� ������
		// Src�� Dest �ڽ��� �ְ�
		// Dest�� ������ Src�� �ִ´�.
		destResult.Src = Dest;
		destResult.Dest = Src;

		Src->m_Result = srcResult;
		Dest->m_Result = destResult;

		return true;
	}

	return false;
}

bool CCollision::CollisionBox2DToPixel(CColliderBox2D* Src, CColliderPixel* Dest)
{
	CollisionResult srcResult, destResult;

	// �浹�� �Ǿ������ ���´�.
	if (CollisionBox2DToPixel(srcResult, destResult, Src->GetInfo(), Dest->GetInfo()))
	{
		// srcResult�� �ڱ� �ڽ��� �浹 ����̱⶧����
		// Src�� Src���� �ְ�
		// Dest�� Dest �� �ִ´�
		srcResult.Src = Src;
		srcResult.Dest = Dest;

		// destResult�� ������ �浹 ����̱� ������
		// Src�� Dest �ڽ��� �ְ�
		// Dest�� ������ Src�� �ִ´�.
		destResult.Src = Dest;
		destResult.Dest = Src;

		Src->m_Result = srcResult;
		Dest->m_Result = destResult;


		return true;
	}

	return false;
}

bool CCollision::CollisionCircleToPixel(CColliderCircle* Src, CColliderPixel* Dest)
{
	CollisionResult srcResult, destResult;

	// �浹�� �Ǿ������ ���´�.
	if (CollisionCircleToPixel(srcResult, destResult, Src->GetInfo(), Dest->GetInfo()))
	{
		// srcResult�� �ڱ� �ڽ��� �浹 ����̱⶧����
		// Src�� Src���� �ְ�
		// Dest�� Dest �� �ִ´�
		srcResult.Src = Src;
		srcResult.Dest = Dest;

		// destResult�� ������ �浹 ����̱� ������
		// Src�� Dest �ڽ��� �ְ�
		// Dest�� ������ Src�� �ִ´�.
		destResult.Src = Dest;
		destResult.Dest = Src;

		Src->m_Result = srcResult;
		Dest->m_Result = destResult;


		return true;
	}

	return false;
}

bool CCollision::CollisionBox2DToBox2D(CollisionResult& SrcResult, CollisionResult& DestResult,
	const Box2DInfo& Src, const Box2DInfo& Dest)
{
	Vector2	CenterDir = Src.Center - Dest.Center;

	Vector2	Axis = Src.Axis[0];

	float	CenterProjDist = abs(CenterDir.Dot(Axis));

	float	r1, r2;

	r1 = Src.Length.x;
	// ���� ���������̱� ������ Length�� �����־� ���̸�ŭ�� ���� ���� ���� �������ִ°�
	r2 = abs(Dest.Axis[0].Dot(Axis) * Dest.Length.x) +
		abs(Dest.Axis[1].Dot(Axis) * Dest.Length.y);

	if (CenterProjDist > r1 + r2)
		return false;

	Axis = Src.Axis[1];

	CenterProjDist = abs(CenterDir.Dot(Axis));

	r1 = Src.Length.y;
	r2 = abs(Dest.Axis[0].Dot(Axis) * Dest.Length.x) +
		abs(Dest.Axis[1].Dot(Axis) * Dest.Length.y);

	if (CenterProjDist > r1 + r2)
		return false;

	Axis = Dest.Axis[0];

	CenterProjDist = abs(CenterDir.Dot(Axis));

	r1 = Dest.Length.x;
	r2 = abs(Src.Axis[0].Dot(Axis) * Src.Length.x) +
		abs(Src.Axis[1].Dot(Axis) * Src.Length.y);

	if (CenterProjDist > r1 + r2)
		return false;

	Axis = Dest.Axis[1];

	CenterProjDist = abs(CenterDir.Dot(Axis));

	r1 = Dest.Length.y;
	r2 = abs(Src.Axis[0].Dot(Axis) * Src.Length.x) +
		abs(Src.Axis[1].Dot(Axis) * Src.Length.y);

	if (CenterProjDist > r1 + r2)
		return false;

	return true;
}

bool CCollision::CollisionCircleToCircle(CollisionResult& SrcResult, CollisionResult& DestResult, const CircleInfo& Src, const CircleInfo& Dest)
{
	float Distance = Src.Center.Distance(Dest.Center);

	// �� �� ������ �Ÿ��� �� ���� ���������� ���� ������ ũ��
	// �浹�̰� �� �۴ٸ� �浹�� �ƴϴ�
	return Distance <= Src.Radius + Dest.Radius;
}

bool CCollision::CollisionBox2DToCircle(CollisionResult& SrcResult, CollisionResult& DestResult, const Box2DInfo& Src, const CircleInfo& Dest)
{
	Vector2 CenterDir = Src.Center - Dest.Center;

	// Box x�� ����
	Vector2 Axis = Src.Axis[0];

	float CenterProjDist = abs(CenterDir.Dot(Axis));

	float r1, r2;

	// Src�� x�� y�࿡�ٰ� ������ �ϱ⶧��
	// Src�� Length�״�ΰ� ���´�
	// ���� ��� ���� ������ �ϵ��� ������ ����
	r1 = Src.Length.x;
	r2 = Dest.Radius;

	// ������ �����Ÿ��� r1 + r2���� ũ�� return false;
	if (CenterProjDist > r1 + r2)
		return false;

	// ������ y�� ����
	Axis = Src.Axis[1];

	CenterProjDist = abs(CenterDir.Dot(Axis));

	r1 = Src.Length.y;
	r2 = Dest.Radius;

	if (CenterProjDist > r1 + r2)
		return false;

	// ������ �߽ɹ������� ����
	// �� ���ͳ����� �Ÿ��� Normalize�ؼ� ����
	Axis = CenterDir;
	Axis.Normalize();

	// ���Ϳ� ������ ����
	CenterProjDist = CenterDir.Length();

	r1 = abs(Src.Axis[0].Dot(Axis) * Src.Length.x) +
		abs(Src.Axis[1].Dot(Axis) * Src.Length.y);
	// ���� ��� ������ �ص� �������� ����
	r2 = Dest.Radius;

	if (CenterProjDist > r1 + r2)
		return false;

	return true;
}

bool CCollision::CollisionBox2DToPixel(CollisionResult& SrcResult, CollisionResult& DestResult, const Box2DInfo& Src, const PixelInfo& Dest)
{
	// �ڽ� To �ڽ��� �ִ��� ���� �Ǵ��� �ؾ��Ѵ�.
	if (!CollisionBox2DToBox2D(SrcResult, DestResult, Src, Dest.Box))
		return false;

	// �������� ���Ѵ�.
	float Left = Src.Min.x < Dest.Min.x ? Dest.Min.x : Src.Min.x;
	float Right = Src.Max.x > Dest.Max.x ? Dest.Max.x : Src.Max.x;

	float Bottom = Src.Min.y < Dest.Min.y ? Dest.Min.y : Src.Min.y;
	float Top = Src.Max.y > Dest.Max.y ? Dest.Max.y : Src.Max.y;

	// ���� ���������� �� �ϴ� ��ǥ�� ���Ѵ�.
	// ���Ϳ��� ������ x,y�� ���ش�.
	Vector2 LB = Dest.Box.Center - Dest.Box.Length;

	// ���������� ��� ��ǥ�� �����ش�.
	Left -= LB.x;
	Right -= LB.x;

	Bottom -= LB.y;
	Top -= LB.y;

	// Left�� Bottom�� ����� 0�� �Ǿ�� �ȵȴ� ����ó��
	Left = Left < 0.f ? 0.f : Left;
	Bottom = Bottom < 0.f ? 0.f : Bottom;

	// Right�� Top�� ���� �ȼ��̹����� ���ο� ����ũ�⸦ �Ѿ�� �ȵȴ�.
	Right = Right >= (float)Dest.Width ? (float)Dest.Width - 1.f : Right;
	Top = Top >= (float)Dest.Height ? (float)Dest.Height - 1.f : Top;

	// �̹����� �»�ܺ��� �����̱� ������
	// �ȼ����������� ��ǥ�� �����ش�.

	Top = Dest.Height - Top;
	Bottom = Dest.Height - Bottom;

	bool	Collision = false;

	// ������ ������ �ݺ��Ѵ�.
	for (int y = (int)Top; y < (int)Bottom; ++y)
	{
		for (int x = (int)Left; x < (int)Right; ++x)
		{
			// ���������� �ֱ� ������ * 4�� �Ѵ�
			int Index = y * (int)Dest.Width * 4 + x * 4;

			// ���� �ε����� �ȼ��� ���� �ڽ� �ȿ� �����ϴ����� �Ǵ��Ѵ�.
			// ���� �ȼ��� ������������� ��ġ�� �����ش�.
			// y �� ������ �ֱ� ������ �ٽ� ����� ������������� �ȼ� ��ġ�� �����ش�.
			Vector2	 PixelWorldPos = LB + Vector2((float)x, (float)Dest.Height - (float)y);

			// �浹�� �ȵǾ��ٸ� continue���ش�.
			// �ȼ��� �ڽ� �ȿ� ���Դ��� üũ�� �ϴ°�
			if (!CollisionBox2DToPoint(SrcResult, DestResult, Src, PixelWorldPos))
				continue;

			// ����ؼ� ������� �Դٸ� üũ�� �ؾ��Ѵ�.
			switch (Dest.Type)
			{
			case PixelCollision_Type::Color_Ignore:
				// �ȼ� �ε����� �÷��� ����Ʈ�� �÷������� �����ϸ� Ignore�̴ϱ� continue�� �Ѵ�
				if (Dest.Pixel[Index] == Dest.Color[0] &&
					Dest.Pixel[Index + 1] == Dest.Color[1] &&
					Dest.Pixel[Index + 2] == Dest.Color[2])
					continue;

				// �װ� �ƴ϶�� �浹�� �Ȱ��̴�.
				Collision = true;
				break;
			case PixelCollision_Type::Color_Confirm:
				// �ȼ� �ε����� �÷��� ����Ʈ�� �÷������� �����ϸ� Copnfirm�̴ϱ� Collision�� true�Ѵ�
				if (Dest.Pixel[Index] == Dest.Color[0] &&
					Dest.Pixel[Index + 1] == Dest.Color[1] &&
					Dest.Pixel[Index + 2] == Dest.Color[2])
					Collision = true;
				break;
			case PixelCollision_Type::Alpha_Ignore:
				// �ȼ� �ε����� ���Ŀ� ����Ʈ�� ���Ļ����� �����ϸ� Ignore�̴ϱ� continue�� �Ѵ�
				if (Dest.Pixel[Index + 3] == Dest.Color[3])
					continue;

				Collision = true;
				break;
			case PixelCollision_Type::Alpha_Confirm:
				// �ȼ� �ε����� ���Ŀ� ����Ʈ�� ���Ļ����� �����ϸ� Copnfirm�̴ϱ� Collision�� true�Ѵ�
				if (Dest.Pixel[Index + 3] == Dest.Color[3])
					Collision = true;
				break;
			}

			if (Collision)
				break;
		}

		if (Collision)
			break;
	}

	return Collision;
}

bool CCollision::CollisionCircleToPixel(CollisionResult& SrcResult, CollisionResult& DestResult, const CircleInfo& Src, const PixelInfo& Dest)
{
	// �ڽ� To �ڽ��� �ִ��� ���� �Ǵ��� �ؾ��Ѵ�.
	if (!CollisionBox2DToCircle(SrcResult, DestResult, Dest.Box, Src))
		return false;

	// �������� ���Ѵ�.
	float Left = Src.Min.x < Dest.Min.x ? Dest.Min.x : Src.Min.x;
	float Right = Src.Max.x > Dest.Max.x ? Dest.Max.x : Src.Max.x;

	float Bottom = Src.Min.y < Dest.Min.y ? Dest.Min.y : Src.Min.y;
	float Top = Src.Max.y > Dest.Max.y ? Dest.Max.y : Src.Max.y;

	// ���� ���������� �� �ϴ� ��ǥ�� ���Ѵ�.
	// ���Ϳ��� ������ x,y�� ���ش�.
	Vector2 LB = Dest.Box.Center - Dest.Box.Length;

	// ���������� ��� ��ǥ�� �����ش�.
	Left -= LB.x;
	Right -= LB.x;

	Bottom -= LB.y;
	Top -= LB.y;

	// Left�� Bottom�� ����� 0�� �Ǿ�� �ȵȴ� ����ó��
	Left = Left < 0.f ? 0.f : Left;
	Bottom = Bottom < 0.f ? 0.f : Bottom;

	// Right�� Top�� ���� �ȼ��̹����� ���ο� ����ũ�⸦ �Ѿ�� �ȵȴ�.
	Right = Right >= (float)Dest.Width ? (float)Dest.Width - 1.f : Right;
	Top = Top >= (float)Dest.Height ? (float)Dest.Height - 1.f : Top;

	// �̹����� �»�ܺ��� �����̱� ������
	// �ȼ����������� ��ǥ�� �����ش�.

	Top = Dest.Height - Top;
	Bottom = Dest.Height - Bottom;

	bool	Collision = false;

	// ������ ������ �ݺ��Ѵ�.
	for (int y = (int)Top; y < (int)Bottom; ++y)
	{
		for (int x = (int)Left; x < (int)Right; ++x)
		{
			// ���������� �ֱ� ������ * 4�� �Ѵ�
			int Index = y * (int)Dest.Width * 4 + x * 4;

			// ���� �ε����� �ȼ��� ���� �ڽ� �ȿ� �����ϴ����� �Ǵ��Ѵ�.
			// ���� �ȼ��� ������������� ��ġ�� �����ش�.
			// y �� ������ �ֱ� ������ �ٽ� ����� ������������� �ȼ� ��ġ�� �����ش�.
			Vector2	 PixelWorldPos = LB + Vector2((float)x, (float)Dest.Height - (float)y);

			// �浹�� �ȵǾ��ٸ� continue���ش�.
			// �ȼ��� �� �ȿ� ���Դ��� üũ�� �ϴ°�
			if (!CollisionCircleToPoint(SrcResult, DestResult, Src, PixelWorldPos))
				continue;

			// ����ؼ� ������� �Դٸ� üũ�� �ؾ��Ѵ�.
			switch (Dest.Type)
			{
			case PixelCollision_Type::Color_Ignore:
				// �ȼ� �ε����� �÷��� ����Ʈ�� �÷������� �����ϸ� Ignore�̴ϱ� continue�� �Ѵ�
				if (Dest.Pixel[Index] == Dest.Color[0] &&
					Dest.Pixel[Index + 1] == Dest.Color[1] &&
					Dest.Pixel[Index + 2] == Dest.Color[2])
					continue;

				// �װ� �ƴ϶�� �浹�� �Ȱ��̴�.
				Collision = true;
				break;
			case PixelCollision_Type::Color_Confirm:
				// �ȼ� �ε����� �÷��� ����Ʈ�� �÷������� �����ϸ� Copnfirm�̴ϱ� Collision�� true�Ѵ�
				if (Dest.Pixel[Index] == Dest.Color[0] &&
					Dest.Pixel[Index + 1] == Dest.Color[1] &&
					Dest.Pixel[Index + 2] == Dest.Color[2])
					Collision = true;
				break;
			case PixelCollision_Type::Alpha_Ignore:
				// �ȼ� �ε����� ���Ŀ� ����Ʈ�� ���Ļ����� �����ϸ� Ignore�̴ϱ� continue�� �Ѵ�
				if (Dest.Pixel[Index + 3] == Dest.Color[3])
					continue;

				Collision = true;
				break;
			case PixelCollision_Type::Alpha_Confirm:
				// �ȼ� �ε����� ���Ŀ� ����Ʈ�� ���Ļ����� �����ϸ� Copnfirm�̴ϱ� Collision�� true�Ѵ�
				if (Dest.Pixel[Index + 3] == Dest.Color[3])
					Collision = true;
				break;
			}

			if (Collision)
				break;
		}

		if (Collision)
			break;
	}

	return Collision;
}

bool CCollision::CollisionBox2DToPoint(CollisionResult& SrcResult, CollisionResult& DestResult,
	const Box2DInfo& BoxInfo, const Vector2& Point)
{
	// obb �� �� �浹
	// ������ x, y�࿡ ���� �����Ͽ� ������ ��ġ���� �Ǵ��Ѵ�.

	// ���� ����
	Vector2 CenterDir = BoxInfo.Center - Point;

	Vector2 Axis = BoxInfo.Axis[0];

	// �����Ҷ� -���� ������ �ȵǾ abs�� �̿��Ͽ� ���밪���� ������ ����
	float CenterProjDist = abs(CenterDir.Dot(Axis));

	// CenterProjDist �� BoxInfo�� Length.x���� ũ�� �浹�� �ȵȰ��̴�.
	if (CenterProjDist > BoxInfo.Length.x)
		return false;

	Axis = BoxInfo.Axis[1];

	CenterProjDist = abs(CenterDir.Dot(Axis));

	// CenterProjDist �� BoxInfo�� Length.y���� ũ�� �浹�� �ȵȰ��̴�.
	if (CenterProjDist > BoxInfo.Length.y)
		return false;

	// �Ѵ� ����Ѱű� ������ true
	return true;
}

bool CCollision::CollisionCircleToPoint(CollisionResult& SrcResult, CollisionResult& DestResult, const CircleInfo& CircleInfo, const Vector2& Point)
{
	// ���� �߽ɰ� ����Ʈ�� �Ÿ�
	float	Dist = CircleInfo.Center.Distance(Point);

	// �������� ���̰� �ΰ��� �Ÿ����� ũ�ų� ������ �浹
	return CircleInfo.Radius >= Dist;
}

bool CCollision::CollisionPixelToPoint(CollisionResult& SrcResult,
	CollisionResult& DestResult, const PixelInfo& PixelInfo, const Vector2& Point)
{
	// �ڽ� To ����Ʈ�� �ִ��� ���� �Ǵ��� �ؾ��Ѵ�.
	if (!CollisionBox2DToPoint(SrcResult, DestResult, PixelInfo.Box, Point))
		return false;

	// LB�� �����ش�
	Vector2 LB = PixelInfo.Box.Center - PixelInfo.Box.Length;

	// LB�� ���־� ������� ��ǥ�� �����
	Vector2 ConvertPoint = Point - LB;

	// �ȼ��� ���� ũ�⿡�� ������ ���Ӱ� ������ y���� ���־�
	// �ȼ� ��ǥ�� �������ش�.
	ConvertPoint.y = PixelInfo.Height - ConvertPoint.y;

	// �ε��� ����
	int Index = (int)ConvertPoint.y * (int)PixelInfo.Width * 4 + (int)ConvertPoint.x * 4;

	bool	Result = false;

	switch (PixelInfo.Type)
	{
	case PixelCollision_Type::Color_Ignore:
		if (PixelInfo.Pixel[Index] == PixelInfo.Color[0] &&
			PixelInfo.Pixel[Index + 1] == PixelInfo.Color[1] &&
			PixelInfo.Pixel[Index + 2] == PixelInfo.Color[2])
			Result = false;

		else
			Result = true;
		break;
	case PixelCollision_Type::Color_Confirm:
		if (PixelInfo.Pixel[Index] == PixelInfo.Color[0] &&
			PixelInfo.Pixel[Index + 1] == PixelInfo.Color[1] &&
			PixelInfo.Pixel[Index + 2] == PixelInfo.Color[2])
			Result = true;

		else
			Result = false;
		break;
	case PixelCollision_Type::Alpha_Ignore:
		if (PixelInfo.Pixel[Index + 3] == PixelInfo.Color[3])
			Result = false;

		else
			Result = true;
		break;
	case PixelCollision_Type::Alpha_Confirm:
		if (PixelInfo.Pixel[Index + 3] == PixelInfo.Color[3])
			Result = true;

		else
			Result = false;
		break;
	}

	return Result;
}

bool CCollision::CollisionBox3DToBox3D(CColliderBox3D* Src, CColliderBox3D* Dest)
{
	CollisionResult srcResult, destResult;

	// �浹�� �Ǿ������ ���´�.
	if (CollisionBox3DToBox3D(srcResult, destResult, Src->GetInfo(), Dest->GetInfo()))
	{
		// srcResult�� �ڱ� �ڽ��� �浹 ����̱⶧����
		// Src�� Src���� �ְ�
		// Dest�� Dest �� �ִ´�
		srcResult.Src = Src;
		srcResult.Dest = Dest;

		// destResult�� ������ �浹 ����̱� ������
		// Src�� Dest �ڽ��� �ְ�
		// Dest�� ������ Src�� �ִ´�.
		destResult.Src = Dest;
		destResult.Dest = Src;

		Src->m_Result = srcResult;
		Dest->m_Result = destResult;


		return true;
	}

	return false;
}

bool CCollision::CollisionSphereToSphere(CColliderSphere* Src, CColliderSphere* Dest)
{
	CollisionResult srcResult, destResult;

	// �浹�� �Ǿ������ ���´�.
	if (CollisionSphereToSphere(srcResult, destResult, Src->GetInfo(), Dest->GetInfo()))
	{
		// srcResult�� �ڱ� �ڽ��� �浹 ����̱⶧����
		// Src�� Src���� �ְ�
		// Dest�� Dest �� �ִ´�
		srcResult.Src = Src;
		srcResult.Dest = Dest;

		// destResult�� ������ �浹 ����̱� ������
		// Src�� Dest �ڽ��� �ְ�
		// Dest�� ������ Src�� �ִ´�.
		destResult.Src = Dest;
		destResult.Dest = Src;

		Src->m_Result = srcResult;
		Dest->m_Result = destResult;

		return true;
	}

	return false;
}

bool CCollision::CollisionBox3DToSphere(CColliderBox3D* Src, CColliderSphere* Dest)
{
	return false;
}

bool CCollision::CollisionBox3DToPixel(CColliderBox3D* Src, CColliderPixel* Dest)
{
	return false;
}

bool CCollision::CollisionSphereToPixel(CColliderSphere* Src, CColliderPixel* Dest)
{
	return false;
}

bool CCollision::CollisionBox3DToBox3D(CollisionResult& SrcResult, CollisionResult& DestResult, const Box3DInfo& Src, const Box3DInfo& Dest)
{
	Vector3	CenterDir = Src.Center - Dest.Center;

	Vector3	Axis = Src.Axis[0];
	Vector3	DestAxis = Src.Axis[0];

	float	CenterProjDist = abs(CenterDir.Dot(Axis));

	float c[3][3];
	float absC[3][3];
	float d[3];

	float r0, r1, r;
	int i;

	const float cutoff = 0.999f;
	bool existsParallelPair = false;

	for (i = 0; i < 3; ++i)
	{
		c[0][i] = Src.Axis[0].Dot(Dest.Axis[i]);
		absC[0][i] = abs(c[0][i]);
		if (absC[0][i] > cutoff)
			existsParallelPair = true;
	}
	d[0] = CenterDir.Dot(Src.Axis[0]);
	r = abs(d[0]);
	r0 = Src.Length.x;
	r1 = Dest.Length.x * absC[0][0] + Dest.Length.y * absC[0][1] + Dest.Length.z * absC[0][2];

	if (r > r0 + r1)
		return false;

	for (i = 0; i < 3; ++i)
	{
		c[1][i] = Src.Axis[1].Dot(Dest.Axis[i]);
		absC[1][i] = abs(c[1][i]);
		if (absC[1][i] > cutoff)
			existsParallelPair = true;
	}
	d[1] = CenterDir.Dot(Src.Axis[1]);
	r = abs(d[1]);
	r0 = Src.Length.y;
	r1 = Dest.Length.x * absC[1][0] + Dest.Length.y * absC[1][1] + Dest.Length.z * absC[1][2];

	if (r > r0 + r1)
		return false;

	for (i = 0; i < 3; ++i)
	{
		c[2][i] = Src.Axis[2].Dot(Dest.Axis[i]);
		absC[2][i] = abs(c[2][i]);
		if (absC[2][i] > cutoff)
			existsParallelPair = true;
	}
	d[2] = CenterDir.Dot(Src.Axis[2]);
	r = abs(d[2]);
	r0 = Src.Length.z;
	r1 = Dest.Length.x * absC[2][0] + Dest.Length.y * absC[2][1] + Dest.Length.z * absC[2][2];

	if (r > r0 + r1)
		return false;


	r = abs(CenterDir.Dot(Dest.Axis[0]));
	r0 = Src.Length.x * absC[0][0] + Src.Length.y * absC[1][0] + Src.Length.z * absC[2][0];
	r1 = Dest.Length.x;

	if (r > r0 + r1)
		return false;

	r = abs(CenterDir.Dot(Dest.Axis[1]));
	r0 = Src.Length.x * absC[0][1] + Src.Length.y * absC[1][1] + Src.Length.z * absC[2][1];
	r1 = Dest.Length.y;

	if (r > r0 + r1)
		return false;

	r = abs(CenterDir.Dot(Dest.Axis[2]));
	r0 = Src.Length.x * absC[0][2] + Src.Length.y * absC[1][2] + Src.Length.z * absC[2][2];
	r1 = Dest.Length.z;

	if (r > r0 + r1)
		return false;

	if (existsParallelPair == true)
		return true;


	r = abs(d[2] * c[1][0] - d[1] * c[2][0]);
	r0 = Src.Length.y * absC[2][0] + Src.Length.z * absC[1][0];
	r1 = Dest.Length.y * absC[0][2] + Dest.Length.z * absC[0][1];
	if (r > r0 + r1)
		return false;

	r = abs(d[2] * c[1][1] - d[1] * c[2][1]);
	r0 = Src.Length.y * absC[2][1] + Src.Length.z * absC[1][1];
	r1 = Dest.Length.x * absC[0][2] + Dest.Length.z * absC[0][0];
	if (r > r0 + r1)
		return false;

	r = abs(d[2] * c[1][2] - d[1] * c[2][2]);
	r0 = Src.Length.y * absC[2][2] + Src.Length.z * absC[1][2];
	r1 = Dest.Length.x * absC[0][1] + Dest.Length.y * absC[0][0];
	if (r > r0 + r1)
		return false;

	r = abs(d[0] * c[2][0] - d[2] * c[0][0]);
	r0 = Src.Length.x * absC[2][0] + Src.Length.z * absC[0][0];
	r1 = Dest.Length.y * absC[1][2] + Dest.Length.z * absC[1][1];
	if (r > r0 + r1)
		return false;

	r = abs(d[0] * c[2][1] - d[2] * c[0][1]);
	r0 = Src.Length.x * absC[2][1] + Src.Length.z * absC[0][1];
	r1 = Dest.Length.x * absC[1][2] + Dest.Length.z * absC[1][0];
	if (r > r0 + r1)
		return false;

	r = abs(d[0] * c[2][2] - d[2] * c[0][2]);
	r0 = Src.Length.x * absC[2][2] + Src.Length.z * absC[0][2];
	r1 = Dest.Length.x * absC[1][1] + Dest.Length.y * absC[1][0];
	if (r > r0 + r1)
		return false;

	r = abs(d[1] * c[0][0] - d[0] * c[1][0]);
	r0 = Src.Length.x * absC[1][0] + Src.Length.y * absC[0][0];
	r1 = Dest.Length.y * absC[2][2] + Dest.Length.z * absC[2][1];
	if (r > r0 + r1)
		return false;

	r = abs(d[1] * c[0][1] - d[0] * c[1][1]);
	r0 = Src.Length.x * absC[1][1] + Src.Length.y * absC[0][1];
	r1 = Dest.Length.x * absC[2][2] + Dest.Length.z * absC[2][0];
	if (r > r0 + r1)
		return false;

	r = abs(d[1] * c[0][2] - d[0] * c[1][2]);
	r0 = Src.Length.x * absC[1][2] + Src.Length.y * absC[0][2];
	r1 = Dest.Length.x * absC[2][1] + Dest.Length.y * absC[2][0];

	if (r > r0 + r1)
		return false;


	return true;
}

bool CCollision::CollisionSphereToSphere(CollisionResult& SrcResult, CollisionResult& DestResult,
	const SphereInfo& Src, const SphereInfo& Dest)
{
	/*float DistanceX = Dest.Center.x - Src.Center.x;
	float DistanceY = Dest.Center.y - Src.Center.y;
	float DistanceZ = Dest.Center.z - Src.Center.z;

	// sqrt = ��Ʈ
	float Distance = sqrtf((DistanceX * DistanceX) + (DistanceY * DistanceY) + (DistanceZ * DistanceZ));*/

	// �� ����� ������ Ǯ�� ������
	// �Ʒ��� �Լ�ȭ �Ѱ�
	float Distance = Src.Center.Distance(Dest.Center);

	return Distance <= Src.Radius + Dest.Radius;
}

bool CCollision::CollisionBox3DToSphere(CollisionResult& SrcResult, CollisionResult& DestResult, const Box3DInfo& Src, const SphereInfo& Dest)
{
	return false;
}

bool CCollision::CollisionBox3DToPixel(CollisionResult& SrcResult, CollisionResult& DestResult, const Box3DInfo& Src, const PixelInfo& Dest)
{
	return false;
}

bool CCollision::CollisionSphereToPixel(CollisionResult& SrcResult, CollisionResult& DestResult, const SphereInfo& Src, const PixelInfo& Dest)
{
	return false;
}

bool CCollision::CollisionBox3DToPoint(CollisionResult& SrcResult, CollisionResult& DestResult, const Box3DInfo& BoxInfo, const Vector2& Point)
{
	return false;
}

bool CCollision::CollisionSphereToPoint(CollisionResult& SrcResult, CollisionResult& DestResult, const SphereInfo& CircleInfo, const Vector2& Point)
{
	return false;
}

bool CCollision::CollisionRayToBox3D(Vector3& HitPoint, const Ray& ray, const Box3DInfo& Box)
{
	float tmin = (Box.Min.x - ray.Pos.x) / ray.Dir.x;
	float tmax = (Box.Max.x - ray.Pos.x) / ray.Dir.x;

	if (tmin > tmax) 
		SWAP(tmin, tmax);

	float tymin = (Box.Min.y - ray.Pos.y) / ray.Dir.y;
	float tymax = (Box.Max.y - ray.Pos.y) / ray.Dir.y;

	if (tymin > tymax)
		SWAP(tymin, tymax);

	if ((tmin > tymax) || (tymin > tmax))
		return false;

	if (tymin > tmin)
		tmin = tymin;

	if (tymax < tmax)
		tmax = tymax;

	float tzmin = ray.Dir.z != 0.f ? (Box.Min.z - ray.Pos.z) / ray.Dir.z : 0.f;
	float tzmax = ray.Dir.z != 0.f ? (Box.Max.z - ray.Pos.z) / ray.Dir.z : 0.f;

	if (tzmin > tzmax) 
		SWAP(tzmin, tzmax);

	if ((tmin > tzmax) || (tzmin > tmax))
		return false;

	if (tzmin > tmin)
		tmin = tzmin;

	if (tzmax < tmax)
		tmax = tzmax;

	float Min = 0.f;

	if (tmin < tymin)
	{
		if (tmin < tzmin)
			Min = tmin;

		else
			Min = tzmin;
	}

	else
	{
		if (tymin < tzmin)
			Min = tymin;

		else
			Min = tzmin;
	}
	

	HitPoint = ray.Pos + ray.Dir * Min;

	return true;
}

bool CCollision::CollisionRayToSphere(Vector3& HitPoint, const Ray& ray, const SphereInfo& Sphere)
{
	/*
	���� : O
	���� : D
	���� : P(t) = O + Dt
	�������� : ||P - C|| - r = 0
	�� ���� �������� P�� ���� P(t)�� ����
	||P(t) - C|| - r = 0

	||O + Dt - C|| - r = 0
	O - C : M
	||Dt + M|| - r = 0
	(Dt + M)(Dt + M) - r * r = 0
	Dt^2 + 2MDt + M^2 - r^2 = 0
	A : D^2 = 1 �̱� ������ A�� ����
	B : 2MD
	C : M^2 - r^2

	(-B +- ��Ʈ(B^2 - 4C)) / 2
	*/
	Vector3 M = ray.Pos - Sphere.Center;

	float b = 2.f * M.Dot(ray.Dir);
	float c = M.Dot(M) - Sphere.Radius * Sphere.Radius;

	float Det = b * b - 4.f * c;

	// �Ǻ��Ŀ��� ���� �Ǻ��� �Ѵ�.(��Ʈ(B^2 - 4C))) �̺κ�
	if (Det < 0.f)
		return false;

	// ��Ʈ
	Det = sqrtf(Det);

	float t1, t2;

	t1 = (-b + Det) / 2.f;
	t2 = (-b - Det) / 2.f;

	// �ΰ��� 0�̻��̿��� ��
	if (t1 < 0.f && t2 < 0.f)
		return false;

	// �Ÿ��� ª������ ��������
	float Dist = t1 < t2 ? t1 : t2;

	if (Dist < 0.f)
		Dist = t2;

	// ����Ʈ ��ġ�� ���� ������ �� ī�޶� ��ġ + ������ ���� * �Ÿ��� �ȴ�.
	HitPoint = ray.Pos + ray.Dir * Dist;

	return true;
}
