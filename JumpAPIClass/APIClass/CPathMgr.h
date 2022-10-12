#pragma once
class CPathMgr
{
	SINGLE(CPathMgr);

private:
	wchar_t			m_szContentPath[256];

public:
	const wchar_t* GetContentPath() { return m_szContentPath; }
public:
	void init();
	void render();


};

