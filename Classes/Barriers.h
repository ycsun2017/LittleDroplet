#pragma once

#include "cocos2d.h"
#include "Barrier.h"
#include "Drip.h"

USING_NS_CC;
class Barriers :
	public Node
{
public:
	Barriers(void);
	virtual ~Barriers(void);

	bool init();
	void Update(Drip* drip,float dt);
	CREATE_FUNC(Barriers);

private:
	Vector<Barrier*> m_barriers;

};

