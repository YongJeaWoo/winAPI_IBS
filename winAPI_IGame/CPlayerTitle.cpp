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
	GetAnimator()->CreateAnimation(L"JustDance", m_pImg, fPoint(0.f, 0.f), fPoint(30.f, 24.f), fPoint(30.f, 0.f), 1.f, 4);
	GetAnimator()->Play(L"JustDance");
	
	/*CAnimation* pAni;
	pAni = GetAnimator()->FindAnimation(L"JustDance");
	pAni->GetFrame(1).fptOffset = fPoint(0.f, -10.f);
	pAni = GetAnimator()->FindAnimation(L"JustDance");
	pAni->GetFrame(1).fptOffset = fPoint(0.f, -10.f);*/
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
