#pragma once
#include "Obj.h"

class CBullet :
	public CObj
{
public:
	CBullet();
	virtual ~CBullet();
	const float& Get_RotSpeed() const { return m_fRotSpeed; }
	const float& Get_RotAngle() const { return m_fRotAngle; }
	const BULLET_TYPE& Get_BulletType() const { return m_eBulletType; }

	void Set_RotSpeed(float _fRotSpeed) { m_fRotSpeed = _fRotSpeed; }
	void Set_RotAngle(float _fRotAngle) { m_fRotAngle = _fRotAngle; }
	void Set_BulletType(BULLET_TYPE _eBulletType) { m_eBulletType = _eBulletType; }

protected:
	float	 m_fRotSpeed;		// 회전속도
	float	 m_fRotAngle;		// 회전각도
	bool	 m_bStart;
};