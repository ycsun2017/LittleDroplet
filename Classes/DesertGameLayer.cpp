#include "DesertGameLayer.h"
#include "RestartScene.h"
#include "AppDelegate.h"
#include "PopScene.h"
#include "SimpleAudioEngine.h" 
#include "JungleGameScene.h"
using namespace CocosDenshion;  

DesertGameLayer::DesertGameLayer(void)
{
	_drip = NULL;
	_bg = NULL;
	_spars = NULL;
	_barriers = NULL;
	_cutter = NULL;
	_cutterEncounter = false;
	_cutterAlive = true;
	_levelPassed = false;
}


DesertGameLayer::~DesertGameLayer(void)
{
	this->unscheduleUpdate();
	NotificationCenter::getInstance()->removeAllObservers(this);
}

bool DesertGameLayer::init()
{
	bool bRet;
	do
	{
		CC_BREAK_IF(!Layer::init());
		AppDelegate* app = (AppDelegate*)Application::getInstance();
		app->setLevel(1);
		//添加背景
		this->initBG();
		//添加水滴
		this->initDrip();
		//添加障碍
		_barriers = DesertBarriers::create();
		this->addChild(_barriers,-1);
		//添加boss
		this->initCutter();
		//添加晶石
		_spars = Spars::create();
		this->addChild(_spars,-1);
		//订阅消息
		NotificationCenter::getInstance()->addObserver(this,callfuncO_selector(DesertGameLayer::receiveActionMsg),"action",NULL);
		NotificationCenter::getInstance()->addObserver(this,callfuncO_selector(DesertGameLayer::receiveStormMsg),"storm",NULL);
		//启动定时器
		this->scheduleUpdate();
		//游戏初始提示 
		this->scheduleOnce(schedule_selector(DesertGameLayer::startHint),0.5f);
		//this->schedule(schedule_selector(DesertGameLayer::stormBegin),10.0f);
		
		bRet = true;
	}while(0);
	return bRet;
}

void DesertGameLayer::initBG()
{
	_bg = Sprite::create("desert/desertBg.jpg");
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	_bg->setAnchorPoint(Point(0,0));
	this->addChild(_bg,-3);
}

void DesertGameLayer::initDrip()
{
	_drip = Drip::create();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	_drip->setPosition(Point(origin.x+150, origin.y+200));
	_drip->setDesiredPosition(Point(_drip->getPosition()));
	this->addChild(_drip,0);
	_drip->idle();
}

void DesertGameLayer::initCutter()
{
	_cutter = Sprite::create("desert/cutter.png");
	this->addChild(_cutter,0);
	_cutter->setPosition(Point(5700,100));
	_cutter->setAnchorPoint(Point(0,0));
	auto jump = JumpBy::create(2,Point(0,0),20,10);
	auto moveLeft = MoveBy::create(2,Point(-100,0));
	auto actionLeft = Spawn::create(jump,moveLeft,NULL);
	auto moveRight = MoveBy::create(2,Point(100,0));
	auto actionRight = Spawn::create(jump,moveRight,NULL);
	auto flip = FlipX::create(true);
	auto action = Sequence::create(actionLeft,flip,actionRight,flip->reverse(),NULL);
	auto actionRepeat = RepeatForever::create(action);
	_cutter->runAction(actionRepeat);
}
void DesertGameLayer::update(float dt)
{
	_drip->Update(dt);		
	this->updatePositions();
	this->setViewPointCenter(_drip->getPosition());
	_barriers->Update(_drip,dt);
	_spars->Update(_drip,dt);

	if(_drip->getHpPoints() <= 0)
	{
		//this->unscheduleUpdate();
		//auto restartScene = RestartScene::create();
		Size visibleSize = Director::getInstance()->getVisibleSize();
		CCRenderTexture *renderTexture = CCRenderTexture::create(visibleSize.width,visibleSize.height);
		renderTexture->begin(); 
		this->getParent()->visit();
		renderTexture->end();

		auto restartScene = PopScene::create();
		restartScene->initRestart(renderTexture);
		//restartScene->create(renderTexture);
		Director::getInstance()->replaceScene(restartScene);
	}

	if(_drip->getPosition().x>5400 && !_cutterEncounter)
	{
		_cutterEncounter = true;
		Size visibleSize = Director::getInstance()->getVisibleSize();
		CCRenderTexture *renderTexture = CCRenderTexture::create(visibleSize.width,visibleSize.height);

		renderTexture->begin(); 
		this->getParent()->visit();
		renderTexture->end();

		auto bossHint = PopScene::create();
		bossHint->initWithDialogs("dialog/cutter_",2,renderTexture);

		Director::getInstance()->pushScene(bossHint);
	}

	if(_cutterEncounter && _cutterAlive && _cutter->getBoundingBox().containsPoint(Point(_drip->getPosition().x,_drip->getPosition().y-_drip->getCenterToBottom())))
	{
		Rect cutterBox;
		//if(_cutterFlip)
		//	cutterBox.setRect(_cutter->getPosition().x+60, _cutter->getPosition().y+155, 65, 50);
		//else
			cutterBox.setRect(_cutter->getPosition().x+145, _cutter->getPosition().y+155, 65, 50);

	
		//if(cutterBox.containsPoint(Point(_drip->getPosition().x,_drip->getPosition().y-_drip->getCenterToBottom())))
		if(cutterBox.intersectsRect(_drip->getBoundingBox()))
		{
			cutterDie();
		}
		else
		{
			_drip->setDesiredPosition(_drip->getPosition()-Point(100,0));
			_drip->hurtWithDamage(10);
		}
	}

	if(_levelPassed)
	{
		auto jungleGameScene = JungleGameScene::create();
		Director::getInstance()->replaceScene(jungleGameScene);

		Size visibleSize = Director::getInstance()->getVisibleSize();
		CCRenderTexture *renderTexture = CCRenderTexture::create(visibleSize.width,visibleSize.height);

		renderTexture->begin(); 
		this->getParent()->visit();
		renderTexture->end();

		auto passHint2 = PopScene::create();
		passHint2->initWithSprite("desert/passHint2.png",renderTexture);

		auto passHint1 = PopScene::create();
		passHint1->initWithSprite("desert/passHint1.png",renderTexture);

		Director::getInstance()->pushScene(passHint2);
		Director::getInstance()->pushScene(passHint1);
	}
	

}

void DesertGameLayer::updatePositions()
{
	float posX = MIN(_bg->getContentSize().width - _drip->getCenterToSides(),
        MAX(_drip->getCenterToSides(), _drip->getDesiredPosition().x));
	float posY = MIN(_bg->getContentSize().height + _drip->getCenterToBottom(),
		MAX(_drip->getCenterToBottom(), _drip->getDesiredPosition().y));
	
	 _drip->setPosition(Point(posX, posY));
	 
}

void DesertGameLayer::setViewPointCenter(Point position)
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

void DesertGameLayer::receiveActionMsg(Ref* pSender)
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

void DesertGameLayer::receiveStormMsg(Ref* pSender)
{
	auto msg = (Integer*)pSender;
	switch (msg->getValue())
	{
	case 1:
		this->schedule(schedule_selector(DesertGameLayer::blowing));
		_drip->startBleeding();
		break;
	case 0:
		this->unschedule(schedule_selector(DesertGameLayer::blowing));
		_drip->endBleeding();
		break;
	}

	msg->release();

}


void DesertGameLayer::blowing(float dt)
{
	_drip->setPosition(Point(_drip->getDesiredPosition().x - 1, _drip->getDesiredPosition().y));
	_drip->setDesiredPosition(_drip->getPosition());
}

void DesertGameLayer::cutterDie()
{
	_cutter->stopAllActions();
	CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("desert/cutterStopped.png");
    _cutter->setTexture(texture);
	_cutterAlive = false;
	this->scheduleOnce(schedule_selector(DesertGameLayer::getCard),1.0f);
}

void DesertGameLayer::getCard(float dt)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	CCRenderTexture *renderTexture = CCRenderTexture::create(visibleSize.width,visibleSize.height);

	renderTexture->begin(); 
	this->getParent()->visit();
	renderTexture->end();

	auto getCardHint = PopScene::create();
	getCardHint->initWithDialogs("dialog/tree_",1,renderTexture);

	auto cardHint = PopScene::create();
	cardHint->initWithSprite("desert/card.png",renderTexture);

	Director::getInstance()->pushScene(cardHint);
	Director::getInstance()->pushScene(getCardHint);
	_levelPassed = true;
}

void DesertGameLayer::startHint(float dt)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	CCRenderTexture *renderTexture = CCRenderTexture::create(visibleSize.width,visibleSize.height);

	renderTexture->begin(); 
	this->getParent ()->visit();
	renderTexture->end();

	auto startHintScene = PopScene::create();
	startHintScene->initWithCsb("desertStartHint.csb",renderTexture);

	Director::getInstance()->pushScene(startHintScene);
}