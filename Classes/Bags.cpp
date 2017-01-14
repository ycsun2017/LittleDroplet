#include "Bags.h"


Bags::Bags(void)
{
	/*bag1 = NULL;
	bag2 = NULL;*/
}


Bags::~Bags(void)
{

}

bool Bags::init()
{
	bool bRet = false;
	do{

		this->scheduleUpdate();

		this->schedule(schedule_selector(Bags::createBag1),7.0f);
		this->schedule(schedule_selector(Bags::createBag2),7.0f);

		bRet = true;
	}while(0);
	return bRet;
}

void Bags::Update(Drip* drip,float dt)
{
	for(auto bag:m_bags)
	{
		if(bag->getPosition().x>6100 || bag->getPosition().x<-100)
		{
			bag->stopAllActions();
		}
			
		if(drip->getBoundingBox().containsPoint(bag->getPosition()))
		{
			drip->hurtWithDamage(5);
		}
	}

}



void Bags::createBag1(float dt)
{
	auto bag1 = Sprite::create("bag1.png");
	m_bags.pushBack(bag1);
	this->addChild(bag1);
	int posY = 200+CCRANDOM_0_1()*400;
	bag1->setPosition(Point(0,posY));

	ccBezierConfig bezierCon;
    bezierCon.controlPoint_1=CCPointMake(100, 100);//控制点1
    bezierCon.controlPoint_2=CCPointMake(200, 50);//控制点2
    bezierCon.endPosition =CCPointMake(300, 0);// 结束位置

	auto action = CCBezierBy::create(2, bezierCon);

	ccBezierConfig bezierCon1;
    bezierCon1.controlPoint_1=CCPointMake(100, -150);//控制点1
    bezierCon1.controlPoint_2=CCPointMake(150, -100);//控制点2
    bezierCon1.endPosition =CCPointMake(200, 0);// 结束位置

	auto action1 = CCBezierBy::create(1, bezierCon1);

	bag1->runAction(RepeatForever::create(Sequence::create(action,action1,NULL)));

}
void Bags::createBag2(float dt)
{
	auto bag2 = Sprite::create("bag2.png");
	m_bags.pushBack(bag2);
	this->addChild(bag2);
	int posY = 200+CCRANDOM_0_1()*400;
	bag2->setPosition(Point(6000,posY));

	ccBezierConfig bezierCon;
    bezierCon.controlPoint_1=CCPointMake(-100, 100);//控制点1
    bezierCon.controlPoint_2=CCPointMake(-200, 50);//控制点2
    bezierCon.endPosition =CCPointMake(-300, 0);// 结束位置

	auto action = CCBezierBy::create(1, bezierCon);

	ccBezierConfig bezierCon1;
    bezierCon1.controlPoint_1=CCPointMake(-100, -150);//控制点1
    bezierCon1.controlPoint_2=CCPointMake(-150, -100);//控制点2
    bezierCon1.endPosition =CCPointMake(-200, 0);// 结束位置

	auto action1 = CCBezierBy::create(2, bezierCon1);

	bag2->runAction(RepeatForever::create(Sequence::create(action,action1,NULL)));
}