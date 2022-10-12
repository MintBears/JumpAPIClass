#include "pch.h"
#include "CTexture.h"
#include "CEngine.h"

CTexture::CTexture()
	: m_hBit(nullptr)
	, m_hDC(nullptr)
	, m_BitmapInfo{}
{
}

CTexture::~CTexture()
{
	DeleteObject(m_hBit);
	DeleteDC(m_hDC);
}

int CTexture::Load(const wstring& _strFilePath)
{
	//bitmap 로딩
	m_hBit = (HBITMAP)LoadImage(nullptr, _strFilePath.c_str(), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	GetObject(m_hBit, sizeof(BITMAP), &m_BitmapInfo);
	//bitmap 과 연결 시킬 dc 생성


	m_hDC = CreateCompatibleDC(CEngine::GetInst(	)->GetMainDC());
	//새로운 dc와 bit를 연결 시켜준다.
	HBITMAP hPrevBit = (HBITMAP)SelectObject(m_hDC, m_hBit);
	//dc를 만들면서 초기에 가르키던 bit를 지워줘야된다.
	DeleteObject(hPrevBit);

	return S_OK;
}

void CTexture::Create(UINT _iWidth, UINT _iHeight)
{
	//별도의 비트맵을 윈도우와 동일한 해상도로 생성.

	
	
	m_hBit = CreateCompatibleBitmap(CEngine::GetInst()->GetMainDC(), _iWidth, _iHeight);
	//새로운 dc 생성 , m_hDC를 받는이유 => 기존에 사용하던 기본 정보들을 가지고 새로운 dc를 만들기위해
	m_hDC = CreateCompatibleDC(CEngine::GetInst()->GetMainDC());
	//새로운 dc와 bit를 연결 시켜준다.
	HBITMAP hPrevBit = (HBITMAP)SelectObject(m_hDC, m_hBit);
	//dc를 만들면서 초기에 가르키던 bit를 지워줘야된다.
	DeleteObject(hPrevBit);


	GetObject(m_hBit, sizeof(BITMAP), &m_BitmapInfo);
}
