#include "framework.h"
#include "CTitle.h"
#include "CTitleGround.h"
#include "CImageObject.h"
#include "CPlayerTitle.h"
#include "CAnimation.h"
#include "CAnimator.h"

CTitle::CTitle()
{
	m_bIsRaise = false;
	Iobj = nullptr;
	Pobj = nullptr;
	m_fAccTime = 0.f;
	m_bIsFadeOut = false;
}

CTitle::~CTitle()
{
}

void CTitle::update()
{
	CScene::update();
	if (KeyDown(VK_SPACE))
	{
		m_bIsRaise = true;
	}

	// �����̽� �� �� ���� �� �ø���
	if (m_bIsRaise)
	{
		fPoint pos = Iobj->GetPos();
		pos.y -= 100.f * fDT;
		Iobj->SetPos(pos);
	}

	// �ش� ���� ���� ��� ������Ʈ ���ְ� �÷��̾� �ִϸ��̼� ����
	if (Iobj->GetPos().y < -800.f)
	{
		m_bIsRaise = false;

		// TODO:
		Pobj->Dance();

		// �ѹ� �� ������ �� �� ��ȯ
		if (KeyDown(VK_SPACE))
		{
			m_bIsRaise = true;
			m_fAccTime += fDT;
			if (!m_bIsFadeOut)
			{
				m_bIsFadeOut = true;
				CCameraManager::getInst()->FadeOut(3.f);
			}
		}

		if (m_fAccTime > 3.f)
			ChangeScn(GROUP_SCENE::STAGE_01);
	}

	if (Key(VK_ESCAPE))
		PostQuitMessage(0);
}

void CTitle::Enter()
{
	// ���� Ÿ��Ʋ
	CTitleGround* m_pTitleBackImage = new CTitleGround;
	m_pTitleBackImage->Load(L"BackTitle", L"texture\\Title\\BackGround_Title.png");
	m_pTitleBackImage->SetPos(fPoint(0, 0));
	m_pTitleBackImage->SetScale(fPoint(WINSIZEX, WINSIZEY));
	AddObject(m_pTitleBackImage, GROUP_GAMEOBJ::BACKGROUNDTITLE);

	// �ö󰡴� Ŀư
	Iobj = new CImageObject;
	Iobj->Load(L"UpTitle", L"texture\\Title\\UpTitle.png");
	Iobj->SetPos(fPoint(0.f, 0.f));
	Iobj->SetScale(fPoint(WINSIZEX, WINSIZEY));
	AddObject(Iobj, GROUP_GAMEOBJ::BACKGROUNDUP);

	// ������Ʈ ����
	Pobj = new CPlayerTitle;
	Pobj->Load(L"TitlePlayer", L"texture\\Title\\TitlePlayerAnimation.png");
	Pobj->SetPos(fPoint(WINSIZEX / 2, 550.f));
	Pobj->SetScale(fPoint(100.f, 100.f));
	AddObject(Pobj, GROUP_GAMEOBJ::TITLEPLAYER);

	// ���� Ÿ��Ʋ �Ϻκ� �����ִ� Ŀư
	CTitleGround* m_pTitleImage = new CTitleGround;
	m_pTitleImage->Load(L"Title", L"texture\\Title\\Title.png");
	m_pTitleImage->SetPos(fPoint(0, 0));
	m_pTitleImage->SetScale(fPoint(WINSIZEX, WINSIZEY));
	AddObject(m_pTitleImage, GROUP_GAMEOBJ::TITLE);
}

void CTitle::Exit()
{
	DeleteAll();
}