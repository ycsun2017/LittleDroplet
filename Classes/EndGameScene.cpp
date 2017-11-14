#include "EndGameScene.h"
#include "AppDelegate.h"
#include "SimpleAudioEngine.h" 
using namespace CocosDenshion;  

EndGameScene::EndGameScene(void)
{
	_gameLayer = NULL;
	_hudLayer = NULL;
}


EndGameScene::~EndGameScene(void)
{
}

bool EndGameScene::init()
{
	bool bRet = false;
    do 
    {
         CC_BREAK_IF(!Scene::init());

		_gameLayer = EndGameLayer::create();
		this->addChild(_gameLayer,0);
		_hudLayer = HudLayer::create();
		this->addChild(_hudLayer,3);
		
		SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("endBgm.mp3");
		AppDelegate* app = (AppDelegate*)Application::getInstance();
		if(app->getMusicState())
			SimpleAudioEngine::sharedEngine()->playBackgroundMusic("endBgm.mp3",true);

		NotificationCenter::getInstance()->addObserver(this,callfuncO_selector(EndGameScene::musicOn),"musicOn",NULL);
		NotificationCenter::getInstance()->addObserver(this,callfuncO_selector(EndGameScene::musicOff),"musicOff",NULL);
	 bRet = true;
    } while (0);

    return bRet;
}

void EndGameScene::musicOn(Ref* pSender)
{
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic("endBgm.mp3",true);
}
void EndGameScene::musicOff(Ref* pSender)
{
	SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
}