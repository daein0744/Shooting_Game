#include "stdafx.h"
#include "Player.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"
#include "NormalBullet.h"
#include "SBullet.h"
#include "TrackBullet.h"
#include "MiniFlight.h"
#include "Boom.h"
#include "Monster.h"
#include "UIMgr.h"
#include "Shield.h"

CPlayer::CPlayer() : CObj(), m_bCreateBullet(false), iBoomNum(3)
{
	// 시작 총알!
	m_eBulletType = BT_NORMAL;
	m_fAttackSpeed = CNormalBullet::g_fNormalAS;
	m_eObjID = PLAYER;
	m_fAngle = 90.f; // 플레이어는 위를 바라본다.
	ZeroMemory(m_dwTime, sizeof(DWORD) * 10);
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize(void)
{
	// 크기, 위치 초기화.
	m_tInfo = { 400.f, 300.f, 30.f, 30.f };

	// 플레이어 스피드 초기화
	m_fMoveSpeed = 10.f;
	Set_HP(90000.f);
	// Time생성
	CreateTime = GetTickCount();
	for (auto time : m_dwTime)
		time = GetTickCount();

	MakeCollisionBox();
}

int CPlayer::Update(void)
{
	if (m_bDead)
	{
		for (auto iter = GET_LIST(MINIFLIGHT)->begin(); iter != GET_LIST(MINIFLIGHT)->end(); ++iter)
			(*iter)->Set_Dead(true);
		return OBJ_DEAD;
	}

	if (m_fTakeDamage >= 0.0001f)
	{
		Take_Damage(m_fTakeDamage);
	}

	Set_IsCreateBullet(false);
	Key_Input();

	CalculateCollisionPos(0.f, -30.f, 10.f, 10.f);
	__super::Update_Rect();
	return OBJ_NOEVENT;
}

void CPlayer::Late_Update(void)
{
	if (m_tInfo.fX < -300 || m_tInfo.fX > WINCX + 300
		|| m_tInfo.fY > WINCY || m_tInfo.fY < -300)
	{
		Set_Dead(true);
	}
}

void CPlayer::Render(HDC hDC)
{
	int x = m_tInfo.fX;
	int y = m_tInfo.fY;

	// 충돌박스 확인
	DrawCollision(hDC);

	HPEN hColor;
	HPEN hPen;
	if (T_TEAM1 == Get_Team())
		hColor = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	else
		hColor = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
	hPen = (HPEN)SelectObject(hDC, hColor);

	//// <플레이어 1>
	////	1.
	MoveToEx(hDC, x, y, 0);
	LineTo(hDC, x += m_tInfo.fCX * 0.5, y += m_tInfo.fCY * 0.5);
	LineTo(hDC, x, y += m_tInfo.fCY);
	LineTo(hDC, x -= m_tInfo.fCX, y);
	LineTo(hDC, x, y -= m_tInfo.fCY);
	LineTo(hDC, x += m_tInfo.fCX * 0.5, y -= m_tInfo.fCY * 0.5);
	//	2.
	MoveToEx(hDC, x += m_tInfo.fCX * 0.5, y += m_tInfo.fCY * 0.5, 0);
	LineTo(hDC, x += m_tInfo.fCX, y);
	LineTo(hDC, x, y);
	LineTo(hDC, x, y += m_tInfo.fCX * 0.5);
	LineTo(hDC, x -= m_tInfo.fCX, y);
	//	3.
	MoveToEx(hDC, x += m_tInfo.fCX * 0.25, y, 0);
	LineTo(hDC, x, y += m_tInfo.fCY * 0.5);
	LineTo(hDC, x += m_tInfo.fCX * 0.5, y);
	LineTo(hDC, x, y);
	LineTo(hDC, x, y -= m_tInfo.fCY * 0.5);
	//	 4.
	MoveToEx(hDC, x -= m_tInfo.fCX * 1.75, y -= m_tInfo.fCY * 0.5, 0);
	LineTo(hDC, x -= m_tInfo.fCX, y);
	LineTo(hDC, x, y += m_tInfo.fCY * 0.5);
	LineTo(hDC, x += m_tInfo.fCX, y);
	//	5.
	MoveToEx(hDC, x -= m_tInfo.fCX *0.25, y, 0);
	LineTo(hDC, x, y += m_tInfo.fCY * 0.5);
	LineTo(hDC, x -= m_tInfo.fCX * 0.5, y);
	LineTo(hDC, x, y -= m_tInfo.fCY * 0.5);

	SelectObject(hDC, hPen);
	DeleteObject(hColor);

}

void CPlayer::Release(void)
{
}

void CPlayer::Key_Input(void)
{
	m_bCreateBullet = false;
	if (GetAsyncKeyState('A'))
	{

		if (GetAsyncKeyState('W'))
		{
			MoveX(-Get_MoveSpeed() / sqrtf(2.f));
			MoveY(Get_MoveSpeed() / sqrtf(2.f));
		}
		else if (GetAsyncKeyState('S'))
		{
			MoveX(-Get_MoveSpeed() / sqrtf(2.f));
			MoveY(-Get_MoveSpeed() / sqrtf(2.f));
		}

		else
			MoveX(-Get_MoveSpeed());
	}

	else if (GetAsyncKeyState('D'))
	{
		if (GetAsyncKeyState('W'))
		{
			MoveX(Get_MoveSpeed() / sqrtf(2.f));
			MoveY(Get_MoveSpeed() / sqrtf(2.f));
		}
		else if (GetAsyncKeyState('S'))
		{
			MoveX(Get_MoveSpeed() / sqrtf(2.f));
			MoveY(-Get_MoveSpeed() / sqrtf(2.f));
		}

		else
			MoveX(Get_MoveSpeed() / sqrtf(2.f));
	}
	else if (GetAsyncKeyState('W'))
	{
		MoveY(Get_MoveSpeed() / sqrtf(2.f));
	}
	else if (GetAsyncKeyState('S'))
	{
		MoveY(-Get_MoveSpeed() / sqrtf(2.f));
	}

	if (GetAsyncKeyState('F'))
	{
		__super::Create_Bullet(90.f, T_TEAM1, m_fAttackSpeed);
	}

	if (GetAsyncKeyState('T'))
	{
		if (m_dwTime[2] + 500 < GetTickCount())
		{
			AddMiniFlight();
			m_dwTime[2] = GetTickCount();
		}
	}

	if (GetAsyncKeyState('B'))
	{
		if (iBoomNum == 0)
			return;

		if (m_dwTime[0] + 3000 < GetTickCount())
		{
			CObjMgr::Get_Instance()->AddObject(BOOM, CAbstractFactory<CBoom>::Create(Get_PosX(), Get_PosY()));
			for (auto iter = GET_LIST(MONSTER)->begin(); iter != GET_LIST(MONSTER)->end(); ++iter)
			{
				static_cast<CMonster*>(*iter)->Set_TakeBoom(false);
			}

			vector<CUI*>::iterator iter = CUIMgr::Get_Instance()->Get_List(UI_BOOM)->begin();
			iter[iBoomNum - 1]->Set_NotDraw(true);
			--iBoomNum;
			m_dwTime[0] = GetTickCount();

		}
	}

	if (GetAsyncKeyState('C'))
	{
		if (5 == GET_LIST(SHIELD)->size())
			return;

		if (m_dwTime[1] + 500 < GetTickCount())
		{
			CObjMgr::Get_Instance()->AddObject(SHIELD, CAbstractFactory<CShield>::Create(Get_PosX(), Get_PosY()));
			m_dwTime[1] = GetTickCount();
		}
	}
}

void CPlayer::AddMiniFlight()
{
	if (GET_LIST(MINIFLIGHT)->size() == 2)
		return;

	CObjMgr::Get_Instance()->AddObject(MINIFLIGHT
		, CAbstractFactory<CMiniFlight>::Create(WINCX / 2, WINCY / 2));
}