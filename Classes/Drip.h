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


	//����
	CC_SYNTHESIZE_RETAIN(Action*, _idleAction, IdleAction);
	CC_SYNTHESIZE_RETAIN(Action*, _walkAction, WalkAction);	
	CC_SYNTHESIZE_RETAIN(Action*, _jumpAction, JumpAction);
	CC_SYNTHESIZE_RETAIN(Action*, _hurtAction, HurtAction);
	

	//����״̬
	CC_SYNTHESIZE(ActionState, _actionState, ActionState);

	//����״̬
	CC_SYNTHESIZE(float, _walkSpeed, WalkSpeed);
	CC_SYNTHESIZE(int, _hpPoints, HpPoints);

	//�ٶȺ�λ��
	CC_SYNTHESIZE(Point, _velocity, Velocity);
	CC_SYNTHESIZE(Point, _desiredPosition, DesiredPosition);

	//�����ο�ֵ
	CC_SYNTHESIZE(float, _centerToSides, CenterToSides);
    CC_SYNTHESIZE(float, _centerToBottom, CenterToBottom);

	bool isBleeding;
};

