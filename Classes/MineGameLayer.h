#pragma once
#include "cocos2d.h"
#include "Drip.h"
#include "Defines.h"
#include "MineBarriers.h"
USING_NS_CC;
class MineGameLayer : public Layer
{
public:
	MineGameLayer(void);
	virtual ~MineGameLayer(void);
	bool init();
	void initBG();
	void initDrip();
	virtual void update(float dt);
	void updatePositions();
	void setViewPointCenter(Point position);
	void receiveActionMsg(Ref* pSender);
	void startHint(float dt);
	void stoneFall(float dt);
	CREATE_FUNC(MineGameLayer);

	Drip* _drip;
	Sprite* _bg;
	Sprite* _stone;
	MineBarriers* _barriers;
};

