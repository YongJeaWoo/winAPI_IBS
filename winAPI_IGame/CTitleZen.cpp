#include "framework.h"
#include "CTitleZen.h"
#include "CAnimator.h"
#include "CAnimation.h"

CTitleZen::CTitleZen()
{
	m_pImg = nullptr;

	CD2DImage* m_pZenTurn = CResourceManager::getInst()->LoadD2DImage(L"TitleZenTurn", L"texture\\Title\\TitleZenTurn.png");
	SetName(L"TitleZenTurn");

	/*CD2DImage* m_pZenDance = CResourceManager::getInst()->LoadD2DImage(L"TitleZenDance", L"texture\\title\\TitleZenDance.png");
	SetName(L"TitleZenDance");*/

	CreateAnimator();
	GetAnimator()->CreateAnimation(L"TitleZenTurn", m_pZenTurn, fPoint(128.f, 21.f), fPoint(32.f, 21.f), fPoint(-32.f, 0.f), 0.8f, 4);
	GetAnimator()->CreateAnimation(L"ZenDance", m_pZenTurn, fPoint(0.f, 0.f), fPoint(32.f, 21.f), fPoint(160.f, 0.f), 0.5f, 2);
	GetAnimator()->Play(L"TitleZenTurn");

	CAnimation* pAni;
	pAni = GetAnimator()->FindAnimation(L"ZenDance");
	pAni->GetFrame(1).fptOffset = fPoint(0.f, -5.f);
}

CTitleZen::~CTitleZen()
{
}

CTitleZen* CTitleZen::Clone()
{
	return new CTitleZen(*this);
}

void CTitleZen::update()
{
	GetAnimator()->update();
}

void CTitleZen::render()
{
	component_render();
}

void CTitleZen::Load(const wstring& strKey, const wstring& strPath)
{
	m_pImg = CResourceManager::getInst()->LoadD2DImage(strKey, strPath);
}

void CTitleZen::Dance()
{
	GetAnimator()->Play(L"ZenDance");
}
