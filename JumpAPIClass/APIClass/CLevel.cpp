#include "pch.h"
#include "CLevel.h"
#include "CObj.h"

#include "CEngine.h"

#include "CTile.h"

CLevel::CLevel()
	: m_iTileXCount(0)
	, m_iTileYCount(0)
{
}

CLevel::~CLevel()
{
	DeleteAllobject();
}

void CLevel::tick()
{
	FindTileScreen();


	for (UINT i = 0; i < (UINT)LAYER::END; i++)
	{
		if (i == (UINT)LAYER::TILE)
		{
			
			for (size_t j = 0; j < m_vecTile.size(); j++)
			{
				m_vecTile[j]->tick();
			}

		}
		else
		{
			for (size_t j = 0; j < m_arrLayer[i].size(); j++)
			{
				m_arrLayer[i][j]->tick();
			}
		}

	}
}

void CLevel::final_tick()
{
	for (UINT i = 0; i < (UINT)LAYER::END; i++)
	{
		if (i == (UINT)LAYER::TILE)
		{
			for (size_t j = 0; j < m_vecTile.size(); j++)
			{
				m_vecTile[j]->final_tick();
			}
		}
		else
		{
			for (size_t j = 0; j < m_arrLayer[i].size(); j++)
			{
				m_arrLayer[i][j]->final_tick();
			}
		}
	}
}

void CLevel::render(HDC _dc)
{

	for (UINT i = 0; i < (UINT)LAYER::END; i++)
	{
		if (i == (UINT)LAYER::TILE)
		{

			for (size_t j = 0; j < m_vecTile.size(); j++)
			{
				m_vecTile[j]->render(_dc);
			}

		}
		else
		{
			vector<CObj*>::iterator iter = m_arrLayer[i].begin();

			for (; iter != m_arrLayer[i].end();)
			{
				if ((*iter)->IsDead())
				{
					iter = m_arrLayer[i].erase(iter);
				}
				else
				{
					(*iter)->render(_dc);
					++iter;
				}
			}
		}
	}
}

void CLevel::SetFocusedUI(CObj* _pUI)
{
	vector<CObj*>& vecUI = m_arrLayer[(UINT)LAYER::UI];

	if (vecUI.back() == _pUI)
		return;

	vector<CObj*>::iterator iter = vecUI.begin();
	for (; iter != vecUI.end(); ++iter)
	{
		if ((*iter) == _pUI)
		{
			vecUI.erase(iter);
			vecUI.push_back(_pUI);
			return;
		}
	}

	// Focued 처리할 UI 가 레벨에 없었다?!?!?!?
	assert(nullptr);
}

void CLevel::DeleteAllobject()
{
	for (UINT i = 0; i < (UINT)LAYER::END; i++)
	{
		for (size_t j = 0; j < m_arrLayer[i].size(); j++)
		{
			if (m_arrLayer[i][j]->IsDead())
				continue;

			DEL(m_arrLayer[i][j]);
		}

		//동적할당 해제시킨 주소값들은 백터내에서 비워내기
		m_arrLayer[i].clear();
	}
	//오브젝트 삭제 
}

void CLevel::DeleteObject(LAYER _eLayer)
{
	for (size_t i = 0; i < m_arrLayer[(UINT)_eLayer].size(); i++)
	{
		delete m_arrLayer[(UINT)_eLayer][i];
	}
	m_arrLayer[(UINT)_eLayer].clear();
}

void CLevel::CreateTile(UINT _x, UINT _y)
{
	//기존 타일 제거
	DeleteObject(LAYER::TILE);

	m_iTileXCount = _x;
	m_iTileYCount = _y;

	//가로 세로 숫자에 맞추어 타일 배치
	for (UINT iRow = 0; iRow < m_iTileYCount; iRow++)
	{
		for (UINT iCol = 0; iCol < m_iTileXCount; iCol++)
		{
			CTile* pTile = new CTile;
			pTile->SetPos(Vec2((float)(TILE_SIZE * iCol), (float)(TILE_SIZE * iRow)));
			AddObject(pTile, LAYER::TILE);
		}
	}

}

void CLevel::FindTileScreen()
{
	m_vecTile.clear();



	//좌상단 구함
	Vec2 vLeftTop = CCamera::GetInst()->GetLoot();
	Vec2 vResolution = CEngine::GetInst()->GetResolution();
	vLeftTop -= vResolution / 2.f;

	int iLTCol = (int)vLeftTop.x / TILE_SIZE;						//몇번째 타일 부터 화면에 나오는가
	int iLTRaw = (int)vLeftTop.y / TILE_SIZE;
	if (vLeftTop.x <0.f)											//보정
		iLTCol = 0;
	if (vLeftTop.y < 0.f)
		iLTRaw = 0;


	int iMaxCol = (int)vResolution.x / TILE_SIZE + iLTCol + 1;		//한화면에 표현할수 있는 타일 개수
	int iMaxRaw = (int)vResolution.y / TILE_SIZE + iLTRaw + 1;
	if (m_iTileXCount < iMaxCol)									//보정
		iMaxCol = m_iTileXCount;
	if (m_iTileYCount < iMaxRaw)
		iMaxRaw = m_iTileYCount;

	for (int iRaw = iLTRaw; iRaw < iMaxRaw; iRaw++)
	{
		for (int iCol = iLTCol; iCol < iMaxCol; iCol++)
		{
			int iTileIdx = iRaw * m_iTileXCount + iCol;
			m_vecTile.push_back(m_arrLayer[(UINT)LAYER::TILE][iTileIdx]);
		}
	}
}




