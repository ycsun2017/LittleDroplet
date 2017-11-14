#include "GameLayer.h"
#include "cocostudio\CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Barrier.h"
#include "Bg.h"
#include "RestartScene.h"
#include "PopScene.h"
#include "AppDelegate.h"
#include "Cars.h"
#include "HelloWorldScene.h"
using namespace cocostudio;
using namespace ui;
GameLayer::GameLayer(void)
{
	_drip = NULL;
	_ui = NULL;
	_bg1 = NULL;
	_bg2 = NULL;
	_barriers = NULL;
	_cars = NULL;
	_mask = NULL;
	_bags = NULL;
}


GameLayer::~GameLayer(void)
{
	this->unscheduleUpdate();
	NotificationCenter::getInstance()->removeAllObservers(this);
}

bool GameLayer::init()
{
	bool bRet;
	do
	{
		CC_BREAK_IF(!Layer::init());
		AppDelegate* app = (AppDelegate*)Application::getInstance();
		app->setLevel(2);
		//添加背景
		this->initBG();
		//添加水滴
		this->initDrip();
		//添加障碍
		_barriers = Barriers::create();
		this->addChild(_barriers,-1);
		//添加口罩
		_mask = Sprite::create("mask.png");
		_mask->setPosition(Point(3500,500)); 
		_mask->setTag(3);
		this->addChild(_mask,-1);
		//添加汽车
		_cars = Cars::create();
		this->addChild(_cars,-2);
		//添加垃圾袋
		_bags = Bags::create();
		this->addChild(_bags,1);
		//订阅消息
		NotificationCenter::getInstance()->addObserver(this,callfuncO_selector(GameLayer::receiveActionMsg),"action",NULL);
		//启动定时器
		this->scheduleUpdate();
		//游戏初始提示 
		this->scheduleOnce(schedule_selector(GameLayer::startHint),0.5f);
		//雾霾加重
		this->scheduleOnce(schedule_selector(GameLayer::deeperHaze),15.0f);
		bRet = true;
	}while(0);
	return bRet;
}

void GameLayer::update(float dt)
{
	//更新位置
	_drip->Update(dt);		
	this->updatePositions();
	this->setViewPointCenter(_drip->getPosition());
	_barriers->Update(_drip,dt);
	_bags->Update(_drip,dt);
	this->updateMask();
	
	//生命值降为0的提示--重新开始
	if(_drip->getHpPoints() <= 0)
	{
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

	//触发垃圾桶小游戏的提示
	if(_drip->getPosition().x > 5600)
	//if(_drip->getPosition().x > 500)
	{
		this->unscheduleUpdate();

		auto litterScene = Bg::createScene();
		Director::getInstance()->replaceScene(litterScene);
		
		Size visibleSize = Director::getInstance()->getVisibleSize();
		CCRenderTexture *renderTexture = CCRenderTexture::create(visibleSize.width,visibleSize.height);
		renderTexture->begin(); 
		this->getParent()->visit();
		renderTexture->end();

		auto newHint = PopScene::create();
		newHint->initWithCsb("newSceneHint.csb",renderTexture);

		Director::getInstance()->pushScene(newHint);
	}

	//log("x=%f,y=%f,(%f,%f)",this->getPosition().x,this->getPosition().y,_drip->getPosition().x,_drip->getPosition().y);
	/*if(hinder->getBoundingBox().containsPoint(_drip->getPosition()))
	{
		_drip->hurt();
		hinder->setPosition(Point(1000,1000));
	}*/
}

void GameLayer::updatePositions()
{
	float posX = MIN(_bg1->getContentSize().width + _bg2->getContentSize().width - _drip->getCenterToSides(),
        MAX(_drip->getCenterToSides(), _drip->getDesiredPosition().x));
	float posY = MIN(_bg1->getContentSize().height + _drip->getCenterToBottom(),
		MAX(_drip->getCenterToBottom(), _drip->getDesiredPosition().y));
	
	 _drip->setPosition(Point(posX, posY));
	 
}

void GameLayer::setViewPointCenter(Point position)
{
	Size winSize = Director::getInstance()->getVisibleSize();
	int x = MAX(position.x, winSize.width / 2);
    int y = MAX(position.y, winSize.height / 2);
    x = MIN(x, _bg1->getContentSize().width + _bg2->getContentSize().width - winSize.width / 2);
    y = MIN(y, _bg1->getContentSize().height  - winSize.height / 2);
    Point actualPosition = Point(x, y);

    Point centerOfView = Point(winSize.width / 2, winSize.height / 2);
    Point viewPoint = ccpSub(centerOfView, actualPosition);
	
    this->setPosition(viewPoint);
}

void GameLayer::initBG()
{
	_bg1 = Sprite::create("cityBGp1.png");
	_bg2 = Sprite::create("cityBGp2.png");
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	_bg1->setAnchorPoint(Point(0,0));
	_bg1->setPosition(origin);
	this->addChild(_bg1,-3);
	_bg2->setAnchorPoint(Point(0,0));
	_bg2->setPosition(Point(_bg1->getContentSize().width,0));
	this->addChild(_bg2,-3);
}

void GameLayer::initDrip()
{
	_drip = Drip::create();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	_drip->setPosition(Point(origin.x+150, origin.y+200));
	_drip->setDesiredPosition(Point(_drip->getPosition()));
	this->addChild(_drip,0);
	_drip->idle();
}

void GameLayer::receiveActionMsg(Ref* pSender)
{
	auto msg = (Integer*)pSender;
	switch (msg->getValue())
	{
	case GORIGHTACTION:
		if(_drip->getActionState() == kActionStateIdle)
			_drip->walkWithDirection(Point(1.0,0));
		break;
	case GOLEFTACTION:
		if(_drip->getActionState() == kActionStateIdle)
			_drip->walkWithDirection(Point(-1.0,0));
		break;
	case JUMPACTION:
		if(_drip->getActionState() == kActionStateIdle || _drip->getActionState() == kActionStateWalkLeft
			||_drip->getActionState() == kActionStateWalkRight)
			_drip->jump();
		break;
	case IDLEACTION:
		if(_drip->getActionState() == kActionStateWalkLeft ||_drip->getActionState() == kActionStateWalkRight)
			_drip->idle();
		break;
	}

	msg->release();
}

void GameLayer::deeperHaze(float dt)
{
	_drip->startBleeding();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	CCRenderTexture *renderTexture = CCRenderTexture::create(visibleSize.width,visibleSize.height);

	renderTexture->begin(); 
	this->getParent()->visit();
	renderTexture->end();

	auto deeperHazeHint = PopScene::create();
	deeperHazeHint->initWithSprite("deeperHaze.png",renderTexture);

	Director::getInstance()->pushScene(deeperHazeHint);

	/*auto hint = Sprite::create("deeperHaze.png");
	Size visibleSize = Director::getInstance()->getVisibleSize();
	hint->setPosition(Point(_drip->getPosition().x,visibleSize.height/2));
	this->addChild(hint);

	auto blink = Blink::create(1,1);
	auto delay = DelayTime::create(2);
	auto fadeout = FadeOut::create(1);
	hint->runAction(Sequence::create(blink,delay,fadeout,NULL));*/


}

void GameLayer::startHint(float dt)
{
	//召唤游戏操作提示弹窗
	/*auto msg = Integer::create(1);
	msg->retain();
	NotificationCenter::getInstance()->postNotification("add",msg);*/

	Size visibleSize = Director::getInstance()->getVisibleSize();
	CCRenderTexture *renderTexture = CCRenderTexture::create(visibleSize.width,visibleSize.height);

	renderTexture->begin(); 
	this->getParent()->visit();
	renderTexture->end();

	auto startHintScene = PopScene::create();
	startHintScene->initWithCsb("cityStartHint.csb",renderTexture);

	Director::getInstance()->pushScene(startHintScene);
	
}

void GameLayer::updateMask()
{
	if( _mask!= NULL && _mask->getBoundingBox().intersectsRect(_drip->getBoundingBox()))
	{
		_drip->endBleeding();
		this->removeChildByTag(3);
		_mask = NULL;
		this->getMask();
	}
}
void GameLayer::getMask()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	CCRenderTexture *renderTexture = CCRenderTexture::create(visibleSize.width,visibleSize.height);

	renderTexture->begin(); 
	this->getParent()->visit();
	renderTexture->end();

	auto getMask = PopScene::create();
	getMask->initWithSprite("getMask.png",renderTexture);

	Director::getInstance()->pushScene(getMask);
}
