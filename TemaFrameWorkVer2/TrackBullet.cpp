#include "stdafx.h"
#include "TrackBullet.h"
#include "ObjMgr.h"
float CTrackBullet::g_fTrackBulletAS = 500.f;
CTrackBullet::CTrackBullet() : CBullet(), m_tPosin{}
{
	m_eBulletType = BT_TRACKBULLET;
	m_fAttackSpeed = 500.f;
	m_fPosinAngle = 90.f;
	m_fDistance = 20.f;
}

CTrackBullet::~CTrackBullet()
{
	Release();
}

void CTrackBullet::Initialize()
{
	Set_Size(20.f, 20.f);
	Set_HP(30.f);
	Set_MoveSpeed(10.f);
	CreateTime = GetTickCount();
	MakeCollisionBox();
	m_tPosin.x = GET_LIST(PLAYER)->front()->Get_PosX();
	m_tPosin.y = GET_LIST(PLAYER)->front()->Get_PosY() - m_fDistance;
}

int CTrackBullet::Update()
{
	if (m_bDead || Get_TakeDamage() > 0.0001f)
		return OBJ_DEAD;
	m_tPosin.x = Get_PosX();
	m_tPosin.y = Get_PosY() - m_fDistance;
	if (CreateTime + 500 > GetTickCount())
		MoveY(-3.f);
	else 
	{
		float fWidth = m_tPosin.x - this->Get_PosX();
		float fHeight = m_tPosin.y - this->Get_PosY();
		float fDiagonal = sqrt(fWidth * fWidth + fHeight * fHeight);
		float fRadian = acosf(fWidth / fDiagonal);
		if (m_tPosin.y > this->Get_PosY())
			fRadian = 2 * PI - fRadian;

		CObj* pTarget = SearchNearObj(GET_LIST(MONSTER));
		CalCulateAngle(pTarget);	
		if (abs(m_fPosinAngle - m_fAngle) > 3.1f)
		{
			if (m_fPosinAngle < m_fAngle)
				m_fPosinAngle += 3.f;
			else
				m_fPosinAngle -= 3.f;
		}

		MoveX(m_fMoveSpeed, m_fPosinAngle);
		MoveY(m_fMoveSpeed, m_fPosinAngle);
	}

	__super::Update_Rect();
	return OBJ_NOEVENT;
}

void CTrackBullet::Late_Update()
{
	if (m_tInfo.fX > WINCX  || m_tInfo.fY > WINCY
		|| m_tInfo.fX < 0 || m_tInfo.fY < 0)
		Set_Dead(true);
}

void CTrackBullet::Render(HDC _hDC)
{
	// 포신 그려보기
	//MoveToEx(_hDC, m_tInfo.fX, m_tInfo.fY, 0);
	//LineTo(_hDC, m_tPosin.x, m_tPosin.y);

	int x = Get_PosX();
	int y = Get_PosY();

	HPEN hColor;
	HPEN hPen;
	if (T_TEAM1 == Get_Team())
		hColor = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	else
		hColor = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
	hPen = (HPEN)SelectObject(_hDC, hColor);

	MoveToEx(_hDC, x, y, 0);
	LineTo(_hDC, x -= m_tInfo.fCX* 0.5, y += m_tInfo.fCY);
	LineTo(_hDC, x, y += m_tInfo.fCY);
	LineTo(_hDC, x += m_tInfo.fCX, y);
	LineTo(_hDC, x, y -= m_tInfo.fCY);
	LineTo(_hDC, x -= m_tInfo.fCX * 0.5, y -= m_tInfo.fCY);

	SelectObject(_hDC, hPen);
	DeleteObject(hColor);

}

void CTrackBullet::Release()
{
}