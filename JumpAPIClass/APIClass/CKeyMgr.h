#pragma once


enum class KEY
	//Ű�� ����
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

	END,		//Ű ������ ���� ���� ǥ��
};

enum class KEY_STATE
	//Ű�� ���� ����
{
	TAP,		//��������
	PRESSED,	//������ִµ���
	RELEASED,	//��������
	NONE,		//�ƹ��͵� �ƴѼ���
};

struct tKeyInfo
	//Ű������ ���� ����ü
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

