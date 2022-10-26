#pragma once
#include "CEntity.h"

class CObj;
class CLevel :
    public CEntity
{
public:
    CLevel();
    virtual ~CLevel();

private:
    vector<CObj*>   m_arrLayer[(UINT)LAYER::END];

    vector<CObj*>   m_vecTile;                      //화면안에 들어오는 타일

    UINT            m_iTileXCount;
    UINT            m_iTileYCount;

public:
    UINT GetTileXCount() { return m_iTileXCount; }
    UINT GetTileYCount() { return m_iTileYCount; }

    void AddObject(CObj* _obj, LAYER _layer) { m_arrLayer[(UINT)_layer].push_back(_obj); }

    const vector<CObj*>& GetLayer(LAYER _layer) { return m_arrLayer[(UINT)_layer]; }

    void SetFocusedUI(CObj* _pUI);

public:
    virtual void init() = 0;
    virtual void tick();
    virtual void final_tick();
    virtual void render(HDC _dc); 

    CLONE_DEACTIVATE(CLevel)

    virtual void Enter() = 0;           //레벨에 진입할때 호출
    virtual void Exit() = 0;            //레벨을 벗어날때 호출

public:
    void DeleteAllobject();
    void DeleteObject(LAYER _eLayer);
    void CreateTile(UINT _x, UINT _y);

private:
    void FindTileScreen();
};

