#pragma once

#include "cocos2d.h"
USING_NS_CC;
class Mask :
	public Sprite
{
public:
	Mask(void);
	virtual ~Mask(void);
	bool init();

	CREATE_FUNC(Mask);
private:
	Sprite* m_mask;  
};

