#pragma once
#include "Barrier.h"
#include "Drip.h"

USING_NS_CC;
class ForestBarriers : public Node
{
public:
	ForestBarriers(void);
	virtual ~ForestBarriers(void);
	bool init();
	void Update(Drip* drip,float dt);
	CREATE_FUNC(ForestBarriers);

private:
	Vector<Barrier*> m_barriers;
};

