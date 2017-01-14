#include "Haze.h"


Haze::Haze(void)
{
	m_haze = NULL;
}


Haze::~Haze(void)
{
	this->unscheduleAllSelectors();
}

bool Haze::init()
{
	bool bRet = false;
	do{
		m_haze = Sprite::create("haze.png");
		this->addChild(m_haze);
		m_haze->setAnchorPoint(Point(0,0));
		m_haze->setPosition(Point(0,0));
		m_haze->setOpacity(0);

		thickness = 0;

		this->schedule(schedule_selector(Haze::deepen),0.1f);
		bRet = true;
	}while(0);

	return bRet;
}

void Haze::deepen(float dt)
{
	if(thickness<255)
	{
		thickness += 1;
		m_haze->setOpacity(thickness);
	}
	else
		this->unschedule(schedule_selector(Haze::deepen));  
}