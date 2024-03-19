#include "stdafx.h"
#include "AbstractFactory.h"
// 매니저들 포함 해주면 됨
#include "Stage2.h"
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
#include "Line.h"

CStage2::CStage2()
{
}


CStage2::~CStage2()
{
}

void CStage2::Initialize()
{
	m_dwTime2 = GetTickCount();
	m_dwTime3 = GetTickCount();
}

int CStage2::Update()
{
	Key_Info();
	if (m_dwTime[5] + 1000 * 5.f < GetTickCount())
		++m_iStart[5];

	if (m_dwTime2 + 10 < GetTickCount())
	{
		CUIMgr::Get_Instance()->AddUI(UI_LINE, CAbstractFactory<Line>::CreateUI(0, 0));
		m_dwTime2 = GetTickCount();
	}
		

	if (1 == m_iStart[5])
	{
		CObjMgr::Get_Instance()->AddObject(MONSTER, CAbstractFactory<CBoss2>::Create());
		static_cast<CMonster*>(GET_LIST(MONSTER)->back())->Set_SpawnPos(SP_POS5);
		++m_iStart[5];
	}
	

	CObjMgr::Get_Instance()->Update();
	CUIMgr::Get_Instance()->Update();

	return 0;
}

void CStage2::Late_Update()
{
	CUIMgr::Get_Instance()->Late_Update();
	CObjMgr::Get_Instance()->Late_Update();
}

void CStage2::Render(HDC _hDC)
{
	CObjMgr::Get_Instance()->Render(_hDC);
	CUIMgr::Get_Instance()->Render(_hDC);
}

void CStage2::Release()
{
}

void CStage2::Key_Info()
{
	if (m_dwTime3 + 100 < GetTickCount())
	{
		if ((GetAsyncKeyState('X')))
		{
			CObjMgr::Get_Instance()->AddObject(MONSTER, CAbstractFactory<CBoss2>::Create());
			static_cast<CMonster*>(GET_LIST(MONSTER)->back())->Set_SpawnPos(SP_POS5);
		}
		m_dwTime3 = GetTickCount();
	}
}
