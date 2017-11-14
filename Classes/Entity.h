#ifndef _ENTITY_H_
#define _ENTITY_H_

#include "cocos2d.h"
USING_NS_CC;

const int BLUE = 1;
const int RED = 2;
const int GREEN = 3;
const int YELLOW = 4;

class Entity : public Node{
public:
	Entity();
	~Entity();
	Sprite* getSprite();
	void bindSprite(Sprite*);
	int color;
//private:
	Sprite* m_sprite;
};
#endif