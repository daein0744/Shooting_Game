#include "stdafx.h"
#include "Shield.h"
#include "ObjMgr.h"
CShield::CShield()
{
}

CShield::~CShield()
{
}

void CShield::Initialize()
{
	Set_Size(30.f, 30.f);
	Set_HP(10000.f);
	Set_MoveSpeed(5.f);
	m_fDistance = 100.f;
	if(!GET_LIST(PLAYER)->empty())
		m_pPlayer = GET_LIST(PLAYER)->front();
	dwTime = GetTickCount();
	MakeCollisionBox();
}

int CShield::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	m_fAngle += Get_MoveSpeed();
	m_tInfo.fX = m_pPlayer->Get_Info().fX + m_fDistance * cosf(m_fAngle * PI / 180.f);
	m_tInfo.fY = m_pPlayer->Get_Info().fY - m_fDistance * sinf(m_fAngle * PI / 180.f);

	if (dwTime + 1000 * 30 < GetTickCount())
		Set_Dead(true);

	CalculateCollisionPos(0.f, 0.f, m_tInfo.fCX, m_tInfo.fCY);
	__super::Update_Rect();
	return OBJ_NOEVENT;
}

void CShield::Late_Update()
{
}

void CShield::Render(HDC _hDC)
{
	Ellipse(_hDC,
		m_tRect.left,
		m_tRect.top,
		m_tRect.right,
		m_tRect.bottom);
	DrawCollision(_hDC);
}

void CShield::Release()
{
}
