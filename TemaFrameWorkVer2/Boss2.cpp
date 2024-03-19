#include "stdafx.h"
#include "Boss2.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "SceneMgr.h"
#include "Stage2.h"
CBoss2::CBoss2() : CMonster(), dwTime(0), bSelect(false), dwTime2(0)
{
}


CBoss2::~CBoss2()
{
	Release();
}

void CBoss2::Initialize()
{
	Set_HP(10000.f);
	Set_Size(45.f, 50.f);
	Set_MoveSpeed(5.f);
	Set_AttackSpeed(900.f);
	Set_BulletType(BT_NORMAL);
	MakeCollisionBox();
	Set_Score(10000);
}

int CBoss2::Update()
{
	if (m_bDead)
	{
		
		return OBJ_DEAD;
	}

	if (m_tInfo.fY <= WINCY - 900)
		MoveY(-Get_MoveSpeed());

	if (0 == GET_LIST(PLAYER)->size())
		return OBJ_NOEVENT;

	CalCulateAngle(GET_LIST(PLAYER)->back());
	Create_Bullet(m_fAngle, Get_Team(), Get_AttackSpeed(), 10.f);

	if (dwTime + 1000 < GetTickCount())
	{
		int iSelect = rand() % 3 + 1;
		switch (iSelect)
		{
		case 1:
			Pattern1();
			break;
		case 2:
			Pattern2();
			break;
		case 3:
			Pattern3();
			break;
		default:
			break;
		}
		dwTime = GetTickCount();
	}

	if (m_fTakeDamage >= 0.0001f)
		Take_Damage(m_fTakeDamage);



	CalculateCollisionPos(-5.f, 30.f, 630.f, 100.f);
	__super::Update_Rect();
	return OBJ_NOEVENT;
}

void CBoss2::Late_Update()
{
}

void CBoss2::Render(HDC _hDC)
{
	if (bSelect)
	{
		int startPosX = GET_LIST(PLAYER)->back()->Get_CollisionPosX();
		int startPosY = GET_LIST(PLAYER)->back()->Get_CollisionPosY();
		int x = startPosX;
		int y = startPosY;

		// �� ����
		// �Ű�������(�� Ÿ��, �� �β�, ����)
		HPEN hRedPen = CreatePen(PS_SOLID, 2, RGB(64, 224, 208));

		// �� ���� �� ������ ����� ���� hPen�� ����
		//�Ű������� (DC, ����� ��), ��ȯ�����δ� ������ ����� ��
		HPEN hPen = (HPEN)SelectObject(_hDC, hRedPen); // -> �̾ 127���ٷ� 

		MoveToEx(_hDC, x, y, 0);
		MoveToEx(_hDC, x += 10, y, 0);
		LineTo(_hDC, x += 40, y);
		//����
		MoveToEx(_hDC, x = startPosX, y = startPosY, 0);
		MoveToEx(_hDC, x -= 10, y, 0);
		LineTo(_hDC, x -= 40, y);
		//�Ʒ�
		MoveToEx(_hDC, x = startPosX, y = startPosY, 0);
		MoveToEx(_hDC, x, y += 10, 0);
		LineTo(_hDC, x, y += 40);
		//����
		MoveToEx(_hDC, x = startPosX, y = startPosY, 0);
		MoveToEx(_hDC, x, y -= 10, 0);
		LineTo(_hDC, x, y -= 40);
		// ������ ��
		MoveToEx(_hDC, x = startPosX, y = startPosY, 0);
		MoveToEx(_hDC, x += 10, y -= 40, 0);
		LineTo(_hDC, x += 35, y);
		LineTo(_hDC, x, y += 30);
		// ������ �Ʒ�
		MoveToEx(_hDC, x = startPosX, y = startPosY, 0);
		MoveToEx(_hDC, x += 10, y += 40, 0);
		LineTo(_hDC, x += 35, y);
		LineTo(_hDC, x, y -= 30);
		// ���� �Ʒ�
		MoveToEx(_hDC, x = startPosX, y = startPosY, 0);
		MoveToEx(_hDC, x -= 10, y += 40, 0);
		LineTo(_hDC, x -= 35, y);
		LineTo(_hDC, x, y -= 30);
		// ���� ��
		MoveToEx(_hDC, x = startPosX, y = startPosY, 0);
		MoveToEx(_hDC, x -= 10, y -= 40, 0);
		LineTo(_hDC, x -= 35, y);
		LineTo(_hDC, x, y += 30);

		// �ٽ� hPen����
		SelectObject(_hDC, hPen);

		// �� �� �� ����
		DeleteObject(hRedPen);
	}

	int bX = Get_PosX();
	int bY = Get_PosY();

	//ĳ���� ������ ������
	//����
	MoveToEx(_hDC, bX -= m_tInfo.fCX * 7, bY, 0);
	LineTo(_hDC, bX + m_tInfo.fCX * 7, bY + m_tInfo.fCY * 3);
	LineTo(_hDC, bX + m_tInfo.fCX*13.5, bY);
	LineTo(_hDC, bX, bY);
	//�޴ٸ�1
	MoveToEx(_hDC, bX + m_tInfo.fCX, bY, 0);
	LineTo(_hDC, bX + m_tInfo.fCX*1.5, bY - m_tInfo.fCY);
	LineTo(_hDC, bX + m_tInfo.fCX*2.5, bY - m_tInfo.fCY);
	LineTo(_hDC, bX + m_tInfo.fCX * 3, bY);
	//�޴ٸ�2
	MoveToEx(_hDC, bX + m_tInfo.fCX * 4, bY, 0);
	LineTo(_hDC, bX + m_tInfo.fCX*4.5, bY - m_tInfo.fCY);
	LineTo(_hDC, bX + m_tInfo.fCX*5.5, bY - m_tInfo.fCY);
	LineTo(_hDC, bX + m_tInfo.fCX * 6, bY);
	//�޴ٸ�3
	MoveToEx(_hDC, bX + m_tInfo.fCX * 7, bY, 0);
	LineTo(_hDC, bX + m_tInfo.fCX*7.5, bY - m_tInfo.fCY);
	LineTo(_hDC, bX + m_tInfo.fCX*8.5, bY - m_tInfo.fCY);
	LineTo(_hDC, bX + m_tInfo.fCX * 9, bY);
	//�޴ٸ�4
	MoveToEx(_hDC, bX + m_tInfo.fCX * 10, bY, 0);
	LineTo(_hDC, bX + m_tInfo.fCX*10.5, bY - m_tInfo.fCY);
	LineTo(_hDC, bX + m_tInfo.fCX*11.5, bY - m_tInfo.fCY);
	LineTo(_hDC, bX + m_tInfo.fCX * 12, bY);

}

void CBoss2::Release()
{
}

void CBoss2::MovePos1()
{
}

void CBoss2::MovePos2()
{
}

void CBoss2::MovePos3()
{
}

void CBoss2::MovePos4()
{
}

void CBoss2::Pattern1()
{
	CalCulateAngle(GET_LIST(PLAYER)->back());

	for (int i = 0; i < 18; ++i)
	{
		Create_Bullet(Get_Angle(), Get_Team(), 100.f);
		Create_Bullet(Get_Angle() + 50, Get_Team(), 100.f);
		Create_Bullet(Get_Angle() + 30, Get_Team(), 100.f);
		Create_Bullet(Get_Angle() - 30, Get_Team(), 100.f);
		Create_Bullet(Get_Angle() - 50, Get_Team(), 100.f);
	}
}

void CBoss2::Pattern2()
{
	if (dwTime2 + 3000 < GetTickCount())
	{
		if (bSelect == true)
			bSelect = false;
		else
			bSelect = true;
		Create_Bullet(Get_Angle(), Get_Team(), 10.f, 50.f);
	}
	dwTime2 = GetTickCount();
}

void CBoss2::Pattern3()
{
	for (int i = -10; i < 30; ++i)
	{
		Create_Bullet(m_fAngle + i * 10, Get_Team(), 0.1f, 5.f);
	}
}
