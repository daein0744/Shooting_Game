#pragma once

#include "Scene.h"
#include "Obj.h"
#include "define.h"
#include "ObjMgr.h"

class CSceneMgr
{
private:
	CSceneMgr();
	~CSceneMgr();

public:
	static CSceneMgr*		Get_Instance(void)
 	{
		if (!m_pInstance)
		{
			m_pInstance = new CSceneMgr;
		}

		return m_pInstance;
	}

	static void	Destroy_Instance(void)
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

	vector<CScene*>* Get_List(SCENEID _eSceneID)
	{
		return &m_pSceneList[_eSceneID];
	}

	const CScene* Get_CurScene() const
	{
		return m_pCurScene;
	}

	void Set_CurScene(CScene* _pScene)
	{
		Delete_AllMonster();
		Delete_AllBullet();

		m_pCurScene = _pScene;
	}
public:
	void Delete_AllMonster();
	void Delete_AllBullet();

public:
	void AddScene(SCENEID eID, CScene* pScene);
	void Update(); // �� �༮�� ���� �̺�Ʈ ó���Ұ� ��� ��ȯ���� void��. ���߿� �ٲ�����
	void Late_Update();
	void Render(HDC _hDC);
	void Release();

private:
	// Scene�� �߰�/���� ���ٴ� ������ ���� ���Ƽ� vector����
	vector<CScene*>		m_pSceneList[END]; // �̸��� vec���� �ٲٱ� �����Ƽ� List�� ����
	CScene* m_pCurScene;
	static CSceneMgr* m_pInstance;
};