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

			//Level에 오브젝트를 추가할떄 필요한 두가지 요소, 하나는 CObj*타입과 LAYER타입, 이 두가지 타입을 기역하자
			CurLevel->AddObject(NewObj, Layer);
		}
		break;
		case EVENT_TYPE::DELETE_OBJECT:
			//삭제할떄 두 단계로 진행한다.
			//1. 먼저 재거될 대상이란걸 인지 시킨다.
			//2. 그후 인지 시킨후 모든 연관관계를 다 처리한다음에 실질적인 제거를 진행한다.
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
	//이벤트에서는 잠시 처리해주고 넘겨주는 역할이지 여기서 저장을 해서 처리하는곳은 아니다.
	m_Event.clear();
}

