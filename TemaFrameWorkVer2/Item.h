#pragma once
#include "Obj.h"
class CItem :
	public CObj
{
public:
	CItem();
	virtual ~CItem();

public:
	const BULLET_TYPE& Get_CurBullet() const { return m_eBulletType; }
		void Set_BulletType(BULLET_TYPE _eBulletType) { m_eBulletType = _eBulletType; }

public:
	void EquipItem();

public:
	BULLET_TYPE m_eBulletType;
};