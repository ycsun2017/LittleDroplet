#include "BinManager.h"
#include "Bin.h"
#include "Bg.h"
#include "EndGameScene.h"
#include "PopScene.h"

bool BinManager::init(){
	centerToBottom = 50;
	centerToSide = 50;
	createBins();
	this->schedule(schedule_selector(BinManager::Update),0.2f);
	return true;
}

void BinManager::createBins(){
	Bin* bin = NULL;
	Sprite* s = NULL;

	Size visibleSize = Director::getInstance()->getVisibleSize();

	int interval = (visibleSize.height - centerToBottom * 8) / (MAX_BIN_NUM + 1);

	for (int i = 1; i <= MAX_BIN_NUM; i++){
		bin = Bin::create();
		/*对比litterManager部分进行调整 以及对应实体的init函数
		bin->bindSprite(Sprite::create("bin.png"));
		*/
		switch (i){
		case BLUE:
			s = Sprite::create("bins/blue.png");
			break;
		case RED:
			s = Sprite::create("bins/red.png");
			break;
		case GREEN:
			s = Sprite::create("bins/green.png");
			break;
		case YELLOW:
			s = Sprite::create("bins/yellow.png");
			break;
		}
		bin->color = i;//颜色绑定
		bin->bindSprite(s);//图片绑定
		bin->initActions();

		bin->setPosition(Point(visibleSize.width-centerToSide*2, interval*(i-1) + centerToBottom*(2*(i-1)+1)));//位置初始化
		bin->walk();
		this->addChild(bin);

		arr.pushBack(bin);
	}
}

void BinManager::Update(float dt){
	//if (gameOver){
	//	//game over
	//}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	int n = 0;
	for (auto bin : arr){
		
		if (bin->isAlive()){
			n++;
			bin->setPositionX(bin->getPositionX() - bin->speed);

			if (bin->getPositionX() < visibleSize.width / 12){
				//失败
				this->unscheduleUpdate();
				auto litterScene = Bg::createScene();
				Director::getInstance()->replaceScene(litterScene);
		
				Size visibleSize = Director::getInstance()->getVisibleSize();
				CCRenderTexture *renderTexture = CCRenderTexture::create(visibleSize.width,visibleSize.height);
				renderTexture->begin(); 
				this->getParent()->visit();
				renderTexture->end();

				auto litterHint = PopScene::create();
				litterHint->initWithCsb("litterPassHint.csb",renderTexture);

				Director::getInstance()->pushScene(litterHint);
				break;
			}
		}
		/*else{
			bin->show();
		}*/
	}

	if(n==0)
	{
		this->unscheduleUpdate();
		auto endGameScene = EndGameScene::create();
		Director::getInstance()->replaceScene(endGameScene);
		
		Size visibleSize = Director::getInstance()->getVisibleSize();
		CCRenderTexture *renderTexture = CCRenderTexture::create(visibleSize.width,visibleSize.height);
		renderTexture->begin(); 
		this->getParent()->visit();
		renderTexture->end();

		auto litterHint = PopScene::create();
		litterHint->initWithSprite("litters/litterPassed.jpg",renderTexture);

		Director::getInstance()->pushScene(litterHint);
	}
}
