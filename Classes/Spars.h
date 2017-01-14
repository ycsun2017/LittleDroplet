#pragma once
#include "cocos2d.h"
#include "Drip.h"
#include "Spar.h"
#define SPAR_NUM 20
USING_NS_CC;

class Spars : public Node
{
public:
	Spars(void);
	virtual ~Spars(void);

	bool init();
	void Update(Drip* drip,float dt);
	CREATE_FUNC(Spars);

private:
	Vector<Spar*> m_spars;
};

