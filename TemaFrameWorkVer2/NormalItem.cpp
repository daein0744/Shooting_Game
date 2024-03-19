#include "stdafx.h"
#include "NormalItem.h"
#include "NormalBullet.h"


CNormalItem::CNormalItem()
{
	m_eBulletType = BT_NORMAL;
	m_fAttackSpeed = CNormalBullet::g_fNormalAS;
}

CNormalItem::~CNormalItem()
{
	Release();
}

void CNormalItem::Initialize()
{
	int a = rand() % 2;
	if (0 == a)
		m_fAngle = -45.f;
	else
		m_fAngle = +45.f;
	MakeCollisionBox();
}

int CNormalItem::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	MoveX(Get_MoveSpeed(), Get_Angle());
	MoveY(Get_MoveSpeed(), Get_Angle());

	CalculateCollisionPos(0.f, 0.f, m_tInfo.fCX, m_tInfo.fCY);
	__super::Update_Rect();
	return OBJ_NOEVENT;
}

void CNormalItem::Late_Update()
{

}

void CNormalItem::Render(HDC _hDC)
{
	Rectangle(_hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	Ellipse(_hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CNormalItem::Release()
{
}