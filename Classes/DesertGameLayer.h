#pragma once
#include "cocos2d.h"
#include "Drip.h"
#include "Defines.h"
#include "Spars.h"
#include "DesertBarriers.h"
USING_NS_CC;
class DesertGameLayer : public Layer
{
public:
	DesertGameLayer(void);
	virtual ~DesertGameLayer(void);

	bool init();
	void initBG();
	void initDrip();
	virtual void update(float dt);
	void updatePositions();
	void setViewPointCenter(Point position);
	void receiveActionMsg(Ref* pSender);

	CREATE_FUNC(DesertGameLayer);

	Drip* _drip;
	Sprite* _bg;
	Spars* _spars;
	DesertBarriers* _barriers;
};

