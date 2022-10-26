#include "pch.h"
#include "CLevelMgr.h"

#include "CLevel.h"
#include "CStartLevel.h"
#include "CStage01Level.h"
#include "CEditorLevel.h"

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
	m_arrLevel[(UINT)LEVEL_TYPE::EDITOR] = new CEditorLevel;

	//m_CurLevel = m_arrLevel[(UINT)LEVEL_TYPE::START];
	//m_CurLevel->init();

	ChangeLevel(LEVEL_TYPE::START);
	
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

void CLevelMgr::ChangeLevel(LEVEL_TYPE _eNext)
{
	assert(m_CurLevel != m_arrLevel[(UINT)_eNext]);

	if (nullptr != m_CurLevel)
	{
		m_CurLevel->Exit();
	}
	m_CurLevel = m_arrLevel[(UINT)_eNext];

	m_CurLevel->Enter();
}
