#pragma once
#include "Monster.h"
class CBoss2 :
	public CMonster
{
public:
	CBoss2();
	virtual ~CBoss2();

	// CMonster을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _hDC) override;
	virtual void Release() override;
	virtual void MovePos1() override;
	virtual void MovePos2() override;
	virtual void MovePos3() override;
	virtual void MovePos4() override;
public:
	void Pattern1();
	void Pattern2();
	void Pattern3();
private:
	DWORD dwTime;
	DWORD dwTime2;
	bool bSelect;
};

