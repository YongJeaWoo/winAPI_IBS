#pragma once
#include "CGameObject.h"
class CTitleGround : public CGameObject
{
private:
	CD2DImage* m_pImg;

public:
	CTitleGround();
	virtual ~CTitleGround();

	virtual CTitleGround* Clone();
	virtual void update();
	virtual void render();

	void Load(wstring strKey, wstring strPath);
};

