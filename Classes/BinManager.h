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

	void Update(float dt);  //��Ҫÿһ֡�����ã�̫����
	Vector<Bin*> arr;
private:
	void createBins();
	int centerToSide; //�����Ҽӵ�
	int centerToBottom;//�����Ҽӵ�
};

//bool BinManager::gameOver = false;

#endif