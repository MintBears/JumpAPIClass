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

public:
    void AddObject(CObj* _obj, LAYER _layer) { m_arrLayer[(UINT)_layer].push_back(_obj); }
    const vector<CObj*>& GetLayer(LAYER _layer) { return m_arrLayer[(UINT)_layer]; }

};

