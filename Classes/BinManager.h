#ifndef _BINMANAGER_H_
#define _BINMANAGER_H_
#include "cocos2d.h"
#include "Bin.h"
USING_NS_CC;

#define MAX_BIN_NUM 4

class BinManager :public Node{
public:
	//static bool gameOver;
	CREATE_FUNC(BinManager);
	virtual bool init();

	void Update(float dt);  //不要每一帧都调用，太快了
	Vector<Bin*> arr;
private:
	void createBins();
	int centerToSide; //这是我加的
	int centerToBottom;//这是我加的
};

//bool BinManager::gameOver = false;

#endif