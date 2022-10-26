#include "pch.h"
#include "CStartLevel.h"

#include "CEngine.h"
#include "CCollisionMgr.h"

#include "CResMgr.h"
#include "CKeyMgr.h"

#include "CCamera.h"
#include "CObj.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CForce.h"
#include "CPlatform.h"



CStartLevel::CStartLevel()
{
}

CStartLevel::~CStartLevel()
{
}

void CStartLevel::init()
{
	//택스트 로딩
	CResMgr::GetInst()->LoadTexture(L"Monster", L"texture\\magicmushroom.bmp");

	CPlayer* Player = new CPlayer;
	Player->SetPos(Vec2((FLOAT)(CEngine::GetInst()->GetResolution().x / 2), (FLOAT)(CEngine::GetInst()->GetResolution().y / 2)));
	Player->SetScale(Vec2(100.f, 100.f));
	AddObject(Player, LAYER::PLAYER);

	CMonster* Monster = new CMonster;
	Monster->SetPos(Vec2(50.f, 50.f));
	Monster->SetScale(Vec2(100.f, 100.f));
	Monster->SetTarget(Player);
	AddObject(Monster, LAYER::MONSTER);

	//level의 충돌 체크
	CCollisionMgr::GetInst()->LayerCheck(LAYER::PLAYER, LAYER::MONSTER);
	CCollisionMgr::GetInst()->LayerCheck(LAYER::PLAYER, LAYER::MONSTER_PROJECTILE);
	CCollisionMgr::GetInst()->LayerCheck(LAYER::PLAYER, LAYER::PLATFORM);

	CCollisionMgr::GetInst()->LayerCheck(LAYER::PLAYER_PROJECTILE, LAYER::MONSTER);

	CCollisionMgr::GetInst()->LayerCheck(LAYER::MONSTER, LAYER::MONSTER);


	Vec2 Resolution = CEngine::GetInst()->GetResolution();
	CCamera::GetInst()->SetLook(Resolution/2.f);
}

void CStartLevel::tick()
{
	CLevel::tick();

	if (IsTap(KEY::ENTER))
	{
		//CCamera::GetInst()->FadeOut(1.0f);
		//CCamera::GetInst()->FadeIn(1.0f);
		//CCamera::GetInst()->CameraShake(20.f, 300.f, 0.5f);
		ChangeLevel(LEVEL_TYPE::EDITOR);
	}

	if (IsTap(KEY::LBTN))
	{
		//중앙기준으로 퍼지는힘 작용
		CForce* pForce = new CForce;
		pForce->SetLifeTime(5.0f);
		pForce->SetForceScale(200.f);
		pForce->SetForceRadius(250.f);
		
		Vec2 vMousePos = MOUSE_POS;
		vMousePos = CCamera::GetInst()->GetRealPos(vMousePos);
		
		Instantiate(pForce, vMousePos, LAYER::FORCE);
		
	}
	if (IsTap(KEY::RBTN))
	{
		CPlatform* pPlatform = new CPlatform;

		Vec2 vMousePos = MOUSE_POS;
		vMousePos = CCamera::GetInst()->GetRealPos(vMousePos);

		Instantiate(pPlatform, vMousePos, LAYER::PLATFORM);
	}

}

void CStartLevel::Enter()
{
	init();
}

void CStartLevel::Exit()
{
	DeleteAllobject();
}
