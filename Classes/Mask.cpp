#include "Mask.h"


Mask::Mask(void)
{
	m_mask = NULL;
}


Mask::~Mask(void)
{
}
bool Mask::init()
{
	m_mask = Sprite::create("mask.png");
	this->addChild(m_mask);
	Size size = m_mask->getContentSize();
	m_mask->setPosition(Point(size.width*0.5f,size.height*0.5f));
	this->setContentSize(size);
	return true;
}