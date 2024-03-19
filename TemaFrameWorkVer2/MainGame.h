#pragma once

#include "define.h"

class CMainGame
{
public:
	CMainGame();
	~CMainGame();

public:
	void		Initialize(void);
	void		Update(void);	// 매 프레임마다 좌표 변환에 관련된 코드를 생성하는 함수
	void		Late_Update(void);
	void		Render(void);	// 매 프레임마다 그리기 코드를 호출하는 함수
	void		Release(void);

	
public:
	void MainKey_Info();

private:
	HDC			m_hDC;
	HDC			m_memDC;
	HBITMAP		m_hBitmap;
	HBITMAP		m_hOldBitmap;
	TCHAR		m_szFPS[32];
	int			m_iFPS;
	DWORD		m_dwTime;
	DWORD		m_dwTime3;
	bool		cheat;
	INFO		Prev;
};