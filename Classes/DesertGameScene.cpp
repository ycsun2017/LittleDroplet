#include "DesertGameScene.h"
#include "SimpleAudioEngine.h" 
using namespace CocosDenshion;  

DesertGameScene::DesertGameScene(void)
{
	_gameLayer = NULL;
	_hudLayer = NULL;
}


DesertGameScene::~DesertGameScene(void)
{
}

bool DesertGameScene::init()
{
	bool bRet = false;
    do 
    {
         CC_BREAK_IF(!Scene::init());

		_gameLayer = DesertGameLayer::create();
		this->addChild(_gameLayer,0);
		_hudLayer = HudLayer::create();
		this->addChild(_hudLayer,3);
		
		SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("bgm.mp3");
		SimpleAudioEngine::sharedEngine()->playBackgroundMusic("bgm.mp3",true);

		NotificationCenter::getInstance()->addObserver(this,callfuncO_selector(DesertGameScene::musicOn),"musicOn",NULL);
		NotificationCenter::getInstance()->addObserver(this,callfuncO_selector(DesertGameScene::musicOff),"musicOff",NULL);
	 bRet = true;
    } while (0);

    return bRet;
}

void DesertGameScene::musicOn(Ref* pSender)
{
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic("bgm.mp3",true);
}
void DesertGameScene::musicOff(Ref* pSender)
{
	SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
}