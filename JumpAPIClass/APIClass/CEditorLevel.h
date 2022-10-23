#pragma once
#include "CLevel.h"

enum class EDITOR_MODE
{
    TILE,
    ANINATION,
    OBJECT,

    NONE,
};
class CEditorLevel :
    public CLevel
{
public:
    CEditorLevel();
    ~CEditorLevel();

private:
    HMENU           m_hMenu;

    EDITOR_MODE     m_eMode;

public:
    virtual void init() override;
    virtual void tick() override;

    virtual void Enter();           //레벨에 진입할때 호출
    virtual void Exit();            //레벨을 벗어날때 호출

private:
    void Update();
    void tile_update();
    void animation_update();
    void object_update();

public:
    void SaveTile();
    void LoadTile();
};

