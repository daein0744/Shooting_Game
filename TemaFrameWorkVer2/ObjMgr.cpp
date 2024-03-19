#include "stdafx.h"
#include "ObjMgr.h"
#include "CollisionMgr.h"
#include "Player.h"
#include "Monster.h"
CObjMgr* CObjMgr::m_pInstance = nullptr;

CObjMgr::CObjMgr()
{
}

CObjMgr::~CObjMgr()
{
	Release();
}

void CObjMgr::AddObject(OBJID eID, CObj * pObj)
{
	if (END <= eID || nullptr == pObj)
		return;

	m_pObjList[eID].push_back(pObj);
}

int CObjMgr::Update()
{
	for (size_t i = 0; i < END; ++i)
	{
		for (auto& iter = m_pObjList[i].begin();
		iter != m_pObjList[i].end(); )
		{
			int iResult = (*iter)->Update();

			if (OBJ_DEAD == iResult)
			{
				if (MONSTER == (*iter)->Get_ObjID())
				{
					static_cast<CMonster*>(*iter)->SumScore();
				}
				Safe_Delete<CObj*>(*iter);
				iter = m_pObjList[i].erase(iter);
			}
			else
				++iter;
		}
	}

	return OBJ_NOEVENT;
}

void CObjMgr::Late_Update()
{
	for (size_t i = 0; i < END; ++i)
	{
		for (auto& iter = m_pObjList[i].begin();
		iter != m_pObjList[i].end(); ++iter)
		{
			(*iter)->Late_Update();
		}
	}
}

void CObjMgr::Render(HDC _hDC)
{
	for (size_t i = 0; i < END; ++i)
	{
		for (auto& iter = m_pObjList[i].begin();
		iter != m_pObjList[i].end(); ++iter)
		{
			(*iter)->Render(_hDC);
		}
	}
}

void CObjMgr::Release()
{
	for (size_t i = 0; i < END; ++i)
	{
		for_each(m_pObjList[i].begin(), m_pObjList[i].end(), Safe_Delete<CObj*>);
		m_pObjList[i].clear();
	}
}
