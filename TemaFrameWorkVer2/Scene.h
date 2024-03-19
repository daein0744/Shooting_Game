#pragma once

#include "define.h"

class CScene
{
public:
	CScene();
	~CScene();

	virtual void Initialize() PURE;
	virtual int Update() PURE;
	virtual void Late_Update() PURE;
	virtual void Render(HDC _hDC) PURE;
	virtual void Release() PURE;
	virtual void Key_Info() PURE; // ���������� ���� Ű �Է��� �޸� ��!

protected:
	void TextDraw(HDC _hDC, int _fX, int _fY, const TCHAR* _pTextBuffer);

protected:
	TCHAR m_szBuffer[256];
	DWORD		m_dwTime[10];
	int			m_iStart[10];
};