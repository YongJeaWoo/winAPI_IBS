#pragma once
#include "CGameObject.h"

class CD2DImage;

class CPlayer : public CGameObject
{
private:
	float m_fSpeed = 500;

	void CreateMissile();

public:
	CPlayer();
	~CPlayer();
	virtual CPlayer* Clone();

	virtual void update();
	virtual void render();
};

