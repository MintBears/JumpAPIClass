#include "pch.h"
#include "CCollisionMgr.h"

#include "CLevelMgr.h"

#include "CLevel.h"
#include "CObj.h"
#include "CCollider.h"

CCollisionMgr::CCollisionMgr():
	m_matrix{}
{
}

CCollisionMgr::~CCollisionMgr()
{
}

void CCollisionMgr::tick()
{
	//15*15만큼의 공간을 검사한다.
	for (UINT iRow = 0; iRow < (UINT)LAYER::END; iRow++)
	{
		for (UINT iCol = iRow; iCol < (UINT)LAYER::END; iCol++)
		{
			//사전에 bool값을 넣었으며 없으면 continue
			if (!(m_matrix[iRow] & (1 << iCol)))
			{
				continue;
			}
			//있으면 충돌에 할일이 생긴다.
			CollisionBtwLayer((LAYER)iRow, (LAYER)iCol);
		}
	}
}

void CCollisionMgr::LayerCheck(LAYER _left, LAYER _right)
{
	UINT iRow = (UINT)_left;
	UINT iCol = (UINT)_right;
	//5/2 와 2/5의 비교는 항상 같으므로 이러한 연산을 줄이기 위해 한 장치이다.
	if (iRow > iCol)
	{
		UINT iTemp = iCol;
		iCol = iRow;
		iRow = iTemp;
	}
	
	//비트 합치기		(1 ; 가장 왼쪽을 의미, << iCol : 왼쪽에서부터 몇칸 움직일건지)
	m_matrix[iRow] |= (1 << iCol);
	
	m_matrix;


}

void CCollisionMgr::CollisionBtwLayer(LAYER _left, LAYER _right)
{
	//여기서는 대체로 충돌전,충돌중, 충돌후의 대한 처리를 한다.
	CLevel* CorLevel = CLevelMgr::GetInst()->GetCurLevel();

	const vector<CObj*>& vecLeft = CorLevel->GetLayer(_left);
	const vector<CObj*>& vecRight = CorLevel->GetLayer(_right);

	for (size_t i = 0; i < vecLeft.size(); i++)
	{
		//비교할 물체가없는가
		if (nullptr == vecLeft[i]->GetCollider())
			continue;

		//같은 레이어가 들어왔을때, 이중검사를 피하기위해
		size_t j = 0;
		if (_left == _right)
		{
			j = i;
		}
		
		for (; j < vecRight.size(); j++)
		{
			//비교할 물체가없는가							//자기자신을 비교하는가
			if (nullptr == vecRight[j]->GetCollider() || vecLeft[i] == vecRight[j])
				continue;
			//이전 프레임 충돌 정보 검색
			CollisionID ID = {};
			ID.LeftID = vecLeft[i]->GetCollider()->GetID();
			ID.RightID = vecRight[j]->GetCollider()->GetID();
			//이전 프레임 충돌 확인
			map < UINT_PTR, bool >::iterator iter = m_mapPrevInfo.find(ID.id);
			if (iter == m_mapPrevInfo.end())
			{
				//과거 충돌 자체가 1도 없었다. 그래서 그 정보를 넣고 다시 한번 검사
				m_mapPrevInfo.insert(make_pair(ID.id, false));
				iter = m_mapPrevInfo.find(ID.id);
			}


			bool Dead = vecLeft[i]->IsDead() || vecRight[i]->IsDead();



			if (CollisionBtwCollider(vecLeft[i]->GetCollider(), vecRight[j]->GetCollider()))
			{
				//오버랩 중이다. 겹친 상태이다.

				//이전에도 겹쳐있었다.
				if (iter->second)
				{
					if (Dead)
					{
						vecLeft[i]->GetCollider()->EndOverlap(vecRight[j]->GetCollider());
						vecRight[j]->GetCollider()->EndOverlap(vecLeft[i]->GetCollider());
					}
					else
					{
						vecLeft[i]->GetCollider()->OnOverlap(vecRight[j]->GetCollider());
						vecRight[j]->GetCollider()->OnOverlap(vecLeft[i]->GetCollider());
					}

				}
				//처음 겹쳤다.
				else
				{
					//둘중 하나라도 dead 상태면, 충돌을 없었던 것으로 한다.
					if (!Dead)
					{
						vecLeft[i]->GetCollider()->BeginOverlap(vecRight[j]->GetCollider());
						vecRight[j]->GetCollider()->BeginOverlap(vecLeft[i]->GetCollider());
						iter->second = true;
					}
					
				}
				
			}
			else
			{
				if (iter->second)
				{
					//방금 막 떨어져있을때
					vecLeft[i]->GetCollider()->EndOverlap(vecRight[j]->GetCollider());
					vecRight[j]->GetCollider()->EndOverlap(vecLeft[i]->GetCollider());
					iter->second = false;
				}
			}
		}
	}

}

bool CCollisionMgr::CollisionBtwCollider(CCollider* _left, CCollider* _right)
{
	//여기서는 대체로 충돌체간의 거리와 충돌체 크기 절반의 길이 합을 비교해 붙었는지 아닌지 알수가있으며
	//여기서 검사를 한다.
	Vec2 LeftPos = _left->GetFinalPos();
	Vec2 LeftScale = _left->GetScale();

	Vec2 RightPos = _right->GetFinalPos();
	Vec2 RightScale = _right->GetScale();

	if (fabsf(LeftPos.x - RightPos.x) > (LeftScale.x / 2.0f + RightScale.x / 2.0f))
	{
		return false;
	}
	if (fabsf(LeftPos.y - RightPos.y) > (LeftScale.y / 2.0f + RightScale.y / 2.0f))
	{
		return false;
	}

	return true;
}
