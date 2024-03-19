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

	GetCursorPos(&Pt);	// ���콺 Ŀ���� ��ǥ���� ������ �Լ�
	ScreenToClient(g_hWnd, &Pt);	// ��ũ�� ��ǥ ������ ���콺�� Ŭ���̾�Ʈ ������ ��ǥ�� ��ȯ �����ִ� �Լ�

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
