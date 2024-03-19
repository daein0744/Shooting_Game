#include "stdafx.h"
#include "dummyMonster.h"
#include "ObjMgr.h"
#include "NormalBullet.h"
#include "AbstractFactory.h"
dummyMonster::dummyMonster() : dTime(0)
{

}

dummyMonster::~dummyMonster()
{
	Release();
}

void dummyMonster::Initialize()
{
	Set_Size(25.f, 25.f);
	Set_HP(30.f);
	Set_BulletType(BT_NORMAL);
	Set_MoveSpeed(4.f);
	Set_AttackSpeed(1000.f);
	MakeCollisionBox();
	Set_Score(15);
}

int dummyMonster::Update()
{
	if (m_bDead)
		return OBJ_DEAD;
	if (m_fTakeDamage >= 0.0001f)
		Take_Damage(m_fTakeDamage);

	// 스폰에 따른 몬스터 이동방향
	switch (m_eSpawnPos)
	{
	case SP_POS1:
		MovePos1();
		break;
	case SP_POS2:
		MovePos2();
		break;
	case SP_POS3:
		MovePos3();
		break;
	case SP_POS4:
		MovePos4();
		break;
	default:
		break;
	}
	MoveY(1.f);
	Create_Bullet(-90.f, Get_Team(), Get_AttackSpeed(), Get_MoveSpeed(), 45.f);

	CalculateCollisionPos(37.f, -25.f, 80.f, 55.f);
	__super::Update_Rect();
	return OBJ_NOEVENT;
}

void dummyMonster::Late_Update()
{
	BorderRange();
}

void dummyMonster::Render(HDC _hDC)
{
	int x = Get_PosX();
	int y = Get_PosY();
	MoveToEx(_hDC, x, y, 0);
	LineTo(_hDC, x, y + m_tInfo.fCY);
	LineTo(_hDC, x + m_tInfo.fCX, y + m_tInfo.fCY*0.5f);
	LineTo(_hDC, x + m_tInfo.fCX*1.5, y + m_tInfo.fCY*2.5f);
	LineTo(_hDC, x + m_tInfo.fCX * 2, y + m_tInfo.fCY*0.5f);
	LineTo(_hDC, x + m_tInfo.fCX * 3, y + m_tInfo.fCY);
	LineTo(_hDC, x + m_tInfo.fCX * 3, y);
	LineTo(_hDC, x, y);
}

void dummyMonster::Release()
{
}

void dummyMonster::MovePos1()
{
	MoveX(2.f);
	MoveY(-2.f);
}

void dummyMonster::MovePos2()
{
	MoveY(-2.f);
}

void dummyMonster::MovePos3()
{
	MoveY(-2.f);
}

void dummyMonster::MovePos4()
{
	MoveX(-2.f);
	MoveY(-2.f);
}