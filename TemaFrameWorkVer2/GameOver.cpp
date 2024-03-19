#include "stdafx.h"
#include "GameOver.h"
#include "SceneMgr.h"

CGameOver::CGameOver() : CScene()
{
	
}

CGameOver::~CGameOver()
{
	Release();
}

void CGameOver::Initialize()
{
}

int CGameOver::Update()
{
	return OBJ_NOEVENT;
}

void CGameOver::Late_Update()
{
}

void CGameOver::Render(HDC _hDC)
{
	TextDraw(_hDC, 40, 50, L"Game Over");
}

void CGameOver::Release()
{
}

void CGameOver::Key_Info()
{
}
