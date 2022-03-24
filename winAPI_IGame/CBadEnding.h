#pragma once
#include "CScene.h"

class CBadEnding : public CScene
{
private:

public:
	CBadEnding();
	~CBadEnding();

	virtual void update();
	virtual void Enter();
	virtual void Exit();
};

