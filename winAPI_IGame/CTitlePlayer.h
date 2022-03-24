#pragma once
#include "CGameObject.h"
#include "CD2DImage.h"

class CTitlePlayer : public CGameObject
{
private:
	CD2DImage* m_pImg;

public:
	CTitlePlayer();
	~CTitlePlayer();

	virtual CTitlePlayer* Clone();

	virtual void update();
	virtual void render();

	void Load(const wstring& strKey, const wstring& strPath);

	virtual void Dance();
};