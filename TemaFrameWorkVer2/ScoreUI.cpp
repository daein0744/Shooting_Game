#include "stdafx.h"
#include "ScoreUI.h"


CScoreUI::CScoreUI() : CUI(), iSumScore(0)
{
	m_eUIID = UI_SCORE;
}


CScoreUI::~CScoreUI()
{
	Release();
}

void CScoreUI::Initialize()
{
}

int CScoreUI::Update()
{
	if (m_bDead)
		return OBJ_DEAD;




	__super::Update_Rect();
	return OBJ_NOEVENT;
}

void CScoreUI::Late_Update()
{
}

void CScoreUI::Render(HDC _hDC)
{
	if (true == m_bNotDraw)
		return;

	int x = Get_PosX();
	int y = Get_PosY();

	TCHAR		szBuffer[32] = L"";
	wsprintf(szBuffer, L"SCORE : %d", iSumScore);
	TextOut(_hDC, WINCX * 0.01f, WINCY * 0.01f, szBuffer, lstrlen(szBuffer));
}

void CScoreUI::Release()
{
}

void CScoreUI::DiagramDraw(HDC _hDC, float _posX, float _posY, float _sizeX, float _sizeY)
{
}
