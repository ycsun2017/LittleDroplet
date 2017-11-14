#include "PauseScene.h"
#include "AppDelegate.h"
#include "PopScene.h"

PauseScene::PauseScene(void)
{
	exitBtn = NULL;
	returnBtn = NULL;
	hintBtn = NULL;
	musicControl = NULL;
	effectControl = NULL;
	renderTexture = NULL;
}


PauseScene::~PauseScene(void)
{
}

void PauseScene::create(CCRenderTexture* sqr)
{
	auto m_layer = Layer::create();
	this->addChild(m_layer);

	renderTexture = sqr;
	renderTexture->retain();
	auto pic = Sprite::createWithTexture(sqr->getSprite()->getTexture());  
	Size visibleSize = Director::getInstance()->getVisibleSize();
	pic->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
	pic->setFlipY(true);
	pic->setColor(Color3B::GRAY);
	m_layer->addChild(pic);

	Node* hint = CSLoader::createNode("Pause.csb");
	this->addChild(hint);

	hint->setPosition(Point(visibleSize.width/2-480,0));

	exitBtn = static_cast<Button*>(hint->getChildByName("exitButton"));
	exitBtn->addTouchEventListener(CC_CALLBACK_2(PauseScene::exit,this));	

	returnBtn = static_cast<Button*>(hint->getChildByName("returnButton"));
	returnBtn->addTouchEventListener(CC_CALLBACK_2(PauseScene::exit,this));	

	hintBtn = static_cast<Button*>(hint->getChildByName("operationButton"));
	hintBtn->addTouchEventListener(CC_CALLBACK_2(PauseScene::hint,this));

	AppDelegate* app = (AppDelegate*)Application::getInstance();
	musicControl = static_cast<Sprite*>(hint->getChildByName("musicOn"));
	if(app->getMusicState()==false)
		musicControl->setVisible(false);
	effectControl = static_cast<Sprite*>(hint->getChildByName("effectOn"));
	if(app->getEffectState()==false)
		effectControl->setVisible(false);


	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [=](Touch *t,Event *e){
		AppDelegate* app = (AppDelegate*)Application::getInstance();
		if(musicControl->getBoundingBox().containsPoint(t->getLocation()))
		{
			if(app->getMusicState() == false)
			{
				musicControl->setVisible(true);
				app->setMusicState(true);
				NotificationCenter::getInstance()->postNotification("musicOn");
			}
			else
			{
				musicControl->setVisible(false);
				app->setMusicState(false);
				NotificationCenter::getInstance()->postNotification("musicOff");
			}
		}
		if(effectControl->getBoundingBox().containsPoint(t->getLocation()))
		{
			if(app->getEffectState() == false)
			{
				effectControl->setVisible(true);
				app->setEffectState(true);
			}
			else
			{
				effectControl->setVisible(false);
				app->setEffectState(false);
			}
		}
		return false;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,m_layer);
	
}

void PauseScene::exit(Ref* sender,Widget::TouchEventType controlEvent)
{
	if(controlEvent == cocos2d::ui::Widget::TouchEventType::BEGAN)
		Director::getInstance()->popScene();
}

void PauseScene::hint(Ref* sender,Widget::TouchEventType controlEvent)
{
	if(controlEvent == cocos2d::ui::Widget::TouchEventType::BEGAN)
	{
		auto startHintScene = PopScene::create();
		startHintScene->initWithCsb("Layer1.csb",renderTexture);

		Director::getInstance()->pushScene(startHintScene);
	}

}
