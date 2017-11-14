#pragma once
#include "cocos2d.h"
#include "JungleGameLayer.h"
#include "HudLayer.h"
USING_NS_CC;

class JungleGameScene : public Scene
{
public:
	JungleGameScene(void);
	virtual ~JungleGameScene(void);

	virtual bool init();
	void musicOn(Ref* pSender);
	void musicOff(Ref* pSender);
    CREATE_FUNC(JungleGameScene);

    CC_SYNTHESIZE(JungleGameLayer*, _gameLayer, GameLayer);
    CC_SYNTHESIZE(HudLayer*, _hudLayer, HudLayer);
};

