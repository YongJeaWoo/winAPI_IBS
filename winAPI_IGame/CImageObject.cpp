#include "framework.h"
#include "CImageObject.h"

CImageObject::CImageObject()
{
	m_pImg = CResourceManager::getInst()->LoadD2DImage(L"Title", L"texture\\background\\UpTitle.png");
	m_bIsRaise = false;

	SetPos(fPoint(0.f, 0.f));
	
}

CImageObject::~CImageObject()
{
}

CImageObject* CImageObject::Clone()
{
	return nullptr;
}

void CImageObject::update()
{
	if (KeyDown(VK_SPACE))
	{
		m_bIsRaise = true;
	}
}

void CImageObject::render()
{
}
