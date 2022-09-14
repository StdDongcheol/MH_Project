
#include "CollisionManager.h"

DEFINITION_SINGLE(CCollisionManager)

CCollisionManager::CCollisionManager()
{
}

CCollisionManager::~CCollisionManager()
{
	auto	iter = m_mapProfile.begin();
	auto	iterEnd = m_mapProfile.end();

	for (; iter != iterEnd; ++iter)
	{
		SAFE_DELETE(iter->second);
	}
}

bool CCollisionManager::Init()
{
	CreateProfile("Object", Collision_Channel::Object, true);
	CreateProfile("Player", Collision_Channel::Player, true);
	CreateProfile("Monster", Collision_Channel::Monster, true);
	CreateProfile("PlayerAttack", Collision_Channel::PlayerAttack, true);
	CreateProfile("MonsterAttack", Collision_Channel::MonsterAttack, true);
	CreateProfile("Environment", Collision_Channel::Environment, true);
	CreateProfile("Carving", Collision_Channel::Carving, true);
	CreateProfile("MonsterSpot", Collision_Channel::MonsterSpot, true);
	CreateProfile("FieldObj", Collision_Channel::FieldObj, true);
	CreateProfile("MonsterSliding", Collision_Channel::MonsterSliding, true);
	CreateProfile("PlayerSliding", Collision_Channel::PlayerSliding, true);
	CreateProfile("NPC", Collision_Channel::NPC, true);

	SetCollisionState("Player", Collision_Channel::Player, Collision_Interaction::Ignore);
	SetCollisionState("Player", Collision_Channel::PlayerAttack, Collision_Interaction::Ignore);
	SetCollisionState("Player", Collision_Channel::Environment, Collision_Interaction::Collision);
	SetCollisionState("Player", Collision_Channel::Carving, Collision_Interaction::Collision);
	SetCollisionState("Player", Collision_Channel::MonsterSpot, Collision_Interaction::Collision);
	SetCollisionState("Player", Collision_Channel::MonsterSliding, Collision_Interaction::Ignore);
	SetCollisionState("Player", Collision_Channel::NPC, Collision_Interaction::Collision);
	SetCollisionState("Player", Collision_Channel::FieldObj, Collision_Interaction::Collision);
	SetCollisionState("Player", Collision_Channel::PlayerSliding, Collision_Interaction::Ignore);


	SetCollisionState("Monster", Collision_Channel::Monster, Collision_Interaction::Ignore);
	SetCollisionState("Monster", Collision_Channel::MonsterAttack, Collision_Interaction::Ignore);
	SetCollisionState("Monster", Collision_Channel::Environment, Collision_Interaction::Ignore);
	SetCollisionState("Monster", Collision_Channel::Carving, Collision_Interaction::Ignore);
	SetCollisionState("Monster", Collision_Channel::MonsterSpot, Collision_Interaction::Ignore);
	SetCollisionState("Monster", Collision_Channel::FieldObj, Collision_Interaction::Ignore);
	SetCollisionState("Monster", Collision_Channel::MonsterSliding, Collision_Interaction::Ignore);
	SetCollisionState("Monster", Collision_Channel::NPC, Collision_Interaction::Ignore);
	SetCollisionState("Monster", Collision_Channel::PlayerSliding, Collision_Interaction::Ignore);

	SetCollisionState("PlayerAttack", Collision_Channel::Player, Collision_Interaction::Ignore);
	SetCollisionState("PlayerAttack", Collision_Channel::PlayerAttack, Collision_Interaction::Ignore);
	SetCollisionState("PlayerAttack", Collision_Channel::MonsterAttack, Collision_Interaction::Ignore);
	SetCollisionState("PlayerAttack", Collision_Channel::Environment, Collision_Interaction::Ignore);
	SetCollisionState("PlayerAttack", Collision_Channel::Carving, Collision_Interaction::Ignore);
	SetCollisionState("PlayerAttack", Collision_Channel::MonsterSpot, Collision_Interaction::Ignore);
	SetCollisionState("PlayerAttack", Collision_Channel::MonsterSliding, Collision_Interaction::Ignore);
	SetCollisionState("PlayerAttack", Collision_Channel::NPC, Collision_Interaction::Ignore);
	SetCollisionState("PlayerAttack", Collision_Channel::PlayerSliding, Collision_Interaction::Ignore);
	SetCollisionState("PlayerAttack", Collision_Channel::FieldObj, Collision_Interaction::Ignore);

	SetCollisionState("MonsterAttack", Collision_Channel::Monster, Collision_Interaction::Ignore);
	SetCollisionState("MonsterAttack", Collision_Channel::PlayerAttack, Collision_Interaction::Ignore);
	SetCollisionState("MonsterAttack", Collision_Channel::MonsterAttack, Collision_Interaction::Ignore);
	SetCollisionState("MonsterAttack", Collision_Channel::Environment, Collision_Interaction::Ignore);
	SetCollisionState("MonsterAttack", Collision_Channel::Carving, Collision_Interaction::Ignore);
	SetCollisionState("MonsterAttack", Collision_Channel::MonsterSpot, Collision_Interaction::Ignore);
	SetCollisionState("MonsterAttack", Collision_Channel::MonsterSliding, Collision_Interaction::Ignore);
	SetCollisionState("MonsterAttack", Collision_Channel::FieldObj, Collision_Interaction::Ignore);
	SetCollisionState("MonsterAttack", Collision_Channel::NPC, Collision_Interaction::Ignore);
	SetCollisionState("MonsterAttack", Collision_Channel::PlayerSliding, Collision_Interaction::Ignore);

	SetCollisionState("Environment", Collision_Channel::Environment, Collision_Interaction::Ignore);
	SetCollisionState("Environment", Collision_Channel::Player, Collision_Interaction::Collision);
	SetCollisionState("Environment", Collision_Channel::Monster, Collision_Interaction::Ignore);
	SetCollisionState("Environment", Collision_Channel::PlayerAttack, Collision_Interaction::Ignore);
	SetCollisionState("Environment", Collision_Channel::MonsterAttack, Collision_Interaction::Ignore);
	SetCollisionState("Environment", Collision_Channel::Carving, Collision_Interaction::Ignore);
	SetCollisionState("Environment", Collision_Channel::MonsterSpot, Collision_Interaction::Ignore);
	SetCollisionState("Environment", Collision_Channel::MonsterSliding, Collision_Interaction::Ignore);
	SetCollisionState("Environment", Collision_Channel::NPC, Collision_Interaction::Ignore);
	SetCollisionState("Environment", Collision_Channel::PlayerSliding, Collision_Interaction::Ignore);
	SetCollisionState("Environment", Collision_Channel::FieldObj, Collision_Interaction::Ignore);

	SetCollisionState("Carving", Collision_Channel::Carving, Collision_Interaction::Ignore);
	SetCollisionState("Carving", Collision_Channel::Monster, Collision_Interaction::Ignore);
	SetCollisionState("Carving", Collision_Channel::MonsterAttack, Collision_Interaction::Ignore);
	SetCollisionState("Carving", Collision_Channel::PlayerAttack, Collision_Interaction::Ignore);
	SetCollisionState("Carving", Collision_Channel::Environment, Collision_Interaction::Ignore);
	SetCollisionState("Carving", Collision_Channel::Player, Collision_Interaction::Collision);
	SetCollisionState("Carving", Collision_Channel::MonsterSpot, Collision_Interaction::Ignore);
	SetCollisionState("Carving", Collision_Channel::MonsterSliding, Collision_Interaction::Ignore);
	SetCollisionState("Carving", Collision_Channel::NPC, Collision_Interaction::Ignore);
	SetCollisionState("Carving", Collision_Channel::PlayerSliding, Collision_Interaction::Ignore);
	SetCollisionState("Carving", Collision_Channel::FieldObj, Collision_Interaction::Ignore);

	SetCollisionState("MonsterSpot", Collision_Channel::Carving, Collision_Interaction::Ignore);
	SetCollisionState("MonsterSpot", Collision_Channel::Monster, Collision_Interaction::Ignore);
	SetCollisionState("MonsterSpot", Collision_Channel::MonsterAttack, Collision_Interaction::Ignore);
	SetCollisionState("MonsterSpot", Collision_Channel::PlayerAttack, Collision_Interaction::Ignore);
	SetCollisionState("MonsterSpot", Collision_Channel::Environment, Collision_Interaction::Ignore);
	SetCollisionState("MonsterSpot", Collision_Channel::Player, Collision_Interaction::Collision);
	SetCollisionState("MonsterSpot", Collision_Channel::MonsterSpot, Collision_Interaction::Ignore);
	SetCollisionState("MonsterSpot", Collision_Channel::MonsterSliding, Collision_Interaction::Ignore);
	SetCollisionState("MonsterSpot", Collision_Channel::NPC, Collision_Interaction::Ignore);
	SetCollisionState("MonsterSpot", Collision_Channel::PlayerSliding, Collision_Interaction::Ignore);
	SetCollisionState("MonsterSpot", Collision_Channel::FieldObj, Collision_Interaction::Ignore);

	SetCollisionState("FieldObj", Collision_Channel::FieldObj, Collision_Interaction::Ignore);
	SetCollisionState("FieldObj", Collision_Channel::Carving, Collision_Interaction::Ignore);
	SetCollisionState("FieldObj", Collision_Channel::Monster, Collision_Interaction::Ignore);
	SetCollisionState("FieldObj", Collision_Channel::MonsterAttack, Collision_Interaction::Ignore);
	SetCollisionState("FieldObj", Collision_Channel::PlayerAttack, Collision_Interaction::Ignore);
	SetCollisionState("FieldObj", Collision_Channel::Environment, Collision_Interaction::Ignore);
	SetCollisionState("FieldObj", Collision_Channel::Player, Collision_Interaction::Collision);
	SetCollisionState("FieldObj", Collision_Channel::MonsterSpot, Collision_Interaction::Ignore);
	SetCollisionState("FieldObj", Collision_Channel::MonsterSliding, Collision_Interaction::Collision);
	SetCollisionState("FieldObj", Collision_Channel::NPC, Collision_Interaction::Ignore);
	SetCollisionState("FieldObj", Collision_Channel::PlayerSliding, Collision_Interaction::Collision);

	SetCollisionState("MonsterSliding", Collision_Channel::Player, Collision_Interaction::Ignore);
	SetCollisionState("MonsterSliding", Collision_Channel::PlayerAttack, Collision_Interaction::Ignore);
	SetCollisionState("MonsterSliding", Collision_Channel::Monster, Collision_Interaction::Ignore);
	SetCollisionState("MonsterSliding", Collision_Channel::MonsterAttack, Collision_Interaction::Ignore);
	SetCollisionState("MonsterSliding", Collision_Channel::PlayerAttack, Collision_Interaction::Ignore);
	SetCollisionState("MonsterSliding", Collision_Channel::Environment, Collision_Interaction::Ignore);
	SetCollisionState("MonsterSliding", Collision_Channel::Carving, Collision_Interaction::Ignore);
	SetCollisionState("MonsterSliding", Collision_Channel::MonsterSpot, Collision_Interaction::Ignore);
	SetCollisionState("MonsterSliding", Collision_Channel::FieldObj, Collision_Interaction::Collision);
	SetCollisionState("MonsterSliding", Collision_Channel::NPC, Collision_Interaction::Ignore);
	SetCollisionState("MonsterSliding", Collision_Channel::PlayerSliding, Collision_Interaction::Ignore);

	SetCollisionState("PlayerSliding", Collision_Channel::PlayerSliding, Collision_Interaction::Ignore);
	SetCollisionState("PlayerSliding", Collision_Channel::Player, Collision_Interaction::Ignore);
	SetCollisionState("PlayerSliding", Collision_Channel::PlayerAttack, Collision_Interaction::Ignore);
	SetCollisionState("PlayerSliding", Collision_Channel::Monster, Collision_Interaction::Ignore);
	SetCollisionState("PlayerSliding", Collision_Channel::MonsterAttack, Collision_Interaction::Ignore);
	SetCollisionState("PlayerSliding", Collision_Channel::PlayerAttack, Collision_Interaction::Ignore);
	SetCollisionState("PlayerSliding", Collision_Channel::Environment, Collision_Interaction::Ignore);
	SetCollisionState("PlayerSliding", Collision_Channel::Carving, Collision_Interaction::Ignore);
	SetCollisionState("PlayerSliding", Collision_Channel::MonsterSpot, Collision_Interaction::Ignore);
	SetCollisionState("PlayerSliding", Collision_Channel::FieldObj, Collision_Interaction::Collision);
	SetCollisionState("PlayerSliding", Collision_Channel::NPC, Collision_Interaction::Ignore);

	SetCollisionState("NPC", Collision_Channel::NPC, Collision_Interaction::Ignore);
	SetCollisionState("NPC", Collision_Channel::Player, Collision_Interaction::Collision);
	SetCollisionState("NPC", Collision_Channel::PlayerAttack, Collision_Interaction::Ignore);
	SetCollisionState("NPC", Collision_Channel::Monster, Collision_Interaction::Ignore);
	SetCollisionState("NPC", Collision_Channel::MonsterAttack, Collision_Interaction::Ignore);
	SetCollisionState("NPC", Collision_Channel::PlayerAttack, Collision_Interaction::Ignore);
	SetCollisionState("NPC", Collision_Channel::Environment, Collision_Interaction::Ignore);
	SetCollisionState("NPC", Collision_Channel::Carving, Collision_Interaction::Ignore);
	SetCollisionState("NPC", Collision_Channel::MonsterSpot, Collision_Interaction::Ignore);
	SetCollisionState("NPC", Collision_Channel::FieldObj, Collision_Interaction::Ignore);

	return true;
}

bool CCollisionManager::CreateProfile(const std::string& Name, Collision_Channel Channel, 
	bool Enable, Collision_Interaction State)
{
	CollisionProfile* Profile = FindProfile(Name);

	if (Profile)
		return false;

	Profile = new CollisionProfile;

	Profile->Name = Name;
	Profile->Channel = Channel;
	Profile->CollisionEnable = Enable;
	Profile->vecInteraction.resize((int)Collision_Channel::Max);

	for (int i = 0; i < (int)Collision_Channel::Max; ++i)
	{
		Profile->vecInteraction[i] = State;
	}
	
	m_mapProfile.insert(std::make_pair(Name, Profile));

	return true;
}

bool CCollisionManager::SetCollisionState(const std::string& Name, Collision_Channel Channel,
	Collision_Interaction State)
{
	CollisionProfile* Profile = FindProfile(Name);

	if (!Profile)
		return false;

	Profile->vecInteraction[(int)Channel] = State;

	return true;
}

CollisionProfile* CCollisionManager::FindProfile(const std::string& Name)
{
	auto	iter = m_mapProfile.find(Name);

	if (iter == m_mapProfile.end())
		return nullptr;

	return iter->second;
}
