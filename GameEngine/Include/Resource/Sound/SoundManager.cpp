
#include "SoundManager.h"
#include "../ResourceManager.h"
#include "../../Scene/Scene.h"
#include "../../Scene/SceneManager.h"
#include "../../Component/CameraComponent.h"
#include "../../GameObject/GameObject.h"

CSoundManager::CSoundManager()	:
	m_System(nullptr),
	m_MasterGroup(nullptr),
	m_SoundDistance(160.f)
{
}

CSoundManager::~CSoundManager()
{
	auto	iter = m_mapGroup.begin();
	auto	iterEnd = m_mapGroup.end();

	for (; iter != iterEnd; ++iter)
	{
		iter->second->release();
	}

	m_mapSound.clear();

	if (m_System)
	{
		m_System->close();
		m_System->release();
	}
}

bool CSoundManager::Init()
{
	FMOD_RESULT	result = FMOD::System_Create(&m_System);
	
	if (result != FMOD_OK)
		return false;

	result = m_System->init(4093, FMOD_INIT_NORMAL, nullptr);

	if (result != FMOD_OK)
		return false;

	// MasterGroup�� ���´�.
	result = m_System->getMasterChannelGroup(&m_MasterGroup);

	if (result != FMOD_OK)
		return false;

	m_mapGroup.insert(std::make_pair("Master", m_MasterGroup));

	return true;
}

void CSoundManager::Update()
{
	m_System->update();
}

bool CSoundManager::LoadSound(const std::string& ChannelGroupName, bool Loop, 
	const std::string& Name, const char* FileName, const std::string& PathName)
{
	CSound* Sound = FindSound(Name);

	if (Sound)
		return true;

	FMOD::ChannelGroup* Group = FindChannelGroup(ChannelGroupName);
	
	Sound = new CSound;

	if (!Sound->LoadSound(m_System, Group, Loop, Name, FileName, PathName))
	{
		SAFE_RELEASE(Sound);
		return false;
	}

	m_mapSound.insert(std::make_pair(Name, Sound));

	return true;
}

bool CSoundManager::CreateSoundChannelGroup(const std::string& Name)
{
	FMOD::ChannelGroup* Group = FindChannelGroup(Name);

	if (Group)
		return true;

	FMOD_RESULT	result = m_System->createChannelGroup(Name.c_str(), &Group);

	if (result != FMOD_OK)
		return false;

	m_MasterGroup->addGroup(Group);

	m_mapGroup.insert(std::make_pair(Name, Group));

	return true;
}

bool CSoundManager::SetVolume(int Volume)
{
	FMOD_RESULT result = m_MasterGroup->setVolume(Volume / 100.f);

	return result == FMOD_OK;
}

void CSoundManager::GetVolume(const std::string& ChannelGroupName, float* Volume)
{
	FMOD::ChannelGroup* Group = FindChannelGroup(ChannelGroupName);

	if (!Group)
		return;

	Group->getVolume(Volume);
}

bool CSoundManager::SetVolume(const std::string& ChannelGroupName, int Volume)
{
	FMOD::ChannelGroup* Group = FindChannelGroup(ChannelGroupName);
	
	if (!Group)
		return false;

	FMOD_RESULT result = Group->setVolume(Volume / 100.f);

	return result == FMOD_OK;
}

bool CSoundManager::SetVolume(const std::string& ChannelGroupName, float Volume)
{
	FMOD::ChannelGroup* Group = FindChannelGroup(ChannelGroupName);

	if (!Group)
		return false;

	FMOD_RESULT result = Group->setVolume(Volume);

	return result == FMOD_OK;
}

bool CSoundManager::SoundPlay(const std::string& Name, CGameObject* Obj)
{
	CSound* Sound = FindSound(Name);

	if (!Sound)
		return false;

	// Obj�� ������ �Ÿ������ ���.
	if (Obj)
	{
		SoundPlayAtDistance(Sound, Obj);
	}
	
	// Obj�� ������ �״�� ���.
	else
	{
		Sound->Play();
	}

	return true;
}

bool CSoundManager::SoundStop(const std::string& Name)
{
	CSound* Sound = FindSound(Name);

	if (!Sound)
		return false;

	Sound->Stop();

	return true;
}

bool CSoundManager::SoundPause(const std::string& Name)
{
	CSound* Sound = FindSound(Name);

	if (!Sound)
		return false;

	Sound->Pause();

	return true;
}

bool CSoundManager::SoundResume(const std::string& Name)
{
	CSound* Sound = FindSound(Name);

	if (!Sound)
		return false;

	Sound->Resume();

	return true;
}

CSound* CSoundManager::FindSound(const std::string& Name)
{
	auto	iter = m_mapSound.find(Name);

	if (iter == m_mapSound.end())
		return nullptr;

	return iter->second;
}

FMOD::ChannelGroup* CSoundManager::FindChannelGroup(const std::string& Name)
{
	auto	iter = m_mapGroup.find(Name);

	if (iter == m_mapGroup.end())
		return nullptr;

	return iter->second;
}

void CSoundManager::ReleaseSound(const std::string& Name)
{
	auto	iter = m_mapSound.find(Name);

	if (iter != m_mapSound.end())
	{
		if (iter->second->GetRefCount() == 1)
			m_mapSound.erase(iter);
	}
}

bool CSoundManager::IsSoundPlay(const std::string& Name)
{
	CSound* Sound = FindSound(Name);

	if (!Sound)
		return false;

	return Sound->IsPlay();
}

void CSoundManager::SoundPlayAtDistance(CSound* Sound, CGameObject* Obj)
{
	// �Ҹ� û������� Camera.

	// ���� ���� ������Ʈ�θ� �Ǵ��Ͽ� ��������� ������.
	// ��, ���� ä��, ���� �ν��Ͻ��� �����ϰ� ���ÿ� �Ҹ��� ����Ұ��, 
	// �Ҹ� ũ�Ⱑ ���������Ұ���.

	CCameraComponent* Cam = CSceneManager::GetInst()->GetScene()->GetCameraManager()->GetCurrentCamera();
	
	Vector3 CurrentPos = Cam->GetWorldPos();
	Vector3 TargetPos = Obj->GetWorldPos();

	float Distance = CurrentPos.Distance(TargetPos);

	float SrcVolume = 0.f;

	FMOD::ChannelGroup* Group = Sound->m_Group;

	Group->getVolume(&SrcVolume);

	// 1.0 ~ 0.0 ���� ��ȯ
	float ConvertedVolume = (m_SoundDistance - Distance) / m_SoundDistance;

	if (ConvertedVolume > 1.f)
	{
		ConvertedVolume = 1.f;
	}

	else if (ConvertedVolume < 0.f)
	{
		ConvertedVolume = 0.f;
	}

	Group->setVolume(ConvertedVolume);

	Sound->Play();

	return;
}
