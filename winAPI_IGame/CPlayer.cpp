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
	SetScale(fPoint(70.f, 70.f));

	CreateCollider();
	GetCollider()->SetScale(fPoint(55.f, 45.f));
	GetCollider()->SetOffsetPos(fPoint(0.f, 10.f));

	CreateAnimator();
	GetAnimator()->CreateAnimation(L"PlayerLIdle",		m_pImgLIdle,  fPoint(0.f, 0.f),	   fPoint(27.f, 22.f),   fPoint(27.f, 0.f), 0.5f, 2);
	GetAnimator()->CreateAnimation(L"PlayerRIdle",		m_pImgRIdle,  fPoint(0.f, 0.f),    fPoint(27.f, 22.f),   fPoint(27.f, 0.f), 0.5f, 2);
	GetAnimator()->CreateAnimation(L"PlayerLMove",		m_pImgLMove,  fPoint(0.f, 0.f),    fPoint(26.5f, 24.f),  fPoint(26.5f, 0.f), 0.25f, 5);
	GetAnimator()->CreateAnimation(L"PlayerRMove",		m_pImgRMove,  fPoint(0.f, 0.f),    fPoint(26.5f, 24.f),  fPoint(26.5f, 0.f), 0.25f, 5);
	GetAnimator()->CreateAnimation(L"PlayerLShoot",		m_pImgLShoot, fPoint(0.f, 0.f),    fPoint(28.75f, 22.f), fPoint(28.75f, 0.f), 0.25f, 4);
	GetAnimator()->CreateAnimation(L"PlayerRShoot",		m_pImgRShoot, fPoint(0.f, 0.f),    fPoint(28.75f, 22.f), fPoint(28.75f, 0.f), 0.25f, 4);
	GetAnimator()->Play(L"LeftNone");

	CAnimation* pAni;
	pAni = GetAnimator()->FindAnimation(L"PlayerLMove");
	pAni->GetFrame(1).fptOffset = fPoint(0.f, -10.f);
	pAni = GetAnimator()->FindAnimation(L"PlayerRMove");
	pAni->GetFrame(1).fptOffset = fPoint(0.f, -10.f);

	act = {};
	act.m_fDelay = 0.f;
	m_uiGround = 0;
	m_uiWall = 0;
	act.m_fHorizontalSpeed = 0;

	// 중력과 점프력 설정
	act.m_fUpforce = 400.f;
	act.m_fGravity = 600.f;
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
	act.m_fVelocity = 0;			// 속도 상태 확인

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

	if (Key('X'))		// 점프 구현
	{
		act.m_fUpforce -= (act.m_fGravity * fDT);
		pos.y -= act.m_fUpforce * fDT;
	}

	if (KeyDown('Z'))
	{
		if (act.m_bIsLeft)
		{
			act.m_fDelay = 0.6f;
			CreateMissile();
			GetAnimator()->Play(L"PlayerLShoot");
		}
		else
		{
			act.m_fDelay = 0.6f;
			CreateMissile();
			GetAnimator()->Play(L"PlayerRShoot");
		}
	}
	act.m_fDelay -= fDT;

	SetPos(pos);
}

void CPlayer::update_ani()			// 움직임에 대한 업데이트
{
	if (act.m_fHorizontalSpeed < 0)
	{
		GetAnimator()->Play(L"PlayerLJump");
	}

	else if (act.m_fHorizontalSpeed > 0)
	{
		GetAnimator()->Play(L"PlayerRJump");
	}

	if (act.m_bIsLeft)
	{
		if (act.m_fDelay >= 0.f)
			GetAnimator()->Play(L"PlayerLShoot");

		else if (act.m_fVelocity > 0.f)
			GetAnimator()->Play(L"PlayerLMove");

		else
			GetAnimator()->Play(L"PlayerLIdle");
	}

	else
	{
		if (act.m_fDelay >= 0.f)
			GetAnimator()->Play(L"PlayerRShoot");

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

void CPlayer::OnCollision(CCollider* _other)
{
	if (_other->GetObj()->GetName() == L"Tile")
	{
		CTile* pTile = (CTile*)(_other->GetObj());
		fPoint pos = GetPos();
		fPoint offset = GetCollider()->GetOffsetPos();
		fPoint thisPos = GetCollider()->GetFinalPos();
		fPoint thisScale = GetCollider()->GetScale();
		fPoint otherPos = _other->GetFinalPos();
		fPoint otherScale = _other->GetScale();

		if (pTile->GetGroup() == GROUP_TILE::GROUND)
		{
			// 바닥과 충돌 처리
			// 계속 밀어내기 - 정해진 위치로 set
			// 위에서 아래로 충돌
			pos.y = otherPos.y - otherScale.y / 2.f - thisScale.y / 2.f - offset.y + 1;

			// 좌우에서 충돌

		}
		else if (pTile->GetGroup() == GROUP_TILE::WALL)
		{
			// 벽과 충돌 처리
		}

		else if (pTile->GetGroup() == GROUP_TILE::PLATFORM)
		{
			// 플랫폼과 충돌 처리
			pos.y = otherPos.y - otherScale.y / 2.f - thisScale.y / 2.f - offset.y + 1;
		}
		SetPos(pos);
	}
}

void CPlayer::OnCollisionEnter(CCollider* _other)
{
	if (_other->GetObj()->GetName() == L"Tile")
	{
		CTile* pTile = (CTile*)_other->GetObj();
		fPoint thisPos = GetCollider()->GetFinalPos();
		fPoint otherPos = _other->GetFinalPos();
		if (pTile->GetGroup() == GROUP_TILE::GROUND)
		{
			// 바닥과 충돌 처리
			m_uiGround++;
		}

		else if (pTile->GetGroup() == GROUP_TILE::WALL)
		{
			// 벽과 충돌 처리
			if (GetCollider()->GetFinalPos().y - _other->GetFinalPos().y + 2.f >= GetCollider()->GetScale().y / 2.f + _other->GetScale().y / 2.f)
			{
				m_uiGround++;
				m_uiWall++;
			}

			else
			{
				if (GetCollider()->GetFinalPos().x < _other->GetFinalPos().x)
				{
					thisPos.x -= 1.f;
				}

				else if (GetCollider()->GetFinalPos().x > _other->GetFinalPos().x)
				{
					thisPos.x += 1.f;
				}
			}
		}
		SetPos(thisPos);
	}

}

void CPlayer::OnCollisionExit(CCollider* _other)
{
	if (_other->GetObj()->GetName() == L"Tile")
	{
		CTile* pTile = (CTile*)_other->GetObj();
		if (pTile->GetGroup() == GROUP_TILE::GROUND)
		{
			// 바닥과 충돌 처리
			m_uiGround--;
		}
		else if (pTile->GetGroup() == GROUP_TILE::WALL)
		{
			// 벽과 충돌 처리
			m_uiGround--;
			m_uiWall--;
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