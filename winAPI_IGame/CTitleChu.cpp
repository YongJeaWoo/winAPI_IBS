#include "framework.h"
#include "CTitleChu.h"
#include "CAnimator.h"
#include "CAnimation.h"

CTitleChu::CTitleChu()
{
	m_pImg = nullptr;

	CD2DImage* m_pPlayerImg = CResourceManager::getInst()->LoadD2DImage(L"TitlePlayer", L"texture\\Title\\TitlePlayerAnimation.png");
	SetName(L"TitlePlayer");

	CreateAnimator();
	// Player
	GetAnimator()->CreateAnimation(L"PlayerStand", m_pPlayerImg, fPoint(54.f, 0.f), fPoint(27.f, 26.f), fPoint(0.f, 0.f), 5.f, 1);
	GetAnimator()->CreateAnimation(L"PlayerDance", m_pPlayerImg, fPoint(0.f, 0.f), fPoint(27.f, 26.f), fPoint(27.f, 0.f), 0.5f, 2);
	GetAnimator()->Play(L"PlayerStand");

	CAnimation* pAni;
	pAni = GetAnimator()->FindAnimation(L"PlayerDance");
	pAni->GetFrame(1).fptOffset = fPoint(0.f, -5.f);
}

CTitleChu::~CTitleChu()
{
}

CTitleChu* CTitleChu::Clone()
{
	return new CTitleChu(*this);
}

void CTitleChu::update()
{
	GetAnimator()->update();
}

void CTitleChu::render()
{
	component_render();
}

void CTitleChu::Load(const wstring& strKey, const wstring& strPath)
{
	m_pImg = CResourceManager::getInst()->LoadD2DImage(strKey, strPath);
}

void CTitleChu::Dance()
{
	GetAnimator()->Play(L"PlayerDance");
}
