#pragma once
#include "cocos2d.h"

USING_NS_CC;

#define SCREEN Director::sharedDirector->getVisiblSize()
#define CENTER Vec2(SCREEN.width/2,SCREEN.height/2)
#define GORIGHTACTION 1
#define GOLEFTACTION 2
#define JUMPACTION 3
#define IDLEACTION 0
#define MAXHP 100
typedef enum _ActionState {
    kActionStateNone = 0,
    kActionStateIdle,
    kActionStateWalkLeft,
	kActionStateWalkRight,
    kActionStateHurt,
	kActionStateJump,
	kActionStateJumpWalk,
    kActionStateKnockedOut,
	kActionStateStop,
    kActionStateWalk,
	kActionStateAngry
} ActionState;

