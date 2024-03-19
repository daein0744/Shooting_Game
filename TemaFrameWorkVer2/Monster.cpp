#include "stdafx.h"
#include "Monster.h"
#include "ObjMgr.h"
#include "UIMgr.h"
#include "ScoreUI.h"
#include "SBulletItem.h"
#include "NormalItem.h"
#include "ShotBullet.h"
#include "TrackItem.h"
#include "AbstractFactory.h"
#include "NormalBullet.h"
#include "SBullet.h"
#include "ShotBullet.h"
#include "TrackBullet.h"

CMonster::CMonster() : CObj(), m_eSpawnPos(SP_END), iScore(0)
{
	this->Set_ObjID(MONSTER);
	this->Set_Team(T_TEAM2);
	this->Set_Angle(-90.f);
	if (0 < GET_LIST(PLAYER)->size())
		m_pPlayer = GET_LIST(PLAYER)->back();
	m_bTakeBoom = false;
}

CMonster::~CMonster()
{
}

void CMonster::Set_SpawnPos(SPAWN_POS _eSpawn)
{
	switch (_eSpawn)
	{
	case SP_POS1:
		Set_Pos(WINCX - (WINCX * 1.2f), WINCY * 0.2f);
		break;
	case SP_POS2:
		Set_Pos(WINCX * 0.2f, WINCY - (WINCY * 1.2f));
		break;
	case SP_POS3:
		Set_Pos(WINCX * 0.8f, WINCY - (WINCY * 1.2f));
		break;
	case SP_POS4:
		Set_Pos(WINCX * 1.2f, WINCY * 0.2f);
		break;
	case SP_POS5:
		Set_Pos(WINCX * 0.5f, WINCY - (WINCY * 1.2f));
		break;
	default:
		break;
	}
}

void CMonster::RandomSpawn()
{
	m_eSpawnPos = (SPAWN_POS)(rand() % SP_POS5);
	switch (m_eSpawnPos)
	{
	case SP_POS1:
		Set_Pos(WINCX - (WINCX * 1.2f), WINCY * 0.2f);
		break;
	case SP_POS2:
		Set_Pos(WINCX * 0.2f, WINCY - (WINCY * 1.2f));
		break;
	case SP_POS3:
		Set_Pos(WINCX * 0.8f, WINCY - (WINCY * 1.2f));
		break;
	case SP_POS4:
		Set_Pos(WINCX * 1.2f, WINCY * 0.2f);
		break;
	case SP_POS5:
		Set_Pos(WINCX * 0.5f, WINCY - (WINCY * 1.2f));
		break;
	default:
		break;
	}
}

void CMonster::BorderRange()
{
	if (m_tInfo.fX < -300 || m_tInfo.fX > WINCX + 300
		|| m_tInfo.fY > WINCY || m_tInfo.fY < -300)
	{
		Set_Dead(true);
	}
}

void CMonster::SumScore()
{
	random_device rd;

	// random_device 를 통해 난수 생성 엔진을 초기화 한다.
	mt19937 gen(rd());

	// 0 부터 99 까지 균등하게 나타나는 난수열을 생성하기 위해 균등 분포 정의.
	uniform_int_distribution<int> dis(0, 30);

	dynamic_cast<CScoreUI*>(CUIMgr::Get_Instance()->Get_List(UI_SCORE)->back())->SeT_SumScore(iScore);

	switch (dis(gen))
	{
	case 1:
		CObjMgr::Get_Instance()->AddObject(ITEM, CAbstractFactory<CNormalItem>::Create(m_tInfo.fX, m_tInfo.fY));
		GET_LIST(ITEM)->back()->Set_BulletType(BT_NORMAL);
		break;
	case 2:
		CObjMgr::Get_Instance()->AddObject(ITEM, CAbstractFactory<CSBulletItem>::Create(m_tInfo.fX, m_tInfo.fY));
		GET_LIST(ITEM)->back()->Set_BulletType(BT_SBULLET);
		break;
	case 3:
		CObjMgr::Get_Instance()->AddObject(ITEM, CAbstractFactory<CTrackItem>::Create(m_tInfo.fX, m_tInfo.fY));
		GET_LIST(ITEM)->back()->Set_BulletType(BT_TRACKBULLET);
		break;
	case 4:
		CObjMgr::Get_Instance()->AddObject(ITEM, CAbstractFactory<CShotBullet>::Create(m_tInfo.fX, m_tInfo.fY));
		GET_LIST(ITEM)->back()->Set_BulletType(BT_SHOTGUN);
		break;
	default:
		break;
	}
}