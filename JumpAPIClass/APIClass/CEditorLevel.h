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

    virtual void Enter();           //레벨에 진입할때 호출
    virtual void Exit();            //레벨을 벗어날때 호출
};

