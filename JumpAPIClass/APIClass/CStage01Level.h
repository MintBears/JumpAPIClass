#pragma once
#include "CLevel.h"
class CStage01Level :
    public CLevel
{
public: 
    CStage01Level();
    ~CStage01Level();

public : 
    virtual void init() override;
    virtual void tick() override;

    virtual void Enter();           //������ �����Ҷ� ȣ��
    virtual void Exit();            //������ ����� ȣ��
};

