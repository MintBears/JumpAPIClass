#pragma once
#include "CState.h"
class CtraceState :
    public CState
{
public:
    CtraceState();
    ~CtraceState();
private:

public:
    virtual void finaltick() override;
    virtual void Enter() override;
    virtual void Exit()override;

    CLONE(CtraceState)
};

