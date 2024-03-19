#include "stdafx.h"
#include "UIMgr.h"
#include "AbstractFactory.h"

CUIMgr* CUIMgr::m_pInstance = nullptr;

CUIMgr::CUIMgr()
{
}

CUIMgr::~CUIMgr()
{
}

void CUIMgr::AddUI(UIID eID, CUI* pObj)
{
	if (UI_END <= eID || nullptr == pObj)
		return;

	m_pUIList[eID].push_back(pObj);
}
    
int CUIMgr::Update()
{
	for (size_t i = 0; i < UI_END; ++i)
	{
		for (auto& iter = m_pUIList[i].begin();
		iter != m_pUIList[i].end(); )
		{
			int iResult = (*iter)->Update();

			if (OBJ_DEAD == iResult)
			{
				Safe_Delete<CUI*>(*iter);
				iter = m_pUIList[i].erase(iter);
			}
			else
				++iter;
		}
	}

	return OBJ_NOEVENT;
}

void CUIMgr::Late_Update()
{
	for (size_t i = 0; i < UI_END; ++i)
	{
		for (auto& iter = m_pUIList[i].begin();
		iter != m_pUIList[i].end(); ++iter)
		{
			(*iter)->Late_Update();
		}
	}
}

void CUIMgr::Render(HDC _hDC)
{
 	for (size_t i = 0; i < UI_END; ++i)
	{
		for (auto& iter = m_pUIList[i].begin();
		iter != m_pUIList[i].end(); ++iter)
		{
			(*iter)->Render(_hDC);
		}
	}
}

void CUIMgr::Release()
{
	for (size_t i = 0; i < UI_END; ++i)
	{
		for_each(m_pUIList[i].begin(), m_pUIList[i].end(), Safe_Delete<CUI*>);
		m_pUIList[i].clear();
	}
}