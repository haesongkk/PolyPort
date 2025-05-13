#pragma once
#include <fmod.hpp>

// ���� ������ ä�� ���
// ���� ä�γ����� volume, pause, resume ���� ������
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