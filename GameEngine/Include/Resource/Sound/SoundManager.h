#pragma once

#include "Sound.h"

class CSoundManager
{
	friend class CResourceManager;

private:
	CSoundManager();
	~CSoundManager();

private:
	FMOD::System* m_System;
	FMOD::ChannelGroup* m_MasterGroup;
	std::unordered_map<std::string, FMOD::ChannelGroup*>	m_mapGroup;
	std::unordered_map<std::string, CSharedPtr<CSound>>		m_mapSound;

private:
	float	m_SoundDistance;

public:
	bool Init();
	void Update();

	bool LoadSound(const std::string& ChannelGroupName, bool Loop, const std::string& Name, const char* FileName,
		const std::string& PathName = SOUND_PATH);
	bool CreateSoundChannelGroup(const std::string& Name);
	bool SetVolume(int Volume);
	void GetVolume(const std::string& ChannelGroupName, float* Volume);
	bool SetVolume(const std::string& ChannelGroupName, int Volume);
	bool SetVolume(const std::string& ChannelGroupName, float Volume);

	// 2번째 인자 CGameObject*에 this 추가하면 거리에 따른 볼륨으로 출력함.
	// 아무것도 넣지않으면 원본 볼륨으로 출력.
	bool SoundPlay(const std::string& Name, class CGameObject* Obj = nullptr);
	bool SoundStop(const std::string& Name);
	bool SoundPause(const std::string& Name);
	bool SoundResume(const std::string& Name);
	class CSound* FindSound(const std::string& Name);
	FMOD::ChannelGroup* FindChannelGroup(const std::string& Name);
	void ReleaseSound(const std::string& Name);
	bool IsSoundPlay(const std::string& Name);

private:
	void SoundPlayAtDistance(CSound* Sound, class CGameObject* Obj);
};

