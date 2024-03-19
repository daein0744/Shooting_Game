#pragma once
#define			WINCX			666
#define			WINCY			1000
#define			PURE			= 0
#define			OBJ_NOEVENT		0
#define			OBJ_DEAD		1
#define			PI		3.141592f
#define			RADIAN			* (PI / 180.f)
#define			GET_LIST(_type) CObjMgr::Get_Instance()->Get_List(_type)
#define			GET_UI() CUIMgr::Get_Instance()
#define			NULL_PLAYER CObjMgr::Get_Instance()->GET_LIST(PLAYER)->empty()

typedef struct tagInfo
{
	float	fX;
	float	fY;
	float	fCX;
	float	fCY;
}INFO;

template<typename T>
void Safe_Delete(T& Temp)
{
	if (Temp)
	{
		delete Temp;
		Temp = nullptr;
	}
}

template<typename T>
float Distance(T _f1, T _f2)
{
	return sqrtf(_f1 * _f1 + _f2 * _f2);
}

enum OBJID { PLAYER, BULLET, MONSTER, MOUSE, ITEM, SHIELD, MINIFLIGHT, BORDER, BOOM, END };
enum UIID { UI_HP, UI_BOOM, UI_BULLETTYPE, UI_GAMEOVER, UI_BULLETNUM, UI_SCORE, UI_LINE, UI_END };
enum SCENEID { SC_LOGIN, SC_STAGE, SC_GAMEOVER, SC_END };

enum TEAM { T_TEAM1, T_TEAM2, T_END };
enum BULLET_TYPE { BT_NORMAL, BT_TRACKBULLET, BT_SHOTGUN, BT_SBULLET, BT_SHIELD, BT_END };
enum SPAWN_POS { SP_POS1, SP_POS2, SP_POS3, SP_POS4, SP_POS5, SP_END };
enum STAGE { STAGE_1, STAGE_2, STAGE_END };
extern	HWND	g_hWnd;