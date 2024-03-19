#include "stdafx.h"
#include "Boom.h"

CBoom::CBoom() : CObj()
{
	m_eObjID = BOOM;
	dwTime = 0;
}


CBoom::~CBoom()
{
	Release();
}

void CBoom::Initialize()
{
	Set_Team(T_TEAM1);
	Set_Size(400.f, 400.f);
	Set_HP(1000.f);
	Set_MoveSpeed(3.f);
	MakeCollisionBox();
	dwTime = GetTickCount();
}

int CBoom::Update()
{
	if (m_bDead || Get_TakeDamage() > 0.0001f)
		return OBJ_DEAD;

	MoveY(3.f);

	if (dwTime + 3000 < GetTickCount())
		Set_Dead(true);

	__super::Update_Rect();
	return OBJ_NOEVENT;
}

void CBoom::Late_Update()
{
}

void CBoom::Render(HDC _hDC)
{
	int x = Get_PosX();
	int y = Get_PosY();

	Ellipse(_hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	MoveToEx(_hDC, x, y, 0);
	LineTo(_hDC, x += m_tInfo.fCX * 0.6, y -= m_tInfo.fCY * 0.6);
}

void CBoom::Release()
{
}
