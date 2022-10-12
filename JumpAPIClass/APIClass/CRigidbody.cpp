#include "pch.h"
#include "CRigidbody.h"

#include "CTimeMgr.h"
#include "CObj.h"

CRigidbody::CRigidbody(CObj* _pOwner)
	: CComponent(_pOwner)
	, m_fMass(1.0f)
	, m_fVelocityLimit(10000.f)
	, m_fFriction(100.f)
	, m_fFrictionScale(1.f)
{
}

CRigidbody::~CRigidbody()
{
}

void CRigidbody::tick()
{
	
}

void CRigidbody::final_tick()
{


	// f = m * a (가속도 구하기)
	//여기 들어오는 힘이 최종 힘이다.
	Vec2 vAccel = m_vForce / m_fMass;

	//v = f * t (속도 구하기)
	//누적된 속도를 구한다.
	m_vVelocity += vAccel * DT;

	//최대속도제한
	if (m_fVelocityLimit < m_vVelocity.Length())
	{
		//정규화를 이용해 최대속도만큼 속도를유지한다.
		m_vVelocity.Normalize();
		m_vVelocity *= m_fVelocityLimit;
	}

	//마찰력
	//마찰 가속도
	Vec2 vFriction = -m_vVelocity;
	if (!vFriction.IsZero())
	{
		vFriction.Normalize();
		vFriction *= (m_fFriction * m_fFrictionScale * m_fMass * DT);
	}

	if (m_vVelocity.Length() < vFriction.Length())
	{
		m_vVelocity = Vec2(0.f, 0.f);
	}
	else 
	{
		m_vVelocity += vFriction;
	}

	//오브젝트의 위치
	Vec2 vPos = GetOwner()->GetPos();
	//s = v * t(거리 구하기/ 속력 구하기)
	vPos.x += m_vVelocity.x * DT;
	vPos.y += m_vVelocity.y * DT;

	GetOwner()->SetPos(vPos);

	//힘 리셋
	m_vForce = Vec2(0.f, 0.f);
}

void CRigidbody::render(HDC _dc)
{
}
