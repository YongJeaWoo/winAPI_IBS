#include "framework.h"
#include "CPlayerTitle.h"

CPlayerTitle::CPlayerTitle()
{
    m_pImg = nullptr;
    m_bIsRaise = false;
}

CPlayerTitle::~CPlayerTitle()
{
}

CPlayerTitle* CPlayerTitle::Clone()
{
    return nullptr;
}

void CPlayerTitle::update()
{
}

void CPlayerTitle::render()
{
	CRenderManager::getInst()->RenderImage(
		m_pImg,
		GetPos().x,
		GetPos().y,
		GetPos().x + GetScale().x,
		GetPos().y + GetScale().y);
}

void CPlayerTitle::Load(const wstring& strKey, const wstring& strPath)
{
	m_pImg = CResourceManager::getInst()->LoadD2DImage(strKey, strPath);
}
