#pragma once
#include "CObj.h"
class CPlatform :
    public CObj
{
public:
    CPlatform();
    ~CPlatform();

public:

    CLONE(CPlatform)

    virtual void BeginOverlap(CCollider* _Other) override;
    virtual void OnOverlap(CCollider* _Other) override;
    virtual void EndOverlap(CCollider* _Other) override;
private:

};

