#pragma once
#include "cocos2d.h"
USING_NS_CC;
class Barrier:public Sprite
{
public:
	Barrier(void);
	virtual ~Barrier(void);
	bool init();
	void bindSprite(Sprite* sprite);
	bool isAlive();
	NodeGrid* getBarrier();
	void isBreak();
	void destory();
	
	CREATE_FUNC(Barrier);
private:
	NodeGrid* m_barrier;
	bool m_isAlive;

};

