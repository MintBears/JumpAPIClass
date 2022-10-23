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

	//���� ��� �귯�ø� ���� ������ �͵�� ���۴�.
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
	//�ٽ� ����ġ
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

	//�����ȿ� ���Դ�. => ���콺�� ��ư���� �ִ�.
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
