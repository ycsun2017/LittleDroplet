#include "Barriers.h"


Barriers::Barriers(void)
{
	//m_mask = NULL;
}


Barriers::~Barriers(void)
{
	
}

bool Barriers::init()
{
	bool bRet = false;
	do{
		char name[15];
		int yPos[]={150,180,180,120,150,150,150};
		float xPos=100;
		for(int i=1;i<11;i++)
		{
			memset(name,0,15);
			sprintf(name,"barrier%02d.png",(i%7));
			auto barrier = Barrier::create();
			barrier->bindSprite(Sprite::create(name));
			xPos = xPos+300+CCRANDOM_0_1()*400;       
			barrier->setPosition(Point(xPos,yPos[i%7]));
			this->addChild(barrier);
			m_barriers.pushBack(barrier);
			
		}

		bRet = true;
	}while(0);
	return bRet;
}
void Barriers::Update(Drip* drip,float dt)
{
	for(auto barrier:m_barriers)
	{
		if(barrier->isAlive())
		{
			//log("%f,%f",barrier->getPosition().x,barrier->getPosition().y);
			//if(drip->getBoundingBox().intersectsRect(barrier->getBoundingBox()) )
			if(barrier->getBoundingBox().containsPoint(Point(drip->getPosition().x,drip->getPosition().y-drip->getCenterToBottom())))
			{
				barrier->isBreak();
				drip->hurtWithDamage(15);
			}
		}
	}

}