#pragma once
#include "UI.h"
class CScoreUI :
	public CUI
{
public:
	CScoreUI();
	virtual ~CScoreUI();

	// CUI��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _hDC) override;
	virtual void Release() override;
	virtual void DiagramDraw(HDC _hDC, float _posX, float _posY, float _sizeX, float _sizeY) override;

public: // �ټºκ�
	int Get_SumScore() { return iSumScore; }
	void SeT_SumScore(int _iSumScore) { iSumScore += _iSumScore; }
private:
	int iSumScore;
};

