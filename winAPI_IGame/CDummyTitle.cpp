#include "framework.h"
#include "CDummyTitle.h"
#include "CTexture.h"
#include "CAnimation.h"
#include "CAnimator.h"
#include "CTitle.h"

CDummyTitle::CDummyTitle()
{
    m_pImg = nullptr;

	CD2DImage* m_pImg = CResourceManager::getInst()->LoadD2DImage(L"TitlePlayer", L"texture\\Title\\TitlePlayerAnimation.png");
	SetName(L"TitlePlayer");

	CreateAnimator();
	GetAnimator()->CreateAnimation(L"JustStand",	m_pImg, fPoint(54.f, 0.f), fPoint(27.f, 26.f), fPoint(0.f, 0.f), 5.f, 1);
	GetAnimator()->CreateAnimation(L"JustDance",	m_pImg, fPoint(0.f, 0.f), fPoint(27.f, 26.f), fPoint(27.f, 0.f), 0.5f, 2);
	GetAnimator()->Play(L"JustStand");

	CAnimation* pAni;
	pAni = GetAnimator()->FindAnimation(L"JustDance");
	pAni->GetFrame(1).fptOffset = fPoint(0.f, -5.f);
}

CDummyTitle::~CDummyTitle()
{
}

CDummyTitle* CDummyTitle::Clone()
{
    return new CDummyTitle(*this);
}

void CDummyTitle::update()
{
	GetAnimator()->update();
}

void CDummyTitle::render()
{
	component_render();
}

void CDummyTitle::Load(const wstring& strKey, const wstring& strPath)
{
	m_pImg = CResourceManager::getInst()->LoadD2DImage(strKey, strPath);
}

void CDummyTitle::Dance()
{
	GetAnimator()->Play(L"JustDance");
}
