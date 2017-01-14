#pragma once

#include "cocos2d.h"
#include "Drip.h"
#include "HudLayer.h"
#include "Defines.h"
#include "Barriers.h"
#include "Cars.h"
#include "Mask.h"
#include "Bags.h"
USING_NS_CC;

class GameLayer :
	public Layer
{
public:
	GameLayer(void);
	virtual ~GameLayer(void);

	bool init();

	void initBG();
	void initDrip();
	virtual void update(float dt);
	void updatePositions();
	void setViewPointCenter(Point position);
	void deeperHaze(float dt);
	void startHint(float dt);
	void updateMask();
	void getMask();
	void receiveActionMsg(Ref* pSender);

	CREATE_FUNC(GameLayer);

	Drip* _drip;
	HudLayer* _ui;
	Sprite* _bg1;
	Sprite* _bg2;
	Barriers* _barriers;
	Cars* _cars;
	Sprite* _mask;
	Bags* _bags;
};

