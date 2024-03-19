#pragma once
#include "Obj.h"
class CBorder :
	public CObj
{
public:
	CBorder();
	~CBorder();

	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _hDC) override;
	virtual void Release() override;
};