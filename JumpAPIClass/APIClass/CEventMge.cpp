#include "pch.h"
#include "CEventMge.h"

#include "CLevelMgr.h"
#include "CLevel.h"
#include "CObj.h"

CEventMge::CEventMge()
{
}

CEventMge::~CEventMge()
{
}

void CEventMge::tick()
{
	for (size_t i = 0; i < m_Garbage.size(); i++)
	{
		delete m_Garbage[i];
	}
	m_Garbage.clear();




	for (size_t i = 0; i < m_Event.size(); i++)
	{
		switch (m_Event[i].eType)
		{
			//wParam : Object Adress		
			//lParam : Layer type
		case EVENT_TYPE::CREATE_OBJECT:
		{
			CLevel* CurLevel = CLevelMgr::GetInst()->GetCurLevel();
			CObj* NewObj = (CObj*)m_Event[i].wParam;
			LAYER Layer = (LAYER)m_Event[i].lParam;

			//Level�� ������Ʈ�� �߰��ҋ� �ʿ��� �ΰ��� ���, �ϳ��� CObj*Ÿ�԰� LAYERŸ��, �� �ΰ��� Ÿ���� �⿪����
			CurLevel->AddObject(NewObj, Layer);
		}
		break;
		case EVENT_TYPE::DELETE_OBJECT:
			//�����ҋ� �� �ܰ�� �����Ѵ�.
			//1. ���� ��ŵ� ����̶��� ���� ��Ų��.
			//2. ���� ���� ��Ų�� ��� �������踦 �� ó���Ѵ����� �������� ���Ÿ� �����Ѵ�.
		{
			CObj* Obj = (CObj*)m_Event[i].wParam;
			if (false == Obj->m_Dead)
			{
				m_Garbage.push_back(Obj);
				Obj->m_Dead = true;
			}
		}
			break;
		case EVENT_TYPE::LEVEL_CHANGE:
			break;
		default:
			break;
		}
		
	}
	//�̺�Ʈ������ ��� ó�����ְ� �Ѱ��ִ� �������� ���⼭ ������ �ؼ� ó���ϴ°��� �ƴϴ�.
	m_Event.clear();
}

