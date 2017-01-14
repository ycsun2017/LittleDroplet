#include "Spar.h"


Spar::Spar(void)
{
}


Spar::~Spar(void)
{
}

bool Spar::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!Sprite::init());
		m_spar = Sprite::create("desert/spar.png");
		this->addChild(m_spar);
		Size size = m_spar->getContentSize();
		m_spar->setPosition(Point(size.width*0.5f,size.height*0.5f));
		this->setContentSize(size);

		bRet = true;
	}while(0);
	return bRet;
}