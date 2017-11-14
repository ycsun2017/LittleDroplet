#include "DesertGameScene.h"
#include "AppDelegate.h"
#include "SimpleAudioEngine.h" 
using namespace CocosDenshion;  

DesertGameScene::DesertGameScene(void)
{
	_gameLayer = NULL;
	_hudLayer = NULL;
	_stormLayer = NULL;
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
		_stormLayer = Storm::create();
		this->addChild(_stormLayer,1);
		
		SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("desertBgm.wav");
		AppDelegate* app = (AppDelegate*)Application::getInstance();
		if(app->getMusicState())
			SimpleAudioEngine::sharedEngine()->playBackgroundMusic("desertBgm.wav",true);

		NotificationCenter::getInstance()->addObserver(this,callfuncO_selector(DesertGameScene::musicOn),"musicOn",NULL);
		NotificationCenter::getInstance()->addObserver(this,callfuncO_selector(DesertGameScene::musicOff),"musicOff",NULL);
	 bRet = true;
    } while (0);

    return bRet;
}

void DesertGameScene::musicOn(Ref* pSender)
{
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic("desertBgm.wav",true);
}
void DesertGameScene::musicOff(Ref* pSender)
{
	SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
}