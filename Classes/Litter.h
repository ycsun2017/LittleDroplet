#ifndef _LITTER_H_
#define _LITTER_H_

#include "Entity.h"
#include "Bin.h"

class Litter : public Entity{
public:
	Litter();
	~Litter();
	CREATE_FUNC(Litter);
	virtual bool init();
public:
	//void show();
	Point origin;
	void hide();
	void set(int color,int i);
	//void reset();
	bool isAlive();
	bool collide(Bin*);
	void bindBin(Vector<Bin*>);
	Vector<Bin*> getBoundingBin();
private:
	bool alive;
	Vector<Bin*> boundBin;
};

#endif