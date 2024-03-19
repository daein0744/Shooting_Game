#include "stdafx.h"
#include "Obj.h"
#include "NormalBullet.h"
#include "SBullet.h"
#include "TrackBullet.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"

CObj::CObj() : m_fMoveSpeed(0.f), m_bDead(false), m_fHP(0.f)
, m_fAngle(0.f), m_fDirX(1.f), m_fDirY(1.f), m_fLentgh(0.f)
, m_eObjID(END), m_eTeam(T_END), m_fTakeDamage(0.f), m_pPlayer(nullptr)
, m_bCreateBullet(false), m_fAttackSpeed(1.f)
{
	m_tInfo = { 1200, 1200, 0, 0};
	//ZeroMemory(&m_tInfo, sizeof(INFO));
	ZeroMemory(&m_tRect, sizeof(RECT));
	CreateTime = GetTickCount();
	// 체력=데미지 -> 잎노드가 결정
}

CObj::~CObj()
{
}

void CObj::MakeCollisionBox()
{
	m_vecCollisionPos.push_back(INFO(Get_Info()));
	
	// 값 초기화를 위한 Update_Rect() 1번 호출
	Update_Rect();
	m_vecCollisionBox.push_back(RECT(Get_Rect())); 
}

void CObj::Update_Rect(void)
{
	m_tRect.left =   long(m_tInfo.fX - (m_tInfo.fCX * 0.5f));
	m_tRect.top =    long(m_tInfo.fY - (m_tInfo.fCY * 0.5f));
	m_tRect.right =  long(m_tInfo.fX + (m_tInfo.fCX * 0.5f));
	m_tRect.bottom = long(m_tInfo.fY + (m_tInfo.fCY * 0.5f));

	for (size_t i = 0; i < m_vecCollisionBox.size(); ++i)
	{
		m_vecCollisionBox[i].left = long(m_vecCollisionPos[i].fX - (m_vecCollisionPos[i].fCX * 0.5f));
		m_vecCollisionBox[i].top = long(m_vecCollisionPos[i].fY - (m_vecCollisionPos[i].fCY * 0.5f));
		m_vecCollisionBox[i].right = long(m_vecCollisionPos[i].fX + (m_vecCollisionPos[i].fCX * 0.5f));
		m_vecCollisionBox[i].bottom = long(m_vecCollisionPos[i].fY + (m_vecCollisionPos[i].fCY * 0.5f));
	}
}

void CObj::Take_Damage(float _fHP)
{
	m_fHP -= _fHP;

	if (m_fHP <= 0)
	{
		Set_HP(0.f);
		Set_Dead(true);
	}

	Set_IsDamage(false);
	Set_TakeDamage(0.f);
}

CObj* CObj::SearchNearObj(list<CObj*>* _pObjList)
{ 
	float m_fMinDistance = 10000.f; 	// 최소값을 갱신하기 위해 매우 큰 값을 저장.
	CObj* m_pMinTarget = nullptr;

	if (_pObjList->empty())
		return nullptr;

	// 모든 몬스터 정보 순회
	for (auto iter = _pObjList->begin()
		; iter != _pObjList->end()
		; ++iter)
	{
		if ((*iter)->Get_Dead())
			continue;

		// 각 몬스터 거리 계산
		float fWidth = (*iter)->Get_PosX() - this->Get_PosX();
		float fHeight = (*iter)->Get_PosY() - this->Get_PosY();
		float fDistance = sqrt(fWidth * fWidth + fHeight * fHeight);

		// 기존의 몬스터보다 거리가 가까우면 최소 거리값 갱신.
		if (m_fMinDistance > fDistance)
		{
			m_pMinTarget = (*iter);
			m_fMinDistance = fDistance;
		}
	}

	return m_pMinTarget;
}

void CObj::CalCulateAngle(CObj * _pDest)
{
	if (nullptr == _pDest)
		return;

	float fWidth = _pDest->Get_PosX() - this->Get_PosX();
	float fHeight = _pDest->Get_PosY() - this->Get_PosY();
	float fDiagonal = sqrt(fWidth * fWidth + fHeight * fHeight);
	float fRadian = acosf(fWidth / fDiagonal);

	if (_pDest->Get_PosY() > this->Get_PosY())
		fRadian = 2 * PI - fRadian;

	m_fAngle = fRadian * 180.f / PI;
}

void CObj::Create_Bullet(float _fAngle, TEAM _eTeam, float _fAttackSpeed
	, float _moveSpeed, float _fX, float _fY)
{
	Set_IsCreateBullet(true);
	CObj* pBullet = nullptr;
	if (CreateTime + _fAttackSpeed > GetTickCount())
		return;

	switch (m_eBulletType)
	{
	case BT_NORMAL:
			pBullet = CAbstractFactory<CNormalBullet>::Create(m_tInfo.fX + _fX, m_tInfo.fY + _fY);
		break;
	case BT_SHOTGUN:
			pBullet = CAbstractFactory<CNormalBullet>::Create(m_tInfo.fX, m_tInfo.fY);
		break;
	case BT_TRACKBULLET:
			pBullet = CAbstractFactory<CTrackBullet>::Create(m_tInfo.fX, m_tInfo.fY);
		break;
	case BT_SBULLET:
			pBullet = CAbstractFactory<CSBullet>::Create(m_tInfo.fX, m_tInfo.fY);
		break;
	default:
		break;
	}

	if (!pBullet)
		return;

		pBullet->Set_Angle(_fAngle);
		pBullet->Set_Team(_eTeam);
		pBullet->Set_MoveSpeed(_moveSpeed);
		CObjMgr::Get_Instance()->AddObject(BULLET, pBullet);

		if (BT_SHOTGUN == m_eBulletType)
		{
			pBullet = CAbstractFactory<CNormalBullet>::Create(m_tInfo.fX, m_tInfo.fY);
			pBullet->Set_Angle(_fAngle + 30.f);
			pBullet->Set_Team(_eTeam);
			pBullet->Set_MoveSpeed(_moveSpeed);
			CObjMgr::Get_Instance()->AddObject(BULLET, pBullet);
			pBullet = CAbstractFactory<CNormalBullet>::Create(m_tInfo.fX, m_tInfo.fY);
			pBullet->Set_Angle(_fAngle - 30.f);
			pBullet->Set_Team(_eTeam);
			pBullet->Set_MoveSpeed(_moveSpeed);
			CObjMgr::Get_Instance()->AddObject(BULLET, pBullet);
		}


	CreateTime = GetTickCount();
}

void CObj::DrawCollision(HDC _hDC)
{
	Rectangle(_hDC, Get_CollisionRect().left, Get_CollisionRect().top,
		Get_CollisionRect().right, Get_CollisionRect().bottom);
}

void CObj::MoveX(float _fMoveSpeed)
{
	m_tInfo.fX += _fMoveSpeed * m_fDirX;
	for (size_t i = 0; i < m_vecCollisionPos.size(); ++i)
		m_vecCollisionPos[i].fX = m_tInfo.fX;
}

void CObj::MoveX(float _fMoveSpeed, float _fAngle)
{
	m_tInfo.fX += _fMoveSpeed * cosf(_fAngle * PI / 180.f) * m_fDirX;
	for (size_t i = 0; i < m_vecCollisionPos.size(); ++i)
		m_vecCollisionPos[i].fX = m_tInfo.fX;
}

void CObj::MoveY(float _fMoveSpeed)
{
	m_tInfo.fY -= _fMoveSpeed * m_fDirY;
	for (size_t i = 0; i < m_vecCollisionPos.size(); ++i)
		m_vecCollisionPos[i].fY = m_tInfo.fY;
}

void CObj::MoveY(float _fMoveSpeed, float _fAngle)
{
	m_tInfo.fY -= _fMoveSpeed * sinf(_fAngle * PI / 180.f) * m_fDirY;
	for (size_t i = 0; i < m_vecCollisionPos.size(); ++i)
		m_vecCollisionPos[i].fY = m_tInfo.fY;
}

void CObj::CalculateCollisionPos(float _fX, float _fY, float _fCX, float _fCY, int i)
{
	for (size_t i = 0; i < m_vecCollisionBox.size(); ++i)
		m_vecCollisionPos[i] = m_tInfo;

	m_vecCollisionPos[i].fX += _fX;
	m_vecCollisionPos[i].fY -= _fY;
	m_vecCollisionPos[i].fCX = _fCX;
	m_vecCollisionPos[i].fCY = _fCY;
}

void CObj::ReverseDirX()
{
	m_fDirX *= -1.f;
}

void CObj::ReverseDirY()
{
	m_fDirY *= -1.f;
}

