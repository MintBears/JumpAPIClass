#pragma once
#include "CComponent.h"
class CRigidbody :
    public CComponent
{
public:
    CRigidbody(CObj* _pOwner);
    ~CRigidbody();

private:

    Vec2            m_vVelocity;        //속도
    Vec2            m_vForce;           //힘
    float           m_fMass;            //질량

    float           m_fFriction;        //마찰력
    float           m_fFrictionScale;   //마찰계수

    float           m_fVelocityLimit;   //제한속도


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

