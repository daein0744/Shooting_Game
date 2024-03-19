#pragma once
#include "Obj.h"
class CMiniFlight :
	public CObj
{
public:
	CMiniFlight();
	~CMiniFlight();

	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _hDC) override;
	virtual void Release() override;

public:
	bool isNear();
private:
	DWORD dwTime;
	int m_iIDX;
	INFO m_pMyPos[2];
};