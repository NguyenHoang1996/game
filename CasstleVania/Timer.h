#pragma once
#ifndef	_TIMER_H
#define _TIMER_H

#include "windows.h"
#include "math.h"
#include "tchar.h"

const ULONG MAX_FPS_COUNT = 50;

class Timer
{
private:
	float			m_Count;
	DWORD			m_LastFPSTime;
	float			m_FPSAvarage;

	LARGE_INTEGER	m_NS_LastTime;
	LARGE_INTEGER	m_NS_CurrentTime;
	LARGE_INTEGER	m_NS_Frequency;

	bool			m_IsPerfHardware;

	DWORD			m_MS_LastTime;
	DWORD			m_MS_CurrentTime;

public:
	Timer();
	~Timer();

	float	Tick();
	void	FreshTime();
	float	GetFrameRate();
};

#endif