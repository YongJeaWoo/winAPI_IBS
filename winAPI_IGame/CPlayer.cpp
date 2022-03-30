#include "framework.h"
#include "CPlayer.h"
#include "CMissile.h"
#include "CScene.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CTile.h"

#define MAX_SPEED	200.f
#define GRAVITY		500.f
#define UPPER		-350.f

CPlayer* CPlayer::instance = nullptr;

CPlayer::CPlayer()
{
	SetName(L"Player");
	SetPos(fVec2(150.f, 650.f));
	SetScale(fPoint(70.f, 70.f));
	CD2DImage* m_Idle	= CResourceManager::getInst()->LoadD2DImage(L"Idle", L"texture\\player\\Player_Idle.png");
	CD2DImage* m_Move	= CResourceManager::getInst()->LoadD2DImage(L"Move", L"texture\\player\\Player_Move.png");
	CD2DImage* m_Jump	= CResourceManager::getInst()->LoadD2DImage(L"Jump", L"texture\\player\\Player_Jump.png");
	CD2DImage* m_Bubble = CResourceManager::getInst()->LoadD2DImage(L"Bubble", L"texture\\player\\Player_Bubble.png");

	CreateAnimator();
	GetAnimator()->CreateAnimation(L"Idle",	   m_Idle, fPoint(0.f, 0.f), fPoint(27.f, 22.f), fPoint(27.f, 0.f), 0.2f, 2, true);
	GetAnimator()->CreateAnimation(L"LIdle",   m_Idle, fPoint(0.f, 0.f), fPoint(27.f, 22.f), fPoint(27.f, 0.f), 0.2f, 2, false);
	GetAnimator()->CreateAnimation(L"Move",	   m_Move, fPoint(0.f, 0.f), fPoint(26.6f, 24.f), fPoint(26.6f, 0.f), 0.2f, 5, true);
	GetAnimator()->CreateAnimation(L"LMove",   m_Move, fPoint(0.f, 0.f), fPoint(26.6f, 24.f), fPoint(26.6f, 0.f), 0.2f, 5, false);
	GetAnimator()->CreateAnimation(L"Jump",    m_Jump, fPoint(0.f, 0.f), fPoint(27.57f, 25.f), fPoint(27.57f, 0.f), 0.2f, 7, true);
	GetAnimator()->CreateAnimation(L"LJump",   m_Jump, fPoint(0.f, 0.f), fPoint(27.57f, 25.f), fPoint(27.57f, 0.f), 0.2f, 7, false);
	GetAnimator()->CreateAnimation(L"Bubble",  m_Bubble, fPoint(0.f, 0.f), fPoint(28.75f, 22.f), fPoint(28.75f, 0.f), 0.2f, 4, true);
	GetAnimator()->CreateAnimation(L"LBubble", m_Bubble, fPoint(0.f, 0.f), fPoint(28.75f, 22.f), fPoint(28.75f, 0.f), 0.2f, 4, false);
	GetAnimator()->Play(L"Idle");

	CreateCollider();
	GetCollider()->SetScale(fPoint(45.f, 45.f));
	GetCollider()->SetOffsetPos(fPoint(0.f, 5.f));

	pState.IsRight = false;
	pState.JustHit = false;
	pState.Grounding = true;
	pState.Attacking = false;
	pState.AccelGravity = 0.f;
	pState.Speed = MAX_SPEED;
	pState.Upper = UPPER;

	m_gravity = GRAVITY;

	m_fCurDir = { 1.f, 1.f };
	m_fPrevDir = {};

	m_GtileCount = 0;
	m_WtileCount = 0;
	m_PtileCount = 0;
	
	m_State = CharacterState::IDLE;
}

CPlayer::~CPlayer()
{
}

CPlayer* CPlayer::Clone()
{
	return new CPlayer(*this);
}

void CPlayer::update()
{
	update_animation();
	update_state();
	update_action();
	
	m_PrevState		= m_State;
	pState.CurDir	= m_fCurDir;

	GetAnimator()->update();
}

void CPlayer::render()
{
	component_render();
}

void CPlayer::update_action()
{
	if (Key(VK_LEFT))
	{
		m_fCurDir.x = -1;
		pState.Speed = MAX_SPEED;
	}

	if (KeyUp(VK_LEFT))
	{
		pState.Speed = 0.f;
	}

	if (Key(VK_RIGHT))
	{
		m_fCurDir.x = 1;
		pState.Speed = MAX_SPEED;
	}

	if (KeyUp(VK_RIGHT))
	{
		pState.Speed = 0.f;
	}

	if (m_State == CharacterState::JUMP && pState.Grounding)
	{
		Jump();
	}

	fPoint Pos = GetPos();
	Pos.x += m_fCurDir.x * pState.Speed * fDT;
	Pos.y += pState.AccelGravity * fDT;

	// ¸Ê ¹þ¾î³ª¸é À§·Î ¿Å±â±â
	if (Pos.y > WINSIZEY)
		Pos.y = 0;

	SetPos(Pos);
	pState.AccelGravity += GRAVITY * fDT;
	if (pState.AccelGravity >= 1000.f)
		pState.AccelGravity = 1000.f;

	
}

void CPlayer::update_state()
{
	if (Key(VK_LEFT) && !pState.Attacking)
	{
		m_State = CharacterState::MOVE;
	}

	if (Key(VK_RIGHT) && !pState.Attacking)
	{
		m_State = CharacterState::MOVE;
	}

	if (KeyDown('X') && pState.Grounding && !pState.Attacking)
	{
		m_State = CharacterState::JUMP;
	}

	if (KeyDown('Z') && !pState.Grounding)
	{
		CreateMissile();
		m_State = CharacterState::ATTACK;
		pState.Attacking = true;
	}

	if (KeyDown('Z') && pState.Grounding && pState.Speed <= 0)
	{
		CreateMissile();
		m_State = CharacterState::ATTACK;
		pState.Attacking = true;
	}

	if (Key(VK_LEFT) && KeyDown('Z') && pState.Grounding && pState.Speed >= MAX_SPEED)
	{
		CreateMissile();
		m_State = CharacterState::ATTACK;
		pState.Attacking = true;
	}

	if (Key(VK_RIGHT) && KeyDown('Z') && pState.Grounding && pState.Speed >= MAX_SPEED)
	{
		CreateMissile();
		m_State = CharacterState::ATTACK;
		pState.Attacking = true;
	}
}

void CPlayer::update_animation()
{
	if (m_PrevState == m_State && m_fPrevDir == m_fCurDir)
	{
		return;
	}

	switch (m_State)
	{
	case CharacterState::IDLE:
	{
		static float IdleTime = 0.f;
		IdleTime += fDT;
		if (-1 == m_fCurDir.x && IdleTime < 3)
		{
			GetAnimator()->Play(L"Idle");
		}

		else if (1 == m_fCurDir.x && IdleTime < 3)
		{
			GetAnimator()->Play(L"LIdle");
		}
		break;
	}

	case CharacterState::MOVE:
	{
		if (-1 == m_fCurDir.x)
		{
			GetAnimator()->Play(L"Move");
		}

		else
		{
			GetAnimator()->Play(L"LMove");
		}
		break;
	}

	case CharacterState::JUMP:
	{
		if (-1 == m_fCurDir.x)
		{
			GetAnimator()->Play(L"Jump");
		}

		else
		{
			GetAnimator()->Play(L"LJump");
		}
		break;
	}

	case CharacterState::ATTACK:
	{
		if (-1 == m_fCurDir.x)
		{
			GetAnimator()->Play(L"Bubble");
		}

		else
		{
			GetAnimator()->Play(L"LBubble");
		}
		static float fTime = 0.f;
		fTime += fDT;
		if (0.4 <= fTime)
		{
			pState.Attacking = false;
			fTime = 0.f;
		}
		break;
	}
	}
}

void CPlayer::CreateMissile()
{
	fPoint fptMissilePos = GetPos();
	fptMissilePos.x += GetScale().x / 2.f;

	CMissile* pMissile = new CMissile;
	pMissile->SetPos(fptMissilePos);

	if (-1 == m_fCurDir.x)
	{
		pMissile->SetDir(fVec2(-1, 0));
		pMissile->SetName(L"Missile");
		CreateObj(pMissile, GROUP_GAMEOBJ::MISSILE);
	}

	else
	{
		pMissile->SetDir(fVec2(1, 0));
		pMissile->SetName(L"Missile");
		CreateObj(pMissile, GROUP_GAMEOBJ::MISSILE);
	}

}

void CPlayer::Jump()
{
	pState.Grounding = false;
	pState.AccelGravity += pState.Upper;
}

void CPlayer::RegisterPlayer()
{
	instance = this;
}

CPlayer* CPlayer::GetPlayer()
{
	return instance;
}

void CPlayer::OnCollisionEnter(CCollider* pOther)
{
	CGameObject* pOtherObj = pOther->GetObj();
	CTile* pTile = (CTile*)pOtherObj;
	GROUP_TILE Type = pTile->GetGroup();

}

void CPlayer::OnCollision(CCollider* pOther)
{
	CGameObject* pOtherObj = pOther->GetObj();
	CTile* pTile = (CTile*)pOtherObj;
	GROUP_TILE Type = pTile->GetGroup();

	if (pOtherObj->GetName() == L"Tile")
	{
		switch (Type)
		{
		case GROUP_TILE::GROUND:
		{
			LONG xDiff = 0;
			LONG yDiff = 0;

			if (pOther->GetBorderPos().left > GetCollider()->GetBorderPos().left)
			{
				xDiff = (GetCollider()->GetBorderPos().right - pOther->GetBorderPos().left);
			}

			else if (pOther->GetBorderPos().right < GetCollider()->GetBorderPos().right)
			{
				xDiff = (pOther->GetBorderPos().right - GetCollider()->GetBorderPos().left);
			}

			else
			{
				xDiff = (GetCollider()->GetBorderPos().right - GetCollider()->GetBorderPos().left);
			}

			if (m_fCurDir.x < 0.f)
			{
				if (pOther->GetBorderPos().top < GetCollider()->GetBorderPos().bottom
					&& pOther->GetBorderPos().bottom > GetCollider()->GetBorderPos().top)
				{
					yDiff = (GetCollider()->GetBorderPos().bottom - pOther->GetBorderPos().top);

					if (yDiff > xDiff && GetCollider()->GetBorderPos().right > pOther->GetBorderPos().right)
					{
						fPoint Pos = GetPos();
						Pos.x += (float)(pOther->GetBorderPos().right - GetCollider()->GetBorderPos().left);
						SetPos(Pos);
					}
				}
			}

			if (m_fCurDir.x > 0.f)
			{
				if (pOther->GetBorderPos().top < GetCollider()->GetBorderPos().bottom
					&& pOther->GetBorderPos().bottom > GetCollider()->GetBorderPos().top)
				{
					yDiff = (GetCollider()->GetBorderPos().bottom - pOther->GetBorderPos().top);

					if (yDiff > xDiff && GetCollider()->GetBorderPos().left < pOther->GetBorderPos().left
						&& GetCollider()->GetBorderPos().right > pOther->GetBorderPos().left)
					{
						fPoint fptPos = GetPos();
						fptPos.x -= (float)(GetCollider()->GetBorderPos().right - pOther->GetBorderPos().left);
						SetPos(fptPos);
					}
				}
			}

			if (GetCollider()->GetBorderPos().bottom > pOther->GetBorderPos().bottom &&
				GetCollider()->GetBorderPos().top <= pOther->GetBorderPos().bottom)
			{
				yDiff = (pOther->GetBorderPos().bottom - GetCollider()->GetBorderPos().top);

				if (yDiff < xDiff)
				{
					fPoint fptPos = GetPos();
					fptPos.y += (float)(pOther->GetBorderPos().bottom - GetCollider()->GetBorderPos().top);
					SetPos(fptPos);
				}
			}

			if (GetCollider()->GetBorderPos().top < pOther->GetBorderPos().top
				&& GetCollider()->GetBorderPos().bottom >= pOther->GetBorderPos().top)
			{
				yDiff = (GetCollider()->GetBorderPos().bottom - pOther->GetBorderPos().top);

				if (yDiff < xDiff)
				{
					fPoint fptPos = GetPos();
					fptPos.y -= (float)(GetCollider()->GetBorderPos().bottom - pOther->GetBorderPos().top);
					SetPos(fptPos);

					pState.Grounding = true;
					pState.AccelGravity = 0.f;
				}
			}
			break;
		}

		case GROUP_TILE::WALL:
		{

		}

		case GROUP_TILE::PLATFORM:
		{
			LONG yDiff = 0;
			LONG xDiff = 0;

			if (pOther->GetBorderPos().left > GetCollider()->GetBorderPos().left)
			{
				xDiff = (GetCollider()->GetBorderPos().right - pOther->GetBorderPos().left);
			}
			else if (pOther->GetBorderPos().right < GetCollider()->GetBorderPos().right)
			{
				xDiff = (pOther->GetBorderPos().right - GetCollider()->GetBorderPos().left);
			}
			else
				xDiff = (GetCollider()->GetBorderPos().right - GetCollider()->GetBorderPos().left);

			if (pState.AccelGravity > 0.f || pState.Upper > 0.f)
			{
				if (GetCollider()->GetBorderPos().top < pOther->GetBorderPos().top
					&& GetCollider()->GetBorderPos().bottom >= pOther->GetBorderPos().top)
				{
					yDiff = (GetCollider()->GetBorderPos().bottom - pOther->GetBorderPos().top);

					if (yDiff < xDiff)
					{
						fPoint fptPos = GetPos();
						fptPos.y -= (float)(GetCollider()->GetBorderPos().bottom - pOther->GetBorderPos().top);
						SetPos(fptPos);

						pState.Grounding = true;
						pState.AccelGravity = 0.f;
					}
				}
			}
			break;
		}
		}
	}
}

void CPlayer::OnCollisionExit(CCollider* pOther)
{
}