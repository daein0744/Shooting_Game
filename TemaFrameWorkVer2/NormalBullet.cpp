#include "stdafx.h"
#include "NormalBullet.h"
float CNormalBullet::g_fNormalAS = 200.f;
CNormalBullet::CNormalBullet() : CBullet()
{
	m_eBulletType = BT_NORMAL;
	m_fAttackSpeed = g_fNormalAS;
}

CNormalBullet::~CNormalBullet()
{
	Release();
}

void CNormalBullet::Initialize()
{
	Set_Size(30.f, 30.f);
	Set_HP(30.f);
	Set_MoveSpeed(20.f);
	MakeCollisionBox();
}

int CNormalBullet::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	if (m_fTakeDamage >= 0.0001f)
	{
		return OBJ_DEAD;
	}

	MoveX(Get_MoveSpeed(), Get_Angle());
	MoveY(Get_MoveSpeed(), Get_Angle());

	CalculateCollisionPos(0.f, 0.f, m_tInfo.fCX, m_tInfo.fCY);
	__super::Update_Rect();
	return OBJ_NOEVENT;
}

void CNormalBullet::Late_Update()
{
	if (m_tInfo.fX > WINCX || m_tInfo.fY > WINCY
		|| m_tInfo.fX < 0 || m_tInfo.fY < 0)
	{
		m_bDead = true;
	}
}

void CNormalBullet::Render(HDC _hDC)
{
	HPEN hColor;
	HPEN hPen;
	if (T_TEAM1 == Get_Team())
		hColor = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	else
		hColor = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
	hPen = (HPEN)SelectObject(_hDC, hColor);

	Ellipse(_hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

	SelectObject(_hDC, hPen);
	DeleteObject(hColor);

}

void CNormalBullet::Release()
{
}