#pragma once
#include "cocos2d.h"
#include "StomachGameLayer.h"
#include "HudLayer.h"
USING_NS_CC;
class StomachGameScene : public Scene
{
public:
	StomachGameScene(void);
	virtual ~StomachGameScene(void);
	virtual bool init();
	void musicOn(Ref* pSender);
	void musicOff(Ref* pSender);
    CREATE_FUNC(StomachGameScene);

    CC_SYNTHESIZE(StomachGameLayer*, _gameLayer, GameLayer);
    CC_SYNTHESIZE(HudLayer*, _hudLayer, HudLayer);
};

