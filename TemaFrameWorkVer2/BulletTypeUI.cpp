#include "stdafx.h"
#include "BulletTypeUI.h"
#include "ObjMgr.h"

CBulletTypeUI::CBulletTypeUI() : CUI()
{
	m_eUIID = UI_BULLETTYPE;
}

CBulletTypeUI::~CBulletTypeUI()
{
	Release();
}

void CBulletTypeUI::Initialize()
{
	m_tInfo.fCX = 65.f;
	m_tInfo.fCY = 65.f;
	m_pPlayer = GET_LIST(PLAYER)->back();
}

int CBulletTypeUI::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	if (nullptr == m_pPlayer)
		return OBJ_NOEVENT;

	__super::Update_Rect();
	return OBJ_NOEVENT;
}

void CBulletTypeUI::Late_Update()
{
}

void CBulletTypeUI::Render(HDC _hDC)
{
	if (true == m_bNotDraw)
		return;

	int x = Get_PosX();
	int y = Get_PosY();

	if (BT_NORMAL == m_pPlayer->Get_BulletType())
	{
		Rectangle(_hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
		Ellipse(_hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	}
	else if (BT_SBULLET == m_pPlayer->Get_BulletType())
	{
		Rectangle(_hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
		int x = m_tInfo.fX - m_tInfo.fCX * 0.25;
		int y = m_tInfo.fY;

		MoveToEx(_hDC, x += m_tInfo.fCX * 0.5, y -= m_tInfo.fCY *0.5, 0);
		LineTo(_hDC, x -= m_tInfo.fCX * 0.5, y += m_tInfo.fCY *0.5);
		LineTo(_hDC, x += m_tInfo.fCX * 0.5, y);
		LineTo(_hDC, x -= m_tInfo.fCX * 0.5, y += m_tInfo.fCY * 0.5);
	}
	else if (BT_SHOTGUN == m_pPlayer->Get_BulletType())
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
	else if (BT_TRACKBULLET == m_pPlayer->Get_BulletType())
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
}

void CBulletTypeUI::Release()
{
}

void CBulletTypeUI::DiagramDraw(HDC _hDC, float _posX, float _posY, float _sizeX, float _sizeY)
{
}
