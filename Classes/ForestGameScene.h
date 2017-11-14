#pragma once
#include "cocos2d.h"
#include "Defines.h"
#include "HudLayer.h"
#include "ForestGameLayer.h"
USING_NS_CC;
class ForestGameScene : public Scene
{
public:
	ForestGameScene(void);
	virtual ~ForestGameScene(void);

	virtual bool init();
	void musicOn(Ref* pSender);
	void musicOff(Ref* pSender);
    CREATE_FUNC(ForestGameScene);

	CC_SYNTHESIZE(ForestGameLayer*, _gameLayer, GameLayer);
    CC_SYNTHESIZE(HudLayer*, _hudLayer, HudLayer);
};

