#include "stdafx.h"
#include "Monster2.h"
#include "ObjMgr.h"

CMonster2::CMonster2() : CMonster()
{
}

CMonster2::~CMonster2()
{
	Release();
}

void CMonster2::Initialize()
{
	Set_HP(30.f);
	CreateTime3 = GetTickCount();
	Set_Size(15.f, 15.f);
	Set_MoveSpeed(4.f);
	Set_AttackSpeed(1000.f);
	MakeCollisionBox();
	Set_Score(25);
}

int CMonster2::Update()
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

	if (Get_TakeDamage() >= 0.0001f)
	{
		Take_Damage(m_fTakeDamage);
	}

	CalculateCollisionPos(15.f, -19.f, 55.f, 50.f);
	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CMonster2::Late_Update()
{
	BorderRange();
}

void CMonster2::Render(HDC _hDC)
{
	int x = this->Get_PosX();
	int y = this->Get_PosY();

	MoveToEx(_hDC, x, y, 0);
	LineTo(_hDC, x - m_tInfo.fCX * 2, y + m_tInfo.fCY * 2);
	LineTo(_hDC, x, y + m_tInfo.fCY * 2);
	LineTo(_hDC, x + m_tInfo.fCX, y + m_tInfo.fCY * 4);
	LineTo(_hDC, x + m_tInfo.fCX * 2, y + m_tInfo.fCY * 2);
	LineTo(_hDC, x + m_tInfo.fCX * 4, y + m_tInfo.fCY * 2);
	LineTo(_hDC, x + m_tInfo.fCX * 2, y);
	LineTo(_hDC, x, y);
}

void CMonster2::Release()
{
}

void CMonster2::MovePos1()
{
	if (!m_pPlayer)
		return;

	if (CreateTime3 + 2500 > GetTickCount())
		MoveX(5.f, 0.f);
	
	float		fWidth = 0.f, fHeight = 0.f, fDiagonal = 0.f, fRadian = 0.f;

	fWidth = m_pPlayer->Get_PosX() - this->Get_PosX();
	fHeight = m_pPlayer->Get_PosY() - this->Get_PosY();

	fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

	fRadian = acosf(fWidth / fDiagonal);

	if (m_pPlayer->Get_PosY()> this->Get_PosY())
		fRadian = 2 * PI - fRadian;

	Set_Angle(fRadian * 180.f / PI);

	MoveX(Get_MoveSpeed(), Get_Angle());
	MoveY(Get_MoveSpeed(), Get_Angle());
}

void CMonster2::MovePos2()
{
	if (!m_pPlayer)
		return;

	if (CreateTime3 + 2000 > GetTickCount())
	{
		MoveY(-3.f);
	}
	float		fWidth = 0.f, fHeight = 0.f, fDiagonal = 0.f, fRadian = 0.f;

	fWidth = m_pPlayer->Get_PosX() - this->Get_PosX();
	fHeight = m_pPlayer->Get_PosY() - this->Get_PosY();

	fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

	fRadian = acosf(fWidth / fDiagonal);

	if (m_pPlayer->Get_PosY()> this->Get_PosY())
		fRadian = 2 * PI - fRadian;

	Set_Angle(fRadian * 180.f / PI);
	MoveX(Get_MoveSpeed(), Get_Angle());
	MoveY(Get_MoveSpeed(), Get_Angle());
}

void CMonster2::MovePos3()
{
	if (0 == GET_LIST(PLAYER)->size())
		return;

	if (CreateTime3 + 2000 > GetTickCount())
	{
		MoveY(-3.f);
	}

	float		fWidth = 0.f, fHeight = 0.f, fDiagonal = 0.f, fRadian = 0.f;

	fWidth = m_pPlayer->Get_PosX() - this->Get_PosX();
	fHeight = m_pPlayer->Get_PosY() - this->Get_PosY();

	fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

	fRadian = acosf(fWidth / fDiagonal);

	if (m_pPlayer->Get_PosY()> this->Get_PosY())
		fRadian = 2 * PI - fRadian;

	Set_Angle(fRadian * 180.f / PI);
	MoveX(Get_MoveSpeed(), Get_Angle());
	MoveY(Get_MoveSpeed(), Get_Angle());
}

void CMonster2::MovePos4()
{
	if (0 == GET_LIST(PLAYER)->size())
		return;

	if (CreateTime3 + 2500 > GetTickCount())
	{
		MoveX(-5.f);
	}

	float		fWidth = 0.f, fHeight = 0.f, fDiagonal = 0.f, fRadian = 0.f;

	fWidth = m_pPlayer->Get_PosX() - this->Get_PosX();
	fHeight = m_pPlayer->Get_PosY() - this->Get_PosY();

	fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

	fRadian = acosf(fWidth / fDiagonal);

	if (m_pPlayer->Get_PosY()> this->Get_PosY())
		fRadian = 2 * PI - fRadian;

	Set_Angle(fRadian * 180.f / PI);
	MoveX(Get_MoveSpeed(), Get_Angle());
	MoveY(Get_MoveSpeed(), Get_Angle());
}