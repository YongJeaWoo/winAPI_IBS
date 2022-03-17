#pragma once
#include "CGameObject.h"

class CD2DImage;
class AI;

class CMonster : public CGameObject
{
private:
	CD2DImage* m_pImg;
	float m_fSpeed;
	int m_iHP;

	AI* m_pAI;

public:
	CMonster();
	virtual ~CMonster();
	virtual CMonster* Clone();

	virtual void render();
	virtual void update();

	float GetSpeed();

	void SetSpeed(float speed);

	void SetAI(AI* ai);

	void OnCollisionEnter(CCollider* pOther);
};

