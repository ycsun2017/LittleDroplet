#include "HudLayer.h"
#include "Defines.h"
#include "AppDelegate.h"
#include "PauseScene.h"

HudLayer::HudLayer(void)
{
	goRightBtn = NULL;
	goLeftBtn = NULL;
	pauseBtn = NULL;
	jumpBtn = NULL;
	hpBar = NULL;
	hpValue = 0.0;
}


HudLayer::~HudLayer(void)
{
	NotificationCenter::getInstance()->removeAllObservers(this);
}

bool HudLayer::init()
{
	bool bRet=false;
	do
	{
		CC_BREAK_IF(!Layer::init());
		
		//添加UI层
		Node* ui = CSLoader::createNode("res/MainScene.csb");
		this->addChild(ui);
		//初始化按钮控件
		goRightBtn = static_cast<Button*>(ui->getChildByName("goRightButton"));
		goLeftBtn = static_cast<Button*>(ui->getChildByName("goLeftButton"));
		jumpBtn = static_cast<Button*>(ui->getChildByName("jumpButton"));
		pauseBtn = static_cast<Button*>(ui->getChildByName("pauseBtn"));
		hpBar = static_cast<LoadingBar*>(ui->getChildByName("hpValue"));
		hpBar->setPercent(MAXHP);

		Size visibleSize = Director::getInstance()->getVisibleSize();
		jumpBtn->setPosition(Point(visibleSize.width-80,goRightBtn->getPosition().y));
		pauseBtn->setPosition(Point(visibleSize.width-80,hpBar->getPosition().y+20));

		goRightBtn->addTouchEventListener(CC_CALLBACK_2(HudLayer::goRight,this));	
		goLeftBtn->addTouchEventListener(CC_CALLBACK_2(HudLayer::goLeft,this));
		jumpBtn->addTouchEventListener(CC_CALLBACK_2(HudLayer::jump,this));
		pauseBtn->addTouchEventListener(CC_CALLBACK_2(HudLayer::pause,this));

		auto listener = EventListenerKeyboard::create();
		listener->onKeyPressed = CC_CALLBACK_2(HudLayer::onKeyPressed, this);
		listener->onKeyReleased = CC_CALLBACK_2(HudLayer::onKeyReleased, this);

		Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,this);

		NotificationCenter::getInstance()->addObserver(this,callfuncO_selector(HudLayer::changeHp),"hp",NULL);
		bRet=true;
	}while(0);
	return bRet;
}

void HudLayer::goRight(Ref* sender,Widget::TouchEventType controlEvent)
{
	AppDelegate* app = (AppDelegate*)Application::getInstance();
	if(controlEvent == cocos2d::ui::Widget::TouchEventType::BEGAN)
	{
		app->setRightState(true);
		auto msg = Integer::create(GORIGHTACTION);
		msg->retain();
		NotificationCenter::getInstance()->postNotification("action",msg);
	}
	if(controlEvent == cocos2d::ui::Widget::TouchEventType::ENDED ||
		controlEvent == cocos2d::ui::Widget::TouchEventType::CANCELED)
	{
		app->setRightState(false);
		auto msg = Integer::create(IDLEACTION);
		msg->retain();
		NotificationCenter::getInstance()->postNotification("action",msg);
	}
}	

void HudLayer::goLeft(Ref* sender,Widget::TouchEventType controlEvent)
{
	AppDelegate* app = (AppDelegate*)Application::getInstance();
	if(controlEvent == cocos2d::ui::Widget::TouchEventType::BEGAN)
	{
		app->setLeftState(true);
		auto msg = Integer::create(GOLEFTACTION);
		msg->retain();
		NotificationCenter::getInstance()->postNotification("action",msg);
	}
	if(controlEvent == cocos2d::ui::Widget::TouchEventType::ENDED ||
		controlEvent == cocos2d::ui::Widget::TouchEventType::CANCELED)
	{
		app->setLeftState(false);
		auto msg = Integer::create(IDLEACTION);
		msg->retain();
		NotificationCenter::getInstance()->postNotification("action",msg);
	}
}

void HudLayer::jump(Ref* sender,Widget::TouchEventType controlEvent)
{
	auto msg = Integer::create(JUMPACTION);
	msg->retain();
	NotificationCenter::getInstance()->postNotification("action",msg);
}

void HudLayer::pause(Ref* sender,Widget::TouchEventType controlEvent)
{
	if(controlEvent == cocos2d::ui::Widget::TouchEventType::BEGAN)
	{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	CCRenderTexture *renderTexture = CCRenderTexture::create(visibleSize.width,visibleSize.height);

	renderTexture->begin(); 
	this->getParent()->visit();
	renderTexture->end();
	
	auto pauseScene = PauseScene::create();
	pauseScene->create(renderTexture);

	Director::getInstance()->pushScene(pauseScene);
	}
}

void HudLayer::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	AppDelegate* app = (AppDelegate*)Application::getInstance();
	if( keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
	{
		app->setRightState(true);
		auto msg = Integer::create(GORIGHTACTION);
		msg->retain();
		NotificationCenter::getInstance()->postNotification("action",msg);
	}
	else if( keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
	{
		app->setLeftState(true);
		auto msg = Integer::create(GOLEFTACTION);
		msg->retain();
		NotificationCenter::getInstance()->postNotification("action",msg);
	}
	else if( keyCode == EventKeyboard::KeyCode::KEY_SPACE)
	{
		auto msg = Integer::create(JUMPACTION);
		msg->retain();
		NotificationCenter::getInstance()->postNotification("action",msg);
	}
}

void HudLayer::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
   AppDelegate* app = (AppDelegate*)Application::getInstance();
   if( keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
   {
	    app->setRightState(false);
		auto msg = Integer::create(IDLEACTION);
		msg->retain();
		NotificationCenter::getInstance()->postNotification("action",msg);
   }
   if( keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
   {
	    app->setLeftState(false);
		auto msg = Integer::create(IDLEACTION);
		msg->retain();
		NotificationCenter::getInstance()->postNotification("action",msg);
   }
}   
void HudLayer::changeHp(Ref* sender)
{
	auto hp = (Integer*)sender;
	hpBar->setPercent(hp->getValue());
}
