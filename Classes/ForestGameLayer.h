#pragma once
#include "cocos2d.h"
#include "Defines.h"
#include "Drip.h"
#include "ForestBarriers.h"
USING_NS_CC;
class ForestGameLayer : public Layer
{
public:
	ForestGameLayer(void);
	virtual ~ForestGameLayer(void);

	bool init();
	void initBG();
	void initDrip();
	void initBottles();
	void initMonster();
	virtual void update(float dt);
	void updatePositions();
	void setViewPointCenter(Point position);
	void receiveActionMsg(Ref* pSender);
	void bottleHint();
	void fire();

	CREATE_FUNC(ForestGameLayer);

	Drip* _drip;
	Sprite* _bg;
	Sprite* _monster;
	ForestBarriers* _barriers;
	Vector<Sprite*> _bottles;
	int _bottleNum;
	bool _bottleAlive[5];
	bool _bottlePassed;
	bool _mosterAppear;
};

