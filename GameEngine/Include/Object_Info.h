#pragma once

#include "GameInfo.h"
#include "GameObject/GameObject.h"

struct Object_Info
{
	std::string		SceneName;
	Object_Type		Type;
	Monster_Type	MonsterType;
	FieldObj_Type	FieldObjType;
	int	FieldObjNum;
	std::list<CharacterInfo*>	CharacterInfoList;
	std::list<CSharedPtr<CGameObject>>* ObjectList;

	Object_Info() :
		Type(Object_Type::Max),
		MonsterType(Monster_Type::Max),
		FieldObjType(FieldObj_Type::Max),
		FieldObjNum(0),
		ObjectList(nullptr)
	{
		ObjectList = DBG_NEW std::list<CSharedPtr<class CGameObject>>;
	}

	~Object_Info()
	{
		auto	iter = CharacterInfoList.begin();
		auto	iterEnd = CharacterInfoList.end();

		for (; iter != iterEnd; ++iter)
		{
			SAFE_DELETE(*iter);
		}

		SAFE_DELETE(ObjectList);
	}

	CharacterInfo* FindCharacterInfo(const std::string& Name)
	{
		auto	iter = CharacterInfoList.begin();
		auto	iterEnd = CharacterInfoList.end();

		for (; iter != iterEnd; ++iter)
		{
			if ((*iter)->CharacterName == Name)
				return *iter;
		}

		return nullptr;
	}

	void DeleteCharacterInfo(const std::string& Name)
	{
		auto	iter = CharacterInfoList.begin();
		auto	iterEnd = CharacterInfoList.end();

		for (; iter != iterEnd; ++iter)
		{
			if ((*iter)->CharacterName == Name)
			{
				SAFE_DELETE(*iter);
				CharacterInfoList.erase(iter);
				return;
			}
		}
	}

	void DeleteCharacterInfoAll()
	{
		auto	iter = CharacterInfoList.begin();
		auto	iterEnd = CharacterInfoList.end();

		for (; iter != iterEnd; ++iter)
		{
			SAFE_DELETE(*iter);
		}

		CharacterInfoList.clear();
	}
};