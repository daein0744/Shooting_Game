#pragma once
#include "Bullet.h"
class CTrackBullet
	: public CBullet
{
public:
	CTrackBullet();
	virtual ~CTrackBullet();

	// CBullet��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _hDC) override;
	virtual void Release() override;

public:
	static float g_fTrackBulletAS;

private:
	DWORD		CreateTime;
	POINT		m_tPosin;
	float		m_fPosinAngle;
	float		m_fDistance;
};