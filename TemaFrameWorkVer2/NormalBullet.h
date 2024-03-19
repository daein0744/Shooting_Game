#pragma once
#include "Bullet.h"
class CNormalBullet :
	public CBullet
{
public:
	CNormalBullet();
	virtual ~CNormalBullet();

	// CBullet��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _hDC) override;
	virtual void Release() override;
public:
	static float g_fNormalAS;
};