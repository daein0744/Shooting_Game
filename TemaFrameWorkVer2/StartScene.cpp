#include "stdafx.h"
#include "StartScene.h"
#include "SceneMgr.h"
#include "AbstractFactory.h"
#include "Stage1.h"

CStartScene::CStartScene() : CScene()
{
	ZeroMemory(szBuffer, sizeof(TCHAR ) * 256);
}

CStartScene::~CStartScene()
{
	Release();
}

void CStartScene::Initialize()
{
}

int CStartScene::Update()
{
	Key_Info();
	return OBJ_NOEVENT;
}

void CStartScene::Late_Update()
{
}

void CStartScene::Render(HDC _hDC)
{
	int x;
	int y;
	wsprintf(szBuffer, L"게임을 시작합니다");
	TextOut(_hDC, x = 250, y = 430, szBuffer, lstrlen(szBuffer));
	wsprintf(szBuffer, L"2. 시작  ESC. 발표 종료");	
	TextOut(_hDC, x -= 20, y += 20, szBuffer, lstrlen(szBuffer));
}

void CStartScene::Release()
{
}

void CStartScene::Key_Info()
{
}