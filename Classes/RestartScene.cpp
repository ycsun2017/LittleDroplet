#include "RestartScene.h"
#include "GameScene.h"


RestartScene::RestartScene(void)
{
}


RestartScene::~RestartScene(void)
{
}
void RestartScene::create(CCRenderTexture* sqr)
{
	auto m_layer = Layer::create();
	this->addChild(m_layer);

	auto pic = Sprite::createWithTexture(sqr->getSprite()->getTexture());  
	Size visibleSize = Director::getInstance()->getVisibleSize();
	pic->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
	pic->setFlipY(true);
	pic->setColor(Color3B::GRAY);
	m_layer->addChild(pic);

	Node* hint = CSLoader::createNode("Restart.csb");
	this->addChild(hint);
	hint->setPosition(Point(0,0));	

	auto exitBtn = static_cast<Button*>(hint->getChildByName("exitButton"));
	exitBtn->addTouchEventListener(CC_CALLBACK_2(RestartScene::onClickBtn,this));	

	auto restartBtn = static_cast<Button*>(hint->getChildByName("restartButton"));
	restartBtn->addTouchEventListener(CC_CALLBACK_2(RestartScene::onClickBtn,this));	
	
}

void RestartScene::onClickBtn(Ref* sender,Widget::TouchEventType controlEvent)
{
	auto gameScene = GameScene::create();
	Director::getInstance()->replaceScene(gameScene);
}