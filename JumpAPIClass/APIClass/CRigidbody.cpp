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


	// f = m * a (���ӵ� ���ϱ�)
	//���� ������ ���� ���� ���̴�.
	Vec2 vAccel = m_vForce / m_fMass;

	//v = f * t (�ӵ� ���ϱ�)
	//������ �ӵ��� ���Ѵ�.
	m_vVelocity += vAccel * DT;

	

	//�߷��� ����ϴ� ����, ���� �־�߸����� ����, �߷��� ���� ������ ������ �ٷ� ����
	if (m_bGravityUse && m_bGround || !m_bGravityUse)
	{
		//������
		//���� ���ӵ�
		Vec2 vFriction = -m_vVelocity;
		if (!vFriction.IsZero())
		{
			vFriction.Normalize();
			vFriction *= (m_fFriction * m_fFrictionScale * m_fMass * DT);
		}

		//�ӵ� ���ҷ�
		if (m_vVelocity.Length() < vFriction.Length())
		{
			m_vVelocity = Vec2(0.f, 0.f);
		}
		else
		{
			m_vVelocity += vFriction;
		}

	}
	//���߻���
	if (m_bGravityUse && !m_bGround)
	{
		Vec2 vGravityAccel = Vec2(0.f, m_fGravityAccel);
		m_vVelocity += vGravityAccel * DT;
	}

	//�ִ�ӵ�����
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
			//����ȭ�� �̿��� �ִ�ӵ���ŭ �ӵ��������Ѵ�.
			m_vVelocity.Normalize();
			m_vVelocity *= m_fVelocityLimit;
		}
	}
	

	//������Ʈ�� ��ġ
	Vec2 vPos = GetOwner()->GetPos();
	//s = v * t(�Ÿ� ���ϱ�/ �ӷ� ���ϱ�)
	vPos.x += m_vVelocity.x * DT;
	vPos.y += m_vVelocity.y * DT;

	GetOwner()->SetPos(vPos);

	//�� ����
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
