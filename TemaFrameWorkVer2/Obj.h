#pragma once

#include "define.h"

class CObj
{
public:
	CObj();
	~CObj();
	virtual void Initialize() PURE;
	virtual int Update() PURE;
	virtual void Late_Update() PURE;
	virtual void Render(HDC _hDC) PURE;
	virtual void Release() PURE;

public:
	const INFO& Get_Info() const { return m_tInfo; }
	const INFO& Get_CollisionInfo(int i = 0) const { return m_vecCollisionPos[i]; }
	const RECT& Get_Rect() const { return m_tRect; }
	const RECT& Get_CollisionRect(int i = 0) const { return m_vecCollisionBox[i]; }
	const bool& Get_Dead() const { return m_bDead; }
	const bool& Get_IsDamage() const { return m_bIsDamage; }
	const float& Get_MoveSpeed() const { return m_fMoveSpeed; }
	const float& Get_AttackSpeed() const { return m_fAttackSpeed; }
	const float& Get_TakeDamage() const { return m_fTakeDamage; }
	const float& Get_PosX() const { return m_tInfo.fX; }
	const float& Get_PosY() const { return m_tInfo.fY; }
	const float& Get_CollisionPosX(int i = 0) const { return m_vecCollisionPos[i].fX; }
	const float& Get_CollisionPosY(int i = 0) const { return m_vecCollisionPos[i].fY; }
	const float& Get_DirY() const { return m_fDirY; }
	const float& Get_DirX() const { return m_fDirX; }
	const float& Get_Angle() const { return m_fAngle; }
	const float& Get_HP() const { return m_fHP; }
	const OBJID& Get_ObjID() const { return m_eObjID; }
	const TEAM& Get_Team() const { return m_eTeam; }
	const BULLET_TYPE& Get_BulletType() const { return m_eBulletType; }
	const bool& Get_IsCreateBullet() const { return m_bCreateBullet; }

	void Set_PosX(float _fX) { m_tInfo.fX += _fX; }
	void Set_PosY(float _fY) { m_tInfo.fY += _fY; }
	void Set_Info(INFO _tInfo) { m_tInfo = _tInfo; }
	void Set_CollisionInfo(INFO _tInfo, int i = 0) { m_vecCollisionPos[i] = _tInfo; }
	void Set_Rect(RECT _tRect) { m_tRect = _tRect; }
	void Set_CollisionRect(RECT _tRect, int i = 0) { m_vecCollisionBox[i] = _tRect; }
	void Set_Dead(bool _bDead) { m_bDead = _bDead; }
	void Set_IsDamage(bool _bIsDamage) { m_bIsDamage = _bIsDamage; }
	void Set_MoveSpeed(float _fMoveSpeed) { m_fMoveSpeed = _fMoveSpeed; }
	void Set_AttackSpeed(float _fAttackSpeed) { m_fAttackSpeed = _fAttackSpeed; }
	void Set_Speed(float _fMoveSpeed) { m_fMoveSpeed = _fMoveSpeed; }
	void Set_TakeDamage(float _bTakeDamage) { m_fTakeDamage = _bTakeDamage; }
	void Set_Pos(float _fX, float _fY) { m_tInfo.fX = _fX; m_tInfo.fY = _fY; }
	void Set_CollisionPos(float _fX, float _fY, int i = 0) { m_vecCollisionPos[i].fX = _fX, m_vecCollisionPos[i].fY = _fY; }
	void Set_Angle(float _fAngle) { m_fAngle = _fAngle; }
	void Set_DirX(float _fDirX) { m_fDirX = _fDirX; }
	void Set_DirY(float _fDirY) { m_fDirY = _fDirY; }
	void Set_HP(float _fHP) { m_fHP = _fHP; }
	void Set_ObjID(OBJID _eObjID) { m_eObjID = _eObjID; }
	void Set_Team(TEAM _eTeam) { m_eTeam = _eTeam; }
	void Set_BulletType(BULLET_TYPE _eBulletType) { m_eBulletType = _eBulletType; }
	void Set_Size(float _fCX, float _fCY) { m_tInfo.fCX = _fCX; m_tInfo.fCY = _fCY; }
	void Set_IsCreateBullet(bool _bCreateBullet) { m_bCreateBullet = _bCreateBullet; }
	void Set_CollisionPosX(float _fCollisionPosX) { m_vecCollisionPos[0].fX = _fCollisionPosX; }
	void Set_CollisionPosY(float _fCollisionPosY) { m_vecCollisionPos[0].fY = _fCollisionPosY; }

public:
	void Update_Rect();
	void Take_Damage(float _fDamage);
	CObj* SearchNearObj(list<CObj*>* _pObjList);
	void CalCulateAngle(CObj* _pDest);
	virtual void MakeCollisionBox();
	virtual void Create_Bullet(float _fAngle = 90.f, TEAM _eTeam = T_TEAM1, float _fAttackSpeed = 0.f
							 , float _moveSpeed = 10.f, float _fX = 0.f, float _fY = 0.f);
	void DrawCollision(HDC _hdc); // 충돌박스 랜더용 함수
	void MoveX(float _fMoveSpeed);
	void MoveX(float _fMoveSpeed, float _fAngle);
	void MoveY(float _fMoveSpeed);
	void MoveY(float _fMoveSpeed, float _fAngle);
	void CalculateCollisionPos(float _fX, float _fY, float _fCX, float _fCY, int i = 0);
	void ReverseDirX();// 방향반전함수
	void ReverseDirY();

protected:
	INFO m_tInfo;
	RECT m_tRect;
	OBJID m_eObjID;

	float m_fMoveSpeed;
	bool m_bDead;
	float m_fTakeDamage; // 데미지 수치
	bool m_bIsDamage; // 데미지 받았는지 여부
	float m_fHP;
	float m_fAngle;
	float m_fDirX;
	float m_fDirY;
	float m_fLentgh;
	float m_fAttackSpeed;
	bool m_bCreateBullet;
	CObj* m_pPlayer;
	BULLET_TYPE m_eBulletType;
	TEAM m_eTeam;
	DWORD CreateTime;
	vector<INFO> m_vecCollisionPos;
	vector<RECT> m_vecCollisionBox;
};