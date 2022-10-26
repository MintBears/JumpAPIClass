#include "pch.h"
#include "CIdleState.h"

#include "CLevelMgr.h"
#include "CLevel.h"
#include "CPlayer.h"

#include "CMonster.h"

CIdleState::CIdleState()
{
}

CIdleState::~CIdleState()
{
}

void CIdleState::finaltick()
{
	CMonster* pMon = dynamic_cast<CMonster*>(GetOwnerObj());
	assert(pMon);

	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(pCurLevel->GetLayer(LAYER::PLAYER)[0]);
	assert(pPlayer);
	

	float fDerectRange = pMon->GetMonsterInfo().m_fDetectRange;

	Vec2 vDir = pMon->GetPos() - pPlayer->GetPos();
	if (vDir.Length() < fDerectRange)
	{
		GetOwnerAI()->ChangeState(L"Trace");
	}



}

void CIdleState::Enter()
{
}

void CIdleState::Exit()
{
}
