#include "JagrasAnimation.h"

CJagrasAnimation::CJagrasAnimation()
{
	SetTypeID<CJagrasAnimation>();
}

CJagrasAnimation::CJagrasAnimation(const CJagrasAnimation& Anim) :
	CAnimationSequenceInstance(Anim)
{
}

CJagrasAnimation::~CJagrasAnimation()
{
}

/*

*/

bool CJagrasAnimation::Init()
{
	if (!CAnimationSequenceInstance::Init())
		return false;

	AddAnimation("jagrasmain", "jagrasmain", true, 1.5f);//Æó±â
	AddAnimation("jagras1", "jagras1", true, 1.5f);//Æó±â
	AddAnimation("jagras2", "jagras2", true, 1.5f);
	AddAnimation("jagras3", "jagras3", true, 1.5f);//Æó±â
	AddAnimation("jagras4", "jagras4", true, 1.5f);
	AddAnimation("jagras5", "jagrasmove", true, 6.f);
	AddAnimation("jagras6", "jagrasdodgeleft", true, 1.5f);
	AddAnimation("jagras7", "jagrasdodgeright", true, 1.5f);
	AddAnimation("jagras8", "jagrasdodgeback", true, 1.5f);
	AddAnimation("jagras9", "jagrasattackup1", true, 1.5f);
	AddAnimation("jagras10", "jagrasattackup2", true, 1.5f);
	AddAnimation("jagras11", "jagrasattackup3", true, 1.5f);
	AddAnimation("jagras12", "jagras12", true, 1.5f);
	AddAnimation("jagras13", "jagras13", true, 1.5f);
	AddAnimation("jagras14", "jagras14", true, 1.5f);
	AddAnimation("jagras15", "jagras15", true, 1.5f);
	AddAnimation("jagras16", "jagrasattack1", true, 1.5f);
	AddAnimation("jagras17", "jagrasattack2", true, 1.5f);
	AddAnimation("jagras18", "jagrasattack3", true, 1.5f);
	AddAnimation("jagras19", "jagras19", true, 3.f);
	AddAnimation("jagras20", "jagras20", true, 3.f);
	AddAnimation("jagras21", "jagrasattack4", true, 1.5f);
	AddAnimation("jagras22", "jagrasattack5", true, 0.5f);
	AddAnimation("jagras23", "jagras23", true, 1.5f);
	AddAnimation("jagras24", "jagrasattack6", true, 1.5f);
	AddAnimation("jagras25", "jagras25", true, 2.f);
	AddAnimation("jagras26", "jagras26", true, 2.f);
	AddAnimation("jagras27", "jagrasroll", true, 1.5f);
	AddAnimation("jagras28", "jagrasstandup", true, 1.5f);
	AddAnimation("jagras29", "jagrasdeath1", false, 2.5f);
	AddAnimation("jagras30", "jagrasparalysis", true, 1.5f);
	AddAnimation("jagras31", "jagrasparalysisretore", true, 1.5f);
	AddAnimation("jagras32", "jagras32", true, 3.f);
	AddAnimation("jagras33", "jagrasdeath2", false, 4.5f);
	AddAnimation("jagras34", "jagrasidle", true, 4.f);
	
	




	return true;
}

CJagrasAnimation* CJagrasAnimation::Clone()
{
	return DBG_NEW CJagrasAnimation(*this);
}
