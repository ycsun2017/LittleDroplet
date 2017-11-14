#pragma once
#include "cocos2d.h"
USING_NS_CC;
class Cutter : public Sprite
{
public:
	Cutter(void);
	virtual ~Cutter(void);
	bool init();

	CREATE_FUNC(Cutter);
private:
	Sprite* m_cutter;  
};

