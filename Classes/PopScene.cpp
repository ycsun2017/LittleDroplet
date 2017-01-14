#include "PopScene.h"


PopScene::PopScene(void)
{
	exitBtn = NULL;
	newScene = NULL;
	replaceScene = false;
	pushScene = false;
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
	hint->setPosition(Point(0,visibleSize.height));
	exitBtn = static_cast<Button*>(hint->getChildByName("exitButton"));

	exitBtn->addTouchEventListener(CC_CALLBACK_2(PopScene::onClickBtn,this));	
	auto move = MoveTo::create(1.0f,Point(0,0));
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
	spr->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
	m_layer->addChild(spr);
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [=](Touch *t,Event *e){
		Director::getInstance()->popScene();
		return false;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,m_layer);
}

void PopScene::onClickBtn(Ref* sender,Widget::TouchEventType controlEvent)
{
	Director::getInstance()->popScene();
	//this->runAction(Sequence::create(CCCallFunc::create(this, callfunc_selector(PopScene::exit)),
		//CCCallFunc::create(this, callfunc_selector(PopScene::changeScene)),NULL));
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