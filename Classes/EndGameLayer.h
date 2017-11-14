#pragma once
#include "cocos2d.h"
#include "Drip.h"
#include "Defines.h"
USING_NS_CC;

class EndGameLayer : public Layer
{
public:
	EndGameLayer(void);
	virtual ~EndGameLayer(void);

	bool init();
	void initBG();
	void initDrip();
	virtual void update(float dt);
	void updatePositions();
	void setViewPointCenter(Point position);
	void receiveActionMsg(Ref* pSender);

	CREATE_FUNC(EndGameLayer);

	Drip* _drip;
	Sprite* _bg;
	bool _sea;
	bool _home;
};

