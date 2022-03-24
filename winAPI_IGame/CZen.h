#pragma once
#include "CGameObject.h"

class CD2DImage;
class AI;

struct MonInfo
{
	float	fSpeed;
	float	fHp;
	float	fRecogRange;
	float	fAtt;
};

enum class MON_TYPE
{
	NORMAL,
	SHOOT,


	SIZE,
};

typedef void(*MON_FUNC) (DWORD_PTR, DWORD_PTR);

class CZen : public CGameObject
{
private:
	MonInfo Info;
	AI*		m_pAI;

public:
	CZen();
	virtual ~CZen();
	virtual CZen* Clone();

	static CZen* Create(MON_TYPE type, fPoint pos);		// ∆—≈‰∏Æ ∆–≈œ

	virtual void render();
	virtual void update();

	float GetSpeed();
	const MonInfo& GetMonInfo();

	void SetSpeed(float speed);

	void SetAI(AI* ai);
	void SetMonInfo(const MonInfo& info);

	void OnCollisionEnter(CCollider* pOther);
};

