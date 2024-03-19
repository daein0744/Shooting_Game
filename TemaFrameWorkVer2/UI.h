#pragma once

#include "define.h"
#include "Obj.h"

class CUI
{
public:
	CUI();
	~CUI();

	virtual void Initialize() PURE;
	virtual int Update() PURE;
	virtual void Late_Update() PURE;
	virtual void Render(HDC _hDC) PURE;
	virtual void Release() PURE;

	const INFO& Get_Info() const { return m_tInfo; }
	const RECT& Get_Rect() const { return m_tRect; }
	const float& Get_PosX() const { return m_tInfo.fX; }
	const float& Get_PosY() const { return m_tInfo.fY; }
	const UIID& Get_UIID() const { return m_eUIID; }
	const bool& Get_Dead() const { return m_bDead; }
	const CObj* Get_Player() const { return m_pPlayer; }
	const TCHAR* Get_TextBuffer() const	{ return m_szTextBuffer; }
	const bool& Get_NotDraw() const { return m_bNotDraw; }

	void Set_Info(INFO _tInfo) { m_tInfo = _tInfo; }
	void Set_Rect(RECT _tRect) { m_tRect = _tRect; }
	void Set_PosX(float _fX) { m_tInfo.fX += _fX; }
	void Set_PosY(float _fY) { m_tInfo.fY += _fY; }
	void Set_UIID(UIID _eUIID) { m_eUIID = _eUIID; }
	void Set_Dead(bool _bDead) { m_bDead = _bDead; }
	void Set_Player(CObj* _pPlayer) { m_pPlayer = _pPlayer; }
	void Set_NotDraw(bool _bNotDraw) { m_bNotDraw = _bNotDraw; }

	void Set_TextBuffer(const TCHAR* _pText)
	{
		// api유니코드 strcpy_s버전
		_tcscpy_s(m_szTextBuffer, _pText);
	}

	void TextDraw(HDC _hDC, int _fX, int _fY, const TCHAR* _pTextBuffer);
	virtual void DiagramDraw(HDC _hDC, float _posX, float _posY, float _sizeX, float _sizeY) PURE;
	void Update_Rect();

protected:
	INFO m_tInfo;
	RECT m_tRect;
	UIID m_eUIID;
	bool m_bDead;
	CObj* m_pPlayer;
	TCHAR m_szTextBuffer[256];
	bool m_bNotDraw;
};