#include "framework.h"
#include "CPlayerTitle.h"
#include "CTexture.h"
#include "CAnimation.h"
#include "CAnimator.h"
#include "CTitle.h"

CPlayerTitle::CPlayerTitle()
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

CPlayerTitle::~CPlayerTitle()
{
}

CPlayerTitle* CPlayerTitle::Clone()
{
    return new CPlayerTitle(*this);
}

void CPlayerTitle::update()
{
	GetAnimator()->update();
}

void CPlayerTitle::render()
{
	component_render();
}

void CPlayerTitle::Load(const wstring& strKey, const wstring& strPath)
{
	m_pImg = CResourceManager::getInst()->LoadD2DImage(strKey, strPath);
}

void CPlayerTitle::Dance()
{
	GetAnimator()->Play(L"JustDance");
}
