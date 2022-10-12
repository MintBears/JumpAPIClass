#pragma once
class CLevel;
class CLevelMgr
{
	SINGLE(CLevelMgr);

private:
	//상속을 한 이유가 여기있다.
	//부모 객체 포인터로 변수를 만들면 그 자식의 있는 모든 형태의 객체로 형변환 할수있기 때문에 
	//한 타입으로 관리 하기가 쉬워진다.
	//
	CLevel* m_arrLevel[(UINT)LEVEL_TYPE::END];
	CLevel* m_CurLevel;

public: 
	CLevel* GetCurLevel() { return m_CurLevel; }

public:

	void init();
	void tick();
	void render(HDC _dc);
};

