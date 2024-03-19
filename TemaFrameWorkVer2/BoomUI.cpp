#include "stdafx.h"
#include "BoomUI.h"
#include "ObjMgr.h"
#include "Player.h"

CBoomUI::CBoomUI()
{
}


CBoomUI::~CBoomUI()
{
}

void CBoomUI::Initialize()
{
	m_eUIID = UI_BOOM;
	m_pPlayer = GET_LIST(PLAYER)->back();
	m_tInfo.fCX = 40.f;
	m_tInfo.fCY = 40.f;
}

int CBoomUI::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	if (nullptr == m_pPlayer)
		return OBJ_NOEVENT;



	__super::Update_Rect();
	return OBJ_NOEVENT;
}

void CBoomUI::Late_Update()
{
}

void CBoomUI::Render(HDC _hDC)
{
	if (true == m_bNotDraw)
		return;

	int x = Get_PosX();
	int y = Get_PosY();

	Ellipse(_hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	MoveToEx(_hDC, x, y, 0);
	LineTo(_hDC, x += m_tInfo.fCX * 0.6, y -= m_tInfo.fCY * 0.6);
}

void CBoomUI::Release()
{
}

void CBoomUI::DiagramDraw(HDC _hDC, float _posX, float _posY, float _sizeX, float _sizeY)
{
}
