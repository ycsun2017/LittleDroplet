#include "StartScene.h"
#include "GameScene.h"
#include "DesertGameScene.h"
#include "JungleGameScene.h"
#include "MineGameScene.h"
#include "ForestGameScene.h"
#include "EndGameScene.h"
#include "PopScene.h"
#include "StomachGameScene.h"

StartScene::StartScene(void)
{
	startBtn = NULL;
	introBtn = NULL;
}


StartScene::~StartScene(void)
{
}

bool StartScene::init()
{
	bool bRet = false;
    do 
    {
         CC_BREAK_IF(!Scene::init());
		 Node* startCSB = CSLoader::createNode("GameStart.csb");
		 Size visibleSize = Director::getInstance()->getVisibleSize();
		 this->addChild(startCSB);
		 startCSB->setPosition(Point(visibleSize.width/2-480,visibleSize.height/2-320));
		 startBtn = static_cast<Button*>(startCSB->getChildByName("startBtn"));
		 startBtn->addTouchEventListener(CC_CALLBACK_2(StartScene::start,this));	
		 introBtn = static_cast<Button*>(startCSB->getChildByName("introBtn"));
		 introBtn->addTouchEventListener(CC_CALLBACK_2(StartScene::intro,this));	
	 bRet = true;
    } while (0);

    return bRet;
}

void StartScene::start(Ref* sender,Widget::TouchEventType controlEvent)
{
	auto gameScene = DesertGameScene::create();
	if(controlEvent == cocos2d::ui::Widget::TouchEventType::BEGAN)
		Director::getInstance()->replaceScene(gameScene);
}

void StartScene::intro(Ref* sender,Widget::TouchEventType controlEvent)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	CCRenderTexture *renderTexture = CCRenderTexture::create(visibleSize.width,visibleSize.height);

	renderTexture->begin(); 
	renderTexture->end();

	auto introScene = PopScene::create();
	introScene->initWithSprite("intro.jpg",renderTexture);

	Director::getInstance()->pushScene(introScene);
}