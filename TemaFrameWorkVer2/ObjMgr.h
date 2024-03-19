#pragma once

#include "Obj.h"

class CObjMgr
{
	// 싱글톤에서는 생성자를 숨겨서 외부에서 못만들게함.
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