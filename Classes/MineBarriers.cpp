#include "MineBarriers.h"


MineBarriers::MineBarriers(void)
{
}


MineBarriers::~MineBarriers(void)
{
}

bool MineBarriers::init()
{
	bool bRet = false;
	do{
		char name[40];
		//int yPos[]={150,180,180,120,150,150,150};
		int yPos[]={150,180,180,350,180,150};
		float xPos=100;
		for(int i=1;i<7;i++)
		{
			memset(name,0,40);
			sprintf(name,"mine/mineBarrier%02d.png",(i%6));
			auto barrier = Barrier::create();
			barrier->bindSprite(Sprite::create(name));
			xPos = xPos+300+CCRANDOM_0_1()*300;       
			barrier->setPosition(Point(xPos,yPos[i%6]));
			this->addChild(barrier);
			m_barriers.pushBack(barrier);
			
		}

		bRet = true;
	}while(0);
	return bRet;
}
void MineBarriers::Update(Drip* drip,float dt)
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