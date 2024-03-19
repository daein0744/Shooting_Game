#include "stdafx.h"
#include "Line.h"


Line::Line()
{
	m_eUIID = UI_LINE;
}


Line::~Line()
{
}

void Line::Initialize()
{
	m_tInfo.fCX = 0;
	m_tInfo.fCY = 0;
	m_tInfo.fY = 0;
	m_fSpeed = 30.f;
	m_tInfo.fX = rand() % WINCX;
	distance = 70.f;
	dwTime = GetTickCount();
}

int Line::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	if (dwTime + 1000 < GetTickCount())
		return OBJ_DEAD;

	m_tInfo.fY += m_fSpeed;

	return OBJ_NOEVENT;
}

void Line::Late_Update()
{
}

void Line::Render(HDC _hDC)
{
	HPEN hPen;
	HPEN hColor = CreatePen(PS_SOLID, 1, RGB(211, 211, 211));
	hPen = (HPEN)SelectObject(_hDC, hColor);

	MoveToEx(_hDC, m_tInfo.fX, m_tInfo.fY, 0);
	LineTo(_hDC, m_tInfo.fX, m_tInfo.fY + distance);

	hPen = (HPEN)SelectObject(_hDC, hPen);
	DeleteObject(hColor);
	
}

void Line::Release()
{
}

void Line::DiagramDraw(HDC _hDC, float _posX, float _posY, float _sizeX, float _sizeY)
{
}
