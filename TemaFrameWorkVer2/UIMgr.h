#pragma once

#include "UI.h" 

class CUIMgr
{
private:
	CUIMgr();
	~CUIMgr();

public:
	static CUIMgr*		Get_Instance(void)
	{
		if (!m_pInstance)
		{
			m_pInstance = new CUIMgr;
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
	void AddUI(UIID eID, CUI* pUI);
	int Update();
	void Late_Update();
	void Render(HDC _hDC);
	void Release();

	vector<CUI*>* Get_List(UIID _eUIID)
	{
		return &m_pUIList[_eUIID];
	}

private:
	// UI는 추가/삭제 보다는 접근할 일이 많아서 vector로함
	vector<CUI*>		m_pUIList[END]; // 이름은 짓기 귀찮아서 놔둠
	static CUIMgr* m_pInstance;
};