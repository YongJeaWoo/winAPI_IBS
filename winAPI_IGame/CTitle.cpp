#include "framework.h"
#include "CTitle.h"
#include "CBackGround.h"


void CTitle::Enter()
{
	CBackGround* m_pTitleImage = new CBackGround;
	m_pTitleImage->Load(L"Title", L"texture\\background\\Title.png");
	m_pTitleImage->SetPos(fPoint(0, 0));
	AddObject(m_pTitleImage, GROUP_GAMEOBJ::BACKGROUND);
}

void CTitle::Exit()
{
	DeleteAll();
}