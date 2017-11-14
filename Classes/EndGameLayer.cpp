#include "EndGameLayer.h"
#include "PopScene.h"
#include "StartScene.h"

EndGameLayer::EndGameLayer(void)
{
	_drip = NULL;
	_bg = NULL;
	_sea = false;
	_home = false;
}


EndGameLayer::~EndGameLayer(void)
{
	this->unscheduleUpdate();
	NotificationCenter::getInstance()->removeAllObservers(this);
}

bool EndGameLayer::init()
{
	bool bRet;
	do
	{
		CC_BREAK_IF(!Layer::init());
		//添加背景
		this->initBG();
		//添加水滴
		this->initDrip();
		
		//订阅消息
		NotificationCenter::getInstance()->addObserver(this,callfuncO_selector(EndGameLayer::receiveActionMsg),"action",NULL);
		//启动定时器
		this->scheduleUpdate();
		
		bRet = true;
	}while(0);
	return bRet;
}

void EndGameLayer::initBG()
{
	_bg = Sprite::create("endBg.png");
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	_bg->setAnchorPoint(Point(0,0));
	this->addChild(_bg,-3);
}

void EndGameLayer::initDrip()
{
	_drip = Drip::create();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	_drip->setPosition(Point(origin.x+150, origin.y+120));
	_drip->setDesiredPosition(Point(_drip->getPosition()));
	this->addChild(_drip,0);
	_drip->idle();
}

void EndGameLayer::update(float dt)
{
	_drip->Update(dt);		
	this->updatePositions();
	this->setViewPointCenter(_drip->getPosition());

	
	if(!_sea && _drip->getPosition().x>500)
	{
		_sea = true;
		Size visibleSize = Director::getInstance()->getVisibleSize();
		CCRenderTexture *renderTexture = CCRenderTexture::create(visibleSize.width,visibleSize.height);

		renderTexture->begin(); 
		this->getParent ()->visit();
		renderTexture->end();

		auto seaHintScene = PopScene::create();
		seaHintScene->initWithDialogs("dialog/sea_",1,renderTexture);

		Director::getInstance()->pushScene(seaHintScene);
	}
	if(!_home && _drip->getPosition().x>1000)
	{	
		Size visibleSize = Director::getInstance()->getVisibleSize();
		CCRenderTexture *renderTexture = CCRenderTexture::create(visibleSize.width,visibleSize.height);

		renderTexture->begin(); 
		this->getParent()->visit();
		renderTexture->end();

		auto homeHintScene = PopScene::create();
		homeHintScene->initWithDialogs("dialog/home_",1,renderTexture);

		Director::getInstance()->pushScene(homeHintScene);
		_home = true;
	}

	if(_home && _drip->getPosition().x>1010)
	{
		this->unscheduleUpdate();
		auto startScene = StartScene::create();
		Director::getInstance()->replaceScene(startScene);

		Size visibleSize = Director::getInstance()->getVisibleSize();
		CCRenderTexture *renderTexture = CCRenderTexture::create(visibleSize.width,visibleSize.height);

		renderTexture->begin(); 
		this->getParent()->visit();
		renderTexture->end();

		auto passHint3 = PopScene::create();
		passHint3->initWithSprite("final3.jpg",renderTexture);

		auto passHint2 = PopScene::create();
		passHint2->initWithSprite("final2.jpg",renderTexture);

		auto passHint1 = PopScene::create();
		passHint1->initWithSprite("final1.jpg",renderTexture);

		Director::getInstance()->pushScene(passHint3);
		Director::getInstance()->pushScene(passHint2);
		Director::getInstance()->pushScene(passHint1);
	}
}

void EndGameLayer::updatePositions()
{
	float posX = MIN(_bg->getContentSize().width - _drip->getCenterToSides(),
        MAX(_drip->getCenterToSides(), _drip->getDesiredPosition().x));
	float posY = MIN(_bg->getContentSize().height + _drip->getCenterToBottom(),
		MAX(_drip->getCenterToBottom(), _drip->getDesiredPosition().y));
	
	 _drip->setPosition(Point(posX, posY));
	 
}

void EndGameLayer::setViewPointCenter(Point position)
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

void EndGameLayer::receiveActionMsg(Ref* pSender)
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
