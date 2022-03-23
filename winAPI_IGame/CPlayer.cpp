#include "framework.h"
#include "CPlayer.h"
#include "CMissile.h"
#include "CScene.h"
#include "CTexture.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"

CPlayer* CPlayer::instance = nullptr;

CPlayer::CPlayer()
{
	CD2DImage* m_pImg = CResourceManager::getInst()->LoadD2DImage(L"PlayerImg", L"texture\\Animation_Player.bmp");
	SetName(L"Player");
	SetPos(fPoint(100.f, 600.f));
	SetScale(fPoint(80.f, 80.f));

	CreateCollider();
	GetCollider()->SetScale(fPoint(40.f, 40.f));
	GetCollider()->SetOffsetPos(fPoint(0.f, 10.f));

	CreateAnimator();
	GetAnimator()->CreateAnimation(L"LeftNone",		m_pImg, fPoint(0.f, 0.f),	fPoint(70.f, 70.f), fPoint(70.f, 0.f), 0.5f, 2);
	GetAnimator()->CreateAnimation(L"RightNone",	m_pImg, fPoint(0.f, 70.f),	fPoint(70.f, 70.f), fPoint(70.f, 0.f), 0.5f, 2);
	GetAnimator()->CreateAnimation(L"LeftMove",		m_pImg, fPoint(0.f, 140.f),	fPoint(70.f, 70.f), fPoint(70.f, 0.f), 0.25f, 3);
	GetAnimator()->CreateAnimation(L"RightMove",	m_pImg, fPoint(0.f, 210.f), fPoint(70.f, 70.f), fPoint(70.f, 0.f), 0.25f, 3);
	GetAnimator()->CreateAnimation(L"LeftHit",		m_pImg, fPoint(140.f, 0.f), fPoint(70.f, 70.f), fPoint(70.f, 0.f), 0.25f, 1);
	GetAnimator()->CreateAnimation(L"RightHit",		m_pImg, fPoint(140.f, 70.f), fPoint(70.f, 70.f), fPoint(70.f, 0.f), 0.25f, 1);
	GetAnimator()->Play(L"LeftNone");

	CAnimation* pAni;
	pAni = GetAnimator()->FindAnimation(L"LeftMove");
	pAni->GetFrame(1).fptOffset = fPoint(0.f, -20.f);
	pAni = GetAnimator()->FindAnimation(L"RightMove");
	pAni->GetFrame(1).fptOffset = fPoint(0.f, -20.f);

	act = {};
}

CPlayer::~CPlayer()
{
	instance = nullptr;
}

CPlayer* CPlayer::Clone()
{
	return new CPlayer(*this);
}

void CPlayer::update()
{
	update_act();
	update_ani();

	GetAnimator()->update();
}

void CPlayer::render()
{
	component_render();
}

void CPlayer::update_act()			// 상황에 대한 업데이트
{
	fPoint pos = GetPos();
	act.m_fVelocity = 0;

	if (Key(VK_LEFT))
	{
		pos.x -= m_fSpeed * fDT;
		act.m_bIsLeft = true;
		act.m_fVelocity = m_fSpeed;
	}
	if (Key(VK_RIGHT))
	{
		pos.x += m_fSpeed * fDT;
		act.m_bIsLeft = false;
		act.m_fVelocity = m_fSpeed;
		
	}
	if (Key(VK_UP))
	{
		pos.y -= m_fSpeed * fDT;
	}
	if (Key(VK_DOWN))
	{
		pos.y += m_fSpeed * fDT;
	}

	SetPos(pos);

	if (KeyDown(VK_SPACE))
	{
		CreateMissile();
		GetAnimator()->Play(L"LeftHit");
	}
}

void CPlayer::update_ani()			// 움직임에 대한 업데이트
{
	if (act.m_bIsLeft)
	{
		if (act.m_fVelocity > 0.f)
			GetAnimator()->Play(L"LeftMove");
		else
			GetAnimator()->Play(L"LeftNone");
	}

	else
	{
		if (act.m_fVelocity > 0.f)
			GetAnimator()->Play(L"RightMove");
		else
			GetAnimator()->Play(L"RightNone");
	}
}

void CPlayer::RegisterPlayer()
{
	instance = this;
}

CPlayer* CPlayer::GetPlayer()
{
	return instance;
}

void CPlayer::CreateMissile()
{
	if (!act.m_bIsLeft)
	{
		fPoint fpMissilePos = GetPos();
		fpMissilePos.x += GetScale().x / 2.f;

		// Misiile Object
		CMissile* pMissile = new CMissile;
		pMissile->SetPos(fpMissilePos);
		pMissile->SetDir(fVec2(1, 0));
		pMissile->SetName(L"Missile");

		CreateObj(pMissile, GROUP_GAMEOBJ::MISSILE);
	}

	// 반대방향일 경우 반대방향으로
	else
	{
		fPoint fpMissilePos = GetPos();
		fpMissilePos.x -= GetScale().x / 2.f;

		// Misiile Object
		CMissile* pMissile = new CMissile;
		pMissile->SetPos(fpMissilePos);
		pMissile->SetDir(fVec2(-1, 0));
		pMissile->SetName(L"Missile");

		CreateObj(pMissile, GROUP_GAMEOBJ::MISSILE);
	}
}