#include "pch.h"
#include "CTimeMgr.h"

#include "CEngine.h"

CTimeMgr::CTimeMgr():
	m_llPrevCount{},
	m_llCurCount{},
	m_llFrequency{},
	m_iCallCount(0),
	m_fDeltaTime(0.f),
	m_fTime(0.f)
{
}

CTimeMgr::~CTimeMgr()
{
}

void CTimeMgr::init()
{
	//1초동안 얼마나 카운터 세는지 값을 가져온다.
	QueryPerformanceFrequency(&m_llFrequency);

	QueryPerformanceCounter(&m_llCurCount);
	QueryPerformanceCounter(&m_llPrevCount);

}

void CTimeMgr::tick()
{

	//이때까지 누적해온 모든 카운터 값
	QueryPerformanceCounter(&m_llCurCount);

	//tick간격
	m_fDeltaTime = (FLOAT)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart) / (FLOAT)m_llFrequency.QuadPart;
	//누적시간
	m_fTime += m_fDeltaTime;
	//함수호출 횟수
	++m_iCallCount;;



	m_llPrevCount = m_llCurCount;

}

void CTimeMgr::render()
{
	if (m_fTime >= 1.f)
	{
		wchar_t szBuff[256] = {};
		swprintf_s(szBuff, L"FPS : %d, DT : %f", m_iCallCount, m_fDeltaTime);
		SetWindowText(CEngine::GetInst()->GethMainWnd(), szBuff);

		m_fTime = 0.f;
		m_iCallCount = 0;
	}
}
