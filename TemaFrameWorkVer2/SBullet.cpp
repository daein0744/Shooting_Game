#include "stdafx.h"
#include "SBullet.h"
float CSBullet::g_fSBulletAS = 100.f;
CSBullet::CSBullet() : CBullet()
{
	m_eBulletType = BT_SBULLET;
	m_fAttackSpeed = g_fSBulletAS;
}

CSBullet::~CSBullet()
{
	Release();
}

void CSBullet::Initialize()
{
	Set_Size(15.f, 15.f);
	Set_MoveSpeed(30.f);
	m_bStart = true;
	m_fHP = 10.f;
	Set_RotAngle(0.f);
	Set_RotSpeed(40.f);
	m_fLentgh = 40.f;

	MakeCollisionBox();
}

int CSBullet::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	if (m_fTakeDamage >= 0.0001f)
		return OBJ_DEAD;


	if (m_bStart)
		m_bStart = false;

	MoveX(Get_MoveSpeed(), Get_Angle());
	MoveY(Get_MoveSpeed(), Get_Angle());

	m_fRotAngle += m_fRotSpeed;

	m_tInfo.fX = m_tInfo.fX + m_fLentgh * cosf(m_fRotAngle RADIAN);
	m_tInfo.fY = m_tInfo.fY - m_fLentgh * sinf(m_fRotAngle RADIAN);
	CalculateCollisionPos(0.f, 0.f, 5.f, 5.f);
	__super::Update_Rect();
	return OBJ_NOEVENT;
}

void CSBullet::Late_Update()
{
	if (m_tInfo.fX > WINCX || m_tInfo.fY > WINCY
		|| m_tInfo.fX < 0 || m_tInfo.fY < 0)
	{
		m_bDead = true;
	}
}

void CSBullet::Render(HDC _hDC)
{
	int x = m_tInfo.fX - m_tInfo.fCX *0.5;
	int y = m_tInfo.fY - m_tInfo.fCY *0.5;

	HPEN hColor;
	HPEN hPen;
	if (T_TEAM1 == Get_Team())
		hColor = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	else
		hColor = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
	hPen = (HPEN)SelectObject(_hDC, hColor);

	// XÀÚ ÃÑ¾Ë ¸ð¾ç(SÅºÈ¯)
	MoveToEx(_hDC, x, y, 0);
	LineTo(_hDC, x += m_tInfo.fCX, y += m_tInfo.fCY);
	MoveToEx(_hDC, x, y -= m_tInfo.fCY, 0);
	LineTo(_hDC, x -= m_tInfo.fCX, y += m_tInfo.fCY);

	SelectObject(_hDC, hPen);
	DeleteObject(hColor);

}

void CSBullet::Release()
{
}