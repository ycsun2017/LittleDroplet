#pragma once
#include "cocos2d.h"
#include "EndGameLayer.h"
#include "HudLayer.h"
USING_NS_CC;
class EndGameScene : public Scene
{
public:
	EndGameScene(void);
	virtual ~EndGameScene(void);

	virtual bool init();
	void musicOn(Ref* pSender);
	void musicOff(Ref* pSender);
    CREATE_FUNC(EndGameScene);

    CC_SYNTHESIZE(EndGameLayer*, _gameLayer, GameLayer);
    CC_SYNTHESIZE(HudLayer*, _hudLayer, HudLayer);
};

