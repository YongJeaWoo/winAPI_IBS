#pragma once
#include "CState.h"

class CRunState : public CState
{
private:

public:
	CRunState(STATE_MON state);
	virtual	~CRunState();

	virtual void update();
	virtual void Enter();
	virtual void Exit();
};

