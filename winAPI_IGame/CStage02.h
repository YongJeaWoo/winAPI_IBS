#pragma once
#include "CScene.h"

class CPlayer;
class CZen;

class CStage02 : public CScene
{
private:

public:
	CStage02();
	virtual ~CStage02();

	virtual void update();
	virtual void Enter();
	virtual void Exit();
};

