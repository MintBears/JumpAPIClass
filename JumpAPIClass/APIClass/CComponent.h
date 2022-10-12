#pragma once
#include "CEntity.h"

class CObj;
class CComponent:public CEntity
{
public:
	CComponent(CObj* _Owner);
	virtual ~CComponent();

private:
	//나를 소유하고있는 자가 누구인지 초기에 지정만하지 추후에 봐끼지 않을것이기때문에 const를 붙인다.
	CObj* const m_Owner;

public:
	CObj* GetOwner() { return m_Owner; }

public:
	virtual void tick() = 0;
	virtual void final_tick() {};
	virtual void render(HDC _dc) = 0;


};