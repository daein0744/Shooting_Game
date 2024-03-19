#pragma once
#include "Scene.h"
class CStartScene :
	public CScene
{
public:
	CStartScene();
	~CStartScene();

	// CScene을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _hDC) override;
	virtual void Release() override;
	virtual void Key_Info() override;

private:
	TCHAR szBuffer[256];
};