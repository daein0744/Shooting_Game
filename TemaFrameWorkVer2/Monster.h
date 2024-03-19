#pragma once
#include "Obj.h"
class CMonster : public CObj
{
public:
	CMonster();
	virtual ~CMonster();

	const SPAWN_POS& Get_SpawnType() const { return m_eSpawnPos; }
	int Get_Score() { return iScore; }
	bool Get_TakeBoom() { return m_bTakeBoom; }

	void Set_SpawnType(SPAWN_POS _eSpawn) { m_eSpawnPos = _eSpawn; }
	void Set_SpawnPos(SPAWN_POS _eSpawn);
	void Set_Score(int _iScore) { iScore = _iScore; }
	void Set_TakeBoom(bool _boom) { m_bTakeBoom = _boom; }

	void RandomSpawn();
	void BorderRange();
	virtual void MovePos1() PURE;
	virtual void MovePos2() PURE;
	virtual void MovePos3() PURE;
	virtual void MovePos4() PURE;
public:
	// 몬스터 점수 합산
	void SumScore();

protected:
	bool m_bTakeBoom;
	SPAWN_POS m_eSpawnPos;
	int iScore;
};

