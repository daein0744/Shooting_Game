#pragma once

#include "Obj.h"

class CObjMgr
{
	// �̱��濡���� �����ڸ� ���ܼ� �ܺο��� ���������.
private:
	CObjMgr();
	~CObjMgr();

public:
	static CObjMgr*		Get_Instance(void)
	{
		if (!m_pInstance)
		{
			m_pInstance = new CObjMgr;
		}

		return m_pInstance;
	}

	static void	Destroy_Instance(void)
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

public:
	void AddObject(OBJID eID, CObj* pObj);
	int Update();
	void Late_Update();
	void Render(HDC _hDC);
	void Release();

	list<CObj*>* Get_List(OBJID _eObjID)
	{
		return &m_pObjList[_eObjID];
	}

private:
	
	list <CObj*>	m_pObjList[END];
	static CObjMgr* m_pInstance;
};