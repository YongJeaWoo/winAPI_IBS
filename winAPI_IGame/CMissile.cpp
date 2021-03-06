#include "framework.h"
#include "CMissile.h"
#include "CCollider.h"

CMissile* CMissile::Clone()
{
	return new CMissile(*this);
}

CMissile::CMissile()
{
	SetScale(fPoint(25.f, 25.f));
	m_fvDir = fVec2(0, 0);
	SetName(L"Missile_Player");

	CreateCollider();
	GetCollider()->SetScale(fPoint(15.f, 15.f));
}

CMissile::~CMissile()
{
}

void CMissile::update()
{
	fPoint pos = GetPos();

	pos.x += m_fSpeed * m_fvDir.x * fDT;
	pos.y += m_fSpeed * m_fvDir.y * fDT;

	SetPos(pos);

	if (pos.x < 0 || pos.x > WINSIZEX
		|| pos.y < 0 || pos.y > WINSIZEY)
		DeleteObj(this);
}

void CMissile::render()
{
	fPoint pos = GetPos();
	fPoint scale = GetScale();

	fPoint fptRenderPos = CCameraManager::getInst()->GetRenderPos(pos);

	CRenderManager::getInst()->RenderEllipse
	(
		fptRenderPos.x,
		fptRenderPos.y,
		scale.x / 2.f,
		scale.y / 2.f
	);

	component_render();
}

void CMissile::SetDir(fVec2 vec)
{
	m_fvDir = vec.Normalize();
}

void CMissile::SetDir(float theta)
{
	m_fvDir.x = (float)cos(theta);
	m_fvDir.y = (float)sin(theta);
}

void CMissile::OnCollisionEnter(CCollider* pOther)
{
	
	CGameObject* pOtherObj = pOther->GetObj();
	if (pOtherObj->GetName() == L"Zen")
	{
		DeleteObj(this);
	}
	if (pOtherObj->GetName() == L"Tile")
	{
		CMissile::m_fSpeed = 100.f;//t스피드 바꾸기
		this->SetDir(fPoint(0, -1.f));//
		//TODO:여기서 if문 써서 타일이 플랫폼인지 wall인지 체크해야함
		//TODO:천장이랑 닿으면 if문 써서 Celling이면 부자연스럽게 강체 추가?
	}
	if (pOtherObj->GetName()==L"Missile")
	{
		CMissile::m_fSpeed =100.f;
		this->SetDir(fPoint(0, -1.f));
	}
}
