#pragma once
#include "cocos2d.h"

USING_NS_CC;
class Cars : public Layer
{
public:
	Cars(void);
	virtual ~Cars(void);
	bool init();
	void createCar1(float dt);
	void createCar2(float dt);
	void lastCar(float dt);
	CREATE_FUNC(Cars);

private:
	Sprite* car1;
	Sprite* car2;
};

