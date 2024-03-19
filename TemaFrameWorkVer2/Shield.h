#pragma once
#include "Obj.h"
class CShield :
	public CObj
{
public:
	CShield();
	~CShield();

	// CObj��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _hDC) override;
	virtual void Release() override;

private:
	float m_fDistance;
	DWORD dwTime;
};