#pragma once
#include "CGameObject.h"

class CD2DImage;
class AI;

struct sMonInfo
{
	float fSpeed;
	float fHp;
	float fRecogRange;
	float fAtt;
};

enum class MON_TYPE
{
	NORMAL,
	RANGE,


	SIZE,
};

typedef void(*MON_FUNC) (DWORD_PTR, DWORD_PTR);

class CMonster : public CGameObject
{
private:
	sMonInfo m_sInfo;
	AI* m_pAI;

public:
	CMonster();
	virtual ~CMonster();
	virtual CMonster* Clone();

	static CMonster* Create(MON_TYPE type, fPoint pos);		// ∆—≈‰∏Æ ∆–≈œ

	virtual void render();
	virtual void update();

	float GetSpeed();
	const sMonInfo& GetMonInfo();

	void SetSpeed(float speed);

	void SetAI(AI* ai);
	void SetMonInfo(const sMonInfo& info);

	void OnCollisionEnter(CCollider* pOther);
};

