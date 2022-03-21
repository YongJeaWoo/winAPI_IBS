#pragma once
#include "CScene.h"

class CPlayer;
class CMonster;

class CStage01 : public CScene
{
private:
	CPlayer*	pObj;
	CMonster*	mObj;

public:
	CStage01();
	virtual ~CStage01();

	virtual void update();
	virtual void render();
	virtual void Enter();
	virtual void Exit();
};

