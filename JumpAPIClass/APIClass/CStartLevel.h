#pragma once
#include "CLevel.h"
class CStartLevel :
    public CLevel
{
public:
    CStartLevel();
    ~CStartLevel();

public:
    virtual void init() override;
    virtual void tick() override;

    virtual void Enter();           //������ �����Ҷ� ȣ��
    virtual void Exit();            //������ ����� ȣ��
};

