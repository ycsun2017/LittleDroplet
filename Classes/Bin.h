#ifndef _BIN_H_
#define _BIN_H_

#include "Entity.h"
#include "Defines.h"
const int DEFAULT_SPEED = 3;

/*typedef enum _ActionState {
    kActionStateNone = 0,
    kActionStateStop,
    kActionStateWalk,
	kActionStateAngry
} ActionState;
*/
class Bin : public Entity{
public:
	Bin();
	Bin(int);
	~Bin(); 
	CREATE_FUNC(Bin);
	virtual bool init();
	int speed;
public:
	bool isAlive();
	void setAlive(bool state); 
	void speedUp();
	void speedDown();
	bool collide();
	void walk();
	void angry();
	void initActions();

	CC_SYNTHESIZE(ActionState, _actionState, ActionState);
	CC_SYNTHESIZE_RETAIN(Action*, _walkAction, WalkAction);
	CC_SYNTHESIZE_RETAIN(Action*, _angryAction, AngryAction);
private:
	bool alive;
};

#endif