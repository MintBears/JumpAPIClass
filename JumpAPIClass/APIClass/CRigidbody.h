#pragma once
#include "CComponent.h"
class CRigidbody :
    public CComponent
{
public:
    CRigidbody(CObj* _pOwner);
    ~CRigidbody();

private:

    Vec2            m_vVelocity;        //�ӵ�
    Vec2            m_vForce;           //��
    float           m_fMass;            //����

    float           m_fFriction;        //������
    float           m_fFrictionScale;   //�������

    float           m_fVelocityLimit;   //���Ѽӵ�


public:
    void AddForce(Vec2 _vForce) { m_vForce += _vForce; }
    void SetVelocityLimit(float _fLimit) { m_fVelocityLimit = _fLimit; }
    void SetVelocity(Vec2 _vVelocity) { m_vVelocity = _vVelocity; }
    Vec2 GetVelocity() { return m_vVelocity; }
    void SetFriction(float _fFriction) { m_fFriction = _fFriction; }
    void SetFrictionScale(float _fFrictionScale) { m_fFrictionScale = _fFrictionScale; }


public:
    virtual void tick() override;
    virtual void final_tick() override;
    virtual void render(HDC _dc) override;
    

};

