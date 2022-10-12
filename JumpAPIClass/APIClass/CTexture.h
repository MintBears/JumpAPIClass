#pragma once
#include "CRes.h"
class CTexture :
    public CRes
{
public:
    CTexture();
    virtual ~CTexture();

private:
    HBITMAP         m_hBit;
    HDC             m_hDC;

    BITMAP          m_BitmapInfo;

public:

    UINT Widht() { return m_BitmapInfo.bmWidth; }
    UINT Height() { return m_BitmapInfo.bmHeight; }

    HDC GetDC() { return m_hDC; }


private:
    virtual int Load(const wstring& _strFilePath) override;
    void Create(UINT _iWidth, UINT _iHeight);

    friend class CResMgr;

};

