#include "pch.h"
#include "CUIMgr.h"

#include "CLevelMgr.h"
#include "CKeyMgr.h"

#include "CLevel.h"
#include "CUI.h"

CUIMgr::CUIMgr()
{
}

CUIMgr::~CUIMgr()
{
}

void CUIMgr::tick()
{
	bool bLbtnPressed = IsTap(KEY::LBTN);
	bool bLbtnReleased = IsRelease(KEY::LBTN);

	//현제 레벨 접근
	//UI Layer 가져오기
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();
	const vector<CObj*>& vecUI = pCurLevel->GetLayer(LAYER::UI);

	for (size_t i = 0; i < vecUI.size(); i++)
	{
		CUI* pUI = (CUI*)vecUI[i];
		if (pUI->IsMouseOn())
		{
			pUI->MouseOn();
			if (bLbtnPressed)
			{
				pUI->MouseLbtnDown();
			}
			else if (bLbtnReleased)
			{
				if (pUI->m_bLbtnDown)
				{
					pUI->MouseLbtnClicked();
				}
			}
		}
		
		if (bLbtnReleased)
		{
			pUI->m_bLbtnDown = false;
		}
	}
}
