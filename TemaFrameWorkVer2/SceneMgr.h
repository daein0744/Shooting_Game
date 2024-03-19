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
	void Update(); // 이 녀석은 아직 이벤트 처리할게 없어서 반환형이 void임. 나중에 바뀔지도
	void Late_Update();
	void Render(HDC _hDC);
	void Release();

private:
	// Scene은 추가/삭제 보다는 접근할 일이 많아서 vector로함
	vector<CScene*>		m_pSceneList[END]; // 이름은 vec으로 바꾸기 귀찮아서 List로 놔둠
	CScene* m_pCurScene;
	static CSceneMgr* m_pInstance;
};