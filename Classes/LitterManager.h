#ifndef _LITTERMANAGER_H_
#define _LITTERMANAGER_H_

#include "cocos2d.h"
#include "Litter.h"
#include "BinManager.h"
USING_NS_CC;

#define MAX_LITTER_NUM 18
#define BLUE_NUM 5
#define GREEN_NUM 4
#define RED_NUM 6
#define YELLOW_NUM 4

class LitterManager :public Node{
public:
	LitterManager();
	virtual ~LitterManager();
	CREATE_FUNC(LitterManager);
	virtual bool init();


	virtual void update(float dt);

	void bindBin(Vector<Bin*>);
private:
	void createLitters();
	Vector<Bin*> bindBinArr;
private:
	Vector<Litter*> arr;
};
#endif