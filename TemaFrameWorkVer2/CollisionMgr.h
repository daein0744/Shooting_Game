#pragma once

#include "Obj.h"
#include "define.h"

class CCollisionMgr
{
public:
	CCollisionMgr();
	~CCollisionMgr();

public:
	static void Collision_Rect(list<CObj*> _Dest, list<CObj*> _Src);
	static void Collision_RectEx(list<CObj*> _Dest, list<CObj*> _Src);
	static void Collision_Sphere(list<CObj*> _Dest, list<CObj*> _Src);
	static	bool Check_Sphere(CObj* pDest, CObj* pSrc);
	static	bool Check_Rect(CObj* pDest, CObj* pSrc, float* pX, float* pY);
	static void CollisionBorder(list<CObj*> _Dest, list<CObj*> _Border);
	static void CollisionShield(list<CObj*> _Dest, list<CObj*> _Shield);

public:
	static int _idxHP;
};