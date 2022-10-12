#include "pch.h"
#include "CResMgr.h"
#include "CPathMgr.h"

#include "CRes.h"
#include "CTexture.h"

CResMgr::CResMgr()
{
}

CResMgr::~CResMgr()
{
	map<wstring, CTexture*>::iterator iter = m_mapTex.begin();

	for (; iter != m_mapTex.end(); iter++)
	{
		delete iter->second;
	}
}

CTexture* CResMgr::FindTexture(const wstring& _Key)
{
	map<wstring, CTexture*>::iterator iter = m_mapTex.find(_Key);

	if (iter == m_mapTex.end())
	{
		return nullptr;
	}


	return iter->second;
}

CTexture* CResMgr::LoadTexture(const wstring& _Key, const wstring& _RelativePath)
{
	CRes* Texture = FindTexture(_Key);

	if (nullptr != Texture)
	{
		return (CTexture*)Texture;
	}

	wstring FindPath = CPathMgr::GetInst()->GetContentPath();
	FindPath += _RelativePath;

	Texture = new  CTexture;
	Texture->Load(FindPath);
	Texture->SetKey(_Key);
	Texture->SetRelativePath(_RelativePath);

	m_mapTex.insert(make_pair(_Key, (CTexture*)Texture));


	return (CTexture*)Texture;
}

CTexture* CResMgr::CreatTexture(const wstring& _Key, UINT _iWidth, UINT _iHeight)
{
	CTexture* Texture = FindTexture(_Key);

	if (nullptr != Texture)
	{
		return (CTexture*)Texture;
	}

	Texture = new  CTexture;
	Texture->Create(_iWidth, _iHeight);
	Texture->SetKey(_Key);

	m_mapTex.insert(make_pair(_Key, Texture));

	return Texture;
}
