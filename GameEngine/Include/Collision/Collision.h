#pragma once

#include "../GameInfo.h"

class CCollision
{
public:
	static bool CollisionBox2DToBox2D(class CColliderBox2D* Src, class CColliderBox2D* Dest);
	static bool CollisionCircleToCircle(class CColliderCircle* Src, class CColliderCircle* Dest);
	static bool CollisionBox2DToCircle(class CColliderBox2D* Src, class CColliderCircle* Dest);
	static bool CollisionBox2DToPixel(class CColliderBox2D* Src, class CColliderPixel* Dest);
	static bool CollisionCircleToPixel(class CColliderCircle* Src, class CColliderPixel* Dest);
	// 픽셀 To 픽셀은 만들지 않는다 너무 느리다고 함.

	static bool CollisionBox2DToBox2D(CollisionResult& SrcResult, CollisionResult& DestResult,
		const Box2DInfo& Src, const Box2DInfo& Dest);
	static bool CollisionCircleToCircle(CollisionResult& SrcResult, CollisionResult& DestResult,
		const CircleInfo& Src, const CircleInfo& Dest);
	static bool CollisionBox2DToCircle(CollisionResult& SrcResult, CollisionResult& DestResult,
		const Box2DInfo& Src, const CircleInfo& Dest);
	static bool CollisionBox2DToPixel(CollisionResult& SrcResult, CollisionResult& DestResult,
		const Box2DInfo& Src, const PixelInfo& Dest);
	static bool CollisionCircleToPixel(CollisionResult& SrcResult, CollisionResult& DestResult,
		const CircleInfo& Src, const PixelInfo& Dest);

public:
	static bool CollisionBox2DToPoint(CollisionResult& SrcResult, CollisionResult& DestResult,
		const Box2DInfo& BoxInfo, const Vector2& Point);
	static bool CollisionCircleToPoint(CollisionResult& SrcResult, CollisionResult& DestResult,
		const CircleInfo& CircleInfo, const Vector2& Point);
	static bool CollisionPixelToPoint(CollisionResult& SrcResult, CollisionResult& DestResult,
		const PixelInfo& PixelInfo, const Vector2& Point);


	// 3D
public:
	static bool CollisionBox3DToBox3D(class CColliderBox3D* Src, class CColliderBox3D* Dest);
	static bool CollisionSphereToSphere(class CColliderSphere* Src, class CColliderSphere* Dest);
	static bool CollisionBox3DToSphere(class CColliderBox3D* Src, class CColliderSphere* Dest);
	static bool CollisionBox3DToPixel(class CColliderBox3D* Src, class CColliderPixel* Dest);
	static bool CollisionSphereToPixel(class CColliderSphere* Src, class CColliderPixel* Dest);
	// 픽셀 To 픽셀은 만들지 않는다 너무 느리다고 함.

	static bool CollisionBox3DToBox3D(CollisionResult& SrcResult, CollisionResult& DestResult,
		const Box3DInfo& Src, const Box3DInfo& Dest);
	static bool CollisionSphereToSphere(CollisionResult& SrcResult, CollisionResult& DestResult,
		const SphereInfo& Src, const SphereInfo& Dest);
	static bool CollisionBox3DToSphere(CollisionResult& SrcResult, CollisionResult& DestResult,
		const Box3DInfo& Src, const SphereInfo& Dest);
	static bool CollisionBox3DToPixel(CollisionResult& SrcResult, CollisionResult& DestResult,
		const Box3DInfo& Src, const PixelInfo& Dest);
	static bool CollisionSphereToPixel(CollisionResult& SrcResult, CollisionResult& DestResult,
		const SphereInfo& Src, const PixelInfo& Dest);

public:
	static bool CollisionBox3DToPoint(CollisionResult& SrcResult, CollisionResult& DestResult,
		const Box3DInfo& BoxInfo, const Vector2& Point);
	static bool CollisionSphereToPoint(CollisionResult& SrcResult, CollisionResult& DestResult,
		const SphereInfo& CircleInfo, const Vector2& Point);

	static bool CollisionRayToBox3D(Vector3& HitPoint, const Ray& ray, const Box3DInfo& Box);
	static bool CollisionRayToSphere(Vector3& HitPoint, const Ray& ray, const SphereInfo& Sphere);
};

