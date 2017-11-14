#include "Cutter.h"


Cutter::Cutter(void)
{
	m_cutter = NULL;
}


Cutter::~Cutter(void)
{
}

bool Cutter::init()
{
	m_cutter = Sprite::create("desert/cutter.png");
	this->addChild(m_cutter);
	Size size = m_cutter->getContentSize();
	m_cutter->setPosition(Point(size.width*0.5f,size.height*0.5f));
	this->setContentSize(size);
	return true;
}