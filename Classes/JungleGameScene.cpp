#include "JungleGameScene.h"
#include "AppDelegate.h"
#include "SimpleAudioEngine.h" 
using namespace CocosDenshion;  

JungleGameScene::JungleGameScene(void)
{
	_gameLayer = NULL;
	_hudLayer = NULL;
}


JungleGameScene::~JungleGameScene(void)
{
}

bool JungleGameScene::init()
{
	bool bRet = false;
    do 
    {
         CC_BREAK_IF(!Scene::init());

		_gameLayer = JungleGameLayer::create();
		this->addChild(_gameLayer,0);
		_hudLayer = HudLayer::create();
		this->addChild(_hudLayer,3);
		
		SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("jungleBgm.mp3");
		AppDelegate* app = (AppDelegate*)Application::getInstance();
		if(app->getMusicState())
			SimpleAudioEngine::sharedEngine()->playBackgroundMusic("jungleBgm.mp3",true);

		NotificationCenter::getInstance()->addObserver(this,callfuncO_selector(JungleGameScene::musicOn),"musicOn",NULL);
		NotificationCenter::getInstance()->addObserver(this,callfuncO_selector(JungleGameScene::musicOff),"musicOff",NULL);
	 bRet = true;
    } while (0);

    return bRet;
}

void JungleGameScene::musicOn(Ref* pSender)
{
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic("jungleBgm.mp3",true);
}
void JungleGameScene::musicOff(Ref* pSender)
{
	SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
}