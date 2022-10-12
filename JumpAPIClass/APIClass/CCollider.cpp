#include "pch.h"
#include "CCollider.h"

#include "CEngine.h"
#include"CObj.h"

CCollider::CCollider(CObj* _Owner) :
	CComponent(_Owner),
	m_OffsetPos(),
	m_FinalPos(),
	m_OverlapCount(0)
{
}

CCollider::~CCollider()
{
}

void CCollider::tick()
{
	m_FinalPos = GetOwner()->GetPos() + m_OffsetPos;

	assert(!(m_OverlapCount < 0));
}

void CCollider::render(HDC _dc)
{
	//��� �귯���� �����
	//HPEN hGreenPen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	//HBRUSH hNullBrush = (HBRUSH)GetStockObject(NULL_BRUSH);

	HPEN hPen = nullptr;

	if (0 < m_OverlapCount)
	{
		hPen = CEngine::GetInst()->GetPen(PEN_TYPE::GREEN);
	}
	else
	{
		hPen = CEngine::GetInst()->GetPen(PEN_TYPE::RED);
	}


	//���� ��� �귯�ø� ���� ������ �͵�� ���۴�.
	HPEN hOriginPen = (HPEN)SelectObject(_dc, hPen);
    HBRUSH hOriginBrush = (HBRUSH)SelectObject(_dc, (HBRUSH)GetStockObject(NULL_BRUSH));

	Vec2 Pos = CCamera::GetInst()->GetRenderPos(m_FinalPos);

	Rectangle(_dc, (int)(Pos.x - m_Scale.x / 2.f)
			   	 , (int)(Pos.y - m_Scale.y / 2.f)
				 , (int)(Pos.x + m_Scale.x / 2.f)
				 , (int)(Pos.y + m_Scale.y / 2.f));
	//�ٽ� ����ġ
	SelectObject(_dc, hOriginPen);
	SelectObject(_dc, hOriginBrush);

	//���� ���� �� ����
	//DeleteObject(hGreenPen);
}

void CCollider::BeginOverlap(CCollider* _Other)
{
	m_OverlapCount++;

	GetOwner()->BeginOverlap(_Other);
}

void CCollider::OnOverlap(CCollider* _Other)
{
	GetOwner()->OnOverlap(_Other);
}

void CCollider::EndOverlap(CCollider* _Other)
{
	GetOwner()->EndOverlap(_Other);
	m_OverlapCount--;
}
