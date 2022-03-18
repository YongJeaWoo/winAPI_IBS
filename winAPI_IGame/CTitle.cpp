#include "framework.h"
#include "CTitle.h"
#include "CTitleGround.h"
#include "CImageObject.h"

CTitle::CTitle()
{
	m_bIsSpace = false;

}

CTitle::~CTitle()
{
}

void CTitle::update()
{
	


	if (KeyDown(VK_SPACE))
	{
		m_bIsSpace = true;
	}

	if (m_bIsSpace)
	{

	}

	if (Key(VK_ESCAPE))
		PostQuitMessage(0);
}

void CTitle::Enter()
{
	// 메인 타이틀
	CTitleGround* m_pTitleBackImage = new CTitleGround;
	m_pTitleBackImage->Load(L"BackTitle", L"texture\\background\\BackGround_Title.png");
	m_pTitleBackImage->SetPos(fPoint(0, 0));
	m_pTitleBackImage->SetScale(fPoint(WINSIZEX, WINSIZEY));
	AddObject(m_pTitleBackImage, GROUP_GAMEOBJ::BACKGROUNDTITLE);

	// 메인 타이틀 일부분 가려주는 커튼
	CTitleGround* m_pTitleImage = new CTitleGround;
	m_pTitleImage->Load(L"Title", L"texture\\background\\Title.png");
	m_pTitleImage->SetPos(fPoint(0, 0));
	m_pTitleImage->SetScale(fPoint(WINSIZEX, WINSIZEY));
	AddObject(m_pTitleImage, GROUP_GAMEOBJ::TITLE);
}

void CTitle::Exit()
{
	DeleteAll();
}