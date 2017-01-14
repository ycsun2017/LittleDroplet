#pragma once

#include "cocos2d.h"
#include "Defines.h"
USING_NS_CC;
class Drip :
	public Sprite
{
public:
	Drip(void);
	virtual ~Drip(void);
	bool init();
	
	void reset();
	void idle();
	void jump();
	void bleeding(float dt);
	void startBleeding();
	void endBleeding();
	void hurtWithDamage(int damage);
	void walkWithDirection(Point direction);

	void Update(float dt);

	CREATE_FUNC(Drip);


	//动作
	CC_SYNTHESIZE_RETAIN(Action*, _idleAction, IdleAction);
	CC_SYNTHESIZE_RETAIN(Action*, _walkAction, WalkAction);	
	CC_SYNTHESIZE_RETAIN(Action*, _jumpAction, JumpAction);
	CC_SYNTHESIZE_RETAIN(Action*, _hurtAction, HurtAction);
	

	//动作状态
	CC_SYNTHESIZE(ActionState, _actionState, ActionState);

	//属性状态
	CC_SYNTHESIZE(float, _walkSpeed, WalkSpeed);
	CC_SYNTHESIZE(int, _hpPoints, HpPoints);

	//速度和位置
	CC_SYNTHESIZE(Point, _velocity, Velocity);
	CC_SYNTHESIZE(Point, _desiredPosition, DesiredPosition);

	//测量参考值
	CC_SYNTHESIZE(float, _centerToSides, CenterToSides);
    CC_SYNTHESIZE(float, _centerToBottom, CenterToBottom);

	bool isBleeding;
};

