#pragma once
#include "Item.h"
class CNormalItem :
	public CItem
{
public:
	CNormalItem();
	virtual ~CNormalItem();

	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _hDC) override;
	virtual void Release() override;
};