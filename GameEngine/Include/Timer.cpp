#include "Timer.h"
#include "Engine.h"

CTimer::CTimer() :
	m_FPS(0.f),
	m_DeltaTime(0.f),
	m_FPSTime(0.f),
	m_Tick(0),
	m_FPSText{}
{
	// ���ػ� Ÿ�̸��� �ʴ� ƽ�� ���´�.
	QueryPerformanceFrequency(&m_Second);

	// ���ػ� Ÿ�̸��� ���� ƽ�� ���´�.
	QueryPerformanceCounter(&m_Time);
}

CTimer::~CTimer()
{
}

float CTimer::Update()
{
	LARGE_INTEGER	Time;
	QueryPerformanceCounter(&Time);

	m_DeltaTime = (Time.QuadPart - m_Time.QuadPart) / (float)m_Second.QuadPart;

	m_Time = Time;


	m_FPSTime += m_DeltaTime;
	++m_Tick;

	if (m_Tick == 60)
	{
		m_FPS = 60 / m_FPSTime;
		m_FPSTime = 0.f;
		m_Tick = 0;

		memset(m_FPSText, 0, sizeof(char) * 64);

		if (!CEngine::GetInst()->IsEditMode())
		{
#ifdef _DEBUG
			sprintf_s(m_FPSText, "[�����] ���� ���� ���� FPS : %.f", m_FPS);
#else
			sprintf_s(m_FPSText, "���� ���� ���� FPS : %.f", m_FPS);
#endif

			SetWindowTextA(CEngine::GetInst()->GetWindowHandle(), m_FPSText);
		}
	}

	return m_DeltaTime;
}
