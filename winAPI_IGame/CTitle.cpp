#include "framework.h"
#include "CTitle.h"
#include "CTitleGround.h"
#include "CImageObject.h"
#include "CDummyTitle.h"
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

	if (step == 0)	// 커튼이 내려가져 있을 때 시동작업
	{
		if (KeyDown(VK_SPACE))
		{
			m_bIsRaise = true;
			step++;
		}
	}
	else if (step == 1) // 커튼이 스페이스바에 의해 올라감
	{
		if (m_bIsRaise)
		{
			fPoint pos = Iobj->GetPos();
			pos.y -= 200.f * fDT;
			Iobj->SetPos(pos);
		}

		if (Iobj->GetPos().y < -800.f)
		{
			Pobj->Dance();
			step++;
		}
	}
	else if (step == 2)		// 커튼이 모두 올라갔을 때 페이드 아웃
	{
		if (KeyDown(VK_SPACE))
		{
			m_bIsFadeOut = true;
			CCameraManager::getInst()->FadeOut(3.f);
			step++;
		}
	}
	else if (step == 3)	// 페이드 아웃 후 씬 전환
	{
		m_fAccTime += fDT;
		if (m_fAccTime > 3.f)
		{
			ChangeScn(GROUP_SCENE::STAGE_01);
		}
	}

	if (Key(VK_ESCAPE))
	{
		PostQuitMessage(0);
	}

}

void CTitle::Enter()
{
	// 메인 타이틀
	CTitleGround* m_pTitleBackImage = new CTitleGround;
	m_pTitleBackImage->Load(L"BackTitle", L"texture\\Title\\BackGround_Title.png");
	m_pTitleBackImage->SetPos(fPoint(0, 0));
	m_pTitleBackImage->SetScale(fPoint(WINSIZEX, WINSIZEY));
	AddObject(m_pTitleBackImage, GROUP_GAMEOBJ::BACKGROUNDTITLE);

	// 올라가는 커튼
	Iobj = new CImageObject;
	Iobj->Load(L"UpTitle", L"texture\\Title\\UpTitle.png");
	Iobj->SetPos(fPoint(0.f, 0.f));
	Iobj->SetScale(fPoint(WINSIZEX, WINSIZEY));
	AddObject(Iobj, GROUP_GAMEOBJ::BACKGROUNDUP);

	// 메인 타이틀 일부분 가려주는 커튼
	CTitleGround* m_pTitleImage = new CTitleGround;
	m_pTitleImage->Load(L"Title", L"texture\\Title\\Title.png");
	m_pTitleImage->SetPos(fPoint(0, 0));
	m_pTitleImage->SetScale(fPoint(WINSIZEX, WINSIZEY));
	AddObject(m_pTitleImage, GROUP_GAMEOBJ::TITLE);

	// 오브젝트 생성
	Pobj = new CDummyTitle;
	Pobj->Load(L"DumPlayer", L"texture\\Title\\TitlePlayerAnimation.png");
	Pobj->SetPos(fPoint(WINSIZEX / 2, 550.f));
	Pobj->SetScale(fPoint(100.f, 100.f));
	AddObject(Pobj, GROUP_GAMEOBJ::DUMMYTITLE);
}

void CTitle::Exit()
{
	DeleteAll();
}