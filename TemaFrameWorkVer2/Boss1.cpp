#include "stdafx.h"
#include "Boss1.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "WallMonster.h"
#include "AbstractFactory.h"
#include "SceneMgr.h"
#include "Stage2.h"

CBoss1::CBoss1() : CMonster(), dwTime3(0)
{
}


CBoss1::~CBoss1()
{
	Release();
}

void CBoss1::Initialize()
{
	Set_HP(5000.f);
	Set_Size(45.f, 50.f);
	Set_MoveSpeed(5.f);
	Set_AttackSpeed(900.f);
	Set_BulletType(BT_NORMAL);
	MakeCollisionBox();
	Set_Score(5000);
}

int CBoss1::Update()
{
	if (m_bDead)
	{ 
		return OBJ_DEAD;
	}

	if (m_tInfo.fY <= WINCY - 800)
		MoveY(-Get_MoveSpeed());

	if (0 == GET_LIST(PLAYER)->size())
		return OBJ_NOEVENT;

	CalCulateAngle(GET_LIST(PLAYER)->back());

	Create_Bullet(m_fAngle, Get_Team(), Get_AttackSpeed(), 10.f);

	// 3초에 한번씩 3개중 한개씩 패턴생성
	if (dwTime3 + 3000 < GetTickCount())
	{
		int iSelect = rand() % 3 + 1;
		switch (iSelect)
		{
		case 1:
			Pattern1();
			break;
		case 2:
			Pattern2();
			break;
		case 3:
			Pattern3();
			break;
		default:
			break;
		}
		dwTime3 = GetTickCount();
	}

	if (m_fTakeDamage >= 0.0001f)
		Take_Damage(m_fTakeDamage);

	CalculateCollisionPos(-5.f, 30.f, 630.f, 100.f);
	__super::Update_Rect();
	return OBJ_NOEVENT;
}

void CBoss1::Late_Update()
{
}

void CBoss1::Render(HDC _hDC)
{
	int x = m_tInfo.fX - m_tInfo.fCX * 1.2;
	int y = m_tInfo.fY;

	MoveToEx(_hDC, x, y, 0);
	//몸통
	LineTo(_hDC, x, y + m_tInfo.fCY * 4);
	LineTo(_hDC, x + m_tInfo.fCX, y + m_tInfo.fCY * 5);
	LineTo(_hDC, x + m_tInfo.fCX * 2, y + m_tInfo.fCY * 4);
	LineTo(_hDC, x + m_tInfo.fCX * 2, y);
	//오른쪽날개
	LineTo(_hDC, x + m_tInfo.fCX * 8, y - m_tInfo.fCY);
	LineTo(_hDC, x + m_tInfo.fCX * 2, y - m_tInfo.fCY);
	//꼬리
	LineTo(_hDC, x + m_tInfo.fCX * 2, y - m_tInfo.fCY * 3);
	LineTo(_hDC, x + m_tInfo.fCX * 3, y - m_tInfo.fCY * 3);
	LineTo(_hDC, x + m_tInfo.fCX * 3, y - m_tInfo.fCY * 4);
	LineTo(_hDC, x - m_tInfo.fCX, y - m_tInfo.fCY * 4);
	LineTo(_hDC, x - m_tInfo.fCX, y - m_tInfo.fCY * 3);
	LineTo(_hDC, x, y - m_tInfo.fCY * 3);
	LineTo(_hDC, x, y - m_tInfo.fCY);
	//왼쪽날개
	LineTo(_hDC, x - m_tInfo.fCX * 6, y - m_tInfo.fCY);
	LineTo(_hDC, x, y);

}

void CBoss1::Release()
{
}

void CBoss1::MovePos1()
{
}

void CBoss1::MovePos2()
{
}

void CBoss1::MovePos3()
{
}

void CBoss1::MovePos4()
{
}

void CBoss1::Pattern1()
{
	for (int i = -10; i < 30; ++i)
	{
		Create_Bullet(m_fAngle + i * 10, Get_Team(), 0.1f, 5.f);
	}
}

void CBoss1::Pattern2()
{
	CObjMgr::Get_Instance()->AddObject(MONSTER, CAbstractFactory<CWallMonster>::Create());
	dynamic_cast<CMonster*>(GET_LIST(MONSTER)->back())->Set_SpawnPos(SP_POS5);
}

void CBoss1::Pattern3()
{
	for (int i = -10; i < 30; ++i)
	{
		Create_Bullet(m_fAngle + i * 1, Get_Team(), 0.f, 5.f);
	}
}