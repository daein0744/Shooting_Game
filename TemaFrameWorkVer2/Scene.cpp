#include "stdafx.h"
#include "Scene.h"


CScene::CScene()
{
	ZeroMemory(m_szBuffer, sizeof(TCHAR) * 256);
	ZeroMemory(m_dwTime, sizeof(DWORD) * 10);
	ZeroMemory(m_iStart, sizeof(int) * 10);
	for (int i = 0; i < sizeof(m_dwTime) / sizeof(DWORD); ++i)
		m_dwTime[i] = GetTickCount();
}

CScene::~CScene()
{
}

void CScene::Key_Info()
{
}

void CScene::TextDraw(HDC _hDC, int _fX, int _fY, const TCHAR * _pTextBuffer)
{
	wsprintf(m_szBuffer, _pTextBuffer);
	TextOut(_hDC, WINCX / 2 - 60, WINCY / 2 - 40, L"GAME OVER", lstrlen(m_szBuffer));
}
