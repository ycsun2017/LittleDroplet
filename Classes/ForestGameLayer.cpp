#include "ForestGameLayer.h"
#include "StomachGameScene.h"
#include "RestartScene.h"
#include "PopScene.h"
#include "ForestGameScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
using namespace cocostudio::timeline;

ForestGameLayer::ForestGameLayer(void)
{
	_drip = NULL;
	_bg = NULL;
	_barriers = NULL;
	_monster = NULL;
	_bottleNum = 5;
	_bottlePassed = false;
	_mosterAppear = false;
	for(int i=0;i<_bottleNum;i++)
	{
		_bottleAlive[i] = true;
	}
}


ForestGameLayer::~ForestGameLayer(void)
{
	this->unscheduleUpdate();
	NotificationCenter::getInstance()->removeAllObservers(this);
}

bool ForestGameLayer::init()
{
	bool bRet;
	do
	{
		CC_BREAK_IF(!Layer::init());
		//添加背景
		this->initBG();
		//添加水滴
		this->initDrip();
		//添加障碍
		_barriers = ForestBarriers::create();
		this->addChild(_barriers,-1);
		//添加水瓶
		this->initBottles();
		//添加boss
		//this->initMonster();
		//订阅消息
		NotificationCenter::getInstance()->addObserver(this,callfuncO_selector(ForestGameLayer::receiveActionMsg),"action",NULL);
		//启动定时器
		this->scheduleUpdate();
		
		bRet = true;
	}while(0);
	return bRet;
}

void ForestGameLayer::initBG()
{
	_bg = Sprite::create("forest/forestBg.png");
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	_bg->setAnchorPoint(Point(0,0));
	this->addChild(_bg,-3);
}

void ForestGameLayer::initDrip()
{
	_drip = Drip::create();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	_drip->setPosition(Point(origin.x+150, origin.y+200));
	_drip->setDesiredPosition(Point(_drip->getPosition()));
	this->addChild(_drip,0);
	_drip->idle();
}

void ForestGameLayer::initBottles()
{
	float xPos = 500;
	for(int i=0;i<5;i++)
	{
		auto bottle = Sprite::create("forest/bottle.png");
		xPos = xPos+400+CCRANDOM_0_1()*400;
		bottle->setPosition(Point(xPos,150));
		bottle->setRotation(CCRANDOM_0_1()*360);
		this->addChild(bottle);
		_bottles.pushBack(bottle);
	}
}

void ForestGameLayer::initMonster()
{
	_monster = Sprite::create("forest/monster.png");
	_monster->setPosition(Point(4700,300));
	this->addChild(_monster);
	auto walk1 = RotateBy::create(0.1,5);
	auto walk2 = Sequence::create(walk1,walk1->reverse(),NULL);
	auto walk3 = RotateBy::create(0.2,-10);
	auto walk4 = Sequence::create(walk3,walk3->reverse(),NULL);
	auto move = MoveBy::create(0.6,Point(-100,0));
	auto walk = Sequence::create(walk2,walk4,NULL);
	auto moveWalk= Spawn::create(move,walk,NULL);
	_monster->runAction(RepeatForever::create(moveWalk));
}

void ForestGameLayer::update(float dt)
{
	_drip->Update(dt);		
	this->updatePositions();
	this->setViewPointCenter(_drip->getPosition());
	_barriers->Update(_drip,dt);

	if(_drip->getHpPoints() <= 0)
	{
	//	this->unscheduleUpdate();
		Size visibleSize = Director::getInstance()->getVisibleSize();
		CCRenderTexture *renderTexture = CCRenderTexture::create(visibleSize.width,visibleSize.height);
		renderTexture->begin(); 
		this->getParent()->visit();
		renderTexture->end();

		auto restartScene = PopScene::create();
		restartScene->initRestart(renderTexture);
		Director::getInstance()->replaceScene(restartScene);
	}

	int num = 0;
	for(int i=0;i<_bottleNum;i++)
	{
		if(_bottleAlive[i])
		{
			num++;
			auto bottle = _bottles.at(i);
			if(bottle->getBoundingBox().intersectsRect(_drip->getBoundingBox()))
			{
				bottle->setVisible(false);
				_bottleAlive[i] = false;
				this->bottleHint();
			}
		}
	}
	if(num==0)
	{
		_bottlePassed = true;
	}

	if(!_bottlePassed && _drip->getPosition().x>4000)
	{
		_bottlePassed = true;
		auto forestGameScene = ForestGameScene::create();
		Director::getInstance()->replaceScene(forestGameScene);

		Size visibleSize = Director::getInstance()->getVisibleSize();
		CCRenderTexture *renderTexture = CCRenderTexture::create(visibleSize.width,visibleSize.height);

		renderTexture->begin(); 
		this->getParent ()->visit();
		renderTexture->end();

		auto mudHintScene1 = PopScene::create();
		mudHintScene1->initWithSprite("forest/fire1.png",renderTexture);
		auto mudHintScene2 = PopScene::create();
		mudHintScene2->initWithSprite("forest/fire2.png",renderTexture);
		Director::getInstance()->pushScene(mudHintScene2);
		Director::getInstance()->pushScene(mudHintScene1);
	}
	if(!_mosterAppear && _drip->getPosition().x>4100)
	{
		this->initMonster();
		_mosterAppear = true;
	}
	if(_mosterAppear && _monster->getBoundingBox().intersectsRect(_drip->getBoundingBox()))
	{
		auto scene = StomachGameScene::create();
		Director::getInstance()->replaceScene(scene);
	}
}

void ForestGameLayer::updatePositions()
{
	float posX = MIN(_bg->getContentSize().width - _drip->getCenterToSides(),
        MAX(_drip->getCenterToSides(), _drip->getDesiredPosition().x));
	float posY = MIN(_bg->getContentSize().height + _drip->getCenterToBottom(),
		MAX(_drip->getCenterToBottom(), _drip->getDesiredPosition().y));
	
	 _drip->setPosition(Point(posX, posY));
	 
}

void ForestGameLayer::setViewPointCenter(Point position)
{
	Size winSize = Director::getInstance()->getVisibleSize();
	int x = MAX(position.x, winSize.width / 2);
    int y = MAX(position.y, winSize.height / 2);
    //x = MIN(x, _bg1->getContentSize().width + _bg2->getContentSize().width - winSize.width / 2);
	x = MIN(x, _bg->getContentSize().width - winSize.width / 2);
    y = MIN(y, _bg->getContentSize().height  - winSize.height / 2);
    Point actualPosition = Point(x, y);

    Point centerOfView = Point(winSize.width / 2, winSize.height / 2);
    Point viewPoint = ccpSub(centerOfView, actualPosition);
	
    this->setPosition(viewPoint);
}

void ForestGameLayer::receiveActionMsg(Ref* pSender)
{
	auto msg = (Integer*)pSender;
	switch (msg->getValue())
	{
	case GORIGHTACTION:
		if(_drip->getActionState() == kActionStateIdle)
			_drip->walkWithDirection(Point(1.0,0));
		//log("right");
		break;
	case GOLEFTACTION:
		if(_drip->getActionState() == kActionStateIdle)
			_drip->walkWithDirection(Point(-1.0,0));
		//log("left");
		break;
	case JUMPACTION:
		if(_drip->getActionState() == kActionStateIdle || _drip->getActionState() == kActionStateWalkLeft
			||_drip->getActionState() == kActionStateWalkRight)
		//log("jump");
			_drip->jump();
		break;
	case IDLEACTION:
		if(_drip->getActionState() == kActionStateWalkLeft ||_drip->getActionState() == kActionStateWalkRight)
			_drip->idle();
		//log("idle");
		break;
	}

	msg->release();

}

void ForestGameLayer::bottleHint()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	CCRenderTexture *renderTexture = CCRenderTexture::create(visibleSize.width,visibleSize.height);

	renderTexture->begin(); 
	this->getParent ()->visit();
	renderTexture->end();

	auto startHintScene = PopScene::create();
	startHintScene->initWithSprite("forest/bottleHint.png",renderTexture);

	Director::getInstance()->pushScene(startHintScene);
}

void ForestGameLayer::fire()
{
	/*auto forestGameScene = ForestGameScene::create();
	Director::getInstance()->replaceScene(forestGameScene);*/

	Size visibleSize = Director::getInstance()->getVisibleSize();
	CCRenderTexture *renderTexture = CCRenderTexture::create(visibleSize.width,visibleSize.height);

	renderTexture->begin(); 
	this->getParent ()->visit();
	renderTexture->end();

	auto mudHintScene1 = PopScene::create();
	mudHintScene1->initWithSprite("forest/fire1.png",renderTexture);
	auto mudHintScene2 = PopScene::create();
	mudHintScene2->initWithSprite("forest/fire2.png",renderTexture);
	Director::getInstance()->pushScene(mudHintScene2);
	Director::getInstance()->pushScene(mudHintScene1);
}