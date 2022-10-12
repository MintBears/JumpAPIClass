#include "pch.h"
#include "CMonster.h"

#include "CTimeMgr.h"
#include "CResMgr.h"
#include "CTexture.h"

#include "CPlayer.h"
#include "CCollider.h"

CMonster::CMonster()
	: m_HP(3)
	, m_Speed(100.f)
	, m_Target(nullptr)
	, m_pTex(nullptr)
{
	CreateCollider();
	GetCollider()->SetScale(Vec2(150.f, 150.f));

	m_pTex = CResMgr::GetInst()->FindTexture(L"Monster");
	
}

CMonster::~CMonster()
{
}

void CMonster::tick()
{
	if (IsValid(m_Target))
	{
		Vec2 TargetPos = m_Target->GetPos();
		m_Target->SetName(L"Player");
		Vec2 ThisPos = GetPos();

		Vec2 Dir = 	TargetPos - ThisPos;
		Dir.Normalize();

		ThisPos.x += Dir.x * m_Speed * DT;
		ThisPos.y += Dir.y * m_Speed * DT;

		SetPos(ThisPos);
	}
	CObj::tick();
}

void CMonster::render(HDC _dc)
{
	Vec2 vPos = CCamera::GetInst()->GetRenderPos(GetPos());
	Vec2 vSize = GetScale();

	static float fRatio = 0.f;
	static float Dir = 1.0f;
	fRatio += DT * Dir * 8.0f;
	if (1.0f < fRatio)
	{
		fRatio = 1.0f;
		Dir = -1.0f;	
	}
	else if (fRatio < 0.f)
	{
		fRatio = 0.0f;
		Dir = 1.0f;
	}

	 
	BLENDFUNCTION tBlend = {};

	tBlend.AlphaFormat = AC_SRC_ALPHA;
	tBlend.BlendFlags = 0;
	tBlend.BlendOp = AC_SRC_OVER;
	tBlend.SourceConstantAlpha = (int)(255 * fRatio);
	//tBlend.SourceConstantAlpha = 255;


	AlphaBlend(_dc, (int)(vPos.x - m_pTex->Widht() / 2.0f)
				  , (int)(vPos.y - m_pTex->Height() / 2.0f)
				  , m_pTex->Widht()
				  , m_pTex->Height()
				  , m_pTex->GetDC()
				  , 0, 0
				  , m_pTex->Widht()
				  , m_pTex->Height()
				  , tBlend);

	CObj::render(_dc);
}

void CMonster::BeginOverlap(CCollider* _Other)
{
	SetDead();
	_Other;
}
