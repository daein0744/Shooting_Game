#include "stdafx.h"
#include "AbstractFactory.h"
// 매니저들 포함 해주면 됨
#include "ObjMgr.h"
#include "CollisionMgr.h"
#include "UIMgr.h"
#include "SceneMgr.h"
#include "Stage1.h"
#include "Player.h"
#include "dummyMonster.h"
#include "NormalItem.h"
#include "Monster2.h"
#include "Monster3.h"
#include "Monster4.h"
#include "Boss1.h"
#include "Boss2.h"
#include "HP.h"
#include "StartScene.h"

CStage1::CStage1() : CScene()
{
	m_dWtime1 = GetTickCount();
}

CStage1::~CStage1()
{
}

void CStage1::Initialize()
{

}

int CStage1::Update()
{
	Key_Info();
	if (m_dwTime[0] + 500.f < GetTickCount())
	{
		int ran = rand() % 5;
		switch (ran)
		{
		case 0:
			CObjMgr::Get_Instance()->AddObject(MONSTER, CAbstractFactory<dummyMonster>::Create());
			static_cast<CMonster*>(GET_LIST(MONSTER)->back())->RandomSpawn();
			break;
		case 1:
			CObjMgr::Get_Instance()->AddObject(MONSTER, CAbstractFactory<CMonster2>::Create());
			static_cast<CMonster*>(GET_LIST(MONSTER)->back())->RandomSpawn();
			break;
		case 2:
			CObjMgr::Get_Instance()->AddObject(MONSTER, CAbstractFactory<CMonster3>::Create());
			static_cast<CMonster*>(GET_LIST(MONSTER)->back())->RandomSpawn();
			break;
		case 3:
			CObjMgr::Get_Instance()->AddObject(MONSTER, CAbstractFactory<CMonster4>::Create());
			static_cast<CMonster*>(GET_LIST(MONSTER)->back())->RandomSpawn();
			break;
		}
		
		m_dwTime[0] = GetTickCount();
	}

	/*if (m_dwTime[1] + 1000 * 20.f < GetTickCount())
		++m_iStart[1];

	if (1 == m_iStart[1])
	{
		CObjMgr::Get_Instance()->AddObject(MONSTER, CAbstractFactory<CBoss1>::Create());
		static_cast<CMonster*>(GET_LIST(MONSTER)->back())->Set_SpawnPos(SP_POS5);
		++m_iStart[1];
	}*/

	CObjMgr::Get_Instance()->Update();
	CUIMgr::Get_Instance()->Update();

	return OBJ_NOEVENT;
}

void CStage1::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
	CUIMgr::Get_Instance()->Late_Update();
}

void CStage1::Render(HDC _hDC)
{
	CObjMgr::Get_Instance()->Render(_hDC);
	CUIMgr::Get_Instance()->Render(_hDC);
}

void CStage1::Release()
{
}

void CStage1::Key_Info()
{
	if (m_dWtime1 + 300 < GetTickCount())
	{
		if ((GetAsyncKeyState('Z')))
		{
			CObjMgr::Get_Instance()->AddObject(MONSTER, CAbstractFactory<CBoss1>::Create());
			static_cast<CMonster*>(GET_LIST(MONSTER)->back())->Set_SpawnPos(SP_POS5);
		}
		m_dWtime1 = GetTickCount();
	}
}