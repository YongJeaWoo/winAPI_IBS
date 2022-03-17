#include "framework.h"
#include "CMonster.h"
#include "CCollider.h"
#include "CD2DImage.h"
#include "CAnimator.h"
#include "AI.h"

CMonster* CMonster::Clone()
{
	return new CMonster(*this);
}

CMonster::CMonster()
{
	m_pImg = CResourceManager::getInst()->LoadD2DImage(L"MonsterTex", L"texture\\PlayerStand.png");

	m_fSpeed = 0;
	m_iHP = 5;
	m_pAI = nullptr;

	SetName(L"Monster");
	SetScale(fPoint(100, 100));

	CreateCollider();
	GetCollider()->SetScale(fPoint(90.f, 90.f));

	CreateAnimator();
	GetAnimator()->CreateAnimation(L"PlayerStand", m_pImg, fPoint(0, 0), fPoint(32.f, 32.f), fPoint(32.f, 0), 0.1f, 5, true);
	GetAnimator()->Play(L"PlayerStand");
}

CMonster::~CMonster()
{
	if (nullptr != m_pAI)
	{
		delete m_pAI;
	}
}

void CMonster::render()
{
	fPoint pos = GetPos();
 	fPoint scale = GetScale();
	pos = CCameraManager::getInst()->GetRenderPos(pos);

	component_render();
}

void CMonster::update()
{
	if (nullptr != GetAnimator())
	{
		GetAnimator()->update();
	}

	if (nullptr != m_pAI)
	{
		m_pAI->update();
	}
}

float CMonster::GetSpeed()
{
	return m_fSpeed;
}

void CMonster::SetSpeed(float speed)
{
	m_fSpeed = speed;
}

void CMonster::SetAI(AI* ai)
{
	m_pAI = ai;
	m_pAI->m_pOwner = this;
}

void CMonster::OnCollisionEnter(CCollider* pOther)
{
	CGameObject* pOtherObj = pOther->GetObj();

	if (pOtherObj->GetName() == L"Missile_Player")
	{
		m_iHP -= 1;
		if (m_iHP <= 0)
			DeleteObj(this);
	}
}