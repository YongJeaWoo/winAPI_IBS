#include "framework.h"
#include "CPlayer.h"
#include "CMissile.h"
#include "CScene.h"
#include "CTexture.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CTile.h"

CPlayer* CPlayer::instance = nullptr;

CPlayer::CPlayer()
{
	CD2DImage* m_pImgLIdle = CResourceManager::getInst()->LoadD2DImage(L"PlayerLIdle", L"texture\\player\\Player_Idle_Left.png");
	CD2DImage* m_pImgRIdle = CResourceManager::getInst()->LoadD2DImage(L"PlayerRIdle", L"texture\\player\\Player_Idle_Right.png");
	CD2DImage* m_pImgLJump = CResourceManager::getInst()->LoadD2DImage(L"PlayerLJump", L"texture\\player\\Player_Jump_Left.png");
	CD2DImage* m_pImgRJump = CResourceManager::getInst()->LoadD2DImage(L"PlayerRJump", L"texture\\player\\Player_Jump_Right.png");
	CD2DImage* m_pImgLMove = CResourceManager::getInst()->LoadD2DImage(L"PlayerLMove", L"texture\\player\\Player_Move_Left.png");
	CD2DImage* m_pImgRMove = CResourceManager::getInst()->LoadD2DImage(L"PlayerRMove", L"texture\\player\\Player_Move_Right.png");
	CD2DImage* m_pImgLShoot = CResourceManager::getInst()->LoadD2DImage(L"PlayerLShoot", L"texture\\player\\Player_Shoot_Left.png");
	CD2DImage* m_pImgRShoot = CResourceManager::getInst()->LoadD2DImage(L"PlayerRShoot", L"texture\\player\\Player_Shoot_Right.png");
	SetName(L"Player");
	SetPos(fVec2(150.f, 650.f));
	SetScale(fPoint(70.f, 70.f));

	CreateCollider();
	GetCollider()->SetScale(fPoint(55.f, 45.f));
	GetCollider()->SetOffsetPos(fPoint(0.f, 10.f));

	CreateAnimator();
	GetAnimator()->CreateAnimation(L"PlayerLIdle",		m_pImgLIdle,  fPoint(0.f, 0.f),	   fPoint(27.f, 22.f),   fPoint(27.f, 0.f), 0.5f, 2);
	GetAnimator()->CreateAnimation(L"PlayerRIdle",		m_pImgRIdle,  fPoint(0.f, 0.f),    fPoint(27.f, 22.f),   fPoint(27.f, 0.f), 0.5f, 2);
	GetAnimator()->CreateAnimation(L"PlayerLMove",		m_pImgLMove,  fPoint(0.f, 0.f),    fPoint(26.5f, 24.f),  fPoint(26.5f, 0.f), 0.25f, 5);
	GetAnimator()->CreateAnimation(L"PlayerRMove",		m_pImgRMove,  fPoint(0.f, 0.f),    fPoint(26.5f, 24.f),  fPoint(26.5f, 0.f), 0.25f, 5);
	GetAnimator()->CreateAnimation(L"PlayerLShoot",		m_pImgLShoot, fPoint(0.f, 0.f),    fPoint(28.75f, 22.f), fPoint(28.75f, 0.f), 0.3f, 4);
	GetAnimator()->CreateAnimation(L"PlayerRShoot",		m_pImgRShoot, fPoint(0.f, 0.f),    fPoint(28.75f, 22.f), fPoint(28.75f, 0.f), 0.3f, 4);

	// 점프 리소스 재구현
	GetAnimator()->CreateAnimation(L"PlayerLJump",		m_pImgLJump, fPoint(0.f, 0.f), fPoint(27.57f, 25.f), fPoint(27.57f, 0.f), 0.6f, 6);
	GetAnimator()->CreateAnimation(L"PlayerRJump",		m_pImgRJump, fPoint(0.f, 0.f), fPoint(27.57f, 25.f), fPoint(27.57f, 0.f), 0.6f, 6);

	GetAnimator()->Play(L"LeftNone");

	CAnimation* pAni;
	pAni = GetAnimator()->FindAnimation(L"PlayerLMove");
	pAni->GetFrame(1).fptOffset = fPoint(0.f, -10.f);
	pAni = GetAnimator()->FindAnimation(L"PlayerRMove");
	pAni->GetFrame(1).fptOffset = fPoint(0.f, -10.f);

	act = {};
	act.m_fDelay = 0.f;
	act.m_YPower = 1000.f;
	act.Jump = false;
	act.m_bIsLeft = false;

	m_GtileCount = 0;
	m_WtileCount = 0;
	m_PtileCount = 0;
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
	update_action();
	update_animation();

	GetAnimator()->update();
}

void CPlayer::render()
{
	component_render();
}

void CPlayer::update_action()			// 상황에 대한 업데이트
{
	fPoint pos = GetPos();
	act.m_fVelocity = 0;			// 속도 상태 확인

	if (m_GtileCount > 0 && m_WtileCount > 0 && m_PtileCount > 0)
		act.m_YPower = 0.f;

	else
	{
		act.m_YPower += fDT * 1000.f;
		if (act.m_YPower > 1000.f)
			act.m_YPower = 1000.f;
	}

	if (Key(VK_LEFT))
	{
		pos.x -= act.m_fSpeed * fDT;
		act.m_bIsLeft = true;
		act.m_fVelocity = act.m_fSpeed;
	}

	if (Key(VK_RIGHT))
	{
		pos.x += act.m_fSpeed * fDT;
		act.m_bIsLeft = false;
		act.m_fVelocity = act.m_fSpeed;
	}

	if (Key(VK_UP))
	{
		pos.y -= act.m_fSpeed * fDT;
	}

	if (Key(VK_DOWN))
	{
		pos.y += act.m_fSpeed * fDT;
	}

	if (KeyDown('X') && act.Jump == false)		// 점프 구현
	{
		act.Jump = true;
		pos.y -= 1.f;
		act.m_YPower = -600.f;
	}
	pos.y += act.m_YPower * fDT;

	if (KeyDown('Z'))
	{
		if (act.m_bIsLeft)
		{
			act.m_fDelay = 0.8f;
			CreateMissile();
		}
		else
		{
			act.m_fDelay = 0.8f;
			CreateMissile();
		}
	}
	act.m_fDelay -= fDT;

	// 맵을 벗어날 때 다시 위로 올리기
	if (pos.y > WINSIZEY)
	{
		pos.y = 0;
	}

	SetPos(pos);

	GetAnimator()->update();
}

void CPlayer::update_animation()			// 움직임에 대한 업데이트
{
	// 순서 확인 
	if (act.m_bIsLeft)
	{
		if (act.m_fDelay >= 0.f)
			GetAnimator()->Play(L"PlayerLShoot");

		else if (act.m_YPower < 0)		// 점프가 된 상황
			GetAnimator()->Play(L"PlayerLJump");

		else if (act.m_fVelocity > 0.f)
			GetAnimator()->Play(L"PlayerLMove");

		else
			GetAnimator()->Play(L"PlayerLIdle");
	}

	else
	{
		if (act.m_fDelay >= 0.f)
			GetAnimator()->Play(L"PlayerRShoot");

		else if (act.m_YPower < 0)
			GetAnimator()->Play(L"PlayerRJump");

		else if (act.m_fVelocity > 0.f)
			GetAnimator()->Play(L"PlayerRMove");

		else
			GetAnimator()->Play(L"PlayerRIdle");
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

void CPlayer::OnCollisionEnter(CCollider* _other)
{
	CGameObject* pOtherObj = _other->GetObj();
	CTile* pTile = (CTile*)pOtherObj;
	GROUP_TILE Type = pTile->GetGroup();

	fPoint thisPos = GetCollider()->GetFinalPos();
	fPoint otherPos = _other->GetFinalPos();

	if (pOtherObj->GetName() == L"Tile")
	{
		switch (Type)
		{
		case GROUP_TILE::GROUND:
		{
			act.Jump = false;
			m_GtileCount++;
			m_WtileCount++;
			break;
		}

		case GROUP_TILE::WALL:
		{
			m_GtileCount++;
			m_WtileCount++;
			m_PtileCount++;
			break;
		}

		case GROUP_TILE::PLATFORM:
		{
			act.Jump = false;
			m_GtileCount++;
			m_WtileCount++;
			m_PtileCount++;
			break;
		}

		SetPos(thisPos);
		}
	}
}

void CPlayer::OnCollision(CCollider* _other)
{
	CGameObject* pOtherObj = _other->GetObj();
	CTile* pTile = (CTile*)pOtherObj;
	GROUP_TILE Type = pTile->GetGroup();

	fPoint pos = GetPos();								// 충돌 감지 좌표
	fPoint offset = GetCollider()->GetOffsetPos();

	fPoint thisPos = GetCollider()->GetFinalPos();		// 플레이어 좌표
	fPoint thisScale = GetCollider()->GetScale();

	fPoint otherPos = _other->GetFinalPos();			// 타일 좌표
	fPoint otherScale = _other->GetScale();

	if (pOtherObj->GetName() == L"Tile")
	{
		switch (Type)
		{
		case GROUP_TILE::GROUND:
		{
			pos.y = otherPos.y - otherScale.y / 2.f - thisScale.y / 2.f - offset.y + 1;
			break;
		}

		case GROUP_TILE::WALL:
		{
			if (thisPos.x > WINSIZEX)
			// 플레이어가 왼쪽으로 와서 벽에 부딪칠 때
				pos.x = otherPos.x + otherScale.x / 2.f + thisScale.x / 2.f - offset.x + 1;

			else if (thisPos.x < WINSIZEX)
			// 플레이어가 오른쪽으로 와서 벽에 부딪칠 때
				pos.x = otherPos.x - thisScale.x + offset.x + 1;
			break;
		}

		case GROUP_TILE::PLATFORM:
		{
			pos.y = otherPos.y - otherScale.y / 2.f - thisScale.y / 2.f - offset.y + 1;
			break;
		}

		}

		SetPos(pos);
	}
}

void CPlayer::OnCollisionExit(CCollider* _other)
{
	CGameObject* pOtherObj = _other->GetObj();
	CTile* pTile = (CTile*)pOtherObj;
	GROUP_TILE Type = pTile->GetGroup();

	switch (Type)
	{
	case GROUP_TILE::GROUND:
	{
		m_GtileCount--;
		m_WtileCount--;
		break;
	}

	case GROUP_TILE::WALL:
	{
		m_GtileCount--;
		m_WtileCount--;
		m_PtileCount--;
		break;
	}

	case GROUP_TILE::PLATFORM:
	{
		m_GtileCount--;
		m_WtileCount--;
		m_PtileCount--;
		break;
	}
	}
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