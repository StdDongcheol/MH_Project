#pragma once

#include "GameInfo.h"

/// <summary>
/// ������ �̺�Ʈ Ű����� ����� Ű���� EventManager�� ����صӴϴ�(AddEventName).
/// �� ������Ʈ�� �ش� �̺�Ʈ Ű���忡 �Լ��� ���(AddEventCallback)�ϰ�,
/// ���߿� Ư�� ������Ʈ�� �ش��ϴ� �̺�Ʈ(CallEvent) �Լ��� ȣ���� ���,
/// �ش� �̺�Ʈ Ű����� ���ε��� �Լ��� ��� ȣ���մϴ�. 
/// </summary>
class CEventManager
{
public:
	bool Init();

private:
	std::unordered_map<std::string, std::list<std::function<void()>>> m_mapEvent;

private:
	Stage_Type		m_LoadStageType;

public:
	void SetStageType(Stage_Type Type)
	{
		m_LoadStageType = Type;
	}

public:
	Stage_Type GetLoadStageType() const
	{
		return m_LoadStageType;
	}

public:
	/*
	* Name�� Key������ �ش� Key���� ���ε��� �Լ��� **���** ȣ���մϴ�.
	*/
	void CallEvent(const std::string& Name)
	{
		auto	iter = m_mapEvent[Name].begin();
		auto	iterEnd = m_mapEvent[Name].end();

		for (; iter != iterEnd; ++iter)
		{
			(*iter)();
		}
	}



public:
	void ClearAllCallback()
	{
		auto	iter = m_mapEvent.begin();
		auto	iterEnd = m_mapEvent.end();

		for (; iter != iterEnd; ++iter)
		{
			iter->second.clear();
		}
	}

	/*
	* KeyName�� Key������ �Լ��� ���.
	* ���� ��ϵ������� Key���̶�� ��� �߰�����.
	*/
public:
	template <typename T>
	void AddEventCallback(const std::string& KeyName, T* Obj, void(T::* Func)())
	{
		auto	iter = m_mapEvent.find(KeyName);

		if (iter != m_mapEvent.end())
		{
			iter->second.push_back(std::bind(Func, Obj));
		}

		else
		{
			std::list<std::function<void()>> List;

			List.push_back(std::bind(Func, Obj));

			m_mapEvent.insert(std::make_pair(KeyName, List));
		}

	}

private:
	void AddEventName(const std::string& KeyName)
	{
		auto iter = m_mapEvent.find(KeyName);

		if (iter == m_mapEvent.end())
		{
			std::list<std::function<void()>> List;

			m_mapEvent.insert(std::make_pair(KeyName, List));
		}
	}

private:
	void ShakeOn();

	DECLARE_SINGLE(CEventManager)
};

