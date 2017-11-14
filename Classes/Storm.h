#pragma once
#include "cocos2d.h"
USING_NS_CC;

class Storm : public Layer
{
public:
	Storm(void);
	virtual ~Storm(void);
	bool init();
	void stormAppear(float dt);
	void stormDisappear();
	CREATE_FUNC(Storm);
private:
	Sprite* m_storm;
};

