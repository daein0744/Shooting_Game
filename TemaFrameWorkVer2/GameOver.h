#pragma once
#include "Scene.h"
class CGameOver :
	public CScene
{
public:
	CGameOver();
	~CGameOver();

	// CScene��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _hDC) override;
	virtual void Release() override;
	virtual void Key_Info() override;
};