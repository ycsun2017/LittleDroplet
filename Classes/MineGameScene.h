#pragma once
#include "cocos2d.h"
#include "MineGameLayer.h"
#include "HudLayer.h"
USING_NS_CC;
class MineGameScene : public Scene
{
public:
	MineGameScene(void);
	virtual ~MineGameScene(void);

	virtual bool init();
	void musicOn(Ref* pSender);
	void musicOff(Ref* pSender);
    CREATE_FUNC(MineGameScene);

    CC_SYNTHESIZE(MineGameLayer*, _gameLayer, GameLayer);
    CC_SYNTHESIZE(HudLayer*, _hudLayer, HudLayer);
};

