#include "stdafx.h"
#include "TrackItem.h"
#include "TrackBullet.h"
CTrackItem::CTrackItem()
{
	m_eBulletType = BT_TRACKBULLET;
	m_fAttackSpeed = CTrackBullet::g_fTrackBulletAS;
}

CTrackItem::~CTrackItem()
{
	Release();
}

void CTrackItem::Initialize()
{
	m_tInfo = { 100.f, 100.f, 50.f, 50.f };
	m_fMoveSpeed = 2.f;
	MakeCollisionBox();
}

int CTrackItem::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	MoveX(Get_MoveSpeed(), Get_Angle());
	MoveY(Get_MoveSpeed(), Get_Angle());

	CalculateCollisionPos(0.f, 0.f, m_tInfo.fCX, m_tInfo.fCY);
	__super::Update_Rect();
	return OBJ_NOEVENT;
}

void CTrackItem::Late_Update()
{
}

void CTrackItem::Render(HDC _hDC)
{
	Rectangle(_hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	int x = m_tInfo.fX;
	int y = m_tInfo.fY - m_tInfo.fCY * 0.5;

	MoveToEx(_hDC, x, y, 0);
	LineTo(_hDC, x -= m_tInfo.fCX * 0.3, y += m_tInfo.fCY * 0.5);
	LineTo(_hDC, x, y += m_tInfo.fCY * 0.4);
	LineTo(_hDC, x += m_tInfo.fCX * 0.6, y);
	LineTo(_hDC, x, y -= m_tInfo.fCY * 0.4);
	LineTo(_hDC, x -= m_tInfo.fCX * 0.3, y -= m_tInfo.fCY * 0.5);
}

void CTrackItem::Release()
{
}
