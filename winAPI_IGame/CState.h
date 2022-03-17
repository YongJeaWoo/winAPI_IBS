#pragma once

class AI;

class CState
{
	friend class AI;

private:
	AI* m_pOwnerAi;
	MON_STATE m_eState;

public:
	CState(MON_STATE state);
	virtual ~CState();

	AI* GetOwner();

	virtual void update() = 0;
	virtual void Enter() = 0;
	virtual void Exit() = 0;
};

