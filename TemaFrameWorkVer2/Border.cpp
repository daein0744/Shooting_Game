#include "stdafx.h"
#include "Border.h"


CBorder::CBorder() : CObj()
{
}

CBorder::~CBorder()
{
}

void CBorder::Initialize()
{
	Set_Size(30.f, 1000.f);
	Set_ObjID(BORDER);
	MakeCollisionBox();
}

int CBorder::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	CalculateCollisionPos(0.f, 0.f, m_tInfo.fCX, m_tInfo.fCY);
	__super::Update_Rect();
	return OBJ_NOEVENT;
}

void CBorder::Late_Update()
{

}

void CBorder::Render(HDC _hDC)
{
	DrawCollision(_hDC);
}

void CBorder::Release()
{
}
