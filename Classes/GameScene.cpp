#include "GameScene.h"
#include "SimpleAudioEngine.h" 
using namespace CocosDenshion;  
GameScene::GameScene(void)
{
	_gameLayer = NULL;
	_hudLayer = NULL;
	_hazeLayer = NULL;
}


GameScene::~GameScene(void)
{
	NotificationCenter::getInstance()->removeAllObservers(this);
}

bool GameScene::init()
{
	bool bRet = false;
    do 
    {
         CC_BREAK_IF(!Scene::init());

		_gameLayer = GameLayer::create();
		this->addChild(_gameLayer,0);
		_hudLayer = HudLayer::create();
		this->addChild(_hudLayer,3);
		_hazeLayer = Haze::create();
		this->addChild(_hazeLayer,2);
		
		SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("bgm.mp3");
		SimpleAudioEngine::sharedEngine()->playBackgroundMusic("bgm.mp3",true);

		NotificationCenter::getInstance()->addObserver(this,callfuncO_selector(GameScene::musicOn),"musicOn",NULL);
		NotificationCenter::getInstance()->addObserver(this,callfuncO_selector(GameScene::musicOff),"musicOff",NULL);
	 bRet = true;
    } while (0);

    return bRet;
}
void GameScene::musicOn(Ref* pSender)
{
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic("bgm.mp3",true);
}
void GameScene::musicOff(Ref* pSender)
{
	SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
}