#pragma once

#include "../../Ref.h"

class CSound :
	public CRef
{
	friend class CSoundManager;

private:
	CSound();
	~CSound();

private:
	FMOD::System* m_System;
	FMOD::Sound* m_Sound;
	FMOD::ChannelGroup* m_Group;
	FMOD::Channel* m_Channel;
	bool        m_Play;
	bool        m_Loop;
	bool        m_FadeIn;	// ���� �Ҹ��� Ŀ��
	bool		m_FadeOut;	// ���� �Ҹ��� �۾���
	float		m_FadeTime;	// ���̵���, �ƿ� ���� �ð�
	float		m_FadeTimeMax;	// ���̵���, �ƿ� �� �ð�

public:
	void FadeIn()
	{
		m_FadeIn = true;
	}

	void FadeOut()
	{
		m_FadeOut = true;
	}

public:
	bool IsFadeIn()	const
	{
		return m_FadeIn;
	}

	bool IsFadeOut()	const
	{
		return m_FadeOut;
	}

	bool IsPlay()   const
	{
		return m_Play;
	}

	bool IsLoop()   const
	{
		return m_Loop;
	}

public:
	bool LoadSound(FMOD::System* System, FMOD::ChannelGroup* Group,
		bool Loop, const std::string& Name, const char* FileName, const std::string& PathName = SOUND_PATH);
	void Play();
	void Stop();
	void Pause();
	void Resume();
};

