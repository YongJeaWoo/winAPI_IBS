#pragma once
#include "CScene.h"
#include "CPlayerTitle.h"

class CImageObject;

class CTitle : public CScene
{
private:
	bool m_bIsSpace;
	CImageObject* Iobj;
	CPlayerTitle* Pobj;

public:
	CTitle();
	virtual ~CTitle();

	virtual void update();
	virtual void Enter();
	virtual void Exit();

	virtual void GetPos(CImageObject* Iobj);
};