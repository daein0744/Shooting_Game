#pragma once
#include "Obj.h"
class CBoom :
	public CObj
{
public:
	CBoom();
	virtual ~CBoom();
public:
	// CObj��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _hDC) override;
	virtual void Release() override;

private:
	DWORD dwTime;
};