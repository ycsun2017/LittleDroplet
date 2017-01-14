#include "Spars.h"

Spars::Spars(void)
{
}


Spars::~Spars(void)
{
}

bool Spars::init()
{
	bool bRet = false;
	do
	{
		for(int i=0;i<SPAR_NUM;i++)
		{
			auto spar = Spar::create();
			this->addChild(spar);
			int x = 500 + CCRANDOM_0_1() * 5000;
			int y = 150 + CCRANDOM_0_1() * 350;
			spar->setPosition(Point(x,y));
			m_spars.pushBack(spar);
		}

		bRet = true;
	}while(0);
	return bRet;
}