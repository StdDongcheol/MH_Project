#include "Collision.h"
#include "../Component/ColliderBox2D.h"
#include "../Component/ColliderCircle.h"
#include "../Component/ColliderPixel.h"
#include "../Component/ColliderSphere.h"
#include "../Component/ColliderBox3D.h"

bool CCollision::CollisionBox2DToBox2D(CColliderBox2D* Src, CColliderBox2D* Dest)
{
	CollisionResult srcResult, destResult;

	// 충돌이 되었을경우 들어온다.
	if (CollisionBox2DToBox2D(srcResult, destResult, Src->GetInfo(), Dest->GetInfo()))
	{
		// srcResult는 자기 자신의 충돌 결과이기때문에
		// Src에 Src본인 넣고
		// Dest에 Dest 를 넣는다
		srcResult.Src = Src;
		srcResult.Dest = Dest;

		// destResult는 상대방의 충돌 결과이기 때문에
		// Src에 Dest 자신을 넣고
		// Dest에 상대방인 Src를 넣는다.
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

	// 충돌이 되었을경우 들어온다.
	if (CollisionCircleToCircle(srcResult, destResult, Src->GetInfo(), Dest->GetInfo()))
	{
		// srcResult는 자기 자신의 충돌 결과이기때문에
		// Src에 Src본인 넣고
		// Dest에 Dest 를 넣는다
		srcResult.Src = Src;
		srcResult.Dest = Dest;

		// destResult는 상대방의 충돌 결과이기 때문에
		// Src에 Dest 자신을 넣고
		// Dest에 상대방인 Src를 넣는다.
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

	// 충돌이 되었을경우 들어온다.
	if (CollisionBox2DToCircle(srcResult, destResult, Src->GetInfo(), Dest->GetInfo()))
	{
		// srcResult는 자기 자신의 충돌 결과이기때문에
		// Src에 Src본인 넣고
		// Dest에 Dest 를 넣는다
		srcResult.Src = Src;
		srcResult.Dest = Dest;

		// destResult는 상대방의 충돌 결과이기 때문에
		// Src에 Dest 자신을 넣고
		// Dest에 상대방인 Src를 넣는다.
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

	// 충돌이 되었을경우 들어온다.
	if (CollisionBox2DToPixel(srcResult, destResult, Src->GetInfo(), Dest->GetInfo()))
	{
		// srcResult는 자기 자신의 충돌 결과이기때문에
		// Src에 Src본인 넣고
		// Dest에 Dest 를 넣는다
		srcResult.Src = Src;
		srcResult.Dest = Dest;

		// destResult는 상대방의 충돌 결과이기 때문에
		// Src에 Dest 자신을 넣고
		// Dest에 상대방인 Src를 넣는다.
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

	// 충돌이 되었을경우 들어온다.
	if (CollisionCircleToPixel(srcResult, destResult, Src->GetInfo(), Dest->GetInfo()))
	{
		// srcResult는 자기 자신의 충돌 결과이기때문에
		// Src에 Src본인 넣고
		// Dest에 Dest 를 넣는다
		srcResult.Src = Src;
		srcResult.Dest = Dest;

		// destResult는 상대방의 충돌 결과이기 때문에
		// Src에 Dest 자신을 넣고
		// Dest에 상대방인 Src를 넣는다.
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
	// 축은 단위벡터이기 때문에 Length를 곱해주어 길이만큼을 갖는 축을 만들어서 내적해주는것
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

	// 두 원 사이의 거리가 두 원의 반지름끼리 더한 값보다 크면
	// 충돌이고 더 작다면 충돌이 아니다
	return Distance <= Src.Radius + Dest.Radius;
}

bool CCollision::CollisionBox2DToCircle(CollisionResult& SrcResult, CollisionResult& DestResult, const Box2DInfo& Src, const CircleInfo& Dest)
{
	Vector2 CenterDir = Src.Center - Dest.Center;

	// Box x축 투영
	Vector2 Axis = Src.Axis[0];

	float CenterProjDist = abs(CenterDir.Dot(Axis));

	float r1, r2;

	// Src의 x축 y축에다가 투영을 하기때문
	// Src는 Length그대로가 나온다
	// 원의 경우 어디로 투영을 하든지 반지름 고정
	r1 = Src.Length.x;
	r2 = Dest.Radius;

	// 센터의 투영거리가 r1 + r2보다 크면 return false;
	if (CenterProjDist > r1 + r2)
		return false;

	// 상자의 y축 투영
	Axis = Src.Axis[1];

	CenterProjDist = abs(CenterDir.Dot(Axis));

	r1 = Src.Length.y;
	r2 = Dest.Radius;

	if (CenterProjDist > r1 + r2)
		return false;

	// 상자의 중심방향으로 투영
	// 각 센터끼리의 거리를 Normalize해서 투영
	Axis = CenterDir;
	Axis.Normalize();

	// 센터와 센터의 길이
	CenterProjDist = CenterDir.Length();

	r1 = abs(Src.Axis[0].Dot(Axis) * Src.Length.x) +
		abs(Src.Axis[1].Dot(Axis) * Src.Length.y);
	// 원은 어디에 투영을 해도 반지름이 나옴
	r2 = Dest.Radius;

	if (CenterProjDist > r1 + r2)
		return false;

	return true;
}

bool CCollision::CollisionBox2DToPixel(CollisionResult& SrcResult, CollisionResult& DestResult, const Box2DInfo& Src, const PixelInfo& Dest)
{
	// 박스 To 박스가 있는지 먼저 판단을 해야한다.
	if (!CollisionBox2DToBox2D(SrcResult, DestResult, Src, Dest.Box))
		return false;

	// 교집합을 구한다.
	float Left = Src.Min.x < Dest.Min.x ? Dest.Min.x : Src.Min.x;
	float Right = Src.Max.x > Dest.Max.x ? Dest.Max.x : Src.Max.x;

	float Bottom = Src.Min.y < Dest.Min.y ? Dest.Min.y : Src.Min.y;
	float Top = Src.Max.y > Dest.Max.y ? Dest.Max.y : Src.Max.y;

	// 월드 공간에서의 좌 하단 좌표를 구한다.
	// 센터에서 절반의 x,y를 빼준다.
	Vector2 LB = Dest.Box.Center - Dest.Box.Length;

	// 원점에서의 상대 좌표를 구해준다.
	Left -= LB.x;
	Right -= LB.x;

	Bottom -= LB.y;
	Top -= LB.y;

	// Left와 Bottom은 절대로 0이 되어서는 안된다 예외처리
	Left = Left < 0.f ? 0.f : Left;
	Bottom = Bottom < 0.f ? 0.f : Bottom;

	// Right와 Top은 절대 픽셀이미지의 가로와 세로크기를 넘어서면 안된다.
	Right = Right >= (float)Dest.Width ? (float)Dest.Width - 1.f : Right;
	Top = Top >= (float)Dest.Height ? (float)Dest.Height - 1.f : Top;

	// 이미지는 좌상단부터 시작이기 때문에
	// 픽셀공간으로의 좌표를 구해준다.

	Top = Dest.Height - Top;
	Bottom = Dest.Height - Bottom;

	bool	Collision = false;

	// 교집합 구간을 반복한다.
	for (int y = (int)Top; y < (int)Bottom; ++y)
	{
		for (int x = (int)Left; x < (int)Right; ++x)
		{
			// 색상정보도 있기 때문에 * 4를 한다
			int Index = y * (int)Dest.Width * 4 + x * 4;

			// 현재 인덱스의 픽셀이 상대방 박스 안에 존재하는지를 판단한다.
			// 현재 픽셀을 월드공간에서의 위치를 구해준다.
			// y 가 뒤집혀 있기 때문에 다시 뒤집어서 월드공간에서의 픽셀 위치를 구해준다.
			Vector2	 PixelWorldPos = LB + Vector2((float)x, (float)Dest.Height - (float)y);

			// 충돌이 안되었다면 continue해준다.
			// 픽셀이 박스 안에 들어왔는지 체크를 하는것
			if (!CollisionBox2DToPoint(SrcResult, DestResult, Src, PixelWorldPos))
				continue;

			// 통과해서 여기까지 왔다면 체크를 해야한다.
			switch (Dest.Type)
			{
			case PixelCollision_Type::Color_Ignore:
				// 픽셀 인덱스의 컬러와 데스트의 컬러색상이 동일하면 Ignore이니깐 continue를 한다
				if (Dest.Pixel[Index] == Dest.Color[0] &&
					Dest.Pixel[Index + 1] == Dest.Color[1] &&
					Dest.Pixel[Index + 2] == Dest.Color[2])
					continue;

				// 그게 아니라면 충돌이 된것이다.
				Collision = true;
				break;
			case PixelCollision_Type::Color_Confirm:
				// 픽셀 인덱스의 컬러와 데스트의 컬러색상이 동일하면 Copnfirm이니깐 Collision을 true한다
				if (Dest.Pixel[Index] == Dest.Color[0] &&
					Dest.Pixel[Index + 1] == Dest.Color[1] &&
					Dest.Pixel[Index + 2] == Dest.Color[2])
					Collision = true;
				break;
			case PixelCollision_Type::Alpha_Ignore:
				// 픽셀 인덱스의 알파와 데스트의 알파색상이 동일하면 Ignore이니깐 continue를 한다
				if (Dest.Pixel[Index + 3] == Dest.Color[3])
					continue;

				Collision = true;
				break;
			case PixelCollision_Type::Alpha_Confirm:
				// 픽셀 인덱스의 알파와 데스트의 알파색상이 동일하면 Copnfirm이니깐 Collision을 true한다
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
	// 박스 To 박스가 있는지 먼저 판단을 해야한다.
	if (!CollisionBox2DToCircle(SrcResult, DestResult, Dest.Box, Src))
		return false;

	// 교집합을 구한다.
	float Left = Src.Min.x < Dest.Min.x ? Dest.Min.x : Src.Min.x;
	float Right = Src.Max.x > Dest.Max.x ? Dest.Max.x : Src.Max.x;

	float Bottom = Src.Min.y < Dest.Min.y ? Dest.Min.y : Src.Min.y;
	float Top = Src.Max.y > Dest.Max.y ? Dest.Max.y : Src.Max.y;

	// 월드 공간에서의 좌 하단 좌표를 구한다.
	// 센터에서 절반의 x,y를 빼준다.
	Vector2 LB = Dest.Box.Center - Dest.Box.Length;

	// 원점에서의 상대 좌표를 구해준다.
	Left -= LB.x;
	Right -= LB.x;

	Bottom -= LB.y;
	Top -= LB.y;

	// Left와 Bottom은 절대로 0이 되어서는 안된다 예외처리
	Left = Left < 0.f ? 0.f : Left;
	Bottom = Bottom < 0.f ? 0.f : Bottom;

	// Right와 Top은 절대 픽셀이미지의 가로와 세로크기를 넘어서면 안된다.
	Right = Right >= (float)Dest.Width ? (float)Dest.Width - 1.f : Right;
	Top = Top >= (float)Dest.Height ? (float)Dest.Height - 1.f : Top;

	// 이미지는 좌상단부터 시작이기 때문에
	// 픽셀공간으로의 좌표를 구해준다.

	Top = Dest.Height - Top;
	Bottom = Dest.Height - Bottom;

	bool	Collision = false;

	// 교집합 구간을 반복한다.
	for (int y = (int)Top; y < (int)Bottom; ++y)
	{
		for (int x = (int)Left; x < (int)Right; ++x)
		{
			// 색상정보도 있기 때문에 * 4를 한다
			int Index = y * (int)Dest.Width * 4 + x * 4;

			// 현재 인덱스의 픽셀이 상대방 박스 안에 존재하는지를 판단한다.
			// 현재 픽셀을 월드공간에서의 위치를 구해준다.
			// y 가 뒤집혀 있기 때문에 다시 뒤집어서 월드공간에서의 픽셀 위치를 구해준다.
			Vector2	 PixelWorldPos = LB + Vector2((float)x, (float)Dest.Height - (float)y);

			// 충돌이 안되었다면 continue해준다.
			// 픽셀이 원 안에 들어왔는지 체크를 하는것
			if (!CollisionCircleToPoint(SrcResult, DestResult, Src, PixelWorldPos))
				continue;

			// 통과해서 여기까지 왔다면 체크를 해야한다.
			switch (Dest.Type)
			{
			case PixelCollision_Type::Color_Ignore:
				// 픽셀 인덱스의 컬러와 데스트의 컬러색상이 동일하면 Ignore이니깐 continue를 한다
				if (Dest.Pixel[Index] == Dest.Color[0] &&
					Dest.Pixel[Index + 1] == Dest.Color[1] &&
					Dest.Pixel[Index + 2] == Dest.Color[2])
					continue;

				// 그게 아니라면 충돌이 된것이다.
				Collision = true;
				break;
			case PixelCollision_Type::Color_Confirm:
				// 픽셀 인덱스의 컬러와 데스트의 컬러색상이 동일하면 Copnfirm이니깐 Collision을 true한다
				if (Dest.Pixel[Index] == Dest.Color[0] &&
					Dest.Pixel[Index + 1] == Dest.Color[1] &&
					Dest.Pixel[Index + 2] == Dest.Color[2])
					Collision = true;
				break;
			case PixelCollision_Type::Alpha_Ignore:
				// 픽셀 인덱스의 알파와 데스트의 알파색상이 동일하면 Ignore이니깐 continue를 한다
				if (Dest.Pixel[Index + 3] == Dest.Color[3])
					continue;

				Collision = true;
				break;
			case PixelCollision_Type::Alpha_Confirm:
				// 픽셀 인덱스의 알파와 데스트의 알파색상이 동일하면 Copnfirm이니깐 Collision을 true한다
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
	// obb 대 점 충돌
	// 상자의 x, y축에 점을 투영하여 구간이 겹치는지 판단한다.

	// 센터 방향
	Vector2 CenterDir = BoxInfo.Center - Point;

	Vector2 Axis = BoxInfo.Axis[0];

	// 내적할때 -값이 나오면 안되어서 abs를 이용하여 절대값으로 나오게 설정
	float CenterProjDist = abs(CenterDir.Dot(Axis));

	// CenterProjDist 가 BoxInfo의 Length.x보다 크면 충돌이 안된것이다.
	if (CenterProjDist > BoxInfo.Length.x)
		return false;

	Axis = BoxInfo.Axis[1];

	CenterProjDist = abs(CenterDir.Dot(Axis));

	// CenterProjDist 가 BoxInfo의 Length.y보다 크면 충돌이 안된것이다.
	if (CenterProjDist > BoxInfo.Length.y)
		return false;

	// 둘다 통과한거기 때문에 true
	return true;
}

bool CCollision::CollisionCircleToPoint(CollisionResult& SrcResult, CollisionResult& DestResult, const CircleInfo& CircleInfo, const Vector2& Point)
{
	// 원의 중심과 포인트의 거리
	float	Dist = CircleInfo.Center.Distance(Point);

	// 반지름의 길이가 두개의 거리보다 크거나 같으면 충돌
	return CircleInfo.Radius >= Dist;
}

bool CCollision::CollisionPixelToPoint(CollisionResult& SrcResult,
	CollisionResult& DestResult, const PixelInfo& PixelInfo, const Vector2& Point)
{
	// 박스 To 포인트가 있는지 먼저 판단을 해야한다.
	if (!CollisionBox2DToPoint(SrcResult, DestResult, PixelInfo.Box, Point))
		return false;

	// LB를 구해준다
	Vector2 LB = PixelInfo.Box.Center - PixelInfo.Box.Length;

	// LB를 빼주어 상대적인 좌표로 만든다
	Vector2 ConvertPoint = Point - LB;

	// 픽셀의 세로 크기에서 위에서 새롭게 구해준 y값을 빼주어
	// 픽셀 좌표로 변경해준다.
	ConvertPoint.y = PixelInfo.Height - ConvertPoint.y;

	// 인덱스 구성
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

	// 충돌이 되었을경우 들어온다.
	if (CollisionBox3DToBox3D(srcResult, destResult, Src->GetInfo(), Dest->GetInfo()))
	{
		// srcResult는 자기 자신의 충돌 결과이기때문에
		// Src에 Src본인 넣고
		// Dest에 Dest 를 넣는다
		srcResult.Src = Src;
		srcResult.Dest = Dest;

		// destResult는 상대방의 충돌 결과이기 때문에
		// Src에 Dest 자신을 넣고
		// Dest에 상대방인 Src를 넣는다.
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

	// 충돌이 되었을경우 들어온다.
	if (CollisionSphereToSphere(srcResult, destResult, Src->GetInfo(), Dest->GetInfo()))
	{
		// srcResult는 자기 자신의 충돌 결과이기때문에
		// Src에 Src본인 넣고
		// Dest에 Dest 를 넣는다
		srcResult.Src = Src;
		srcResult.Dest = Dest;

		// destResult는 상대방의 충돌 결과이기 때문에
		// Src에 Dest 자신을 넣고
		// Dest에 상대방인 Src를 넣는다.
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

	// sqrt = 루트
	float Distance = sqrtf((DistanceX * DistanceX) + (DistanceY * DistanceY) + (DistanceZ * DistanceZ));*/

	// 위 방식이 공식을 풀어 쓴것임
	// 아래는 함수화 한것
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
	원점 : O
	방향 : D
	광선 : P(t) = O + Dt
	원방정식 : ||P - C|| - r = 0
	원 위의 임의의점 P에 광선 P(t)를 대입
	||P(t) - C|| - r = 0

	||O + Dt - C|| - r = 0
	O - C : M
	||Dt + M|| - r = 0
	(Dt + M)(Dt + M) - r * r = 0
	Dt^2 + 2MDt + M^2 - r^2 = 0
	A : D^2 = 1 이기 때문에 A는 무시
	B : 2MD
	C : M^2 - r^2

	(-B +- 루트(B^2 - 4C)) / 2
	*/
	Vector3 M = ray.Pos - Sphere.Center;

	float b = 2.f * M.Dot(ray.Dir);
	float c = M.Dot(M) - Sphere.Radius * Sphere.Radius;

	float Det = b * b - 4.f * c;

	// 판별식에서 먼저 판별을 한다.(루트(B^2 - 4C))) 이부분
	if (Det < 0.f)
		return false;

	// 루트
	Det = sqrtf(Det);

	float t1, t2;

	t1 = (-b + Det) / 2.f;
	t2 = (-b - Det) / 2.f;

	// 두개다 0이상이여야 함
	if (t1 < 0.f && t2 < 0.f)
		return false;

	// 거리가 짧은것을 리턴해줌
	float Dist = t1 < t2 ? t1 : t2;

	if (Dist < 0.f)
		Dist = t2;

	// 포인트 위치는 광선 시작점 즉 카메라 위치 + 광선의 방향 * 거리가 된다.
	HitPoint = ray.Pos + ray.Dir * Dist;

	return true;
}
