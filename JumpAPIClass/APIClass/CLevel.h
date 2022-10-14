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

public:
    virtual void init() = 0;
    virtual void tick();
    virtual void final_tick();
    virtual void render(HDC _dc); 

    virtual void Enter() = 0;           //레벨에 진입할때 호출
    virtual void Exit() = 0;            //레벨을 벗어날때 호출

public:
    void AddObject(CObj* _obj, LAYER _layer) { m_arrLayer[(UINT)_layer].push_back(_obj); }
    const vector<CObj*>& GetLayer(LAYER _layer) { return m_arrLayer[(UINT)_layer]; }

    void DeleteAllobject();

};

