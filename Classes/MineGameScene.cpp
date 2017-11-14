#include "MineGameScene.h"
#include "AppDelegate.h"
#include "SimpleAudioEngine.h" 
using namespace CocosDenshion;  

MineGameScene::MineGameScene(void)
{
	_gameLayer = NULL;
	_hudLayer = NULL;
}


MineGameScene::~MineGameScene(void)
{
}

bool MineGameScene::init()
{
	bool bRet = false;
    do 
    {
         CC_BREAK_IF(!Scene::init());

		_gameLayer = MineGameLayer::create();
		this->addChild(_gameLayer,0);
		_hudLayer = HudLayer::create();
		this->addChild(_hudLayer,3);
		
		SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("mineBgm.wav");
		AppDelegate* app = (AppDelegate*)Application::getInstance();
		if(app->getMusicState())
			SimpleAudioEngine::sharedEngine()->playBackgroundMusic("mineBgm.wav",true);

		NotificationCenter::getInstance()->addObserver(this,callfuncO_selector(MineGameScene::musicOn),"musicOn",NULL);
		NotificationCenter::getInstance()->addObserver(this,callfuncO_selector(MineGameScene::musicOff),"musicOff",NULL);
	 bRet = true;
    } while (0);

    return bRet;
}

void MineGameScene::musicOn(Ref* pSender)
{
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic("mineBgm.wav",true);
}
void MineGameScene::musicOff(Ref* pSender)
{
	SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
}