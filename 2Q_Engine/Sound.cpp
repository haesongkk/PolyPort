#include "pch.h"
#include "Sound.h"

#include <filesystem>

FMOD_SYSTEM* Sound::m_pSystem = nullptr;
FMOD_CHANNEL* Sound::m_pChannel[] = {};
map<string, FMOD_SOUND*> Sound::m_sounds = {};

Sound::Sound()
{
	FMOD_System_Create(&m_pSystem, FMOD_VERSION);
	FMOD_System_Init(m_pSystem, CHANNEL::END_CHANNEL, FMOD_INIT_NORMAL, NULL);
}

Sound::~Sound()
{
	for (auto it = m_sounds.begin(); it != m_sounds.end(); it++)
	{
		FMOD_Sound_Release(it->second);
	}
	m_sounds.clear();

	FMOD_System_Close(m_pSystem);
	FMOD_System_Release(m_pSystem);

	// ä���� �˾Ƽ� �����Ǵ���?
}

bool Sound::Initialize(const string& _folderPath)
{
	filesystem::path folderPath(_folderPath);
	assert(filesystem::exists(folderPath));
	assert(filesystem::is_directory(folderPath));

	for (const auto& entry : filesystem::directory_iterator(_folderPath))
	{
		assert(entry.is_regular_file());

		string filePath = entry.path().string();
		string fileName = entry.path().filename().string();
		string extension = entry.path().extension().string();

		if (extension == ".mp3" || extension == ".wav")
		{
			// �������� '\\'�� ������ '/' �� ��ȯ
			replace(filePath.begin(), filePath.end(), '\\', '/');

			// ���� �� (loop)�� ���ԵǾ��ִٸ� true ��ȯ
			bool bLoop = fileName.find("(loop)") != string::npos;

			AddSound(filePath, bLoop);
		}
	}
	return false;
}

void Sound::Update()
{
	FMOD_System_Update(m_pSystem);
}

void Sound::AddSound(string _soundPath, bool _bLoop)
{
	FMOD_SOUND* sound = nullptr;

	FMOD_MODE mode;
	if (_bLoop) mode = FMOD_LOOP_NORMAL;
	else mode = FMOD_DEFAULT;

	// ���� ��ο� ���� ���η� ���� ����
	FMOD_System_CreateSound(m_pSystem, _soundPath.c_str(), mode, 0, &sound);

	// ���尡 �� �����Ǿ��ٸ� nullptr�� �ƴϾ����
	assert(sound != nullptr);

	// ������ ���带 ���� ��θ� Ű������ ������ �ʿ� �־��ش�
	m_sounds.insert(make_pair(_soundPath, sound));
}

void Sound::Play(CHANNEL _ch, const string& _soundPath)
{
	Stop(SFX);
	FMOD_SOUND* sound = nullptr;
	if (m_sounds.find(_soundPath) != m_sounds.end())
		sound = m_sounds[_soundPath];
	assert(sound != nullptr);

	FMOD_System_PlaySound(m_pSystem, sound, NULL, false, &m_pChannel[_ch]);
	FMOD_Channel_SetVolume(m_pChannel[_ch], 0.5);
}

void Sound::Pause(CHANNEL _ch)
{
	FMOD_Channel_SetPaused(m_pChannel[_ch], true);
}

void Sound::Resume(CHANNEL _ch)
{
	FMOD_Channel_SetPaused(m_pChannel[_ch], false);
}

void Sound::Stop(CHANNEL _ch)
{
	FMOD_Channel_Stop(m_pChannel[_ch]);
}

void Sound::SetVolume(CHANNEL _ch, float _vol)
{
	FMOD_Channel_SetVolume(m_pChannel[_ch], _vol);
}
