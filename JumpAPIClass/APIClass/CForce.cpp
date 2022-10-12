#include "pch.h"
#include "CForce.h"

#include "CTimeMgr.h"
#include "CEngine.h"

#include "CRigidbody.h"

#include "CLevel.h"
#include "CLevelMgr.h"

CForce::CForce()
	: m_fAccTime(0.f)
	, m_fLifeTime(0.f)
	, m_fForce(0.f)
	, m_fRadius(0.f)
{
}

CForce::~CForce()
{
}

void CForce::tick()
{
	m_fAccTime += DT;
	if (m_fLifeTime < m_fAccTime)
	{
		SetDead();
		return;
	}

	//player Layer�� ����

	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();
	const vector<CObj*>& vecPlayerLayer = pCurLevel->GetLayer(LAYER::PLAYER);

	for (size_t i = 0; i < vecPlayerLayer.size(); i++)
	{
		if (nullptr == vecPlayerLayer[i]->GetCRigidbody())
			continue;

		//������ ������ ���ϴ� ����
		Vec2 vForceDir = vecPlayerLayer[i]->GetPos() - GetPos();
		//���� ����� �Ÿ�
		float fDistance = vForceDir.Length();

		float fRatio = 1.f -(fDistance / m_fRadius);
		//float fRatio = cosf((fDistance / m_fRadius) * PI * 0.5f);
		Saturate(fRatio);
		//���� ����
		vForceDir.Normalize();
		//���� ũ��
		vForceDir *= m_fForce * fRatio;

		vecPlayerLayer[i]->GetCRigidbody()->AddForce(vForceDir);
	}

}

void CForce::render(HDC _dc)
{
	HPEN hGreenPen = CEngine::GetInst()->GetPen(PEN_TYPE::GREEN);
	//���� ��� �귯�ø� ���� ������ �͵�� ���۴�.
	HPEN hOriginPen = (HPEN)SelectObject(_dc, hGreenPen);
	HBRUSH hOriginBrush = (HBRUSH)SelectObject(_dc, (HBRUSH)GetStockObject(NULL_BRUSH));

	Vec2 Pos = CCamera::GetInst()->GetRenderPos(GetPos());

	Ellipse(_dc, (int)(Pos.x - m_fRadius)
		, (int)(Pos.y - m_fRadius)
		, (int)(Pos.x + m_fRadius)
		, (int)(Pos.y + m_fRadius));
	//�ٽ� ����ġ
	SelectObject(_dc, hOriginPen);
	SelectObject(_dc, hOriginBrush);
	
}
