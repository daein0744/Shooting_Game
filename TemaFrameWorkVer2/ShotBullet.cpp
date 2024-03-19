#include "stdafx.h"
#include "ShotBullet.h"
#include "NormalBullet.h"
CShotBullet::CShotBullet()
{
	m_eBulletType = BT_SHOTGUN;
	m_fAttackSpeed = CNormalBullet::g_fNormalAS * 1.5;
}

CShotBullet::~CShotBullet()
{
	Release();
}

void CShotBullet::Initialize()
{
	m_tInfo = { 300.f, 250.f, 50.f, 50.f };
	m_fMoveSpeed = 2.f;
	MakeCollisionBox();
}

int CShotBullet::Update()
{
	if (m_bDead)
		return OBJ_DEAD;
	MoveX(Get_MoveSpeed(), Get_Angle());
	MoveY(Get_MoveSpeed(), Get_Angle());
	CalculateCollisionPos(0.f, 0.f, m_tInfo.fCX, m_tInfo.fCY);
	__super::Update_Rect();
	return OBJ_NOEVENT;
}

void CShotBullet::Late_Update()
{

}

void CShotBullet::Render(HDC _hDC)
{
	int x = m_tInfo.fX;
	int y = m_tInfo.fY + m_tInfo.fCY * 0.5;

	Rectangle(_hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	MoveToEx(_hDC, x, y, 0);
	LineTo(_hDC, x -= m_tInfo.fCX * 0.5, y -= m_tInfo.fCY * 0.9);
	MoveToEx(_hDC, x += m_tInfo.fCX * 0.5, y += m_tInfo.fCY* 0.9, 0);
	LineTo(_hDC, x += m_tInfo.fCX * 0.5, y -= m_tInfo.fCY* 0.9);
	MoveToEx(_hDC, x -= m_tInfo.fCX * 0.5, y += m_tInfo.fCY* 0.9, 0);
	LineTo(_hDC, x, y -= m_tInfo.fCY* 0.9);
}

void CShotBullet::Release()
{
}