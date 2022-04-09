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
#define UPPER		-380.f

CPlayer* CPlayer::instance = nullptr;

CPlayer::CPlayer()
{
	SetName(L"Player");
	SetPos(fVec2(150.f, 650.f));
	SetScale(fPoint(70.f, 70.f));
	CD2DImage* m_Idle			= CResourceManager::getInst()->LoadD2DImage(L"Idle", L"texture\\player\\Player_Idle.png");
	CD2DImage* m_Move			= CResourceManager::getInst()->LoadD2DImage(L"Move", L"texture\\player\\Player_Move.png");
	CD2DImage* m_Jump			= CResourceManager::getInst()->LoadD2DImage(L"Jump", L"texture\\player\\Player_Jump.png");
	CD2DImage* m_Fall			= CResourceManager::getInst()->LoadD2DImage(L"Fall", L"texture\\player\\Player_Fall.png");
	CD2DImage* m_JumpBubble		= CResourceManager::getInst()->LoadD2DImage(L"JumpBubble", L"texture\\player\\Player_Jump_Bubble.png");
	CD2DImage* m_Bubble			= CResourceManager::getInst()->LoadD2DImage(L"Bubble", L"texture\\player\\Player_Bubble.png");

	CreateAnimator();
	GetAnimator()->CreateAnimation(L"Idle",			m_Idle, fPoint(0.f, 0.f), fPoint(27.f, 22.f), fPoint(27.f, 0.f), 0.2f, 2, true);
	GetAnimator()->CreateAnimation(L"LIdle",		m_Idle, fPoint(0.f, 0.f), fPoint(27.f, 22.f), fPoint(27.f, 0.f), 0.2f, 2, false);
	GetAnimator()->CreateAnimation(L"Move",			m_Move, fPoint(0.f, 0.f), fPoint(26.6f, 24.f), fPoint(26.6f, 0.f), 0.2f, 5, true);
	GetAnimator()->CreateAnimation(L"LMove",		m_Move, fPoint(0.f, 0.f), fPoint(26.6f, 24.f), fPoint(26.6f, 0.f), 0.2f, 5, false);
	GetAnimator()->CreateAnimation(L"Jump",			m_Jump, fPoint(0.f, 0.f), fPoint(27.f, 25.f), fPoint(27.f, 0.f), 0.2f, 4, true);
	GetAnimator()->CreateAnimation(L"LJump",		m_Jump, fPoint(0.f, 0.f), fPoint(27.f, 25.f), fPoint(27.f, 0.f), 0.2f, 4, false);
	GetAnimator()->CreateAnimation(L"Fall",			m_Fall, fPoint(0.f, 0.f), fPoint(27.25f, 23.f), fPoint(27.25f, 0.f), 0.2f, 4, true);
	GetAnimator()->CreateAnimation(L"LFall",		m_Fall, fPoint(0.f, 0.f), fPoint(27.25f, 23.f), fPoint(27.25f, 0.f), 0.2f, 4, false);
	GetAnimator()->CreateAnimation(L"JumpBubble",	m_JumpBubble, fPoint(0.f, 0.f), fPoint(28.f, 23.f), fPoint(28.f, 0.f), 0.2f, 4, true);
	GetAnimator()->CreateAnimation(L"LJumpBubble",	m_JumpBubble, fPoint(0.f, 0.f), fPoint(28.f, 23.f), fPoint(28.f, 0.f), 0.2f, 4, false);
	GetAnimator()->CreateAnimation(L"Bubble",		m_Bubble, fPoint(0.f, 0.f), fPoint(28.75f, 22.f), fPoint(28.75f, 0.f), 0.2f, 4, true);
	GetAnimator()->CreateAnimation(L"LBubble",		m_Bubble, fPoint(0.f, 0.f), fPoint(28.75f, 22.f), fPoint(28.75f, 0.f), 0.2f, 4, false);
	GetAnimator()->Play(L"Idle");

	CreateCollider();
	GetCollider()->SetScale(fPoint(45.f, 45.f));
	GetCollider()->SetOffsetPos(fPoint(0.f, 5.f));

	pState.JustHit = false;
	pState.Grounding = true;
	pState.Attacking = false;
	pState.AccelGravity = 0.f;
	pState.Speed = 0;
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
	update_state();
	update_animation();
	update_move();

	m_PrevState = m_State;
	m_fPrevDir = m_fCurDir;
	GetAnimator()->update();
}

void CPlayer::render()
{
	component_render();
}

void CPlayer::update_state()
{
	// 기본 자세 상태
	if (pState.Grounding && pState.AccelGravity == 0)
	{
		if (pState.Speed == 0)
			m_State = CharacterState::IDLE;
	}

	// 움직이는 상태
	if (m_State == CharacterState::IDLE)
	{
		if (Key(VK_LEFT) || Key(VK_RIGHT) && pState.Grounding)
			m_State = CharacterState::MOVE;
	}

	// 점프하는 상태
	if (pState.Grounding && KeyDown('X'))
		m_State = CharacterState::JUMP;

	// 떨어지는 상태
	if (pState.AccelGravity >= 100 && !pState.Grounding)
	{
		m_State = CharacterState::FALL;
	}

	// 점프와 떨어짐 동시에 쏘는 상태
	if (!pState.Grounding && pState.Speed <= MAX_SPEED && KeyDown('Z'))
	{
		CreateMissile();
		m_State = CharacterState::JUMPBUBBLE;
		pState.Attacking = true;
	}

	// 땅에서 움직이면서 쏘는 상태
	else if (pState.Grounding && pState.Speed <= MAX_SPEED && KeyDown('Z'))
	{
		CreateMissile();
		m_State = CharacterState::BUBBLE;
		pState.Attacking = true;
	}

	else if (pState.Grounding && pState.Speed == 0 && KeyDown('Z'))
	{
		CreateMissile();
		m_State = CharacterState::BUBBLE;
		pState.Attacking = true;
	}
}

void CPlayer::update_move()
{
	if (Key(VK_LEFT))
	{
		m_fCurDir.x = -1;
		pState.Speed = MAX_SPEED;
	}

	else if (KeyUp(VK_LEFT))
	{
		m_fCurDir.x = -1;
		pState.Speed = 0.f;
	}

	if (Key(VK_RIGHT))
	{
		m_fCurDir.x = 1;
		pState.Speed = MAX_SPEED;
	}

	else if (KeyUp(VK_RIGHT))
	{
		m_fCurDir.x = 1;
		pState.Speed = 0.f;
	}

	if (m_State == CharacterState::JUMP && pState.Grounding)
	{
		Jump();
	}

	fPoint Pos = GetPos();
	Pos.x += m_fCurDir.x * pState.Speed * fDT;
	Pos.y += pState.AccelGravity * fDT;

	// 맵 벗어나면 위로 옮기기
	if (Pos.y > WINSIZEY)
		Pos.y = 0;

	SetPos(Pos);

	pState.AccelGravity += GRAVITY * fDT;
	if (pState.AccelGravity >= 1000.f)
		pState.AccelGravity = 1000.f;

	
}

void CPlayer::update_animation()
{
	if (m_PrevState == m_State && m_fPrevDir == m_fCurDir)
		return;


	switch (m_State)
	{
	case CharacterState::IDLE:
	{
		static float IdleTime = 0.f;
		IdleTime += fDT;
		if (-1 == m_fCurDir.x)
		{
			GetAnimator()->Play(L"Idle");
		}

		else
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

	case CharacterState::FALL:
	{
		if (-1 == m_fCurDir.x)
			GetAnimator()->Play(L"Fall");
		else
			GetAnimator()->Play(L"LFall");
	}

	case CharacterState::JUMPBUBBLE:
	{
		if (-1 == m_fCurDir.x)
		{
			GetAnimator()->Play(L"JumpBubble");
		}

		else
		{
			GetAnimator()->Play(L"LJumpBubble");
		}

		static float fTime = 0.f;
		fTime += fDT;
		if (0.3 <= fTime)
		{
			pState.Attacking = false;
			fTime = 0.f;
		}
		break;
	}

	case CharacterState::BUBBLE:
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
		if (0.3 <= fTime)
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

	CMissile* pMissile = new CMissile;
	pMissile->SetPos(fptMissilePos);

	if (-1 == m_fCurDir.x)
	{
		fptMissilePos.x = (GetScale().x / 2.f) + 10.f;
		pMissile->SetDir(fVec2(-1, 0));
		pMissile->SetName(L"Missile");
		CreateObj(pMissile, GROUP_GAMEOBJ::MISSILE);
	}

	else
	{
		fptMissilePos.x = (GetScale().x / 2.f) - 10.f;
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

	if (pOtherObj->GetName() == L"Tile")
	{
		switch (Type)
		{
			case GROUP_TILE::GROUND:
			{
				if (GetCollider()->GetBorderPos().top < pOther->GetBorderPos().top
					&& GetCollider()->GetBorderPos().bottom >= pOther->GetBorderPos().top)
				{
					if (m_State == CharacterState::JUMP)
						m_State = CharacterState::IDLE;
				}
				break;
			}

			case GROUP_TILE::PLATFORM:
			{
				if (GetCollider()->GetBorderPos().top < pOther->GetBorderPos().top
					&& GetCollider()->GetBorderPos().bottom >= pOther->GetBorderPos().top)
				{
					if (m_State == CharacterState::JUMP)
						m_State = CharacterState::IDLE;
				}
			}
			break;
		}
	}
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