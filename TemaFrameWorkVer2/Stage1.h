#pragma once
#include "Scene.h"
class CStage1 :
	public CScene
{
public:
	CStage1();
	~CStage1();

	// CScene을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _hDC) override;
	virtual void Release() override;
	virtual void Key_Info() override;
private:
	DWORD m_dWtime1;
};