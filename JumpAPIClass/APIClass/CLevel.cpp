#include "pch.h"
#include "CLevel.h"
#include "CObj.h"

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

	for (UINT i = 0; i < (UINT)LAYER::END; i++)
	{
		for (size_t j = 0; j < m_arrLayer[i].size(); j++)
		{
			m_arrLayer[i][j]->tick();
		}
	}
}

void CLevel::final_tick()
{
	for (UINT i = 0; i < (UINT)LAYER::END; i++)
	{
		for (size_t j = 0; j < m_arrLayer[i].size(); j++)
		{
			m_arrLayer[i][j]->final_tick();
		}
	}
}

void CLevel::render(HDC _dc)
{

	for (UINT i = 0; i < (UINT)LAYER::END; i++)
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

		//�����Ҵ� ������Ų �ּҰ����� ���ͳ����� �������
		m_arrLayer[i].clear();
	}
	//������Ʈ ���� 
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
	//���� Ÿ�� ����
	DeleteObject(LAYER::TILE);

	m_iTileXCount = _x;
	m_iTileYCount = _y;

	//���� ���� ���ڿ� ���߾� Ÿ�� ��ġ
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


