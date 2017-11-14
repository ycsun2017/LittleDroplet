#include "Bin.h"

USING_NS_CC;

Bin::Bin(){
	alive = true;  
	speed = DEFAULT_SPEED;
	color = 0;
	_walkAction = NULL;
	_angryAction = NULL;
	_actionState=kActionStateNone;
}

Bin::~Bin(){
	
}

bool Bin::init(){
	
	return true;
}

void Bin::initActions(){
	auto cache = SpriteFrameCache::getInstance();
		
	//前进动作
	if(color == BLUE)
		cache->addSpriteFramesWithFile("bins/blueWalkAnim.plist");
	if(color == GREEN)
		cache->addSpriteFramesWithFile("bins/greenWalkAnim.plist");
	if(color == RED)
		cache->addSpriteFramesWithFile("bins/redWalkAnim.plist");
	if(color == YELLOW)
		cache->addSpriteFramesWithFile("bins/yellowWalkAnim.plist");
	Vector<SpriteFrame*> walkFrames;
	char name[15];
	memset(name,0,15);
	for(int i=0;i<10;i++)
	{
		sprintf(name,"walkAnim%04d",i);
		walkFrames.pushBack(cache->getSpriteFrameByName(name));
	}
	Animation* animation = Animation::createWithSpriteFrames(walkFrames,0.1f);
	this->setWalkAction(RepeatForever::create(Animate::create(animation)));
	cache->removeSpriteFrames();

	//生气动作
	if(color == BLUE)
		cache->addSpriteFramesWithFile("bins/blueAngryAnim.plist");
	if(color == GREEN)
		cache->addSpriteFramesWithFile("bins/greenAngryAnim.plist");
	if(color == RED)
		cache->addSpriteFramesWithFile("bins/redAngryAnim.plist");
	if(color == YELLOW)
		cache->addSpriteFramesWithFile("bins/yellowAngryAnim.plist");
	Vector<SpriteFrame*> angryFrames;
	memset(name,0,15);
	for(int i=0;i<5;i++)
	{
		sprintf(name,"angryAnim%04d",i);
		angryFrames.pushBack(cache->getSpriteFrameByName(name));
	}
	animation = Animation::createWithSpriteFrames(angryFrames,0.1f);
	this->setAngryAction(Sequence::create(Animate::create(animation),CCCallFunc::create(this, callfunc_selector(Bin::walk)),NULL));
	cache->removeSpriteFrames();
}
void Bin::walk(){
	if(_actionState!=kActionStateWalk && _actionState!=kActionStateAngry)
	{
		m_sprite->stopAllActions();
		_actionState=kActionStateWalk;
		m_sprite->runAction(_walkAction);
		//this->setPositionX(this->getPositionX() - this->speed);
		_actionState=kActionStateNone;
	}
}
void Bin::angry(){
	m_sprite->stopAllActions();
	_actionState=kActionStateAngry;
	m_sprite->runAction(_angryAction);
	//this->setPositionX(this->getPositionX() - this->speed);
	_actionState=kActionStateNone;
}


bool Bin::isAlive(){
	return alive;
}

void Bin::speedUp()
{
	speed++;
}
void Bin::speedDown()
{
	speed--;
	if(speed==0)
	{
		alive = false;
		m_sprite->stopAllActions();
	}
}