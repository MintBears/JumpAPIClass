#include "pch.h"
#include "CLevelMgr.h"

#include "CLevel.h"
#include "CStartLevel.h"
#include "CStage01Level.h"

CLevelMgr::CLevelMgr() :
	m_arrLevel{},
	m_CurLevel(nullptr)
{
}

CLevelMgr::~CLevelMgr()
{
	for (size_t i = 0; i < (UINT)LEVEL_TYPE::END; i++)
	{
		DEL(m_arrLevel[i]);
	}
}

void CLevelMgr::init()
{
	//level »ý¼º
	m_arrLevel[(UINT)LEVEL_TYPE::START] = new CStartLevel;
	m_arrLevel[(UINT)LEVEL_TYPE::STAGE_01] = new CStage01Level;

	m_CurLevel = m_arrLevel[(UINT)LEVEL_TYPE::START];
	m_CurLevel->init();
	
}

void CLevelMgr::tick()
{
	m_CurLevel->tick();
	m_CurLevel->final_tick();
}

void CLevelMgr::render(HDC _dc)
{
	m_CurLevel->render(_dc);
}
