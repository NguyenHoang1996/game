#include "Timer.h"
#include "Global.h"

Timer::Timer()
{
	// Query performance hardware 
	if (QueryPerformanceFrequency((LARGE_INTEGER *)&m_NS_Frequency))
	{
		m_IsPerfHardware = TRUE;
		QueryPerformanceCounter((LARGE_INTEGER *)&m_NS_LastTime);
		QueryPerformanceFrequency(&m_NS_LastTime);
		QueryPerformanceCounter(&m_NS_CurrentTime);
	}

	else// no performance counter, read in using timeGetTime 
	{
		m_IsPerfHardware = FALSE;
		m_MS_LastTime = timeGetTime();
		m_MS_CurrentTime = timeGetTime();
	}
	m_LastFPSTime = timeGetTime();
	m_Count = 0;
	m_FPSAvarage = 0;
}


Timer::~Timer()
{

}

float Timer::Tick()
{
	static float deta_Time;
	if (m_IsPerfHardware)
	{
		QueryPerformanceCounter(&m_NS_CurrentTime);
		deta_Time = (m_NS_CurrentTime.QuadPart - m_NS_LastTime.QuadPart) / float(m_NS_Frequency.QuadPart);
	}
	else
	{
		m_MS_CurrentTime = timeGetTime();
		deta_Time = (float)(m_MS_CurrentTime - m_MS_LastTime) / 1000.0f;
	}
	return deta_Time;
}


void Timer::FreshTime()
{
	if (m_IsPerfHardware)
	{
		m_NS_LastTime = m_NS_CurrentTime;
	}
	else
	{
		m_MS_LastTime = m_MS_CurrentTime;
	}
	m_Count++;
	if (m_Count >= g_FPS) {
		DWORD _now = timeGetTime();
		m_FPSAvarage = 1000.0f / ((float)(_now - m_LastFPSTime) / g_FPS);
		m_LastFPSTime = _now;
		m_Count = 0;
	}
}

float Timer::GetFrameRate()
{
	return m_FPSAvarage;
}