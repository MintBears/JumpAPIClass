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


	// f = m * a (���ӵ� ���ϱ�)
	//���� ������ ���� ���� ���̴�.
	Vec2 vAccel = m_vForce / m_fMass;

	//v = f * t (�ӵ� ���ϱ�)
	//������ �ӵ��� ���Ѵ�.
	m_vVelocity += vAccel * DT;

	//�ִ�ӵ�����
	if (m_fVelocityLimit < m_vVelocity.Length())
	{
		//����ȭ�� �̿��� �ִ�ӵ���ŭ �ӵ��������Ѵ�.
		m_vVelocity.Normalize();
		m_vVelocity *= m_fVelocityLimit;
	}

	//������
	//���� ���ӵ�
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
