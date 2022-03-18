#include "framework.h"
#include "CTitleGround.h"
#include "CD2DImage.h"

CTitleGround::CTitleGround()
{
    m_pImg = nullptr;
}

CTitleGround::~CTitleGround()
{

}

CTitleGround* CTitleGround::Clone()
{
    return nullptr;
}

void CTitleGround::update()
{
}

void CTitleGround::render()
{
    if (nullptr == m_pImg)
    {
        return;
    }
    fPoint pos = GetPos();
    fPoint scale = GetScale();
    fPoint renderPos = CCameraManager::getInst()->GetRenderPos(pos);
    renderPos = pos + (renderPos - pos) / 5;    // 배경은 살짝 느리게 이동

    CRenderManager::getInst()->RenderImage(
        m_pImg,
        renderPos.x,
        renderPos.y,
        renderPos.x + scale.x,
        renderPos.y + scale.y
    );
}

void CTitleGround::SetDir(fVec2 vec)
{
    m_fvDir = vec.normalize();
}

void CTitleGround::Load(wstring strKey, wstring strPath)
{
    m_pImg = CResourceManager::getInst()->LoadD2DImage(strKey, strPath);
    SetScale(fPoint(m_pImg->GetWidth() * 4.f, m_pImg->GetHeight() * 4.f));
}
