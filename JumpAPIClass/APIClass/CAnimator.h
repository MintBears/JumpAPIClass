#pragma once
#include "CComponent.h"

class CAnimation;
class CTexture;

class CAnimator :
    public CComponent
{
public:
    CAnimator(CObj* _Owner);
    CAnimator(const CAnimator& _other);
    virtual ~CAnimator();

private:

    map<wstring, CAnimation*>       m_mapAnim;
    CAnimation*                     m_pCurAnim;
    bool                            m_bRepeat;


public:
    virtual void tick() override;
    virtual void final_tick() override;
    virtual void render(HDC _dc) override;

    CLONE(CAnimator)

public:
    void CreateAnimation(const wstring& _strName, CTexture* _pAtlas, Vec2 _vLeftTop, Vec2 _vSize, Vec2 _vOffset, int _iMaxFrmCount, float _fDuration);
    CAnimation* FindAnimation(const wstring& _strName);
    CAnimation* LoadAnimation(const wstring& _strRelativePath);
    void Play(const wstring& _strName, bool _bRepeat);

};

