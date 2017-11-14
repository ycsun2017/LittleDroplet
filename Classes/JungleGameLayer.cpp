#include "JungleGameLayer.h"
#include "JungleGameScene.h"
#include "GameScene.h"
#include "RestartScene.h"
#include "ForestGameScene.h"
#include "AppDelegate.h"
#include "MineGameScene.h"
#include "PopScene.h"
JungleGameLayer::JungleGameLayer(void)
{
	_drip = NULL;
	_bg = NULL;
	_spars = NULL;
	_mine = 0;
	_selected = -1;
	_planted = false;
}


JungleGameLayer::~JungleGameLayer(void)
{
	this->unscheduleUpdate();
	NotificationCenter::getInstance()->removeAllObservers(this);
}

bool JungleGameLayer::init()
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
		//添加晶石
		_spars = Spars::create();
		this->addChild(_spars,-1);
		//订阅消息
		NotificationCenter::getInstance()->addObserver(this,callfuncO_selector(JungleGameLayer::receiveActionMsg),"action",NULL);
		NotificationCenter::getInstance()->addObserver(this,callfuncO_selector(JungleGameLayer::receiveSelectMsg),"select",NULL);
		//启动定时器
		this->scheduleUpdate();
		//游戏初始提示 
		this->scheduleOnce(schedule_selector(JungleGameLayer::startHint),0.5f);
		bRet = true;
	}while(0);
	return bRet;
}

void JungleGameLayer::initBG()
{
	_bg = Sprite::create("jungle/jungleBg.png");
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	_bg->setAnchorPoint(Point(0,0));
	this->addChild(_bg,-3);
}

void JungleGameLayer::initDrip()
{
	_drip = Drip::create();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	_drip->setPosition(Point(origin.x+150, origin.y+200));
	_drip->setDesiredPosition(Point(_drip->getPosition()));
	this->addChild(_drip,0);
	_drip->idle();
}

void JungleGameLayer::update(float dt)
{
	_drip->Update(dt);		
	this->updatePositions();
	this->setViewPointCenter(_drip->getPosition());
	_spars->Update(_drip,dt);

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

	if(_drip->getPosition().x>600)
	{
		if(_mine==0)
		{
			_mine = 1;
			auto mineScene = MineGameScene::create();
			NotificationCenter::getInstance()->removeAllObservers(this);
			Director::getInstance()->pushScene(mineScene);
		}
		else if(_mine==1)
		{
			log("1");
			_mine = 2;
			NotificationCenter::getInstance()->addObserver(this,callfuncO_selector(JungleGameLayer::receiveActionMsg),"action",NULL);
			NotificationCenter::getInstance()->addObserver(this,callfuncO_selector(JungleGameLayer::receiveSelectMsg),"select",NULL);
		}
	}
	if(_selected==-1 && _drip->getPosition().x>1200)
	{
		Size visibleSize = Director::getInstance()->getVisibleSize();
		CCRenderTexture *renderTexture = CCRenderTexture::create(visibleSize.width,visibleSize.height);

		renderTexture->begin(); 
		this->getParent ()->visit();
		renderTexture->end();

		auto selectHintScene = PopScene::create();
		selectHintScene->initWithSelect("selectHint.csb",renderTexture);

		Director::getInstance()->pushScene(selectHintScene);
	}
	if(_selected==2)
	{
		_selected = 0;
		Size visibleSize = Director::getInstance()->getVisibleSize();
		CCRenderTexture *renderTexture = CCRenderTexture::create(visibleSize.width,visibleSize.height);

		renderTexture->begin(); 
		this->getParent ()->visit();
		renderTexture->end();

		auto selectHintScene = PopScene::create();
		selectHintScene->initWithSprite("jungle/failPlant.png",renderTexture);

		Director::getInstance()->pushScene(selectHintScene);
	}
	if(!_planted && _selected==1)
	{
		auto msg = Integer::create(-20);
		msg->retain();
		NotificationCenter::getInstance()->postNotification("spars",msg);

		CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("jungle/jungleBg2.png");
		_bg->setTexture(texture);
		_planted = true;
	}
	if(_planted && _drip->getPosition().x>1800)
	{
		auto forestGameScene = ForestGameScene::create();
		Director::getInstance()->replaceScene(forestGameScene);

		Size visibleSize = Director::getInstance()->getVisibleSize();
		CCRenderTexture *renderTexture = CCRenderTexture::create(visibleSize.width,visibleSize.height);

		renderTexture->begin(); 
		this->getParent()->visit();
		renderTexture->end();

		auto boyHint = PopScene::create();
		boyHint->initWithDialogs("dialog/boy_",9,renderTexture);

		Director::getInstance()->pushScene(boyHint);
	}
	if(_selected==0 && _drip->getPosition().x>1700)
	{
		auto jungleGameScene = JungleGameScene::create();
		Director::getInstance()->replaceScene(jungleGameScene);

		Size visibleSize = Director::getInstance()->getVisibleSize();
		CCRenderTexture *renderTexture = CCRenderTexture::create(visibleSize.width,visibleSize.height);

		renderTexture->begin(); 
		this->getParent ()->visit();
		renderTexture->end();

		auto mudHintScene1 = PopScene::create();
		mudHintScene1->initWithSprite("jungle/mudFlow1.png",renderTexture);
		auto mudHintScene2 = PopScene::create();
		mudHintScene2->initWithSprite("jungle/mudFlow2.png",renderTexture);
		Director::getInstance()->pushScene(mudHintScene2);
		Director::getInstance()->pushScene(mudHintScene1);
	}
}

void JungleGameLayer::updatePositions()
{
	float posX = MIN(_bg->getContentSize().width - _drip->getCenterToSides(),
        MAX(_drip->getCenterToSides(), _drip->getDesiredPosition().x));
	float posY = MIN(_bg->getContentSize().height + _drip->getCenterToBottom(),
		MAX(_drip->getCenterToBottom(), _drip->getDesiredPosition().y));
	
	 _drip->setPosition(Point(posX, posY));
	 
}

void JungleGameLayer::setViewPointCenter(Point position)
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

void JungleGameLayer::receiveActionMsg(Ref* pSender)
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

void JungleGameLayer::receiveSelectMsg(Ref* pSender)
{
	auto msg = (Integer*)pSender;
	auto select = msg->getValue();

	AppDelegate* app = (AppDelegate*)Application::getInstance();
	auto sparNum = app->getSparNum();
	if(select ==1 && sparNum<20)
	{
		_selected = 2;
	}
	else
	{
		_selected = select;
	}

	msg->release();
}
void JungleGameLayer::startHint(float dt)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	CCRenderTexture *renderTexture = CCRenderTexture::create(visibleSize.width,visibleSize.height);

	renderTexture->begin(); 
	this->getParent ()->visit();
	renderTexture->end();

	auto startHintScene = PopScene::create();
	startHintScene->initWithCsb("jungleStartHint.csb",renderTexture);

	Director::getInstance()->pushScene(startHintScene);
}