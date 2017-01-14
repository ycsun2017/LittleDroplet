#include "Drip.h"
#include "AppDelegate.h"
#include "SimpleAudioEngine.h" 
using namespace CocosDenshion;  

Drip::Drip(void)
{
	_idleAction = NULL;
	_walkAction = NULL;
	_hurtAction = NULL;
	_jumpAction = NULL;
	isBleeding = false;
}


Drip::~Drip(void)
{
}

bool Drip::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!Sprite::init());
		//初始化属性
		this->setWalkSpeed(150.0);
		this->setCenterToBottom(60.0);
        this->setCenterToSides(70.0);
		this->setHpPoints(100);

		//初始化动作
		auto cache = SpriteFrameCache::getInstance();
		
		//空闲动作
		cache->addSpriteFramesWithFile("idleAnimList.plist");
		Vector<SpriteFrame*> idleFrames;
		char name[15];
		memset(name,0,15);
		for(int i=0;i<7;i++)
		{
			sprintf(name,"idleAnim%04d",i);
			idleFrames.pushBack(cache->getSpriteFrameByName(name));
		}
		Animation* animation = Animation::createWithSpriteFrames(idleFrames,0.15f);
		this->setIdleAction(RepeatForever::create(Animate::create(animation)));
		cache->removeSpriteFrames();
		
		//行走动作
		cache->addSpriteFramesWithFile("walkAnimList.plist");
		Vector<SpriteFrame*> walkFrames;
		memset(name,0,15);
		for(int i=0;i<20;i++)
		{
			sprintf(name,"walkAnim%04d",i);
			walkFrames.pushBack(cache->getSpriteFrameByName(name));
		}
		animation = Animation::createWithSpriteFrames(walkFrames,0.05f);
		this->setWalkAction(RepeatForever::create(Animate::create(animation)));
		cache->removeSpriteFrames();

		//跳跃动作
		//auto jump = JumpTo::create(2,this->getPosition(),300,1);
		//this->setJumpAction(Sequence::create(jump,CCCallFunc::create(this, callfunc_selector(Drip::idle)),NULL));

		//cache->addSpriteFramesWithFile("jumpAnimList2.plist");
		//Vector<SpriteFrame*> jumpFrames;
		//memset(name,0,15);
		//for(int i=0;i<32;i++)
		//{
		//	sprintf(name,"jumpAnim%04d",i);
		//	jumpFrames.pushBack(cache->getSpriteFrameByName(name));
		//}
		//animation = Animation::createWithSpriteFrames(jumpFrames,0.05f);
		////this->setJumpAction(RepeatForever::create(Animate::create(animation)));
		//this->setJumpAction(Sequence::create(Animate::create(animation),
		//	CCCallFunc::create(this, callfunc_selector(Drip::idle)),NULL));
		//cache->removeSpriteFrames();

		//受伤动作
		auto hurt = Blink::create(1.5,3);
		auto move = MoveBy::create(1.5,Point(-500,0));
		this->setHurtAction(Sequence::create(hurt,CCCallFunc::create(this, callfunc_selector(Drip::idle)),NULL));

		//预加载音效
		SimpleAudioEngine::sharedEngine()->preloadEffect("jumpEffect.wav");
		SimpleAudioEngine::sharedEngine()->preloadEffect("collisionEffect.mp3");
		
		bRet = true;
	}while(0);
	return true;
}

void Drip::idle()
{
	if(_actionState!=kActionStateIdle)
	{
		this->stopAllActions();
		this->runAction(_idleAction);
		_actionState=kActionStateIdle;
		_velocity=Vec2(0,0);
		if(this->getPosition().y != 200)
		{
			this->setDesiredPosition(Point(this->getDesiredPosition().x,200));
		}
	}
}

void Drip::hurtWithDamage(int damage)
{
	if(_actionState != kActionStateHurt)
	{
		this->stopAllActions();
		log("hurt");
		_actionState = kActionStateHurt;
		this->runAction(_hurtAction);
		this->setHpPoints(this->getHpPoints()-damage);

		auto msg = Integer::create(this->getHpPoints());
		msg->retain();
		NotificationCenter::getInstance()->postNotification("hp",msg);

		AppDelegate* app = (AppDelegate*)Application::getInstance();
		if(app->getEffectState()==true)
			SimpleAudioEngine::sharedEngine()->playEffect("collisionEffect.mp3",false);
	}
	
	//this->runAction(Sequence::create(hurt,rotate2,CCCallFunc::create(this, callfunc_selector(Drip::idle)),NULL));
}

void Drip::bleeding(float dt)
{
	this->setHpPoints(this->getHpPoints()-1);
	auto msg = Integer::create(this->getHpPoints());
	msg->retain();
	NotificationCenter::getInstance()->postNotification("hp",msg);
}
void Drip::startBleeding()
{
	this->schedule(schedule_selector(Drip::bleeding),0.7f);
	this->isBleeding = true;
}
void Drip::endBleeding()
{
	this->unschedule(schedule_selector(Drip::bleeding));
	this->isBleeding = false;
}
void Drip::jump()
{
	auto jump = JumpTo::create(2,Point(this->getPosition().x,200),300,1);
	this->setJumpAction(Sequence::create(jump,CCCallFunc::create(this, callfunc_selector(Drip::reset)),NULL));

	AppDelegate* app = (AppDelegate*)Application::getInstance();
	if(app->getEffectState()==true)
		SimpleAudioEngine::sharedEngine()->playEffect("jumpEffect.wav",false);

	if(_actionState == kActionStateIdle)
	{
		this->stopAllActions();
		_actionState = kActionStateJump;
		this->runAction(_jumpAction);
	}
		
	if(_actionState == kActionStateWalkRight || _actionState == kActionStateWalkLeft)
	{
		this->stopAllActions();
		_actionState = kActionStateJumpWalk;
        this->runAction(_jumpAction);
	}
		
}

void Drip::walkWithDirection(Point direction)
{
	if(_actionState==kActionStateIdle || _actionState==kActionStateJumpWalk)
	{
		this->stopAllActions();
		this->runAction(_walkAction);

		if(direction.x>0)
		{
			_actionState=kActionStateWalkRight;
			_velocity = Point( _walkSpeed, 0);
			this->setScaleX(1.0);
		}
			
		else if(direction.x<0)
		{
			_actionState=kActionStateWalkLeft;
			_velocity = Point(-_walkSpeed, 0);
			this->setScaleX(-1.0);
		}
			
	}
	
}

void Drip::reset()
{
	AppDelegate* app = (AppDelegate*)Application::getInstance();
	if(app->getRightState() == true)
	{
		walkWithDirection(Point(1.0,0));
	}
	else if(app->getLeftState() == true)
	{
		walkWithDirection(Point(-1.0,0));
	}
	else
	{
		this->idle();
	}
}

void Drip::Update(float dt)
{
	if (_actionState == kActionStateWalkRight || _actionState == kActionStateWalkLeft || _actionState == kActionStateJumpWalk)
    {
        _desiredPosition = ccpAdd(this->getPosition(), ccpMult(_velocity, dt));
    }
	if (_actionState == kActionStateJump)
    {
        _desiredPosition = this->getPosition();
    }
	if (_actionState == kActionStateHurt)
	{
		_desiredPosition = Point(this->getPosition().x,200);
	}
}
