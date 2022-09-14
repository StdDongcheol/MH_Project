
#include "AnjanathAnimation.h"
#include "Component/AnimationMeshComponent.h"
#include "Scene/Scene.h"

CAnjanathAnimation::CAnjanathAnimation()
{
	SetTypeID<CAnjanathAnimation>();
}

CAnjanathAnimation::CAnjanathAnimation(const CAnjanathAnimation& Anim) :
	CAnimationSequenceInstance(Anim)
{
}

CAnjanathAnimation::~CAnjanathAnimation()
{
}

bool CAnjanathAnimation::Init()
{
	if (!CAnimationSequenceInstance::Init())
		return false;

	AddAnimation("AnjanathNormalIdle", "NormalIdle", true, 1.f);
	AddAnimation("AnjanathNormalTurnLeft", "NormalTurnLeft", false, 1.f);
	AddAnimation("AnjanathNormalTurnRight", "NormalTurnRight", false, 1.f);
	AddAnimation("AnjanathNormalTurnBack", "NormalTurnBack", true, 1.f);
	AddAnimation("AnjanathNormalMoveStart", "NormalMoveStart", false, 3.f);
	AddAnimation("AnjanathNormalMoveLoop", "NormalMoveLoop", true, 4.f);
	AddAnimation("AnjanathNormalMoveEnd", "NormalMoveEnd", false, 1.f);
	AddAnimation("AnjanathNormalMoveStartToLeft", "NormalMoveStartToLeft", false, 2.f);
	AddAnimation("AnjanathNormalMoveStartToRight", "NormalMoveStartToRight", false, 2.f);
	AddAnimation("AnjanathRoaring", "Roaring", false, 7.f);

	AddAnimation("AnjanathAgressiveIdle", "AgressiveIdle", true, 1.f);
	AddAnimation("AnjanathAgressiveMoveStart", "AgressiveMoveStart", false, 3.f);
	AddAnimation("AnjanathAgressiveTurnLeft", "AgressiveTurnLeft", false, 0.8f);
	AddAnimation("AnjanathAgressiveTurnRight", "AgressiveTurnRight", false, 0.8f);
	AddAnimation("AnjanathAgressiveTurnEnd", "AgressiveTurnEnd", false, 0.5f);

	AddAnimation("AnjanathAttackDashStart", "AttackDashStart", false, 1.5f);
	AddAnimation("AnjanathAttackDashEnd", "AttackDashEnd", false, 1.f);

	AddAnimation("AnjanathTripleBiteStart", "TripleBiteStart", false, 1.f);
	AddAnimation("AnjanathTripleBite1", "TripleBite1", false, 1.f);
	AddAnimation("AnjanathTripleBite2", "TripleBite2", false, 1.f);
	AddAnimation("AnjanathTripleBiteV2End", "TripleBiteEndV2", false, 4.f);
	AddAnimation("AnjanathTripleBiteEnd", "TripleBiteEnd", false, 1.5f);

	AddAnimation("AnjanathCriticalDamaged", "CriticalDamaged", false, 3.0f);
	AddAnimation("AnjanathCriticalDamaged2", "CriticalDamaged2", false, 3.0f);
	AddAnimation("AnjanathCriticalDamagedInAttack", "CriticalDamagedInAttack", false, 3.5f);

	return true;
}
