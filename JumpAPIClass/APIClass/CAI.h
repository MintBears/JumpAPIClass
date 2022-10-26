#pragma once
#include "CComponent.h"

class CState;


class CAI :
	public CComponent
{
public:
	CAI(CObj* _pOwner);
	~CAI();
private:
	map<wstring, CState*>			m_mapState;			//모든 상태 모음집 
	CState*							m_pCurState;		//현제 상태 변수

public:


public:
	virtual void tick() override {}
	virtual void final_tick() override;
	virtual void render(HDC _dc) override {}

	CLONE(CAI)

public:
	void AddState(const wstring& _strKey, CState* _pState);
	CState* FindState(const wstring& _strkey);
	void ChangeState(const wstring& _strStateName);
};