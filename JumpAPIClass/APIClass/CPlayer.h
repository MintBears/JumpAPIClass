#pragma once
#include "CObj.h"


class CTexture;

class CPlayer :
    public CObj
{
public:
    CPlayer();
    virtual ~CPlayer();

private:
    FLOAT           m_fSpeed;
public:

    virtual void tick() override;
    virtual void render(HDC _dc) override;

    virtual void BeginOverlap(CCollider* _Other) override;
    virtual void OnOverlap(CCollider* _Other) override;
    virtual void EndOverlap(CCollider* _Other) override;
};

