#pragma once

#include "cocos2d.h"
#include "GameLayer.h"
#include "Haze.h"
#include "Cars.h"
USING_NS_CC;
class GameScene :
	public Scene
{
public:
	GameScene(void);
	virtual ~GameScene(void);

	virtual bool init();
	void musicOn(Ref* pSender);
	void musicOff(Ref* pSender);
    CREATE_FUNC(GameScene);

    CC_SYNTHESIZE(GameLayer*, _gameLayer, GameLayer);
    CC_SYNTHESIZE(HudLayer*, _hudLayer, HudLayer);
	CC_SYNTHESIZE(Haze*, _hazeLayer, HazeLayer);

};


