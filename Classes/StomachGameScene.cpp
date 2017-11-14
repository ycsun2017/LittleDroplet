#include "StomachGameScene.h"
#include "SimpleAudioEngine.h" 
#include "AppDelegate.h"
using namespace CocosDenshion;  

StomachGameScene::StomachGameScene(void)
{
	_gameLayer = NULL;
	_hudLayer = NULL;
}


StomachGameScene::~StomachGameScene(void)
{
}

bool StomachGameScene::init()
{
	bool bRet = false;
    do 
    {
         CC_BREAK_IF(!Scene::init());

		_gameLayer = StomachGameLayer::create();
		this->addChild(_gameLayer,0);
		_hudLayer = HudLayer::create();
		this->addChild(_hudLayer,3);
		
		SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("forestBgm.mp3");
		AppDelegate* app = (AppDelegate*)Application::getInstance();
		if(app->getMusicState())
			SimpleAudioEngine::sharedEngine()->playBackgroundMusic("forestBgm.mp3",true);

		NotificationCenter::getInstance()->addObserver(this,callfuncO_selector(StomachGameScene::musicOn),"musicOn",NULL);
		NotificationCenter::getInstance()->addObserver(this,callfuncO_selector(StomachGameScene::musicOff),"musicOff",NULL);
	 bRet = true;
    } while (0);

    return bRet;
}

void StomachGameScene::musicOn(Ref* pSender)
{
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic("forestBgm.mp3",true);
}
void StomachGameScene::musicOff(Ref* pSender)
{
	SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
}