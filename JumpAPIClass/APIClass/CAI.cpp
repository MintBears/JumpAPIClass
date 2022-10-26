#include "pch.h"
#include "CAI.h"

#include "CState.h"
CAI::CAI(CObj* _pOwner)
	: CComponent(_pOwner)
{

}

CAI::~CAI()
{
	map<wstring, CState*>::iterator iter = m_mapState.begin();
	for (; iter != m_mapState.end(); iter++)
	{
		DEL(iter->second);
	}
	m_mapState.clear();
}

void CAI::final_tick()
{
	if (nullptr == m_pCurState)
		return;
	m_pCurState->finaltick();
}
void CAI::AddState(const wstring& _strKey, CState* _pState)
{
	m_mapState.insert(make_pair(_strKey, _pState));
	_pState->m_pOwnerAI = this;
}

CState* CAI::FindState(const wstring& _strkey)
{

	map<wstring, CState*>::iterator iter = m_mapState.find(_strkey);
	if (iter != m_mapState.end())
		return iter->second;
	return nullptr;

}

void CAI::ChangeState(const wstring& _strStateName)
{
	CState* pNextState = FindState(_strStateName);
	assert(pNextState);

	if (m_pCurState != nullptr)
		m_pCurState->Exit();

	m_pCurState = pNextState;

	m_pCurState->Enter();
}
