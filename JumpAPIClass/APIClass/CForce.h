#pragma once
#include "CObj.h"
class CForce :
    public CObj
{

public:
    CForce();
    ~CForce();

private:

    float           m_fAccTime;
    float           m_fLifeTime;
    float           m_fForce;           //ÈûÀÇ Å©±â
    float           m_fRadius;          //ÈûÀÇ ¹ÝÁö¸§

public:
    void SetLifeTime(float _FLifeTime) { m_fLifeTime = _FLifeTime; }
    void SetForceScale(float _fScale) { m_fForce = _fScale; }
    void SetForceRadius(float _fRadius) { m_fRadius = _fRadius; }

public:
    void tick();
    void render(HDC _dc);

private:
};

