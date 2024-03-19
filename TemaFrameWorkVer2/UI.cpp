#include "stdafx.h"
#include "UI.h"

CUI::CUI() : m_eUIID(UI_END), m_bDead(false), m_pPlayer(nullptr), m_bNotDraw(false)
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	ZeroMemory(&m_tRect, sizeof(RECT));
	ZeroMemory(&m_szTextBuffer, sizeof(TCHAR) * 256);
}

CUI::~CUI()
{
}

void CUI::TextDraw(HDC _hDC, int _fX, int _fY, const TCHAR* _pTextBuffer)
{
	m_tInfo.fX = _fX;
	m_tInfo.fY = _fY;
	wsprintf(m_szTextBuffer, _pTextBuffer);
	TextOut(_hDC, WINCX / 2 - 60, WINCY / 2 - 40, L"GAME OVER", lstrlen(m_szTextBuffer));
}

void CUI::Update_Rect(void)
{
	m_tRect.left = long(m_tInfo.fX - (m_tInfo.fCX * 0.5f));
	m_tRect.top = long(m_tInfo.fY - (m_tInfo.fCY * 0.5f));
	m_tRect.right = long(m_tInfo.fX + (m_tInfo.fCX * 0.5f));
	m_tRect.bottom = long(m_tInfo.fY + (m_tInfo.fCY * 0.5f));
}