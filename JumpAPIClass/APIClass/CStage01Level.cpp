#include "pch.h"
#include "CStage01Level.h"

#include "CEngine.h"
#include "CKeyMgr.h"

#include "CPlayer.h"

CStage01Level::CStage01Level()
{
}

CStage01Level::~CStage01Level()
{
}

void CStage01Level::init()
{
	CPlayer* Player = new CPlayer;
	Player->SetPos(Vec2((FLOAT)(CEngine::GetInst()->GetResolution().x / 2), (FLOAT)(CEngine::GetInst()->GetResolution().y / 2)));
	Player->SetScale(Vec2(100.f, 100.f));
	AddObject(Player, LAYER::PLAYER);
}

void CStage01Level::tick()
{
	CLevel::tick();

	if (IsTap(KEY::ENTER))
	{
		ChangeLevel(LEVEL_TYPE::START);
	}
}

void CStage01Level::Enter()
{
	init();
}

void CStage01Level::Exit()
{
	DeleteAllobject();
}
