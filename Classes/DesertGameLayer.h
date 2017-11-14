#pragma once
#include "cocos2d.h"
#include "Drip.h"
#include "Defines.h"
#include "Spars.h"
#include "DesertBarriers.h"
#include "Cutter.h"
USING_NS_CC;
class DesertGameLayer : public Layer
{
public:
	DesertGameLayer(void);
	virtual ~DesertGameLayer(void);

	bool init();
	void initBG();
	void initDrip();
	void initCutter();
	virtual void update(float dt);
	void updatePositions();
	void setViewPointCenter(Point position);
	void receiveActionMsg(Ref* pSender);
	void receiveStormMsg(Ref* pSender);
	void blowing(float dt);
	void cutterDie();
	void getCard(float dt);
	void startHint(float dt);

	CREATE_FUNC(DesertGameLayer);

	Drip* _drip;
	Sprite* _bg;
	Spars* _spars;
	DesertBarriers* _barriers;
	Sprite* _cutter;
	bool _cutterEncounter;
	bool _cutterAlive;
	bool _levelPassed;
};

