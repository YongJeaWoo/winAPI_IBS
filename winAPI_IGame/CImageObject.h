#pragma once
#include "CGameObject.h"

class CD2DImage;

class CImageObject : public CGameObject
{
private:
	CD2DImage* m_pImg;
	bool m_bIsRaise;

public:
	CImageObject();
	virtual ~CImageObject();

	virtual CImageObject* Clone();

	virtual void update();
	virtual void render();

	void Load(const wstring& strKey, const wstring& strPath);
};

