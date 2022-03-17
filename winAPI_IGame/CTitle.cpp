#include "framework.h"
#include "CTitle.h"
#include "CTitleGround.h"

void CTitle::Enter()
{
	// 메인 타이틀
	/*CTitleGround* m_pTitleBackImage = new CTitleGround;
	m_pTitleBackImage->Load(L"BackTitle", L"texture\\background\\BackGround_Title.png");
	m_pTitleBackImage->SetPos(fPoint(0, 0));
	m_pTitleBackImage->SetScale(fPoint(WINSIZEX, WINSIZEY));
	AddObject(m_pTitleBackImage, GROUP_GAMEOBJ::BACKGROUNDTITLE);*/

	// 위로 움직일 커튼
	CTitleGround* m_pUpImage = new CTitleGround;
	m_pUpImage->Load(L"UpTitle", L"texture\\background\\UpTitle.png");
	m_pUpImage->SetPos(fPoint(120.f, 0));
	m_pUpImage->SetScale(fPoint(WINSIZEX - 240.f, WINSIZEY));
	AddObject(m_pUpImage, GROUP_GAMEOBJ::BACKGROUNDUP);

	// 메인 타이틀 일부분 가려주는 커튼
	CTitleGround* m_pTitleImage = new CTitleGround;
	m_pTitleImage->Load(L"Title", L"texture\\background\\Title.png");
	m_pTitleImage->SetPos(fPoint(0, 0));
	m_pTitleImage->SetScale(fPoint(WINSIZEX, WINSIZEY));
	AddObject(m_pTitleImage, GROUP_GAMEOBJ::TITLE);

	// 키가눌릴때 시작 하는 것을 구현을 못함
	if (Key(VK_SPACE))
	{
		// TODO : m_pUpImage 위로 올리기

		ChangeScn(GROUP_SCENE::STAGE_01);
	}

	else if (Key(VK_ESCAPE))
		PostQuitMessage(0);
}

void CTitle::Exit()
{
	DeleteAll();
}