#pragma once
#include "CLevel.h"
class CEditorLevel :
    public CLevel
{
public:
    CEditorLevel();
    ~CEditorLevel();

public:
    virtual void init() override;
    virtual void tick() override;

    virtual void Enter();           //������ �����Ҷ� ȣ��
    virtual void Exit();            //������ ����� ȣ��
};

