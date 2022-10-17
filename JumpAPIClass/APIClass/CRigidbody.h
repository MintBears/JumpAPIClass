#pragma once
#include "CComponent.h"
class CRigidbody :
    public CComponent
{
public:
    CRigidbody(CObj* _pOwner);
    CRigidbody(const CRigidbody& _other);
    ~CRigidbody();

private:

    Vec2            m_vVelocity;        //속도
    Vec2            m_vForce;           //힘
    float           m_fMass;            //질량

    float           m_fFriction;        //마찰력
    float           m_fFrictionScale;   //마찰계수

    float           m_fVelocityLimit;   //제한속도

    //중력 관련
    bool            m_bGravityUse;      //중력여부
    bool            m_bGround;          //땅체크
    float           m_fGravityAccel;    //중력 가속도
    float           m_fGravityVLimit;   //중력에 의한 제한속도


public:
    void AddForce(Vec2 _vForce) { m_vForce += _vForce; }
    void SetVelocityLimit(float _fLimit) { m_fVelocityLimit = _fLimit; }
    void SetGravityVelocityLimit(float _fLimit) { m_fGravityVLimit = _fLimit; }

    void SetVelocity(Vec2 _vVelocity) { m_vVelocity = _vVelocity; }
    Vec2 GetVelocity() { return m_vVelocity; }

    void AddVelocity(Vec2 _vAddV) { m_vVelocity += _vAddV; }

    void SetFriction(float _fFriction) { m_fFriction = _fFriction; }
    void SetFrictionScale(float _fFrictionScale) { m_fFrictionScale = _fFrictionScale; }
    void SetGravity(bool _bSet) { m_bGravityUse = _bSet; }
    void SetGravityAccel(float _fAccel) { m_fGravityAccel = _fAccel; }



public:
    virtual void tick() override;
    virtual void final_tick() override;
    virtual void render(HDC _dc) override;

    CLONE(CRigidbody)
    
public:
    void SetGround(bool _bGround);
};

