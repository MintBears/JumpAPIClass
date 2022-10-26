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
    virtual void Enter() override;           //������ �����Ҷ� ȣ��
    virtual void Exit() override;            //������ ����� ȣ��

private:
    void Update();
    void tile_update();
    void animation_update();
    void object_update();
    void CreateUI();

public:
    void SaveTile();
    void LoadTile();
};

