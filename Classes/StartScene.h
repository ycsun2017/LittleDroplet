#pragma once
#include "cocos2d.h"
#include "cocostudio\CocoStudio.h"
#include "ui/CocosGUI.h"
using namespace cocostudio;
using namespace ui;
USING_NS_CC;

class StartScene : public Scene
{
public:
	StartScene(void);
	virtual ~StartScene(void);
	virtual bool init();
	void start(Ref* sender,Widget::TouchEventType controlEvent);

	CREATE_FUNC(StartScene);

private:
	Button* startBtn;
};

