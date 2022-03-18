#include "framework.h"
#include "CTitleObject.h"

CTitleObject::CTitleObject()
{
    m_fptPos = {};
    m_fptScale = {};
}

CTitleObject::CTitleObject(const CTitleObject& other)
{
    m_fptPos = other.m_fptPos;
    m_fptScale = other.m_fptScale;
}

CTitleObject::~CTitleObject()
{

}

void CTitleObject::SetPos(fPoint pos)
{
    m_fptPos = pos;
}

void CTitleObject::SetScale(fPoint scale)
{
    m_fptScale = scale;
}

fPoint CTitleObject::GetPos()
{
    return m_fptPos;
}

fPoint CTitleObject::GetScale()
{
    return m_fptScale;
}

void CTitleObject::update()
{
}
