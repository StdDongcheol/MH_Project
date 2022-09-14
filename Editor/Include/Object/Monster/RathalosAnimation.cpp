
#include "RathalosAnimation.h"
#include "Component/AnimationMeshComponent.h"
#include "Scene/Scene.h"

CRathalosAnimation::CRathalosAnimation()
{
	SetTypeID<CRathalosAnimation>();
}

CRathalosAnimation::CRathalosAnimation(const CRathalosAnimation& Anim) :
	CAnimationSequenceInstance(Anim)
{
}

CRathalosAnimation::~CRathalosAnimation()
{
}

bool CRathalosAnimation::Init()
{
	if (!CAnimationSequenceInstance::Init())
		return false;

	AddAnimation("RathalosNormalIdle", "NormalIdle", true, 1.f);
	AddAnimation("RathalosNormalMoveStart", "NormalMoveStart", false, 1.f);
	AddAnimation("RathalosNormalMoveLoop", "NormalMoveLoop", true, 1.f);
	AddAnimation("RathalosRoaring", "Roaring", false, 3.f);

	AddAnimation("RathalosBiteStart", "BiteStart", false, 1.f);
	AddAnimation("RathalosBiteEnd", "BiteEnd", false, 2.f);
	AddAnimation("RathalosChargeStart", "ChargeStart", false, 1.f);
	AddAnimation("RathalosChargeEnd", "ChargeEnd", false, 3.f);
	AddAnimation("RathalosTailSpinAttack", "TailAttack", false, 3.f);

	AddAnimation("RathalosAgressiveTurnLeft", "AgressiveTurnLeft", false, 1.2f);
	AddAnimation("RathalosAgressiveTurnRight", "AgressiveTurnRight", false, 1.2f);

	AddAnimation("RathalosFlyStart", "FlyStart", false, 0.8f);
	AddAnimation("RathalosFlyToIdle", "FlyToIdle", false, 1.f);
	AddAnimation("RathalosFlyIdle", "FlyIdle", true, 1.0f);
	AddAnimation("RathalosLandStart", "LandStart", false, 1.2f);
	AddAnimation("RathalosLandEnd", "LandEnd", false, 1.f);

	AddAnimation("RathalosFlyBreathStart", "FlyBreathStart", false, 0.8f);
	AddAnimation("RathalosFlyBreath", "FlyBreath", false, 1.5f);

	AddAnimation("RathalosDead", "Dead", false, 4.0f);
	AddAnimation("RathalosDamaged", "Damaged", false, 1.5f);
	AddAnimation("RathalosFlyDamaged", "FlyDamaged", false, 1.3f);

	return true;
}
