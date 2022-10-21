#pragma once
#include "CObj.h"
class CTile :
    public CObj
{
public:
    CTile();
    ~CTile();

private:
    CTexture*   m_pAtlas;
    int         m_iImgIdx;

public:
    void SetAltas(CTexture* _pAtlas) { m_pAtlas = _pAtlas; }

public:
    virtual void tick();
    //virtual void final_tick() final;
    virtual void render(HDC _dc);

    
    CLONE(CTile)

    void SetImgIdx(int _imgidx);
    void AddImgIdx();

    void Save(FILE* _pFile);
    void Load(FILE* _pFile);
};

