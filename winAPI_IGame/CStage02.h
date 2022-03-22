#pragma once
#include "CScene.h"

class CStage02 : public CScene
{
private:

public:
	CStage02();
	virtual ~CStage02();

	virtual void update();
	virtual void render();
	virtual void Enter();
	virtual void Exit();
};

