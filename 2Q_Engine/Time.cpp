#include "pch.h"
#include "Time.h"

float Time::m_elapsedTime = 0;

void Time::Initialize()
{
	QueryPerformanceFrequency(&m_frequency);
	QueryPerformanceCounter(&m_previousTime);
	QueryPerformanceCounter(&m_currentTime);
}

void Time::Update()
{


	m_previousTime = m_currentTime;
	QueryPerformanceCounter(&m_currentTime);
	m_deltaTime = (float)(m_currentTime.QuadPart - m_previousTime.QuadPart) / (float)(m_frequency.QuadPart);
}