#pragma once

class CObj;

class CEventMge
{
	SINGLE(CEventMge);
private:
	vector<tEvent>	m_Event;

	vector<CObj*>	m_Garbage;

public:
	void tick();

	void AddEvent(const tEvent& _event) { m_Event.push_back(_event); }
};

