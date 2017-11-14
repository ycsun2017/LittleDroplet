#include "ForestBarriers.h"


ForestBarriers::ForestBarriers(void)
{
}


ForestBarriers::~ForestBarriers(void)
{
}

bool ForestBarriers::init()
{
	bool bRet = false;
	do{
		char name[40];
		//int yPos[]={150,180,180,120,150,150,150};
		int yPos[]={150,180,180,180,150,180,180};
		float xPos=100;
		for(int i=1;i<7;i++)
		{
			memset(name,0,40);
			sprintf(name,"forest/forestBarrier%02d.png",(i%7));
			auto barrier = Barrier::create();
			barrier->bindSprite(Sprite::create(name));
			xPos = xPos+500+CCRANDOM_0_1()*400;       
			barrier->setPosition(Point(xPos,yPos[i%7]));
			this->addChild(barrier);
			m_barriers.pushBack(barrier);
			
		}

		bRet = true;
	}while(0);
	return bRet;
}
void ForestBarriers::Update(Drip* drip,float dt)
{
	for(auto barrier:m_barriers)
	{
		if(barrier->isAlive())
		{
			if(barrier->getBoundingBox().containsPoint(Point(drip->getPosition().x,drip->getPosition().y-drip->getCenterToBottom())))
			{
				barrier->isBreak();
				drip->hurtWithDamage(15);
			}
		}
	}

}