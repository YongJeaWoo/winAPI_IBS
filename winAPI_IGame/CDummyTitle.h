#pragma once
#include "CGameObject.h"

class CDummyTitle : public CGameObject
{
private:
	CD2DImage* m_pImg;

public:
	CDummyTitle();
	~CDummyTitle();

	virtual CDummyTitle* Clone();

	virtual void update();
	virtual void render();

	void Load(const wstring& strKey, const wstring& strPath);

	virtual void Dance();
};