#include "framework.h"
#include "CTitleMon.h"
#include "CAnimator.h"
#include "CAnimation.h"

CTitleMon::CTitleMon()
{
	m_pImg = nullptr;

	CD2DImage* m_pPlayerImg = CResourceManager::getInst()->LoadD2DImage(L"TitleMon", L"texture\\Title\\TitleMon.png");
	SetName(L"TitleMon");

	CreateAnimator();
	// Player
	GetAnimator()->CreateAnimation(L"TitleMonIdle", m_pPlayerImg, fPoint(0.f, 0.f), fPoint(29.f, 22.f), fPoint(0.f, 0.f), 5.f, 1);
	GetAnimator()->CreateAnimation(L"TitleMonDance", m_pPlayerImg, fPoint(0.f, 0.f), fPoint(29.f, 22.f), fPoint(29.f, 0.f), 0.5f, 2);
	GetAnimator()->Play(L"TitleMonIdle");

	CAnimation* pAni;
	pAni = GetAnimator()->FindAnimation(L"TitleMonDance");
	pAni->GetFrame(1).fptOffset = fPoint(-5.f, -5.f);
}

CTitleMon::~CTitleMon()
{
}

CTitleMon* CTitleMon::Clone()
{
	return new CTitleMon(*this);
}

void CTitleMon::update()
{
	GetAnimator()->update();
}

void CTitleMon::render()
{
	component_render();
}

void CTitleMon::Load(const wstring& strKey, const wstring& strPath)
{
	m_pImg = CResourceManager::getInst()->LoadD2DImage(strKey, strPath);
}

void CTitleMon::Dance()
{
	GetAnimator()->Play(L"TitleMonDance");
}
