#pragma once
#include "Monster.h"
class dummyMonster :
	public CMonster
{
public:
	dummyMonster();
	~dummyMonster();

public:
	// CMonster��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _hDC) override;
	virtual void Release() override;

public:
	// CMonster��(��) ���� ��ӵ�
	virtual void MovePos1() override;
	virtual void MovePos2() override;
	virtual void MovePos3() override;
	virtual void MovePos4() override;

private:
	DWORD dTime;
	CObj* m_pMonsterBullet;
};