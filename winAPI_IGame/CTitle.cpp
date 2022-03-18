#include "framework.h"
#include "CTitle.h"
#include "CTitleGround.h"
#include "CTitleObject.h"

void CTitle::update()
{
	fPoint fptTitlePos = GetPos();
	fptTitlePos.y += GetScale().y / 2.f;

	int i = 0;

	// 위로 움직일 커튼
	CTitleGround* m_pUpImage = new CTitleGround;
	m_pUpImage->Load(L"UpTitle", L"texture\\background\\UpTitle.png");
	m_pUpImage->SetPos(fPoint(120.f, i));
	m_pUpImage->SetScale(fPoint(WINSIZEX - 240.f, WINSIZEY));
	m_pUpImage->GetPos();
	CreateObj(m_pUpImage, GROUP_GAMEOBJ::BACKGROUNDUP);

	if (Key(VK_SPACE))
	{
		// TODO : 의도대로 하고 싶다면 이게 아닌가 했는데 아님..
		for (int i = 300; i >= 0; i--)
			m_pUpImage->SetPos(fPoint(120.f, i));

		//ChangeScn(GROUP_SCENE::STAGE_01);
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