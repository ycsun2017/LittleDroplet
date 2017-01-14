#pragma once
#include "cocos2d.h"

USING_NS_CC;
class Haze :public Layer
{
public:
	Haze(void);
	virtual ~Haze(void);
	bool init();
	void deepen(float dt);

	CREATE_FUNC(Haze);
private:
	Sprite* m_haze;
	int thickness;
};

