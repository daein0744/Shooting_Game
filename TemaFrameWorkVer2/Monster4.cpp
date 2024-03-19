#include "stdafx.h"
#include "Monster4.h"


CMonster4::CMonster4() : CMonster()
{
}


CMonster4::~CMonster4()
{
	Release();
}

void CMonster4::Initialize()
{
	Set_HP(30.f);
	Set_Size(15.f, 15.f);
	Set_MoveSpeed(7.f);
	Set_AttackSpeed(1000.f);
	Set_BulletType(BT_NORMAL);
	MakeCollisionBox();
	Set_Score(45);
}

int CMonster4::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

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

	Create_Bullet(Get_Angle(), Get_Team(), Get_AttackSpeed());

	if (m_fTakeDamage >= 0.0001f)
	{
		Take_Damage(m_fTakeDamage);
	}

	CalculateCollisionPos(0.f, 15.f, 30.f, 30.f);
	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CMonster4::Late_Update()
{
	BorderRange();
}

void CMonster4::Render(HDC _hDC)
{
	int x = Get_PosX();
	int y = Get_PosY();

	MoveToEx(_hDC, x, y, 0);
	LineTo(_hDC, x -= m_tInfo.fCX, y -= m_tInfo.fCY * 2);
	LineTo(_hDC, x += m_tInfo.fCX, y += m_tInfo.fCY * 0.5);
	LineTo(_hDC, x += m_tInfo.fCX, y -= m_tInfo.fCY * 0.5);
	LineTo(_hDC, x -= m_tInfo.fCX, y += m_tInfo.fCY * 2);
}

void CMonster4::Release()
{
}

void CMonster4::MovePos1()
{
	MoveX(3.f);
	MoveY(-3.f);
}

void CMonster4::MovePos2()
{
	MoveY(-3.f);
}

void CMonster4::MovePos3()
{
	MoveY(-3.f);
}

void CMonster4::MovePos4()
{
	MoveX(-3.f);
	MoveY(-3.f);
}