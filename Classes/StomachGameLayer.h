#pragma once
#include "cocos2d.h"
#include "Defines.h"
#include "Drip.h"
USING_NS_CC;
class StomachGameLayer : public Layer
{
public:
	StomachGameLayer(void);
	virtual ~StomachGameLayer(void);
	bool init();
	void initBG();
	void initDrip();
	virtual void update(float dt);
	void updatePositions();
	void setViewPointCenter(Point position);
	void receiveActionMsg(Ref* pSender);
	void startHint(float dt);
	CREATE_FUNC(StomachGameLayer);

	Drip* _drip;
	Sprite* _bg;
	Sprite* _battery;
};

