#include "PopScene.h"
#include "Defines.h"
#include "AppDelegate.h"
#include "DesertGameScene.h"
#include "JungleGameScene.h"
#include "GameScene.h"

PopScene::PopScene(void)
{
	exitBtn = NULL;
	yesBtn = NULL;
	noBtn = NULL;
	newScene = NULL;
	replaceScene = false;
	pushScene = false;
	digNum = 0;
}


PopScene::~PopScene(void)
{
}

void PopScene::initWithCsb(char name[],CCRenderTexture* sqr)
{
	auto m_layer = Layer::create();
	this->addChild(m_layer);
	Size visibleSize = Director::getInstance()->getVisibleSize();
	if(sqr!=NULL)
	{
		auto pic = Sprite::createWithTexture(sqr->getSprite()->getTexture());  
		pic->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
		pic->setFlipY(true);
		pic->setColor(Color3B::GRAY);
		m_layer->addChild(pic);
	}
	

	Node* hint = CSLoader::createNode(name);
	this->addChild(hint);
	//hint->setAnchorPoint(Point(480 ,320));
	hint->setPosition(Point(visibleSize.width/2-480,visibleSize.height));
	exitBtn = static_cast<Button*>(hint->getChildByName("exitButton"));

	exitBtn->addTouchEventListener(CC_CALLBACK_2(PopScene::onClickBtn,this));	
	auto move = MoveTo::create(1.0f,Point(visibleSize.width/2-480,0));
	auto easeBackOut = CCEaseBackOut::create(move);
    hint->runAction(easeBackOut);

}
void PopScene::initWithSelect(char name[],CCRenderTexture* sqr)
{
	auto m_layer = Layer::create();
	this->addChild(m_layer);
	Size visibleSize = Director::getInstance()->getVisibleSize();
	if(sqr!=NULL)
	{
		auto pic = Sprite::createWithTexture(sqr->getSprite()->getTexture());  
		pic->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
		pic->setFlipY(true);
		pic->setColor(Color3B::GRAY);
		m_layer->addChild(pic);
	}
	

	Node* hint = CSLoader::createNode(name);
	this->addChild(hint);
	//hint->setAnchorPoint(Point(480 ,320));
	hint->setPosition(Point(visibleSize.width/2-480,visibleSize.height));
	exitBtn = static_cast<Button*>(hint->getChildByName("exitButton"));
	yesBtn = static_cast<Button*>(hint->getChildByName("yesButton"));
	noBtn = static_cast<Button*>(hint->getChildByName("noButton"));

	exitBtn->addTouchEventListener(CC_CALLBACK_2(PopScene::onClickBtn,this));	
	yesBtn->addTouchEventListener(CC_CALLBACK_2(PopScene::onClickYes,this));	
	noBtn->addTouchEventListener(CC_CALLBACK_2(PopScene::onClickNo,this));	

	auto move = MoveTo::create(1.0f,Point(visibleSize.width/2-480,0));
	auto easeBackOut = CCEaseBackOut::create(move);
    hint->runAction(easeBackOut);

}
void PopScene::initWithSprite(char name[],CCRenderTexture* sqr)
{
	auto m_layer = Layer::create();
	this->addChild(m_layer);

	auto pic = Sprite::createWithTexture(sqr->getSprite()->getTexture());  
	Size visibleSize = Director::getInstance()->getVisibleSize();
	pic->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
	pic->setFlipY(true);
	m_layer->addChild(pic);

	auto spr = Sprite::create(name);
	spr->setScaleX((float)visibleSize.width/960);
	spr->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
	m_layer->addChild(spr);
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [=](Touch *t,Event *e){
		Director::getInstance()->popScene();
		return false;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,m_layer);


}

void PopScene::initWithDialogs(char se_name[], int num, CCRenderTexture* sqr)
{
	auto m_layer = Layer::create();
	this->addChild(m_layer);

	auto pic = Sprite::createWithTexture(sqr->getSprite()->getTexture());  
	Size visibleSize = Director::getInstance()->getVisibleSize();
	pic->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
	pic->setFlipY(true);
	m_layer->addChild(pic);

	char name[100];
	memset(name,0,100);
	strcat(name,se_name);
	char suffix[10];
	memset(suffix,0,10);
	sprintf(suffix,"%01d.png",++digNum);
	strcat(name,suffix);

	auto spr = Sprite::create(name);
	spr->setAnchorPoint(Point(0,0));
	spr->setScale(visibleSize.width/spr->getContentSize().width);
	spr->setPosition(Point(0,0));
	//spr->setTag(10);
	spr->setName("dialog");
	m_layer->addChild(spr);
	

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [=](Touch *t,Event *e){
		if(digNum>=num)
		{
			Director::getInstance()->popScene();
		}
		else
		{
			char name[100];
			memset(name,0,100);
			strcat(name,se_name);
			char suffix[10];
			memset(suffix,0,10);
			sprintf(suffix,"%01d.png",++digNum);
			strcat(name,suffix);
			auto sp = (Sprite*)m_layer->getChildByName("dialog");
			CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage(name);
			sp->setTexture(texture);
		}
		return false;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,m_layer);


}

void PopScene::initRestart(CCRenderTexture* sqr)
{
	auto m_layer = Layer::create();
	this->addChild(m_layer);
	Size visibleSize = Director::getInstance()->getVisibleSize();
	if(sqr!=NULL)
	{
		auto pic = Sprite::createWithTexture(sqr->getSprite()->getTexture());  
		pic->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
		pic->setFlipY(true);
		pic->setColor(Color3B::GRAY);
		m_layer->addChild(pic);
	}
	

	Node* hint = CSLoader::createNode("Restart.csb");
	this->addChild(hint);
	//hint->setAnchorPoint(Point(480 ,320));
	hint->setPosition(Point(visibleSize.width/2-480,0));

	auto exitBtn = static_cast<Button*>(hint->getChildByName("exitButton"));
	exitBtn->addTouchEventListener(CC_CALLBACK_2(PopScene::onRestartBtn,this));	

	auto restartBtn = static_cast<Button*>(hint->getChildByName("restartButton"));
	restartBtn->addTouchEventListener(CC_CALLBACK_2(PopScene::onRestartBtn,this));

}

void PopScene::onRestartBtn(Ref* sender,Widget::TouchEventType controlEvent)
{
	AppDelegate* app = (AppDelegate*)Application::getInstance();
	Scene* gameScene;
	if(app->getLevel()==1)
		gameScene = DesertGameScene::create();
	if(app->getLevel()==2)
		gameScene = JungleGameScene::create();
	if(app->getLevel()==3)
		gameScene = GameScene::create();
	else
		gameScene = DesertGameScene::create();
	Director::getInstance()->replaceScene(gameScene);
}

void PopScene::onClickBtn(Ref* sender,Widget::TouchEventType controlEvent)
{
	Director::getInstance()->popScene();
	//this->runAction(Sequence::create(CCCallFunc::create(this, callfunc_selector(PopScene::exit)),
		//CCCallFunc::create(this, callfunc_selector(PopScene::changeScene)),NULL));
}
void PopScene::onClickYes(Ref* sender,Widget::TouchEventType controlEvent)
{
	auto msg = Integer::create(1);
	msg->retain();
	NotificationCenter::getInstance()->postNotification("select",msg);

	Director::getInstance()->popScene();
}
void PopScene::onClickNo(Ref* sender,Widget::TouchEventType controlEvent)
{
	auto msg = Integer::create(0);
	msg->retain();
	NotificationCenter::getInstance()->postNotification("select",msg);

	Director::getInstance()->popScene();
}

void PopScene::assignScene(Scene* scene, bool replace, bool push)
{
	newScene = scene;
	replaceScene = replace;
	pushScene = push;
}

void PopScene::exit()
{
	Director::getInstance()->popScene();
}

void PopScene::changeScene()
{
	if(pushScene){
		Director::getInstance()->pushScene(newScene);
	}
	else if(replaceScene){
		Director::getInstance()->replaceScene(newScene);
	}
}
