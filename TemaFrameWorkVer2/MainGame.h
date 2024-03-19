#pragma once

#include "define.h"

class CMainGame
{
public:
	CMainGame();
	~CMainGame();

public:
	void		Initialize(void);
	void		Update(void);	// �� �����Ӹ��� ��ǥ ��ȯ�� ���õ� �ڵ带 �����ϴ� �Լ�
	void		Late_Update(void);
	void		Render(void);	// �� �����Ӹ��� �׸��� �ڵ带 ȣ���ϴ� �Լ�
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