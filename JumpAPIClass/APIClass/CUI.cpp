#include "pch.h"
#include "CUI.h"

#include "CEngine.h"
#include "CKeyMgr.h"

CUI::CUI()
	: m_bLbtnDown(false)
	, m_bMouseOn(false)
	, m_bCmrAfctd(false)
{
}

CUI::~CUI()
{
}

void CUI::tick()
{
	MouseOnCheck();
}

void CUI::render(HDC _dc)
{
	HPEN hPen = CEngine::GetInst()->GetPen(PEN_TYPE::GREEN);

	//기존 펜과 브러시를 새로 가져온 것들로 봐꾼다.
	HPEN hOriginPen = (HPEN)SelectObject(_dc, hPen);
	HBRUSH hOriginBrush = (HBRUSH)SelectObject(_dc, (HBRUSH)GetStockObject(NULL_BRUSH));

	Vec2 vPos = GetPos();
	if (m_bCmrAfctd)
	{
		vPos = CCamera::GetInst()->GetRenderPos(vPos);
	}
	Vec2 vScale = GetScale();

	Rectangle(_dc
		, (int)(vPos.x)
		, (int)(vPos.y)
		, (int)(vPos.x + vScale.x)
		, (int)(vPos.y + vScale.y));
	//다시 원위치
	SelectObject(_dc, hOriginPen);
	SelectObject(_dc, hOriginBrush);

}

void CUI::MouseOnCheck()
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();
	Vec2 vMousePos = MOUSE_POS;
	if (m_bCmrAfctd)
	{
		vMousePos = CCamera::GetInst()->GetRenderPos(vMousePos);
	}

	//범위안에 들어왔다. => 마우스가 버튼위에 있다.
	if (vPos.x <= vMousePos.x && vMousePos.x <= vPos.x + vScale.x &&
		vPos.y <= vMousePos.y && vMousePos.y <= vPos.y + vScale.y)

	{
		m_bMouseOn = true;
	}
	else
	{
		m_bMouseOn = false;
	}


}
