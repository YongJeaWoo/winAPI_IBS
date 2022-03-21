#include "framework.h"
#include "CTitle.h"
#include "CTitleGround.h"
#include "CImageObject.h"
#include "CPlayerTitle.h"
#include "CAnimation.h"
#include "CAnimator.h"

// start
CTitle::CTitle()
{
	m_bIsSpace = false;
	Iobj = nullptr;
	Pobj = nullptr;
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

	// 스페이스 한 번 누를 때 올리기
	if (m_bIsSpace)
	{
		fPoint pos = Iobj->GetPos();
		pos.y -= 100.f * fDT;
		Iobj->SetPos(pos);
	}

	// 해당 범위 갔을 경우 오브젝트 없애고 플레이어 애니메이션 구현
	if (Iobj->GetPos().y < -1000.f)
	{
		m_bIsSpace = false;

		// TODO : 여기서 오브젝트 댄스 적용


		// 한번 더 눌렀을 때 씬 전환
		if (KeyDown(VK_SPACE))
		{
			m_bIsSpace = true;
			ChangeScn(GROUP_SCENE::START);
		}
	}

	if (Key(VK_ESCAPE))
		PostQuitMessage(0);
}

void CTitle::Enter()
{
	// 메인 타이틀
	CTitleGround* m_pTitleBackImage = new CTitleGround;
	m_pTitleBackImage->Load(L"BackTitle", L"texture\\Title\\BackGround_Title.png");
	m_pTitleBackImage->SetPos(fPoint(0, 0));
	m_pTitleBackImage->SetScale(fPoint(WINSIZEX, WINSIZEY));
	AddObject(m_pTitleBackImage, GROUP_GAMEOBJ::BACKGROUNDTITLE);

	Iobj = new CImageObject;
	Iobj->Load(L"UpTitle", L"texture\\Title\\UpTitle.png");
	Iobj->SetPos(fPoint(0.f, 0.f));
	Iobj->SetScale(fPoint(WINSIZEX, WINSIZEY));
	AddObject(Iobj, GROUP_GAMEOBJ::BACKGROUNDUP);

	// 오브젝트 생성
	Pobj = new CPlayerTitle;
	Pobj->Load(L"TitlePlayer", L"texture\\Title\\TitlePlayerAnimation.png");
	Pobj->SetPos(fPoint(WINSIZEX / 2, 550.f));
	Pobj->SetScale(fPoint(100.f, 100.f));
	AddObject(Pobj, GROUP_GAMEOBJ::TITLEPLAYER);

	// 메인 타이틀 일부분 가려주는 커튼
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