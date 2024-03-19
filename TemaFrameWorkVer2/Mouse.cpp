#include "stdafx.h"
#include "Mouse.h"

CMouse::CMouse() : CObj()
{
}

CMouse::~CMouse()
{
	Release();
}

void CMouse::Initialize(void)
{
	m_tInfo.fCX = 50.f;
	m_tInfo.fCY = 50.f;
	MakeCollisionBox();
}

int CMouse::Update(void)
{
	POINT	Pt{};

	GetCursorPos(&Pt);	// 마우스 커서의 좌표값을 얻어오는 함수
	ScreenToClient(g_hWnd, &Pt);	// 스크린 좌표 상태의 마우스를 클라이언트 상태의 좌표로 변환 시켜주는 함수

	m_tInfo.fX = (float)Pt.x;
	m_tInfo.fY = (float)Pt.y;

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CMouse::Late_Update(void)
{
}

void CMouse::Render(HDC hDC)
{
	Rectangle(hDC,
		m_tRect.left,
		m_tRect.top,
		m_tRect.right,
		m_tRect.bottom);
}

void CMouse::Release(void)
{
}
