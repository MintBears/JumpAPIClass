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

//�̱��� �ʱ�ȭ
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
	//���� dc�� �̰ɷ� �����
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

	//������ ũ�� ����
	RECT rt = { 0, 0, (LONG)_iWidth, (LONG)_iHeight};
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);
	SetWindowPos(m_hMainWnd, nullptr, 0, 0, rt.right - rt.left, rt.bottom - rt.top, 0); 

	//HDC �ʱ�ȭ
	m_hDC = GetDC(m_hMainWnd);

	//����� �� ��Ʈ�� ����
	m_pMemTex = CResMgr::GetInst()->CreatTexture(L"BackBuffer", m_Resolution.x, m_Resolution.y);

	//���ֻ���ϴ� �� �귯��
	CreatPenBrush();

	//timeMgr �ʱ�ȭ
	CPathMgr::GetInst()->init();
	CTimeMgr::GetInst()->init();
	CKeyMgr::GetInst()->init();
	CLevelMgr::GetInst()->init();
}

void CEngine::progress()
{
	//������ ����
	tick();

	//ȭ�� ������ ����
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
	//ȭ�� Ŭ����
	Rectangle(m_pMemTex->GetDC(), -1, -1, m_Resolution.x + 1, m_Resolution.y + 1);

	//���� ����
	CLevelMgr::GetInst()->render(m_pMemTex->GetDC());

	//ī�޶� ����Ʈ
	CCamera::GetInst()->render(m_pMemTex->GetDC());

	BitBlt(m_hDC, 0, 0, m_Resolution.x, m_Resolution.y, m_pMemTex->GetDC(), 0, 0, SRCCOPY);

	//������ Ȯ�ο�
	CTimeMgr::GetInst()->render();

}

void CEngine::CreatPenBrush()
{
	m_arrPen[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_arrPen[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	m_arrPen[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));

	////dc �귯�� ����
	//HBRUSH hBlueBrush = CreateSolidBrush(RGB(0, 0, 255));
	//HBRUSH hWhiteBrush = (HBRUSH)SelectObject(m_hDC, hBlueBrush);
	//DeleteObject(hWhiteBrush);
	//
	//GetStockObject(HOLLOW_BRUSH);
}
