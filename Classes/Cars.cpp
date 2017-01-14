#include "Cars.h"
#include "SimpleAudioEngine.h" 
#include "AppDelegate.h"
using namespace CocosDenshion;  

Cars::Cars(void)
{
}


Cars::~Cars(void)
{
	this->unscheduleAllSelectors();
}

bool Cars::init()
{
	bool bRet = false;
	do{
		car1 = Sprite::create("car1.png");
		this->addChild(car1);
		car1->setPosition(Point(-500,220));
		car2 = Sprite::create("car2.png");
		this->addChild(car2);
		car2->setPosition(Point(6500,220));

		this->schedule(schedule_selector(Cars::createCar1),8.0f);
		this->schedule(schedule_selector(Cars::createCar2),11.0f);
		this->scheduleOnce(schedule_selector(Cars::lastCar),15.0f);

		SimpleAudioEngine::sharedEngine()->preloadEffect("carPassbyEffect.wav");

		bRet = true;
	}while(0);
	return bRet;
}

void Cars::createCar1(float dt)
{
	car1->setPosition(Point(-500,220));
	auto move = MoveTo::create(5,Point(6500,220));
	car1->runAction(move);
	
	AppDelegate* app = (AppDelegate*)Application::getInstance();
	if(app->getEffectState()==true)
		SimpleAudioEngine::sharedEngine()->playEffect("carPassbyEffect.wav",false);
}

void Cars::createCar2(float dt)
{
	car2->setPosition(Point(6500,220));
	auto move = MoveTo::create(5,Point(-500,220));
	car2->runAction(move);
	AppDelegate* app = (AppDelegate*)Application::getInstance();
	if(app->getEffectState()==true)
		SimpleAudioEngine::sharedEngine()->playEffect("carPassbyEffect.wav",false);
}

void Cars::lastCar(float dt)
{
	this->unscheduleAllSelectors();
}