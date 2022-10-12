#pragma once
#include "CObj.h"

class CPlayer;
class CTexture;
class CMonster :
    public CObj
{
public:
    CMonster();
    virtual ~CMonster();

private:

    UINT        m_HP;
    CObj*       m_Target;

    FLOAT       m_Speed;
    CTexture*   m_pTex;

public:

    void SetTarget(CObj* _Target)
    {
        m_Target = _Target;
    }

public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;

    virtual void BeginOverlap(CCollider* _Other) override;

public:
     
};

