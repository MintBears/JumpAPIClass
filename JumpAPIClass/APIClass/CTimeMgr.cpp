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
	//1�ʵ��� �󸶳� ī���� ������ ���� �����´�.
	QueryPerformanceFrequency(&m_llFrequency);

	QueryPerformanceCounter(&m_llCurCount);
	QueryPerformanceCounter(&m_llPrevCount);

}

void CTimeMgr::tick()
{

	//�̶����� �����ؿ� ��� ī���� ��
	QueryPerformanceCounter(&m_llCurCount);

	//tick����
	m_fDeltaTime = (FLOAT)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart) / (FLOAT)m_llFrequency.QuadPart;
	//�����ð�
	m_fTime += m_fDeltaTime;
	//�Լ�ȣ�� Ƚ��
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
