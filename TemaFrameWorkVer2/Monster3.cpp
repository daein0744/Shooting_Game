#include "stdafx.h"
#include "Monster3.h"
#include "ObjMgr.h"

CMonster3::CMonster3() : CMonster()
{
}


CMonster3::~CMonster3()
{
	Release();
}

void CMonster3::Initialize()
{
	Set_HP(30.f);
	Set_Size(15.f, 15.f);
	Set_MoveSpeed(7.f);
	Set_AttackSpeed(1000.f);
	Set_BulletType(BT_NORMAL);
	MakeCollisionBox();
	Set_Score(35);
}

int CMonster3::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	if (m_fTakeDamage >= 0.0001f)
	{
		Take_Damage(m_fTakeDamage);
	}

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

	if (0 == GET_LIST(PLAYER)->size())
		return OBJ_NOEVENT;

	CalCulateAngle(GET_LIST(PLAYER)->back());
	Create_Bullet(Get_Angle(), Get_Team(), Get_AttackSpeed());
	CalculateCollisionPos(30.f, 5.f, 40.f, 55.f);

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CMonster3::Late_Update()
{
	BorderRange();
}

void CMonster3::Render(HDC _hDC)
{
	int x = Get_PosX();
	int y = Get_PosY();

	MoveToEx(_hDC, x, y, 0);
	LineTo(_hDC, x + m_tInfo.fCX * 2, y + m_tInfo.fCY * 2);
	LineTo(_hDC, x + m_tInfo.fCX * 4, y);
	LineTo(_hDC, x + m_tInfo.fCX * 3, y);
	LineTo(_hDC, x + m_tInfo.fCX * 3, y - m_tInfo.fCY * 2);
	LineTo(_hDC, x + m_tInfo.fCX * 2, y);
	LineTo(_hDC, x + m_tInfo.fCX, y - m_tInfo.fCY * 2);
	LineTo(_hDC, x + m_tInfo.fCX, y);
	LineTo(_hDC, x, y);
}

void CMonster3::Release()
{
}

void CMonster3::MovePos1()
{
	MoveX(5.f);
	MoveY(-5.f);
}

void CMonster3::MovePos2()
{
	MoveY(-5.f);
}

void CMonster3::MovePos3()
{
	MoveY(-5.f);
}

void CMonster3::MovePos4()
{
	MoveX(-5.f);
	MoveY(-5.f);
}