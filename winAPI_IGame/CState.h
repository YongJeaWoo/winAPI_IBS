#pragma once

class AI;
class CZen;

class CState
{
	friend class AI;

private:
	AI* m_pOwnerAI;
	STATE_MON m_eState;

public:
	CState(STATE_MON state);
	virtual ~CState();

	AI* GetOwnerAI();
	STATE_MON GetType();
	CZen* GetMonster();

	virtual void update() = 0;
	virtual void Enter() = 0;
	virtual void Exit() = 0;
};

