#include "MineGameLayer.h"
#include "RestartScene.h"
#include "PopScene.h"
MineGameLayer::MineGameLayer(void)
{
	_drip = NULL;
	_bg = NULL;
	_barriers = NULL;
	_stone = NULL;
}


MineGameLayer::~MineGameLayer(void)
{
	this->unscheduleUpdate();
	NotificationCenter::getInstance()->removeAllObservers(this);
}

bool MineGameLayer::init()
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
		_barriers = MineBarriers::create();
		this->addChild(_barriers,-1);
		//初始化石头
		_stone = Sprite::create("mine/stone.png");
		_stone->setPosition(Point(-100,-100));
		this->addChild(_stone,1);
		//订阅消息
		NotificationCenter::getInstance()->addObserver(this,callfuncO_selector(MineGameLayer::receiveActionMsg),"action",NULL);
		//启动定时器
		this->scheduleUpdate();
		//游戏初始提示 
		this->scheduleOnce(schedule_selector(MineGameLayer::startHint),0.0f);
		this->schedule(schedule_selector(MineGameLayer::stoneFall),5.0f);
		
		bRet = true;
	}while(0);
	return bRet;
}

void MineGameLayer::initBG()
{
	_bg = Sprite::create("mine/mineBg.png");
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	_bg->setAnchorPoint(Point(0,0));
	this->addChild(_bg,-3);
}

void MineGameLayer::initDrip()
{
	_drip = Drip::create();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	_drip->setPosition(Point(origin.x+150, origin.y+200));
	_drip->setDesiredPosition(Point(_drip->getPosition()));
	this->addChild(_drip,0);
	_drip->idle();
}

void MineGameLayer::update(float dt)
{
	_drip->Update(dt);		
	this->updatePositions();
	this->setViewPointCenter(_drip->getPosition());
	_barriers->Update(_drip,dt);

	if(_drip->getHpPoints() <= 0)
	{
		//this->unscheduleUpdate();
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
	if(_stone->getBoundingBox().containsPoint(_drip->getPosition()))
	{
		_drip->hurtWithDamage(10);
	}
	if(_drip->getPosition().x>2900)
	{
		Director::getInstance()->popScene();
	}
}

void MineGameLayer::updatePositions()
{
	float posX = MIN(_bg->getContentSize().width - _drip->getCenterToSides(),
        MAX(_drip->getCenterToSides(), _drip->getDesiredPosition().x));
	float posY = MIN(_bg->getContentSize().height + _drip->getCenterToBottom(),
		MAX(_drip->getCenterToBottom(), _drip->getDesiredPosition().y));
	
	 _drip->setPosition(Point(posX, posY));
	 
}

void MineGameLayer::setViewPointCenter(Point position)
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

void MineGameLayer::receiveActionMsg(Ref* pSender)
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

void MineGameLayer::startHint(float dt)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	CCRenderTexture *renderTexture = CCRenderTexture::create(visibleSize.width,visibleSize.height);

	renderTexture->begin(); 
	this->getParent ()->visit();
	renderTexture->end();

	auto startHintScene = PopScene::create();
	startHintScene->initWithSprite("mine/mineStart.png",renderTexture);

	Director::getInstance()->pushScene(startHintScene);
}

void MineGameLayer::stoneFall(float dt)
{
	auto move1 = MoveBy::create(0.1,Point(-30,0));
	auto move2 = MoveBy::create(0.1,Point(30,0));
	auto move = Sequence::create(move1,move2,move2,move1,NULL);
	auto shake = Repeat::create(move,5);
	auto shaking = EaseSineInOut::create(shake);
	_bg->runAction(shaking);


	int x = _drip->getPosition().x;
	_stone->setPosition(Point(x,1000));
	
	auto smove = MoveTo::create(1,Point(x,0));
	_stone->runAction(smove);
}