#include "pch.h"
#include "CtraceState.h"

#include "CTimeMgr.h"
#include "CLevelMgr.h"
#include "CLevel.h"
#include "CPlayer.h"

#include "CMonster.h"

CtraceState::CtraceState()
{
}

CtraceState::~CtraceState()
{
}

void CtraceState::finaltick()
{
	CMonster* pMon = dynamic_cast<CMonster*>(GetOwnerObj());
	assert(pMon);

	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(pCurLevel->GetLayer(LAYER::PLAYER)[0]);
	assert(pPlayer);


	Vec2 vMonPos = pMon->GetPos();
	Vec2 vPlayerPos = pPlayer->GetPos();

	Vec2 vMonToPlayer = vPlayerPos - vMonPos;
	vMonToPlayer.Normalize();

	float fSpeed = pMon->GetMonsterInfo().m_fSpeed;

	vMonPos += vMonToPlayer * DT * fSpeed;
	pMon->SetPos(vMonPos);
}

void CtraceState::Enter()
{

}

void CtraceState::Exit()
{
}
