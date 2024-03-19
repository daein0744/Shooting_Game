#pragma once
#include "Monster.h"
class CWallMonster :
	public CMonster
{
public:
	CWallMonster();
	virtual ~CWallMonster();

	// CMonster��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _hDC) override;
	virtual void Release() override;
	virtual void MovePos1() override;
	virtual void MovePos2() override;
	virtual void MovePos3() override;
	virtual void MovePos4() override;
};

