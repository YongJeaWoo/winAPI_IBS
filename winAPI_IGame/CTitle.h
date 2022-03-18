#pragma once
#include "CScene.h"

class CImageObject;

class CTitle : public CScene
{
private:
	bool m_bIsSpace;
	CImageObject* Iobj;

public:
	CTitle();
	virtual ~CTitle();

	virtual void update();
	virtual void Enter();
	virtual void Exit();
};

