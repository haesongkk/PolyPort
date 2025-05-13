#pragma once
#include <fmod.hpp>

// 따로 관리될 채널 목록
// 같은 채널끼리는 volume, pause, resume 등을 공유함
enum CHANNEL
{
    BGM,
    SFX,
    BUBBLE,
    PLAYER,
    END_CHANNEL,
};

class Sound
{
public:
    Sound();
    ~Sound();

public:
    bool Initialize(const string& _folderPath);
    void Update();

private:
    void AddSound(string _soundPath, bool _bLoop);

public:
    static void Play(CHANNEL _ch, const string& _soundPath);
    static void Pause(CHANNEL _ch);
    static void Resume(CHANNEL _ch);
    static void Stop(CHANNEL _ch);
    static void SetVolume(CHANNEL _ch, float _vol);

private:
    static FMOD_SYSTEM* m_pSystem;
    static FMOD_CHANNEL* m_pChannel[CHANNEL::END_CHANNEL];
    static map<string, FMOD_SOUND*> m_sounds;

};