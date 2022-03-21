#include "framework.h"
#include "CPlayerTitle.h"
#include "CTexture.h"
#include "CAnimation.h"
#include "CAnimator.h"

CPlayerTitle::CPlayerTitle()
{
    m_pImg = nullptr;
    m_bIsRaise = false;

	CD2DImage* m_pImg = CResourceManager::getInst()->LoadD2DImage(L"TitlePlayer", L"texture\\Title\\TitlePlayerAnimation.png");
	SetName(L"TitlePlayer");

	CreateAnimator();
	GetAnimator()->CreateAnimation(L"JustStand",	m_pImg, fPoint(92.f, 0.f), fPoint(30.f, 25.f), fPoint(30.f, 0.f), 5.f, 1);
	GetAnimator()->CreateAnimation(L"LeftDance",	m_pImg, fPoint(0.f, 0.f), fPoint(30.f, 24.f), fPoint(30.f, 0.f), 0.5f, 0);
	GetAnimator()->CreateAnimation(L"FaceDance",	m_pImg, fPoint(0.f, 0.f), fPoint(30.f, 24.f), fPoint(30.f, 0.f), 0.5f, 1);
	GetAnimator()->CreateAnimation(L"RightDance",	m_pImg, fPoint(0.f, 0.f), fPoint(30.f, 24.f), fPoint(30.f, 0.f), 0.5f, 2);
	GetAnimator()->Play(L"JustStand");

	/*CAnimation* pAni;
	pAni = GetAnimator()->FindAnimation(L"LeftDance");
	pAni->GetFrame(1).fptOffset = fPoint(-10.f, 0.f);
	pAni = GetAnimator()->FindAnimation(L"FaceDance");
	pAni->GetFrame(1).fptOffset = fPoint(0.f, 0.f);
	pAni = GetAnimator()->FindAnimation(L"RightDance");
	pAni->GetFrame(1).fptOffset = fPoint(10.f, 0.f);*/
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
