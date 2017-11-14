#include "LitterManager.h"
#include "Litter.h"
LitterManager::LitterManager()
{
}
LitterManager::~LitterManager()
{
	this->unscheduleUpdate();
}
bool LitterManager::init(){
	createLitters();
	this->scheduleUpdate();
	return true;
}

void LitterManager::createLitters(){
	Litter* litter = NULL;
	Sprite* sprite = NULL;

	Size visibleSize = Director::getInstance()->getVisibleSize();

	for (int i = 1; i <= BLUE_NUM; i++){
		litter = Litter::create();
		litter->set(BLUE,i);
		//litter->setPosition(Point(visibleSize.width / 4 + CCRANDOM_0_1()*visibleSize.width / 2, ((int)(CCRANDOM_0_1() * 100) % 3 + 1)*visibleSize.height / 4));
		litter->setPosition(Point(100+CCRANDOM_0_1()*(visibleSize.width-200),100+CCRANDOM_0_1()*(visibleSize.height-200)));
		this->addChild(litter);

		arr.pushBack(litter);
	}
	for (int i = 1; i <= GREEN_NUM; i++){
		litter = Litter::create();
		litter->set(GREEN,i);
		litter->setPosition(Point(100+CCRANDOM_0_1()*(visibleSize.width-200),100+CCRANDOM_0_1()*(visibleSize.height-200)));
		//litter->setPosition(Point(visibleSize.width / 4 + CCRANDOM_0_1()*visibleSize.width / 2, ((int)(CCRANDOM_0_1() * 100) % 3 + 1)*visibleSize.height / 4));
		this->addChild(litter);

		arr.pushBack(litter);
	}
	for (int i = 1; i <= RED_NUM; i++){
		litter = Litter::create();
		litter->set(RED,i);
		litter->setPosition(Point(100+CCRANDOM_0_1()*(visibleSize.width-200),100+CCRANDOM_0_1()*(visibleSize.height-200)));
		//litter->setPosition(Point(visibleSize.width / 4 + CCRANDOM_0_1()*visibleSize.width / 2, ((int)(CCRANDOM_0_1() * 100) % 3 + 1)*visibleSize.height / 4));
		this->addChild(litter);

		arr.pushBack(litter);
	}
	for (int i = 1; i <= YELLOW_NUM; i++){
		litter = Litter::create();
		litter->set(YELLOW,i);
		litter->setPosition(Point(100+CCRANDOM_0_1()*(visibleSize.width-200),100+CCRANDOM_0_1()*(visibleSize.height-200)));
		//litter->setPosition(Point(visibleSize.width / 4 + CCRANDOM_0_1()*visibleSize.width / 2, ((int)(CCRANDOM_0_1() * 100) % 3 + 1)*visibleSize.height / 4));
		this->addChild(litter);

		arr.pushBack(litter);
	}
}

void LitterManager::update(float dt){
	//Ìí¼Ó¼àÌı
}

void LitterManager::bindBin(Vector<Bin*> binArr){
	for(auto litter: arr){
		litter->bindBin(binArr);
	}
}