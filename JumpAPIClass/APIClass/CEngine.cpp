#include "pch.h"
#include "CEngine.h"

#include "CPathMgr.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CLevelMgr.h"
#include "CCollisionMgr.h"
#include "CEventMge.h"
#include "CCamera.h"
#include "CResMgr.h"

#include "CTexture.h"

//싱글톤 초기화
//CEngine* CEngine::m_pInst = nullptr;
CEngine::CEngine() 
	: m_hMainWnd(nullptr)
	, m_hDC(nullptr)
	, m_pMemTex(nullptr)
	, m_Resolution{}
	, m_arrPen{}
{
}

CEngine::~CEngine()
{
	//매인 dc는 이걸로 지우고
	ReleaseDC(m_hMainWnd, m_hDC);


	for (UINT i = 0; i < (UINT)PEN_TYPE::END; i++)
	{
		DeleteObject(m_arrPen[i]);
	}
}



void CEngine::Inst(HWND _hwnd, UINT _iWidth, UINT _iHeight)
{
	m_hMainWnd = _hwnd;

	m_Resolution.x = _iWidth;
	m_Resolution.y = _iHeight;

	//원도우 크기 설정
	RECT rt = { 0, 0, (LONG)_iWidth, (LONG)_iHeight};
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);
	SetWindowPos(m_hMainWnd, nullptr, 0, 0, rt.right - rt.left, rt.bottom - rt.top, 0); 

	//HDC 초기화
	m_hDC = GetDC(m_hMainWnd);

	//백버퍼 용 비트맵 제작
	m_pMemTex = CResMgr::GetInst()->CreatTexture(L"BackBuffer", m_Resolution.x, m_Resolution.y);

	//자주사용하는 팬 브러쉬
	CreatPenBrush();

	//timeMgr 초기화
	CPathMgr::GetInst()->init();
	CTimeMgr::GetInst()->init();
	CKeyMgr::GetInst()->init();
	CLevelMgr::GetInst()->init();
}

void CEngine::progress()
{
	//논리적인 연산
	tick();

	//화면 랜더링 갱신
	render();

	CEventMge::GetInst()->tick();
}

void CEngine::tick()
{
	CTimeMgr::GetInst()->tick();
	CKeyMgr::GetInst()->tick();
	CCamera::GetInst()->tick();
	CLevelMgr::GetInst()->tick();
	CCollisionMgr::GetInst()->tick();

}

void CEngine::render()
{
	//화면 클리어
	Rectangle(m_pMemTex->GetDC(), -1, -1, m_Resolution.x + 1, m_Resolution.y + 1);

	//레벨 렌더
	CLevelMgr::GetInst()->render(m_pMemTex->GetDC());

	//카메라 이팩트
	CCamera::GetInst()->render(m_pMemTex->GetDC());

	BitBlt(m_hDC, 0, 0, m_Resolution.x, m_Resolution.y, m_pMemTex->GetDC(), 0, 0, SRCCOPY);

	//프레임 확인용
	CTimeMgr::GetInst()->render();

}

void CEngine::CreatPenBrush()
{
	m_arrPen[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_arrPen[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	m_arrPen[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));

	////dc 브러쉬 설정
	//HBRUSH hBlueBrush = CreateSolidBrush(RGB(0, 0, 255));
	//HBRUSH hWhiteBrush = (HBRUSH)SelectObject(m_hDC, hBlueBrush);
	//DeleteObject(hWhiteBrush);
	//
	//GetStockObject(HOLLOW_BRUSH);
}
