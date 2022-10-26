#include "pch.h"
#include "CEditorLevel.h"

#include "CPathMgr.h"
#include "CKeyMgr.h"
#include "CLevelMgr.h"
#include "CEngine.h"
#include "CCamera.h"
#include "CResMgr.h"
#include "CTexture.h"
#include "CTile.h"

#include "CUI.h"
#include "CPanelUI.h"
#include "CButton.h"

#include "resource.h"

void CEditorLevel::init()
{
	// ī�޶� ����
	Vec2 vResolution = CEngine::GetInst()->GetResolution();
	CCamera::GetInst()->SetLook(vResolution / 2.f);


	// UI ��ġ
	CreateUI();


	// Ÿ���� ����� ��Ʋ�� �̹��� �ε�
	CTexture* pTex = CResMgr::GetInst()->LoadTexture(L"TileAtlas", L"texture\\TILE.bmp");

	// Ÿ�� ����
	CreateTile(100, 100);

	// �� Ÿ�Ͽ��ٰ� ����� ��Ʋ�� �̹�����, �̹��� �ε����� �������ش�.
	const vector<CObj*>& vecTile = GetLayer(LAYER::TILE);
	for (size_t i = 0; i < vecTile.size(); ++i)
	{
		((CTile*)vecTile[i])->SetAltas(pTex);
		((CTile*)vecTile[i])->SetImgIdx((int)0);
	}
}


void CEditorLevel::CreateUI()
{
	Vec2 vResolution = CEngine::GetInst()->GetResolution();

	// Button �� ����� �ؽ���
	CTexture* pButtonTex = CResMgr::GetInst()->LoadTexture(L"Button", L"texture\\button.bmp");
	CTexture* pButtonPressedTex = CResMgr::GetInst()->LoadTexture(L"Button_Pressed", L"texture\\button_pressed.bmp");
	CTexture* pPanelTex = CResMgr::GetInst()->LoadTexture(L"Panel", L"texture\\OakUI.bmp");

	// Panel UI
	CPanelUI* pPanelUI = new CPanelUI;
	pPanelUI->SetIdleTex(pPanelTex);
	pPanelUI->SetPos(Vec2(vResolution.x - (pPanelTex->Widht() + 20.f), 10.f));



	// Tile Save ��ư
	CButton* pSaveTileBtn = new CButton;
	pSaveTileBtn->SetScale(Vec2(100.f, 50.f));
	Vec2 vUIPos = Vec2(10.f, 20.f);
	pSaveTileBtn->SetPos(vUIPos);
	pSaveTileBtn->SetDelegate(this, (DELEGATE)&CEditorLevel::SaveTile);
	pSaveTileBtn->SetIdleTex(pButtonTex);
	pSaveTileBtn->SetPressedTex(pButtonPressedTex);


	// Tile Load ��ư
	CButton* pLoadTileBtn = pSaveTileBtn->Clone();
	pLoadTileBtn->SetPos(Vec2(150.f, 20.f));
	pLoadTileBtn->SetDelegate(this, (DELEGATE)&CEditorLevel::LoadTile);


	// Save, Load ��ư�� Panel �� �ڽ����� �߰�
	pPanelUI->AddChildUI(pSaveTileBtn);
	pPanelUI->AddChildUI(pLoadTileBtn);

	AddObject(pPanelUI, LAYER::UI);


	CUI* pOtherPanelUI = pPanelUI->Clone();
	pOtherPanelUI->SetPos(Vec2(vResolution.x - (pPanelTex->Widht() * 2.f + 20.f), 10.f));
	AddObject(pOtherPanelUI, LAYER::UI);
}