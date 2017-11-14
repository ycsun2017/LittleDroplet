#include "Spars.h"
#include "AppDelegate.h"
#include "SimpleAudioEngine.h" 
using namespace CocosDenshion;  

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

void Spars::Update(Drip* drip,float dt)
{
	for(auto spar : m_spars)
	{
		if(spar->isAlive())
		{
			if(drip->getBoundingBox().intersectsRect(spar->getBoundingBox()))
			{
				spar->hide();
				auto msg = Integer::create(1);
				msg->retain();
				NotificationCenter::getInstance()->postNotification("spars",msg);

				AppDelegate* app = (AppDelegate*)Application::getInstance();
				if(app->getEffectState()==true)
					SimpleAudioEngine::sharedEngine()->playEffect("getSparEffect.wav",false);
			}
		}
	}

}