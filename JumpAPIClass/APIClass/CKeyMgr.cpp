#include "pch.h"

#include "CEngine.h"

#include "CKeyMgr.h"

int g_arrVK[(UINT)KEY::END]
=
{
	VK_UP,
	VK_DOWN,
	VK_LEFT,
	VK_RIGHT,

	VK_SPACE,

	VK_RETURN,
	VK_ESCAPE,
	VK_LMENU,
	VK_LCONTROL,
	VK_LSHIFT,
	VK_TAB,

	VK_LBUTTON,
	VK_RBUTTON,

	'W',
	'A',
	'S',
	'D',
};

CKeyMgr::CKeyMgr()
{
}

CKeyMgr::~CKeyMgr()
{
}

void CKeyMgr::init()
{
	for (int i = 0; i < (int)KEY::END; ++i)
	{
		m_vecKey.push_back(tKeyInfo{ (KEY)i, KEY_STATE::NONE });
	}
}

void CKeyMgr::tick()
{

	if (GetFocus())
		//���� �����찡 ��Ŀ���ϰ��ִ°�
	{
		for (size_t i = 0; i < m_vecKey.size(); i++)
		{
			//m_vecKey[i].key = KEY::UP;
			//GetAsyncKeyState(VK_UP);
			//GetAsyncKeyState(VK_DOWN);
			//GetAsyncKeyState(VK_LEFT);
			//GetAsyncKeyState(VK_RIGHT);
			// => KRY	������ ������ �߰��ϰԵǸ� �̷��� ���ǹ��� ��� �߰��ؾߵȴ�.
			// �׷��Ƿ� �Ʒ��� ���� �̷��� ���� �Ѱ��� ��� 1��1�� ��Ī�����ִ� �۷ι� vector�� ����� Ű�� �׶� ������� ������� vector�� ��ȭ�����ش�.
			// =>		GetAsyncKeyState(g_arrVK[(UINT)m_vecKey[i].key])
			if (GetAsyncKeyState(g_arrVK[(UINT)m_vecKey[i].key]) & 0x8000)
			{
				if (false == m_vecKey[i].bPrev)
				{
					m_vecKey[i].state = KEY_STATE::TAP;
					m_vecKey[i].bPrev = true;
				}
				else
				{
					m_vecKey[i].state = KEY_STATE::PRESSED;
				}

			}
			else
			{
				if (false == m_vecKey[i].bPrev)
				{
					m_vecKey[i].state = KEY_STATE::NONE;
				}
				else
				{
					m_vecKey[i].state = KEY_STATE::RELEASED;
					m_vecKey[i].bPrev = false;
				}
			}

		}
	}
	else
	{
		for (size_t i = 0; i < m_vecKey.size(); i++)
		{
			if (KEY_STATE::TAP == m_vecKey[i].state || KEY_STATE::PRESSED == m_vecKey[i].state)
			{
				m_vecKey[i].state = KEY_STATE::RELEASED;
			}
			else if(KEY_STATE::RELEASED == m_vecKey[i].state)
			{
				m_vecKey[i].state = KEY_STATE::NONE;
			}

		}
	}

	POINT ptMousePos = {};
	GetCursorPos(&ptMousePos);

	ScreenToClient(CEngine::GetInst()->GethMainWnd(), &ptMousePos);

	m_vMousePos = ptMousePos;




	
}
