#pragma once

class CTexture;
class CEngine
{
	SINGLE(CEngine);

private:
	HWND	m_hMainWnd;
	HDC		m_hDC;

	CTexture* m_pMemTex;

	POINT	m_Resolution;
	HPEN	m_arrPen[(UINT)PEN_TYPE::END];

public : 
	HWND GethMainWnd() { return m_hMainWnd; }
	HDC	GetMainDC() { return m_hDC; }
	POINT GetResolution() { return m_Resolution; }
	HPEN GetPen(PEN_TYPE _type) { return m_arrPen[(UINT)_type]; }

public:
	void Inst(HWND _hwnd, UINT _iWidth, UINT _iHeight);
	void progress();


private:
	void tick();
	void render();
	void CreatPenBrush();

};