#pragma once
#include "cocos2d.h"
#include "DesertGameLayer.h"
#include "HudLayer.h"
#include "Storm.h"
USING_NS_CC;
class DesertGameScene : public Scene
{
public:
	DesertGameScene(void);
	virtual ~DesertGameScene(void);

	virtual bool init();
	void musicOn(Ref* pSender);
	void musicOff(Ref* pSender);
    CREATE_FUNC(DesertGameScene);

    CC_SYNTHESIZE(DesertGameLayer*, _gameLayer, GameLayer);
    CC_SYNTHESIZE(HudLayer*, _hudLayer, HudLayer);
	CC_SYNTHESIZE(Storm*, _stormLayer, StormLayer);
};

