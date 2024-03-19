#include "stdafx.h"
#include "SBulletItem.h"
#include "CollisionMgr.h"
#include "SBullet.h"

CSBulletItem::CSBulletItem() : CItem()
{
	m_eBulletType = BT_SBULLET;
	m_fAttackSpeed = CSBullet::g_fSBulletAS;
}

CSBulletItem::~CSBulletItem()
{
	Release();
}

void CSBulletItem::Initialize()
{
	MakeCollisionBox();
}

int CSBulletItem::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	MoveX(Get_MoveSpeed(), Get_Angle());
	MoveY(Get_MoveSpeed(), Get_Angle());

	CalculateCollisionPos(0.f, 0.f, m_tInfo.fCX, m_tInfo.fCY);

	__super::Update_Rect();
	return OBJ_NOEVENT;
}

void CSBulletItem::Late_Update()
{

}

void CSBulletItem::Render(HDC _hDC)
{
	Rectangle(_hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	int x = m_tInfo.fX - m_tInfo.fCX * 0.25;
	int y = m_tInfo.fY;

	MoveToEx(_hDC, x += m_tInfo.fCX * 0.5, y -= m_tInfo.fCY *0.5, 0);
	LineTo(_hDC, x -= m_tInfo.fCX * 0.5, y += m_tInfo.fCY *0.5);
	LineTo(_hDC, x += m_tInfo.fCX * 0.5, y);
	LineTo(_hDC, x -= m_tInfo.fCX * 0.5, y += m_tInfo.fCY * 0.5);
}

void CSBulletItem::Release()
{
}