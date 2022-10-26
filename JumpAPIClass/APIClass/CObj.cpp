#include "pch.h"
#include "CObj.h"

#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CEventMge.h"

#include "CComponent.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CRigidbody.h"
#include "CAI.h"

CObj::CObj()
	: m_vPos()
	, m_vScale()
	, m_Collider(nullptr)
	, m_Animator(nullptr)
	, m_Rigidbody(nullptr)
	, m_pAI(nullptr)
	, m_Dead(false)
{
}

CObj::CObj(const CObj& _other)
	: CEntity(_other)
	, m_vPos(_other.m_vPos)
	, m_vScale(_other.m_vScale)
	, m_Collider(nullptr)
	, m_Animator(nullptr)
	, m_Rigidbody(nullptr)
	, m_pAI(nullptr)
	, m_Dead(false)						//강제 세팅을 해야된다.
{
	//깊은 복사
	if (_other.m_Collider != nullptr)
	{
		m_Collider = _other.m_Collider->Clone();
		m_Collider->SetOwner(this);

	}
	if (_other.m_Animator != nullptr)
	{
		m_Animator = _other.m_Animator->Clone();
		m_Animator->SetOwner(this);
	}
	if (_other.m_Rigidbody != nullptr)
	{
		m_Rigidbody = _other.m_Rigidbody->Clone();
		m_Rigidbody->SetOwner(this);
	}
	if (_other.m_pAI != nullptr)
	{
		m_pAI = _other.m_pAI->Clone();
		m_pAI->SetOwner(this);
	}

}

CObj::~CObj()
{
	DEL(m_Collider);
	DEL(m_Animator);
	DEL(m_Rigidbody);
	DEL(m_pAI);
}



void CObj::tick()
{
	if (nullptr != m_Collider)
	{
		m_Collider->tick();
	}
	if (nullptr != m_Animator)
	{
		m_Animator->tick();
	}
	if (nullptr != m_pAI)
	{
		m_pAI->tick();
	}
	if (nullptr != m_Rigidbody)
	{
		m_Rigidbody->tick();
	}
	
}

void CObj::final_tick()
{
	if (nullptr != m_Rigidbody)
	{
		m_Rigidbody->final_tick();
	}
	if (nullptr != m_Animator)
	{
		m_Animator->final_tick();
	}
	if (nullptr != m_pAI)
	{
		m_pAI->final_tick();
	}
	if (nullptr != m_Collider)
	{
		m_Collider->final_tick();
	}
}

void CObj::render(HDC _dc)
{
	if (nullptr != m_Collider)
	{
		m_Collider->render(_dc);
	}
	if (nullptr != m_Animator)
	{
		m_Animator->render(_dc);
	}
}

void CObj::SetDead()
{
	tEvent _evn = {};
	_evn.eType = EVENT_TYPE::DELETE_OBJECT;
	_evn.wParam = (DWORD_PTR)this;
	CEventMge::GetInst()->AddEvent(_evn);
}

void CObj::CreateCollider()
{
	m_Collider = new CCollider(this);

}

void CObj::CreateAnimator()
{
	m_Animator = new CAnimator(this);
}

void CObj::CreatRigidbody()
{
	m_Rigidbody = new CRigidbody(this);
}

void CObj::CreatAI()
{
	m_pAI = new CAI(this);
}
