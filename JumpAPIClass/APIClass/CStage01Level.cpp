#include "pch.h"
#include "CStage01Level.h"

#include "CEngine.h"
#include "CKeyMgr.h"

#include "CPlayer.h"
#include "CMonster.h"

CStage01Level::CStage01Level()
{
}

CStage01Level::~CStage01Level()
{
}

void CStage01Level::init()
{

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
