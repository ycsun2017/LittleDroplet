#include "StomachGameLayer.h"
#include "PopScene.h"
#include "GameScene.h"

StomachGameLayer::StomachGameLayer(void)
{
	_drip = NULL;
	_bg = NULL;
	_battery = NULL;
}


StomachGameLayer::~StomachGameLayer(void)
{
	this->unscheduleUpdate();
	NotificationCenter::getInstance()->removeAllObservers(this);
}

bool StomachGameLayer::init()
{
	bool bRet;
	do
	{
		CC_BREAK_IF(!Layer::init());
		//添加背景
		this->initBG();
		//添加水滴
		this->initDrip();
		//添加电池
		_battery = Sprite::create("forest/battery.png");
		this->addChild(_battery);
		_battery->setPosition(Point(700,500));
		//订阅消息
		NotificationCenter::getInstance()->addObserver(this,callfuncO_selector(StomachGameLayer::receiveActionMsg),"action",NULL);
		//启动定时器
		this->scheduleUpdate();
		//游戏初始提示 
		this->scheduleOnce(schedule_selector(StomachGameLayer::startHint),0.0f);
		
		bRet = true;
	}while(0);
	return bRet;
}
void StomachGameLayer::initBG()
{
	_bg = Sprite::create("forest/stomachBg.png");
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	_bg->setAnchorPoint(Point(0,0));
	this->addChild(_bg,-3);
}

void StomachGameLayer::initDrip()
{
	_drip = Drip::create();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	_drip->setPosition(Point(origin.x+150, origin.y+200));
	_drip->setDesiredPosition(Point(_drip->getPosition()));
	this->addChild(_drip,0);
	_drip->idle();
}

void StomachGameLayer::update(float dt)
{
	_drip->Update(dt);		
	this->updatePositions();
	this->setViewPointCenter(_drip->getPosition());
	if(_drip->getBoundingBox().containsPoint(_battery->getPosition()))
	{
		auto cityGameScene = GameScene::create();
		Director::getInstance()->replaceScene(cityGameScene);

		Size visibleSize = Director::getInstance()->getVisibleSize();
		CCRenderTexture *renderTexture = CCRenderTexture::create(visibleSize.width,visibleSize.height);

		renderTexture->begin(); 
		this->getParent()->visit();
		renderTexture->end();

		auto batteryHint1 = PopScene::create();
		batteryHint1->initWithSprite("forest/battery1.jpg",renderTexture);

		auto batteryHint2 = PopScene::create();
		batteryHint2->initWithSprite("forest/battery2.jpg",renderTexture);

		auto batteryHint3 = PopScene::create();
		batteryHint3->initWithSprite("forest/battery3.jpg",renderTexture);

		auto batteryHint4 = PopScene::create();
		batteryHint4->initWithSprite("forest/battery4.jpg",renderTexture);

		Director::getInstance()->pushScene(batteryHint4);
		Director::getInstance()->pushScene(batteryHint3);
		Director::getInstance()->pushScene(batteryHint2);
		Director::getInstance()->pushScene(batteryHint1);
	}
}

void StomachGameLayer::updatePositions()
{
	float posX = MIN(_bg->getContentSize().width - _drip->getCenterToSides(),
        MAX(_drip->getCenterToSides(), _drip->getDesiredPosition().x));
	float posY = MIN(_bg->getContentSize().height + _drip->getCenterToBottom(),
		MAX(_drip->getCenterToBottom(), _drip->getDesiredPosition().y));
	
	 _drip->setPosition(Point(posX, posY));
	 
}

void StomachGameLayer::setViewPointCenter(Point position)
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

void StomachGameLayer::receiveActionMsg(Ref* pSender)
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

void StomachGameLayer::startHint(float dt)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	CCRenderTexture *renderTexture = CCRenderTexture::create(visibleSize.width,visibleSize.height);

	renderTexture->begin(); 
	this->getParent()->visit();
	renderTexture->end();

	auto startHintScene = PopScene::create();
	startHintScene->initWithDialogs("dialog/stomach_",2,renderTexture);

	Director::getInstance()->pushScene(startHintScene);
}