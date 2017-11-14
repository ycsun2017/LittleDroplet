#pragma once
#include "cocos2d.h"
#include "Barrier.h"
#include "Drip.h"

USING_NS_CC;
class MineBarriers : public Node
{
public:
	MineBarriers(void);
	virtual ~MineBarriers(void);
	bool init();
	void Update(Drip* drip,float dt);
	CREATE_FUNC(MineBarriers);

private:
	Vector<Barrier*> m_barriers;
};

