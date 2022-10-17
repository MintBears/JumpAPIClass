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
	, m_bGravityUse(false)
	, m_bGround(false)
	, m_fGravityAccel(0.f)
	, m_fGravityVLimit(10000.f)
{
}

CRigidbody::CRigidbody(const CRigidbody& _other)
	: CComponent(_other)
	, m_vVelocity(_other.m_vVelocity)
	, m_vForce(_other.m_vForce)
	, m_fMass(_other.m_fMass)
	, m_fFriction(_other.m_fFriction)
	, m_fFrictionScale(_other.m_fFrictionScale)
	, m_fVelocityLimit(_other.m_fVelocityLimit)
	, m_bGravityUse(_other.m_bGravityUse)
	, m_bGround(false)
	, m_fGravityAccel(_other.m_fGravityAccel)
	, m_fGravityVLimit(_other.m_fGravityVLimit)
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

	

	//중력을 사용하는 경우는, 땅에 있어야마찰력 적용, 중력을 쓰지 않으면 마찰력 바로 적용
	if (m_bGravityUse && m_bGround || !m_bGravityUse)
	{
		//마찰력
		//마찰 가속도
		Vec2 vFriction = -m_vVelocity;
		if (!vFriction.IsZero())
		{
			vFriction.Normalize();
			vFriction *= (m_fFriction * m_fFrictionScale * m_fMass * DT);
		}

		//속도 감소량
		if (m_vVelocity.Length() < vFriction.Length())
		{
			m_vVelocity = Vec2(0.f, 0.f);
		}
		else
		{
			m_vVelocity += vFriction;
		}

	}
	//공중상태
	if (m_bGravityUse && !m_bGround)
	{
		Vec2 vGravityAccel = Vec2(0.f, m_fGravityAccel);
		m_vVelocity += vGravityAccel * DT;
	}

	//최대속도제한
	if (m_bGravityUse)
	{
		if (m_fVelocityLimit < fabs(m_vVelocity.x))
		{
			m_vVelocity.x = (m_vVelocity.x / fabs(m_vVelocity.x)) * m_fVelocityLimit;
		} 
		if (m_fGravityVLimit < fabs(m_vVelocity.y))
		{
			m_vVelocity.y = (m_vVelocity.y / fabs(m_vVelocity.y)) * m_fGravityVLimit;
		}
		m_vVelocity.y;
	}
	else
	{
		if (m_fVelocityLimit < m_vVelocity.Length())
		{
			//정규화를 이용해 최대속도만큼 속도를유지한다.
			m_vVelocity.Normalize();
			m_vVelocity *= m_fVelocityLimit;
		}
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

void CRigidbody::SetGround(bool _bGround)
{
	m_bGround = _bGround;
	if (m_bGround)
	{
		m_vVelocity.y = 0.f;
	}
}
