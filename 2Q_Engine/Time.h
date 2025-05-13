#pragma once
class Time
{
private:
	LARGE_INTEGER m_currentTime;
	LARGE_INTEGER m_previousTime;
	LARGE_INTEGER m_frequency;
	float m_deltaTime;
public:
	static float m_elapsedTime;

	void Initialize();
	void Update();

	float GetDeltaTime() { return m_deltaTime; }
};

