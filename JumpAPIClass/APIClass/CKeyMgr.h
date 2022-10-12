#pragma once


enum class KEY
	//키의 종류
{
	UP,
	DOWN,
	LEFT,
	RIGHR,

	SPACE,
	ENTER,
	ESC,
	LALT,
	LCTRL,
	LSHIFT,
	TAB,

	LBTN,
	RBTN,

	W,
	A,
	S,
	D,

	END,		//키 종류의 대한 갯수 표현
};

enum class KEY_STATE
	//키를 통한 상태
{
	TAP,		//눌린순간
	PRESSED,	//누루고있는동안
	RELEASED,	//해제순간
	NONE,		//아무것도 아닌순간
};

struct tKeyInfo
	//키정보에 대한 구조체
{
	KEY			key;
	KEY_STATE	state;
	bool		bPrev;
};



class CKeyMgr
{
	SINGLE(CKeyMgr);

private:

	vector<tKeyInfo>	m_vecKey;
	Vec2				m_vMousePos;


public:
	void init();
	void tick();

public:
	KEY_STATE GetKeyState(KEY _key) { return m_vecKey[(UINT)_key].state; }
	Vec2 GetMousePos() { return m_vMousePos; }
};

