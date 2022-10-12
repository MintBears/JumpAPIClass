#include "pch.h"
#include "CPathMgr.h"
#include "CEngine.h"

CPathMgr::CPathMgr()
	: m_szContentPath{}
{
}

CPathMgr::~CPathMgr()
{
}

void CPathMgr::init()
{
	GetCurrentDirectory(256, m_szContentPath);

	int iLen = (int)wcslen(m_szContentPath);

	for (int i = iLen - 1; i >= 0; i--)
	{
		if (L'\\' == m_szContentPath[i])
		{
			m_szContentPath[i] = 0;
			break;
		}
	}

	// + bin\\content
	wcscat_s(m_szContentPath, L"\\bin\\content\\");


	//여기서 상위폴더로 이동


	render();
}

void CPathMgr::render()
{
	SetWindowText(CEngine::GetInst()->GethMainWnd(), m_szContentPath);
}  
