#include "stdafx.h"
#include "MainGame.h"
#include "AbstractFactory.h"
// 매니저들 포함 해주면 됨
#include "ObjMgr.h"
#include "CollisionMgr.h"
#include "UIMgr.h"
#include "SceneMgr.h"
#include "StartScene.h"
#include "Stage1.h"
#include "GameOver.h"
#include "NormalItem.h"
#include "SBulletItem.h"
#include "TrackItem.h"
#include "ShotBullet.h"
#include "Player.h"
#include "HP.h"
#include "Border.h"
#include "ScoreUI.h"
#include "BoomUI.h"
#include "BulletTypeUI.h"
#include "Stage2.h"



//#include "dummyMonster.h"
//#include "Monster2.h"
//#include "Monster3.h"
//#include "Monster4.h"
//#include "Boss1.h"
//#include "Boss2.h"


CMainGame::CMainGame() : m_dwTime(0), m_iFPS(0),
	m_hDC(nullptr), m_memDC(nullptr), m_dwTime3(0)
{
	cheat = false;
	ZeroMemory(m_szFPS, sizeof(m_szFPS));
}

CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize(void)
{
	m_hDC = GetDC(g_hWnd);
	m_memDC = CreateCompatibleDC(m_hDC);
	m_hBitmap = CreateCompatibleBitmap(m_hDC, WINCX, WINCY);
	m_hOldBitmap = (HBITMAP)SelectObject(m_memDC, m_hBitmap);
	float fBorderDepth = -10.f;
	CObjMgr::Get_Instance()->AddObject(PLAYER, CAbstractFactory<CPlayer>::Create(WINCX / 2, WINCY / 2));
	CObjMgr::Get_Instance()->AddObject(BORDER, CAbstractFactory<CBorder>::Create()); // 상
	CObjMgr::Get_Instance()->Get_List(BORDER)->back()->Set_Info(INFO{ WINCX / 2.f , fBorderDepth , 1000.f, 20.f });
	CObjMgr::Get_Instance()->AddObject(BORDER, CAbstractFactory<CBorder>::Create()); // 하
	CObjMgr::Get_Instance()->Get_List(BORDER)->back()->Set_Info(INFO{ WINCX / 2.f, WINCY - fBorderDepth * 2, 1000.f, 20.f });
	CObjMgr::Get_Instance()->AddObject(BORDER, CAbstractFactory<CBorder>::Create()); // 좌
	CObjMgr::Get_Instance()->Get_List(BORDER)->back()->Set_Info(INFO{fBorderDepth, WINCY / 2.f, 20.f, 1000.f });
	CObjMgr::Get_Instance()->AddObject(BORDER, CAbstractFactory<CBorder>::Create()); // 우
	CObjMgr::Get_Instance()->Get_List(BORDER)->back()->Set_Info(INFO{ WINCX - fBorderDepth, WINCY / 2.f, 20.f, 1000.f });
	CUIMgr::Get_Instance()->AddUI(UI_HP, CAbstractFactory<CHP>::CreateUI(WINCX * 0.11, WINCY * 0.83));
	CUIMgr::Get_Instance()->AddUI(UI_HP, CAbstractFactory<CHP>::CreateUI(WINCX * 0.20, WINCY * 0.83));
	CUIMgr::Get_Instance()->AddUI(UI_HP, CAbstractFactory<CHP>::CreateUI(WINCX * 0.29, WINCY * 0.83));
	CUIMgr::Get_Instance()->AddUI(UI_SCORE, CAbstractFactory<CScoreUI>::CreateUI(300, 100));
	CUIMgr::Get_Instance()->AddUI(UI_BOOM, CAbstractFactory<CBoomUI>::CreateUI(WINCX * 0.48, WINCY * 0.85));
	CUIMgr::Get_Instance()->AddUI(UI_BOOM, CAbstractFactory<CBoomUI>::CreateUI(WINCX * 0.55, WINCY * 0.85));
	CUIMgr::Get_Instance()->AddUI(UI_BULLETTYPE, CAbstractFactory<CBulletTypeUI>::CreateUI(WINCX * 0.8, WINCY * 0.84));
	CUIMgr::Get_Instance()->AddUI(UI_BOOM, CAbstractFactory<CBoomUI>::CreateUI(WINCX * 0.62, WINCY * 0.85));
	CSceneMgr::Get_Instance()->AddScene(SC_LOGIN, CAbstractFactory<CStartScene>::CreateScene());
	CSceneMgr::Get_Instance()->Set_CurScene(CSceneMgr::Get_Instance()->Get_List(SC_LOGIN)->back());
	CSceneMgr::Get_Instance()->AddScene(SC_STAGE, CAbstractFactory<CStage1>::CreateScene());
	CSceneMgr::Get_Instance()->AddScene(SC_STAGE, CAbstractFactory<CStage2>::CreateScene());
	CSceneMgr::Get_Instance()->AddScene(SC_GAMEOVER, CAbstractFactory<CGameOver>::CreateScene());
}

void CMainGame::Update(void)
{
	MainKey_Info(); // 온갖 치트 여기에 넣음 될듯.
	CSceneMgr::Get_Instance()->Update();
}

void CMainGame::Late_Update(void)
{
	//사실 경우의수 이용해서 짜는 반복문 있거든
	CSceneMgr::Get_Instance()->Late_Update();
	CCollisionMgr::Collision_Rect(*GET_LIST(BULLET), *GET_LIST(MONSTER));
	CCollisionMgr::Collision_Rect(*GET_LIST(BULLET), *GET_LIST(PLAYER));
	CCollisionMgr::Collision_Rect(*GET_LIST(ITEM), *GET_LIST(PLAYER));
	CCollisionMgr::Collision_Rect(*GET_LIST(BOOM), *GET_LIST(MONSTER));
	CCollisionMgr::Collision_Rect(*GET_LIST(BOOM), *GET_LIST(BULLET));
	CCollisionMgr::Collision_RectEx(*GET_LIST(PLAYER), *GET_LIST(MONSTER));
	CCollisionMgr::CollisionBorder(*GET_LIST(BULLET), *GET_LIST(BORDER));
	CCollisionMgr::CollisionBorder(*GET_LIST(ITEM), *GET_LIST(BORDER));
	CCollisionMgr::CollisionBorder(*GET_LIST(PLAYER), *GET_LIST(BORDER));
	CCollisionMgr::CollisionShield(*GET_LIST(BULLET), *GET_LIST(SHIELD));
}

void CMainGame::Render(void)                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    
{
	// 프레임 표시
	++m_iFPS;
	if (m_dwTime + 1000 < GetTickCount())
	{
		swprintf_s(m_szFPS, L"FPS : %d", m_iFPS);
		SetWindowText(g_hWnd, m_szFPS);

		m_iFPS = 0;
   		m_dwTime = GetTickCount();
	}

 	Rectangle(m_memDC, -1, -1, WINCX + 1, WINCY + 1);

	CSceneMgr::Get_Instance()->Render(m_memDC);

	BitBlt(m_hDC, 0, 0, WINCX, WINCY
		, m_memDC, 0, 0, SRCCOPY);
}

void CMainGame::Release(void)
{
	CUIMgr::Get_Instance()->Destroy_Instance();   
	CObjMgr::Get_Instance()->Destroy_Instance();
	CSceneMgr::Get_Instance()->Destroy_Instance();
	SelectObject(m_memDC, m_hOldBitmap);
	ReleaseDC(g_hWnd, m_memDC);
	ReleaseDC(g_hWnd, m_hDC);
}



void CMainGame::MainKey_Info()
{
	if (m_dwTime3 + 100 < GetTickCount())
	{
		if ((GetAsyncKeyState('1')))
		{			
			auto iter = CSceneMgr::Get_Instance()->Get_List(SC_LOGIN)->begin();
			CSceneMgr::Get_Instance()->Set_CurScene(iter[0]); // 시작
		}
		else if ((GetAsyncKeyState('2')))
		{
			auto iter = CSceneMgr::Get_Instance()->Get_List(SC_STAGE)->begin();
			CSceneMgr::Get_Instance()->Set_CurScene(iter[STAGE_1]); // 스테이지 1

		}
		else if ((GetAsyncKeyState('3')))
		{
			auto iter = CSceneMgr::Get_Instance()->Get_List(SC_STAGE)->begin();
			CSceneMgr::Get_Instance()->Set_CurScene(iter[STAGE_2]); // 스테이지 

		}
		else if ((GetAsyncKeyState('4')))
		{
			auto iter = CSceneMgr::Get_Instance()->Get_List(SC_GAMEOVER)->begin();
			CSceneMgr::Get_Instance()->Set_CurScene(iter[0]); // 게임오버
		}
		else if (GetAsyncKeyState('U'))
		{
			CObjMgr::Get_Instance()->AddObject(ITEM, CAbstractFactory<CNormalItem>::Create(100, 50));
			GET_LIST(ITEM)->back()->Set_BulletType(BT_NORMAL);
		}
		else if (GetAsyncKeyState('I'))
		{
			CObjMgr::Get_Instance()->AddObject(ITEM, CAbstractFactory<CSBulletItem>::Create(100, 50));
			GET_LIST(ITEM)->back()->Set_BulletType(BT_SBULLET);
		}
		else if (GetAsyncKeyState('O'))
		{
			CObjMgr::Get_Instance()->AddObject(ITEM, CAbstractFactory<CTrackItem>::Create(100, 50));
			GET_LIST(ITEM)->back()->Set_BulletType(BT_TRACKBULLET);
		}
		else if (GetAsyncKeyState('P'))
		{
			CObjMgr::Get_Instance()->AddObject(ITEM, CAbstractFactory<CShotBullet>::Create(100, 50));
			GET_LIST(ITEM)->back()->Set_BulletType(BT_SHOTGUN);
		}
		m_dwTime3 = GetTickCount();
	}
}