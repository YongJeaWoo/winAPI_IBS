#pragma once
#include "CGameObject.h"

class CD2DImage;

class CMap : public CGameObject
{
private:
	CD2DImage* m_pImg;

public:
	CMap();
	virtual ~CMap();

	virtual CMap* Clone();
	virtual void update();
	virtual void render();

	void Load(wstring strKey, wstring strPath);
};

