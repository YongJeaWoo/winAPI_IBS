#pragma once
#include "CScene.h"
#include "CTitlePlayer.h"
#include "CTitleZen.h"

class CImageObject;

class CTitle : public CScene
{
private:
	bool m_bIsRaise;
	CImageObject*	Iobj;
	CTitlePlayer*	Pobj;
	CTitleZen*		Zobj;


	float m_fAccTime;
	bool m_bIsFadeOut;
	int step = 0;			// Ŀư �ö󰡴� �ܰ�

public:
	CTitle();
	virtual ~CTitle();

	virtual void update();
	virtual void Enter();
	virtual void Exit();
};