#include "Storm.h"
#include "AppDelegate.h"
#include "SimpleAudioEngine.h" 
using namespace CocosDenshion; 

Storm::Storm(void)
{
	m_storm = NULL;
}


Storm::~Storm(void)
{
}

bool Storm::init()
{
	bool bRet = false;
	do{
		m_storm = Sprite::create("desert/storm.png");
		this->addChild(m_storm);
		m_storm->setAnchorPoint(Point(0,0));
		m_storm->setPosition(Point(0,0));
		m_storm->setOpacity(200);
		m_storm->setVisible(false);


		this->schedule(schedule_selector(Storm::stormAppear),10.0f);
		bRet = true;
	}while(0);

	return bRet;
}

void Storm::stormAppear(float dt)
{
	m_storm->setVisible(true);
	m_storm->setAnchorPoint(Point(0,0));
	m_storm->setPosition(Point(0,0));
	m_storm->setOpacity(200);
	auto msg = Integer::create(1);
	msg->retain();
	NotificationCenter::getInstance()->postNotification("storm",msg);

	AppDelegate* app = (AppDelegate*)Application::getInstance();
	if(app->getEffectState()==true)
		SimpleAudioEngine::sharedEngine()->playEffect("desert/storm.wav",false);

	auto blink = Blink::create(4,6);
	auto move = MoveBy::create(4,Point(-100,0));
	auto fadeout = FadeOut::create(0.5);
	m_storm->runAction(Sequence::create(Spawn::create(blink,move,NULL),fadeout,CCCallFunc::create(this, callfunc_selector(Storm::stormDisappear)),NULL));
}

void Storm::stormDisappear()
{
	auto msg = Integer::create(0);
	msg->retain();
	NotificationCenter::getInstance()->postNotification("storm",msg);

	m_storm->setVisible(false);
}