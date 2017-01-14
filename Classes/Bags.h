#pragma once
#include "cocos2d.h"
#include "Drip.h"
USING_NS_CC;
class Bags : public Node
{
public:
	Bags(void);
	virtual ~Bags(void);
	bool init();
	void createBag1(float dt);
	void createBag2(float dt);
	//virtual void update(float dt);
	void Update(Drip* drip,float dt);
	CREATE_FUNC(Bags);
private:
	Vector<Sprite*> m_bags;
//	Sprite* bag1;
//	Sprite* bag2;
};

