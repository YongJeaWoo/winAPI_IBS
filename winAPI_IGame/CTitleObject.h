#pragma once
class CTitleObject
{
private:
	fPoint m_fptPos;
	fPoint m_fptScale;

public:
	CTitleObject();
	CTitleObject(const CTitleObject& other);
	virtual ~CTitleObject();

	void SetPos(fPoint pos);
	void SetScale(fPoint scale);

	fPoint GetPos();
	fPoint GetScale();

	virtual void update();
};

