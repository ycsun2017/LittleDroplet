#pragma once
#include "cocos2d.h"

USING_NS_CC;

class Spar : public Sprite
{
public:
	Spar(void);
	virtual ~Spar(void);

	bool init();
	CREATE_FUNC(Spar);

private:
	Sprite* m_spar;  
};

