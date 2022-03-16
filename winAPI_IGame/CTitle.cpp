#include "framework.h"
#include "CTitle.h"
#include "CBackGround.h"

void CTitle::Enter()
{
	CBackGround* m_pTitleImage = new CBackGround;
	m_pTitleImage->Load(L"Title", L"texture\\background\\Title.png");
	m_pTitleImage->SetPos(fPoint(0, 0));
	m_pTitleImage->SetScale(fPoint(WINSIZEX, WINSIZEY));
	AddObject(m_pTitleImage, GROUP_GAMEOBJ::BACKGROUND);

	if (Key(VK_SPACE))
		ChangeScn(GROUP_SCENE::STAGE_01);

	else if (Key(VK_ESCAPE))
		PostQuitMessage(0);
}

void CTitle::Exit()
{
	DeleteAll();
}