#ifndef _BG_H_
#define _BG_H_

#include "cocos2d.h"

USING_NS_CC;

class Bg : public Layer{
public:
	Bg();
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(Bg);
//private:
//	void initBG();
private:
	Sprite* bgSprite;
};

#endif