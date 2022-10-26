#pragma once
#include "CState.h"
class CIdleState :
    public CState
{
public:
    CIdleState();
    ~CIdleState();
private:

public:
    virtual void finaltick() override;
    virtual void Enter() override;
    virtual void Exit()override;

    CLONE(CIdleState)
};

