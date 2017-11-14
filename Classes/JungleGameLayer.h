#pragma once
#include "cocos2d.h"
#include "Drip.h"
#include "Spars.h"
#include "Defines.h"
USING_NS_CC;
class JungleGameLayer : public Layer
{
public:
	JungleGameLayer(void);
	virtual ~JungleGameLayer(void);
	bool init();
	void initBG();
	void initDrip();
	virtual void update(float dt);
	void updatePositions();
	void setViewPointCenter(Point position);
	
	void receiveActionMsg(Ref* pSender);
	void receiveSelectMsg(Ref* pSender);
	void startHint(float dt);

	CREATE_FUNC(JungleGameLayer);

	Drip* _drip;
	Sprite* _bg;
	Spars* _spars;
	int _mine;
	int _selected;
	bool _planted;
};

