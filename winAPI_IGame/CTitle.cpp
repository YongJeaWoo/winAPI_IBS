#include "framework.h"
#include "CTitle.h"
#include "CTitleGround.h"

void CTitle::Enter()
{
	// ���� Ÿ��Ʋ
	/*CTitleGround* m_pTitleBackImage = new CTitleGround;
	m_pTitleBackImage->Load(L"BackTitle", L"texture\\background\\BackGround_Title.png");
	m_pTitleBackImage->SetPos(fPoint(0, 0));
	m_pTitleBackImage->SetScale(fPoint(WINSIZEX, WINSIZEY));
	AddObject(m_pTitleBackImage, GROUP_GAMEOBJ::BACKGROUNDTITLE);*/

	// ���� ������ Ŀư
	CTitleGround* m_pUpImage = new CTitleGround;
	m_pUpImage->Load(L"UpTitle", L"texture\\background\\UpTitle.png");
	m_pUpImage->SetPos(fPoint(120.f, 0));
	m_pUpImage->SetScale(fPoint(WINSIZEX - 240.f, WINSIZEY));
	AddObject(m_pUpImage, GROUP_GAMEOBJ::BACKGROUNDUP);

	// ���� Ÿ��Ʋ �Ϻκ� �����ִ� Ŀư
	CTitleGround* m_pTitleImage = new CTitleGround;
	m_pTitleImage->Load(L"Title", L"texture\\background\\Title.png");
	m_pTitleImage->SetPos(fPoint(0, 0));
	m_pTitleImage->SetScale(fPoint(WINSIZEX, WINSIZEY));
	AddObject(m_pTitleImage, GROUP_GAMEOBJ::TITLE);

	// Ű�������� ���� �ϴ� ���� ������ ����
	if (Key(VK_SPACE))
	{
		// TODO : m_pUpImage ���� �ø���

		ChangeScn(GROUP_SCENE::STAGE_01);
	}

	else if (Key(VK_ESCAPE))
		PostQuitMessage(0);
}

void CTitle::Exit()
{
	DeleteAll();
}