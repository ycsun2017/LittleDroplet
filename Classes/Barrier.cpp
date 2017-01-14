#include "Barrier.h"


Barrier::Barrier(void)
{
	m_barrier = NULL;
}


Barrier::~Barrier(void)
{
}

bool Barrier::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!Sprite::init());
		m_barrier = NodeGrid::create();
		m_isAlive = false;

		bRet = true;
	}while(0);
	return bRet;
}
void Barrier::bindSprite(Sprite* sprite)
{
	m_barrier->addChild(sprite);
	this->addChild(m_barrier);
	m_isAlive = true;
	Size size = sprite->getContentSize();
	m_barrier->setPosition(Point(size.width*0.5f,size.height*0.5f));
	this->setContentSize(size);
}
bool Barrier::isAlive()
{
	return m_isAlive;
}
NodeGrid* Barrier::getBarrier()
{
	return m_barrier;
}

void Barrier::isBreak()
{
	m_isAlive = false;
	auto shaky = ShakyTiles3D::create(1,Size(25,25),5,false);
	auto shuffle = ShuffleTiles::create(0.5,Size(25,25),25);
	m_barrier->runAction(Sequence::create(shaky,shuffle,CCCallFunc::create(this,callfunc_selector(Barrier::destory)),NULL));
}
void Barrier::destory()
{
	m_barrier->setVisible(false);
	
}