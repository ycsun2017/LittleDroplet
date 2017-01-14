#include "StartScene.h"
#include "GameScene.h"
#include "DesertGameScene.h"

StartScene::StartScene(void)
{
	startBtn = NULL;
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
		 this->addChild(startCSB);
		 startCSB->setPosition(Point(0,0));
		 startBtn = static_cast<Button*>(startCSB->getChildByName("startBtn"));
		 startBtn->addTouchEventListener(CC_CALLBACK_2(StartScene::start,this));	
		
	 bRet = true;
    } while (0);

    return bRet;
}

void StartScene::start(Ref* sender,Widget::TouchEventType controlEvent)
{
	auto cityScene = DesertGameScene::create();
	if(controlEvent == cocos2d::ui::Widget::TouchEventType::BEGAN)
		Director::getInstance()->replaceScene(cityScene);
}