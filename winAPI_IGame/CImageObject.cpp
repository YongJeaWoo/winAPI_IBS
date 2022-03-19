#include "framework.h"
#include "CImageObject.h"

CImageObject::CImageObject()
{
	m_pImg = nullptr;
	m_bIsRaise = false;
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
}

void CImageObject::render()
{
	CRenderManager::getInst()->RenderImage(
		m_pImg,
		GetPos().x,
		GetPos().y,
		GetPos().x + GetScale().x,
		GetPos().y + GetScale().y);
}

void CImageObject::Load(const wstring& strKey, const wstring& strPath)
{
	m_pImg = CResourceManager::getInst()->LoadD2DImage(strKey, strPath);
}
