#pragma once
#include "cocos2d.h"
#include "Barrier.h"
#include "Drip.h"

USING_NS_CC;
class DesertBarriers : public Node
{
public:
	DesertBarriers(void);
	virtual ~DesertBarriers(void);
	bool init();
	void Update(Drip* drip,float dt);
	CREATE_FUNC(DesertBarriers);

private:
	Vector<Barrier*> m_barriers;
};

