#include "framework.h"
#include "CTitleMig.h"
#include "CAnimator.h"
#include "CAnimation.h"

CTitleMig::CTitleMig()
{
	m_pImg = nullptr;

	CD2DImage* m_pPlayerImg = CResourceManager::getInst()->LoadD2DImage(L"TitleMig", L"texture\\Title\\TitleMighta.png");
	SetName(L"TitleMig");

	CreateAnimator();
	// Player
	GetAnimator()->CreateAnimation(L"TitleMigIdle", m_pPlayerImg, fPoint(0.f, 0.f), fPoint(28.f, 23.f), fPoint(0.f, 0.f), 5.f, 1);
	GetAnimator()->CreateAnimation(L"TitleMigDance", m_pPlayerImg, fPoint(0.f, 0.f), fPoint(28.f, 23.f), fPoint(28.f, 0.f), 0.5f, 2);
	GetAnimator()->Play(L"TitleMigIdle");

	CAnimation* pAni;
	pAni = GetAnimator()->FindAnimation(L"TitleMigDance");
	pAni->GetFrame(1).fptOffset = fPoint(0.f, -5.f);
}

CTitleMig::~CTitleMig()
{
}

CTitleMig* CTitleMig::Clone()
{
	return new CTitleMig(*this);
}

void CTitleMig::update()
{
	GetAnimator()->update();
}

void CTitleMig::render()
{
	component_render();
}

void CTitleMig::Load(const wstring& strKey, const wstring& strPath)
{
	m_pImg = CResourceManager::getInst()->LoadD2DImage(strKey, strPath);
}

void CTitleMig::Dance()
{
	GetAnimator()->Play(L"TitleMigDance");
}
