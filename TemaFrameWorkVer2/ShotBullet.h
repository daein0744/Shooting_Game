#pragma once
#include "Item.h"
class CShotBullet :
	public CItem
{
public:
	CShotBullet();
	virtual ~CShotBullet();

	// CItem��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _hDC) override;
	virtual void Release() override;
};