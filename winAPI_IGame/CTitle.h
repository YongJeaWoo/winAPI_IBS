#pragma once
#include "CScene.h"
#include "CTitleObject.h"

class CButtonUI;

class CTitle : public CScene, public CTitleObject
{
public:
	virtual void update();
	virtual void Enter();
	virtual void Exit();
};

