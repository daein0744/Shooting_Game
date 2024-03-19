#include "stdafx.h"
#include "MiniFlight.h"
#include "ObjMgr.h"
#include "Player.h"
#include "NormalBullet.h"

CMiniFlight::CMiniFlight() : m_iIDX(0)
{
	m_eObjID = MINIFLIGHT;
	m_eTeam = T_TEAM1;
}

CMiniFlight::~CMiniFlight()
{
	Release();
}

void CMiniFlight::Initialize()
{
	// 방어코드
	if (0 == GET_LIST(PLAYER)->size())
		return;

	// 플레이어 포인터(m_pPlayer)랑 동기화
	m_pPlayer = GET_LIST(PLAYER)->back();
	Set_BulletType(m_pPlayer->Get_BulletType());
	m_iIDX = GET_LIST(MINIFLIGHT)->size();
	float fX = m_pPlayer->Get_PosX();
	float fY = m_pPlayer->Get_PosY();
	Set_Pos(fX, fY);
	Set_Size(30.f, 30.f);
	Set_Angle(m_fAngle);
	MakeCollisionBox();

	float tmp = m_pPlayer->Get_AttackSpeed() * 2;
	Set_AttackSpeed(tmp);

	float MoveSpeed = m_pPlayer->Get_MoveSpeed() / 2.f;
	Set_MoveSpeed(MoveSpeed);
}


int CMiniFlight::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	if (0 == m_iIDX)
	{
		m_pMyPos[m_iIDX].fX = m_pPlayer->Get_PosX() - 50.f;
		m_pMyPos[m_iIDX].fY = m_pPlayer->Get_PosY() + 50.f;
	}
	else
	{
		m_pMyPos[m_iIDX].fX = m_pPlayer->Get_PosX() + 50.f;
		m_pMyPos[m_iIDX].fY = m_pPlayer->Get_PosY() + 50.f;
	}

	if (isNear())
	{
		float fWidth = m_pMyPos[m_iIDX].fX - this->Get_PosX();
		float fHeight = m_pMyPos[m_iIDX].fY - this->Get_PosY();
		float fDiagonal = sqrt(fWidth * fWidth + fHeight * fHeight);
		float fRadian = acosf(fWidth / fDiagonal);

		if (m_pMyPos[m_iIDX].fY > this->Get_PosY())
			fRadian = 2 * PI - fRadian;

		m_fAngle = fRadian * 180.f / PI;

		MoveX(Get_MoveSpeed(), Get_Angle());
		MoveY(Get_MoveSpeed(), Get_Angle());
	}

	Create_Bullet(90.f, T_TEAM1, m_fAttackSpeed);

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CMiniFlight::Late_Update()
{

}

void CMiniFlight::Render(HDC _hDC)
{
	int x = Get_PosX();
	int y = Get_PosY();
	MoveToEx(_hDC, x, y, 0);
	LineTo(_hDC, x -= m_tInfo.fCX* 0.5, y += m_tInfo.fCY);
	LineTo(_hDC, x += m_tInfo.fCX * 0.5, y -= m_tInfo.fCY * 0.5);
	LineTo(_hDC, x += m_tInfo.fCX * 0.5, y += m_tInfo.fCY * 0.5);
	LineTo(_hDC, x -= m_tInfo.fCX * 0.5, y -= m_tInfo.fCY);
}
void CMiniFlight::Release()
{
}

bool CMiniFlight::isNear()
{
	float fWidth = m_pPlayer->Get_PosX() - Get_PosX();
	float fHegiht = m_pPlayer->Get_PosY() - Get_PosY();

	float fDistance = sqrt(fWidth *fWidth + fHegiht * fHegiht);

	if (fDistance < 100)
		return false;
	else
		return true;
}
