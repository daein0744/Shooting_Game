#pragma once
#include "Obj.h"

class CPlayer : public CObj
{
public:
	CPlayer();
	virtual ~CPlayer();

	// CObj을(를) 통해 상속됨
public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	int Get_Boom() { return iBoomNum; }
	void Set_Boom(int _iBoomNum) { iBoomNum = _iBoomNum; }

public:
	const bool& Get_IsCreateBullet() const { return m_bCreateBullet; }
	void Set_IsCreateBullet(bool _bCreateBullet) { m_bCreateBullet = _bCreateBullet; }

private:
	void	Key_Input(void);
	void	AddMiniFlight();

private:
	CObj*		m_pCurBullet;
	bool		m_bCreateBullet;
	DWORD		m_dwTime[10];
	int			iBoomNum;
};