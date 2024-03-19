#pragma once
#include "define.h"
#include "Obj.h"
#include "UI.h"
#include "Scene.h"

template<typename T>
class CAbstractFactory
{
public:
	CAbstractFactory() {}
	~CAbstractFactory() {}

public:
	static CObj*		Create()
	{
		CObj*		pObj = new T;
		pObj->Initialize();

		OBJID eObjID = pObj->Get_ObjID();
		switch (eObjID)
		{
		case PLAYER:
			pObj->Set_Team(T_TEAM1);
			break;
		case MONSTER:
			pObj->Set_Team(T_TEAM2);
			break;
		default:
			break;
		}

		return pObj;
	}

	static CObj*		Create(float _fX, float _fY)
	{
		CObj*		pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(_fX, _fY);
		pObj->Set_CollisionPos(_fX, _fY);
		OBJID eObjID = pObj->Get_ObjID();
		switch (eObjID)
		{
		case PLAYER:
			pObj->Set_Team(T_TEAM1);
			break;
		case MONSTER:
			pObj->Set_Team(T_TEAM2);
			break;
		default:
			break;
		}
		return pObj;
	}

	static CUI*		CreateUI(float _fX, float _fY)
	{
		CUI*		pUI = new T;
		pUI->Initialize();
		pUI->Set_PosX(_fX);
		pUI->Set_PosY(_fY);

		return pUI;
	}

	static CScene* CreateScene()
	{
		CScene*		pScene = new T;
		pScene->Initialize();
		// 씬은 설정할 위치같은게 없음.

		return pScene;
	}

	//static CObj*		CreateBullet(float _fX, float _fY, float _fAngle)
	//{
	//	CObj*		pObj = new T;
	//	pObj->Initialize();
	//	pObj->Set_Pos(_fX, _fY);
	//	pObj->Set_Angle(_fAngle);
	//	return pObj;
	//}
};