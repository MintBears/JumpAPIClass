#include "pch.h"
#include "CEditorLevel.h"

#include "resource.h"


#include "CEngine.h"
#include "CResMgr.h"
#include "CLevelMgr.h"
#include "CTexture.h"
#include "CCamera.h"
#include "CKeyMgr.h"
#include "CPathMgr.h"

#include "CTile.h"
#include "CUI.h"
#include "CButton.h"

CEditorLevel::CEditorLevel()
	: m_hMenu(nullptr)
	, m_eMode(EDITOR_MODE::TILE)
{
}

CEditorLevel::~CEditorLevel()
{
	if (nullptr != m_hMenu)
	{
		DestroyMenu(m_hMenu);
	}
}

void CEditorLevel::tick()
{
	CLevel::tick();

	if (IsTap(KEY::ENTER))
	{
		ChangeLevel(LEVEL_TYPE::START);
	}

	if (IsTap(KEY::_1))
		m_eMode = EDITOR_MODE::TILE;
	if (IsTap(KEY::_2))
		m_eMode = EDITOR_MODE::ANINATION;
	if (IsTap(KEY::_3))
		m_eMode = EDITOR_MODE::OBJECT;
	if (IsTap(KEY::_0))
		m_eMode = EDITOR_MODE::NONE;


	Update();

}

void CEditorLevel::Enter()
{
	if (nullptr == m_hMenu)
	{
		m_hMenu = LoadMenu(nullptr, MAKEINTRESOURCEW(IDC_APICLASS));
	}

	HWND hWnd = CEngine::GetInst()->GethMainWnd();
	SetMenu(hWnd, m_hMenu);

	POINT ptResolution = CEngine::GetInst()->GetResolution();
	CEngine::GetInst()->ChangeWindowSize(ptResolution.x, ptResolution.y);

	init();
}

void CEditorLevel::Exit()
{
	HWND hWnd = CEngine::GetInst()->GethMainWnd();
	SetMenu(hWnd, nullptr);

	POINT ptResolution = CEngine::GetInst()->GetResolution();
	CEngine::GetInst()->ChangeWindowSize(ptResolution.x, ptResolution.y);
}

void CEditorLevel::Update()
{
	switch (m_eMode)
	{
	case EDITOR_MODE::TILE:
	{
		tile_update();
	}
		break;
	case EDITOR_MODE::ANINATION:
	{
		animation_update();
	}
		break;
	case EDITOR_MODE::OBJECT:
	{
		object_update();
	}
		break;
	case EDITOR_MODE::NONE:
		break;
	default:
		break;
	}

}

void CEditorLevel::tile_update()
{
	//마우스 위치를 받아와서 실제좌표로 변환
	if (IsTap(KEY::LBTN))
	{
		Vec2 vMousePos = CCamera::GetInst()->GetRealPos(MOUSE_POS);

		int iCol = (int)vMousePos.x / TILE_SIZE;
		int iRow = (int)vMousePos.y / TILE_SIZE;

		if (0.f <= vMousePos.x && iCol < GetTileXCount()
			&& 0.f <= vMousePos.y && iRow < GetTileYCount())
		{
			int iIdx = iRow * GetTileXCount() + iCol;
			const vector<CObj*>& vecTile = GetLayer(LAYER::TILE);
			((CTile*)vecTile[iIdx])->AddImgIdx();
		}
	}
	if (IsTap(KEY::LCTRL))
	{
		SaveTile();
	}
	else if (IsTap(KEY::LALT))
	{
		LoadTile();
	}
}

void CEditorLevel::animation_update()
{
}

void CEditorLevel::object_update()
{
}

void CEditorLevel::SaveTile()
{
	// 탐색기 창 만들기(모덜방식)
	OPENFILENAME ofn = {};

	wstring strTileFolderPath = CPathMgr::GetInst()->GetContentPath();
	strTileFolderPath += L"tile\\";

	wchar_t szFilePath[256] = {};

	ZeroMemory(&ofn, sizeof(ofn));								//
	ofn.lStructSize = sizeof(ofn);								//
	ofn.hwndOwner = NULL;										//
	ofn.lpstrFile = szFilePath;									//
	ofn.lpstrFile[0] = '\0';									//
	ofn.nMaxFile = 256;											//
	ofn.lpstrFilter = L"Tile\0*.tile\0ALL\0*.*";				//파일 검색 필터링
	ofn.nFilterIndex = 1;										//어떤 필터를 적용할지
	ofn.lpstrFileTitle = NULL;									//
	ofn.nMaxFileTitle = 0;										//
	ofn.lpstrInitialDir = strTileFolderPath.c_str();			//nullptr이면 윈도우 기준 가장 최근에 열었던 것, 주소가있으면 해당 주소로 열린다.
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;			//

	//이걸 사용하기 위한 사전 작업들
	if (false == GetSaveFileName(&ofn))
		return;

	//위에는 어디다가 저장할지 주소와 이름 을 처리하는곳
	//-----------------------------------------------
	//저장이 실행 하는곳은 이 밑에

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, szFilePath, L"wb");

	UINT iTileXCount = GetTileXCount();
	UINT iTileYCount = GetTileYCount();

	fwrite(&iTileXCount, sizeof(UINT), 1, pFile);
	fwrite(&iTileYCount, sizeof(UINT), 1, pFile);


	const vector<CObj*>& vecTile = GetLayer(LAYER::TILE);
	for (size_t i = 0; i < vecTile.size(); i++)
	{
		((CTile*)vecTile[i])->Save(pFile);
	}


	fclose(pFile);
}

void CEditorLevel::LoadTile()
{
	OPENFILENAME ofn = {};

	wstring strTileFolderPath = CPathMgr::GetInst()->GetContentPath();
	strTileFolderPath += L"tile\\";

	wchar_t szFilePath[256] = {};

	ZeroMemory(&ofn, sizeof(ofn));								//
	ofn.lStructSize = sizeof(ofn);								//
	ofn.hwndOwner = NULL;										//
	ofn.lpstrFile = szFilePath;									//
	ofn.lpstrFile[0] = '\0';									//
	ofn.nMaxFile = 256;											//
	ofn.lpstrFilter = L"Tile\0*.tile\0ALL\0*.*";				//파일 검색 필터링
	ofn.nFilterIndex = 1;										//어떤 필터를 적용할지
	ofn.lpstrFileTitle = NULL;									//
	ofn.nMaxFileTitle = 0;										//
	ofn.lpstrInitialDir = strTileFolderPath.c_str();			//nullptr이면 윈도우 기준 가장 최근에 열었던 것, 주소가있으면 해당 주소로 열린다.
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;			//

	//이걸 사용하기 위한 사전 작업들
	if (false == GetOpenFileName(&ofn))
		return;

	//-----------------------------------------------

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, szFilePath, L"rb");

	UINT iTileXCount = 0;
	UINT iTileYCount = 0;

	fread(&iTileXCount, sizeof(UINT), 1, pFile);
	fread(&iTileYCount, sizeof(UINT), 1, pFile);

	CreateTile(iTileXCount, iTileYCount);

	const vector<CObj*>& vecTile = GetLayer(LAYER::TILE);
	for (size_t i = 0; i < vecTile.size(); i++)
	{
		((CTile*)vecTile[i])->Load(pFile);
	}

	fclose(pFile);
}


//=======================================

INT_PTR CALLBACK TileCount(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK)
        {
			int iTileXCount = GetDlgItemInt(hDlg, IDC_EDIT1, nullptr, true);
			int iTileYCount = GetDlgItemInt(hDlg, IDC_EDIT2, nullptr, true);

			if (!(iTileXCount && iTileYCount))
			{
				MessageBox(nullptr, L"타일개수를 지정하세요", L"타일 생성 오류", MB_OK);
				return (INT_PTR)TRUE;
			}
			//지정된 수치로 타일 새로생성
			CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();
			pCurLevel->CreateTile(iTileXCount, iTileYCount);
			//이미지 로드
			CTexture* pTex = CResMgr::GetInst()->LoadTexture(L"TileAtlas", L"texture\\TILE.bmp");
			//하나하나 출력
			const vector<CObj*>& vecTIle = pCurLevel->GetLayer(LAYER::TILE);
			for (size_t i = 0; i < vecTIle.size(); i++)
			{
				((CTile*)vecTIle[i])->SetAltas(pTex);
				((CTile*)vecTIle[i])->SetImgIdx((int)1);
			}

            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
		else if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
        break;
    }
    return (INT_PTR)FALSE;
}