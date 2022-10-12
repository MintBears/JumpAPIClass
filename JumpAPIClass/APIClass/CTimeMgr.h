#pragma once
class CTimeMgr
{
	SINGLE(CTimeMgr);

private :
	LARGE_INTEGER m_llPrevCount;
	LARGE_INTEGER m_llCurCount;
	LARGE_INTEGER m_llFrequency;

	UINT		  m_iCallCount;
	FLOAT		  m_fDeltaTime;
	FLOAT		  m_fTime;


public :
	void init();
	void tick();
	void render();

public : 
	FLOAT GetDeltaTime() { return m_fDeltaTime; }

};

