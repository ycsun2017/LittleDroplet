#include "Bg.h"
#include "BinManager.h"
#include "LitterManager.h"
Bg::Bg()
{
	bgSprite = NULL;
}
Scene* Bg::createScene()
{
	auto scene = Scene::create();
	auto layer = Bg::create();
	scene->addChild(layer);
	return scene;
}

bool Bg::init(){
	if (!Layer::init()){
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();

	Sprite* bg = Sprite::create("bg.jpg");
	bg->setPosition(Point(visibleSize.width / 2, visibleSize.height/2));
	this->addChild(bg, 2);

	BinManager* binMgr = BinManager::create();
	binMgr->setAnchorPoint(Point(0,0));
	binMgr->setPosition(Point(0,0));
	this->addChild(binMgr, 5);

	LitterManager* litterMgr = LitterManager::create();
	litterMgr->setPosition(Point(0,0));
	this->addChild(litterMgr, 4);
	litterMgr->bindBin(binMgr->arr);

	auto drip = Sprite::create("rightDrip.png");
	drip->setPosition(Point(50,visibleSize.height/2));
	drip->setScale(0.5);
	this->addChild(drip,6);

	return true;
}