#pragma once
#include "CGameObject.h"
#include "CD2DImage.h"

class CTitleZen : public CGameObject
{
private:
	CD2DImage* m_pImg;

public:
	CTitleZen();
	~CTitleZen();

	virtual CTitleZen* Clone();

	virtual void update();
	virtual void render();

	void Load(const wstring& strKey, const wstring& strPath);

	virtual void Dance();
};

