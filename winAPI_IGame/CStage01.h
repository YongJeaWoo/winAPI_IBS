#pragma once
#include "CScene.h"

class CPlayer;
class CMonster;

class CStage01 : public CScene
{
private:

public:
	CStage01();
	virtual ~CStage01();

	virtual void update();
	virtual void Enter();
	virtual void Exit();
};

