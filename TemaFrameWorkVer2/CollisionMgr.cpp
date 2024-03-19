#include "stdafx.h"
#include "CollisionMgr.h"
#include "UIMgr.h"
#include "HP.h"
#include "Player.h"
#include "Bullet.h"
#include "Item.h"
#include "NormalItem.h"
#include "Monster.h"
#include "ObjMgr.h"

int CCollisionMgr::_idxHP = 2;
CCollisionMgr::CCollisionMgr()
{

}

CCollisionMgr::~CCollisionMgr()
{
}

void CCollisionMgr::Collision_RectEx(list<CObj*> _Dest, list<CObj*> _Src)
{
	float	fX = 0.f, fY = 0.f;

	for (auto& Dest : _Dest)
	{
		for (auto& Src : _Src)
		{
			if (Check_Rect(Dest, Src, &fX, &fY))
			{
				// 상하 충돌
				if (fX > fY) // 길이로 비교
				{
					// 상 충돌
					if (Dest->Get_CollisionInfo().fY < Src->Get_CollisionInfo().fY)
					{
						Dest->Set_PosY(-fY);
					}
					else // 하 충돌
					{
						Dest->Set_PosY(fY);
					}
				}
				else // 좌우 충돌
				{
					// 좌 충돌
					if (Dest->Get_CollisionInfo().fX < Src->Get_CollisionInfo().fX)
					{
						Dest->Set_PosX(-fX);
					}
					else // 우 충돌
					{
						Dest->Set_PosX(fX);
					}
				}
			}
		}
	}
}

bool CCollisionMgr::Check_Rect(CObj * pDest, CObj * pSrc, float * pX, float * pY)
{
	float	fX = fabs(pDest->Get_CollisionInfo().fX - pSrc->Get_CollisionInfo().fX);
	float	fY = fabs(pDest->Get_CollisionInfo().fY - pSrc->Get_CollisionInfo().fY);

	float	fRadiusX = (pDest->Get_CollisionInfo().fCX + pSrc->Get_CollisionInfo().fCX) * 0.5f;
	float	fRadiusY = (pDest->Get_CollisionInfo().fCY + pSrc->Get_CollisionInfo().fCY) * 0.5f;

	if ((fRadiusX > fX) && (fRadiusY > fY))
	{
		*pX = fRadiusX - fX;
		*pY = fRadiusY - fY;

		return true;
	}

	return false;
}

void CCollisionMgr::CollisionBorder(list<CObj*> _Dest, list<CObj*> _Border)
{
	if (_Dest.empty())
		return;

	float	fX = 0.f, fY = 0.f;
	RECT rc{};
	OBJID _eOBJID = _Dest.front()->Get_ObjID();

	if (BULLET == _eOBJID)
	{
		for (auto& Dest : _Dest)
			for (auto& Src : _Border)
				if (IntersectRect(&rc, &(Dest->Get_CollisionRect()), &(Src->Get_CollisionRect())))
				{
					Dest->Set_Dead(true);
				}
	}
	else if (ITEM == _eOBJID)
	{
		for (auto& Dest : _Dest)
			for (auto& Src : _Border)
				if (Check_Rect(Dest, Src, &fX, &fY))
					if (fX > fY) // 상하 충돌
					Dest->ReverseDirY();
					else // 좌우 충돌
						Dest->ReverseDirX();
	}
	else if (PLAYER == _eOBJID)
	{
		for (auto& Dest : _Dest)
		{
			for (auto& Src : _Border)
			{
				if (Check_Rect(Dest, Src, &fX, &fY))
				{
					if (fX > fY) // 상하 충돌
					{
						// 상 충돌
						if (Dest->Get_CollisionInfo().fY < Src->Get_CollisionInfo().fY)
						{
							Dest->Set_PosY(-fY);
						}
						else // 하 충돌
						{
							Dest->Set_PosY(fY);
						}
					}
					else // 좌우 충돌
					{
						if (Dest->Get_CollisionInfo().fX < Src->Get_CollisionInfo().fX)
						{
							Dest->Set_PosX(-fX);
						}
						else // 우 충돌
						{
							Dest->Set_PosX(fX);
						}
					}
				}
			}	
		}
	}
}

void CCollisionMgr::CollisionShield(list<CObj*> _Dest, list<CObj*> _Shield)
{
	if (_Dest.empty())
		return;

	float	fX = 0.f, fY = 0.f;
	OBJID _eOBJID = _Dest.front()->Get_ObjID();

	if (BULLET == _eOBJID)
	{
		for (auto& Dest : _Dest)
			for (auto& Src : _Shield)
				if (Check_Rect(Dest, Src, &fX, &fY)
					&& Dest->Get_Team() != Src->Get_Team())
				{
					if (fX > fY) // 상하 충돌
						Dest->ReverseDirY();
					else // 좌우 충돌
						Dest->ReverseDirX();
					Dest->Set_Team(Src->Get_Team());
				}
	}
}

void CCollisionMgr::Collision_Rect(list<CObj*> _Dest, list<CObj*> _Src)
{

	// 안전성과 연산량을 아끼기 위해서 둘 중 하나라도 empty상태면 함수종료.
	if (_Dest.empty() || _Src.empty())
		return;

	vector<CUI*>::iterator iterUI = CUIMgr::Get_Instance()->Get_List(UI_HP)->begin();

	RECT		rc{};
	OBJID eDestID = _Dest.front()->Get_ObjID();
	OBJID eSrcID = _Src.front()->Get_ObjID();

	// BULLET && (PLAYER || MONSTER)인 경우의 충돌처리
	if(BULLET == eDestID &&	(PLAYER == eSrcID || MONSTER == eSrcID))
	{
		for (auto& Dest : _Dest)
		{
			for (auto& Src : _Src)
			{
				if (IntersectRect(&rc, &(Dest->Get_CollisionRect()), &(Src->Get_CollisionRect())))
				{
					if (Dest->Get_Team() != Src->Get_Team())
					{
						if (_idxHP != -1 && Src->Get_ObjID() == PLAYER)
						{ 
							iterUI = CUIMgr::Get_Instance()->Get_List(UI_HP)->begin();
							iterUI[_idxHP--]->Set_NotDraw(true);
						}
						Dest->Set_TakeDamage(Src->Get_HP());
						Src->Set_TakeDamage(Dest->Get_HP());
					}
				}
			}
		}
	}
	// (PLAYER || MONSTER) && BULLET 인 경우(거꾸로 넣어줘도 OK)
	else if ((PLAYER == eDestID || MONSTER == eDestID &&	BULLET == eSrcID))
	{
		for (auto& Dest : _Dest)
		{
			for (auto& Src : _Src)
			{
				if (IntersectRect(&rc, &(Dest->Get_CollisionRect()), &(Src->Get_CollisionRect())))
				{
					if (Dest->Get_Team() != Src->Get_Team())
					{
						Dest->Set_TakeDamage(Src->Get_HP());
						Src->Set_TakeDamage(Dest->Get_HP());


					}
				}
			}
		}
	}
	else if (BOOM == eDestID && MONSTER == eSrcID)
	{
		for (auto& Dest : _Dest)
		{
			for (auto& Src : _Src)
			{
				if (IntersectRect(&rc, &(Dest->Get_CollisionRect()), &(Src->Get_CollisionRect())))
				{
					bool a;
					if (Dest->Get_Team() != Src->Get_Team()
						&& false == (a = (static_cast<CMonster*>(Src)->Get_TakeBoom())))
					{
						static_cast<CMonster*>(Src)->Set_TakeBoom(true);
						Src->Set_TakeDamage(Dest->Get_HP());
					}
				}
			}
		}
	}
	else if (BOOM == eDestID && BULLET == eSrcID)
	{
		for (auto& Dest : _Dest)
		{
			for (auto& Src : _Src)
			{
				if (IntersectRect(&rc, &(Dest->Get_CollisionRect()), &(Src->Get_CollisionRect())))
				{
					if (Dest->Get_Team() != Src->Get_Team())
					{
						Src->Set_TakeDamage(Dest->Get_HP());
					}
				}
			}
		}
	}
	// PLAYER && ITEM
	else if (PLAYER == eDestID && ITEM == eSrcID)
	{
		for (auto& Dest : _Dest)
		{
			for (auto& Src : _Src)
			{
				if (IntersectRect(&rc, &(Dest->Get_CollisionRect()), &(Src->Get_CollisionRect())))
				{
					if (Dest->Get_Team() != Src->Get_Team())
					{
						BULLET_TYPE type = Src->Get_BulletType();
						Dest->Set_BulletType(type);
						Dest->Set_AttackSpeed(Src->Get_AttackSpeed());
						Src->Set_Dead(true);
					}
				}
			}
		}
	}
	// ITEM && PLAYER
	else if (ITEM == eDestID && PLAYER == eSrcID)
	{
		for (auto& Dest : _Dest)
		{
			for (auto& Src : _Src)
			{
				if (IntersectRect(&rc, &(Dest->Get_CollisionRect()), &(Src->Get_CollisionRect())))
				{
					BULLET_TYPE type = Dest->Get_BulletType();
					
					for (auto iter = GET_LIST(MINIFLIGHT)->begin(); iter != GET_LIST(MINIFLIGHT)->end(); ++iter)
					{
						(*iter)->Set_BulletType(type);
					}
					Src->Set_BulletType(type);
					Src->Set_AttackSpeed(Dest->Get_AttackSpeed());
					Dest->Set_Dead(true);
				}
			}
		}
	}
}

void CCollisionMgr::Collision_Sphere(list<CObj*> _Dest, list<CObj*> _Src)
{
	for (auto& Dest : _Dest)
	{
		for (auto& Src : _Src)
		{
			if (Dest->Get_Team() != Src->Get_Team())
			{
				Dest->Set_TakeDamage(Src->Get_HP());
				Src->Set_TakeDamage(Dest->Get_HP());
			}
		}
	}
}

bool CCollisionMgr::Check_Sphere(CObj * pDest, CObj * pSrc)
{
	float		fWidth = fabs(pDest->Get_Info().fX - pSrc->Get_Info().fX);
	float		fHeight = fabs(pDest->Get_Info().fY - pSrc->Get_Info().fY);

	float		fDistance = sqrt(fWidth * fWidth + fHeight * fHeight);

	float		fRadius = (pDest->Get_Info().fCX + pSrc->Get_Info().fCX) * 0.5f;

	return fRadius >= fDistance;
}


