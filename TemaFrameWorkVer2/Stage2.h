#pragma once
#include "Scene.h"
class CStage2 :
	public CScene
{
public:
	CStage2();
	~CStage2();

	// CScene��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _hDC) override;
	virtual void Release() override;
	virtual void Key_Info() override;

private:
	DWORD		m_dwTime2;
	DWORD		m_dwTime3;
};

