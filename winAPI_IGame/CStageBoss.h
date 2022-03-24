#pragma once
#include "CScene.h"

class CPlayer;
class CZen;

class CStageBoss : public CScene
{
private:

public:
	CStageBoss();
	virtual ~CStageBoss();

	virtual void update();
	virtual void Enter();
	virtual void Exit();
};

