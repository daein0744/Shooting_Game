#include "stdafx.h"
#include "SceneMgr.h"
#include "AbstractFactory.h"
#
CSceneMgr* CSceneMgr::m_pInstance = nullptr;
CSceneMgr::CSceneMgr() : m_pCurScene(nullptr)
{
}

CSceneMgr::~CSceneMgr()
{
}

void CSceneMgr::AddScene(SCENEID eID, CScene* pScene)
{
	if (SC_END <= eID || nullptr == pScene)
		return;

	m_pSceneList[eID].push_back(pScene);
}

void CSceneMgr::Update()
{
	m_pCurScene->Update();
}

void CSceneMgr::Late_Update()
{
	m_pCurScene->Late_Update();
}

void CSceneMgr::Render(HDC _hDC)
{
	m_pCurScene->Render(_hDC);
}

void CSceneMgr::Release()
{
	for (size_t i = 0; i < SC_END; ++i)
	{
		for_each(m_pSceneList[i].begin(), m_pSceneList[i].end(), Safe_Delete<CScene*>);
		m_pSceneList[i].clear();
	}
}

void CSceneMgr::Delete_AllMonster()
{
	for_each(GET_LIST(MONSTER)->begin(), GET_LIST(MONSTER)->end(), Safe_Delete<CObj*>);
	GET_LIST(MONSTER)->clear();
}

void CSceneMgr::Delete_AllBullet()
{
	for_each(GET_LIST(BULLET)->begin(), GET_LIST(BULLET)->end(), Safe_Delete<CObj*>);
	GET_LIST(BULLET)->clear();
}

