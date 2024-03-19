#pragma once
#include "Item.h"
class CSBulletItem :
	public CItem
{
public:
	CSBulletItem();
	virtual ~CSBulletItem();

	// CItem을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _hDC) override;
	virtual void Release() override;
};