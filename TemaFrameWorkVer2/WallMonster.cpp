#include "stdafx.h"
#include "WallMonster.h"


CWallMonster::CWallMonster() : CMonster()
{
}


CWallMonster::~CWallMonster()
{
	Release();
}

void CWallMonster::Initialize()
{
	Set_HP(210.f);
	Set_Size(1300.f, 100.f);
	Set_MoveSpeed(5.f);
	MakeCollisionBox();
}

int CWallMonster::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	if (m_fTakeDamage >= 0.0001f)
	{
		Take_Damage(m_fTakeDamage);
	}

	MoveY(-3.f);

	CalculateCollisionPos(0.f, 0.f, m_tInfo.fCX, m_tInfo.fCY);
	__super::Update_Rect();
	return OBJ_NOEVENT;
}

void CWallMonster::Late_Update()
{
}

void CWallMonster::Render(HDC _hDC)
{
	Rectangle(_hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CWallMonster::Release()
{
}

void CWallMonster::MovePos1()
{
}

void CWallMonster::MovePos2()
{
}

void CWallMonster::MovePos3()
{
}

void CWallMonster::MovePos4()
{
}
