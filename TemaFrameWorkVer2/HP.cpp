#include "stdafx.h"
#include "HP.h"
#include "ObjMgr.h"

CHP::CHP()
{

}

CHP::~CHP()
{
}

void CHP::Initialize()
{
	m_eUIID = UI_HP;
	m_pPlayer = GET_LIST(PLAYER)->back();
	m_tInfo.fCX = 20.f;
	m_tInfo.fCY = 20.f;
}

int CHP::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	if (nullptr == m_pPlayer)
		return OBJ_NOEVENT;

	if (10.f > m_pPlayer->Get_HP())
		m_bNotDraw = true;

	__super::Update_Rect();
	return OBJ_NOEVENT;
}

void CHP::Late_Update()
{
}

void CHP::Render(HDC _hDC)
{
	if (true == m_bNotDraw)
		return;

	int x = Get_PosX();
	int y = Get_PosY();

	MoveToEx(_hDC, x, y, 0);
	LineTo(_hDC, x += m_tInfo.fCX * 0.5, y);
	LineTo(_hDC, x += m_tInfo.fCX * 0.5, y += m_tInfo.fCY * 0.5);
	LineTo(_hDC, x += m_tInfo.fCX * 0.5, y -= m_tInfo.fCY * 0.5);
	LineTo(_hDC, x += m_tInfo.fCX * 0.5, y);
	LineTo(_hDC, x += m_tInfo.fCX * 0.5, y += m_tInfo.fCY * 0.5);
	LineTo(_hDC, x -= m_tInfo.fCX * 1.5, y += m_tInfo.fCY * 1.5);
	LineTo(_hDC, x -= m_tInfo.fCX * 1.5, y -= m_tInfo.fCY * 1.5);
	LineTo(_hDC, x += m_tInfo.fCX * 0.5, y -= m_tInfo.fCY * 0.5);

}

void CHP::Release()
{
}

void CHP::DiagramDraw(HDC _hDC, float _posX, float _posY, float _sizeX, float _sizeY)
{
	int x = _posX;
	int y = _posY;
	int sizeX = _sizeX;
	int sizeY = _sizeY;


	Rectangle(_hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}