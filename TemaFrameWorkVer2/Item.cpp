#include "stdafx.h"
#include "Item.h"
#include "Player.h"
#include "ObjMgr.h"

CItem::CItem() : CObj(), m_eBulletType(BT_END)
{
	m_eObjID = ITEM;
	m_tInfo = { 400.f, 150.f, 50.f, 50.f };
	m_fMoveSpeed = 3.f;
}

CItem::~CItem()
{

}