#pragma once
#include "Bullet.h"
class CSBullet :
	public CBullet
{
public:
	CSBullet();
	virtual ~CSBullet();

	// CBullet��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _hDC) override;
	virtual void Release() override;

public:
	static float g_fSBulletAS;
};