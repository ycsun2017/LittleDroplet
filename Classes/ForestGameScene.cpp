#include "ForestGameScene.h"
#include "SimpleAudioEngine.h" 
#include "AppDelegate.h"
using namespace CocosDenshion;  

ForestGameScene::ForestGameScene(void)
{
	_gameLayer = NULL;
	_hudLayer = NULL;
}


ForestGameScene::~ForestGameScene(void)
{
}

bool ForestGameScene::init()
{
	bool bRet = false;
    do 
    {
         CC_BREAK_IF(!Scene::init());

		_gameLayer = ForestGameLayer::create();
		this->addChild(_gameLayer,0);
		_hudLayer = HudLayer::create();
		this->addChild(_hudLayer,3);
		
		SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("forestBgm.mp3");
		AppDelegate* app = (AppDelegate*)Application::getInstance();
		if(app->getMusicState())
			SimpleAudioEngine::sharedEngine()->playBackgroundMusic("forestBgm.mp3",true);

		NotificationCenter::getInstance()->addObserver(this,callfuncO_selector(ForestGameScene::musicOn),"musicOn",NULL);
		NotificationCenter::getInstance()->addObserver(this,callfuncO_selector(ForestGameScene::musicOff),"musicOff",NULL);
	 bRet = true;
    } while (0);

    return bRet;
}

void ForestGameScene::musicOn(Ref* pSender)
{
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic("forestBgm.mp3",true);
}
void ForestGameScene::musicOff(Ref* pSender)
{
	SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
}