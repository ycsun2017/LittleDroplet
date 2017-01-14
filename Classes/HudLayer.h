#pragma once

#include "cocos2d.h"
#include "cocostudio\CocoStudio.h"
#include "ui/CocosGUI.h"
using namespace cocostudio;
using namespace ui;
USING_NS_CC;

class HudLayer :
	public Layer
{
public:
	HudLayer(void);
	virtual ~HudLayer(void);
	bool init();
	void goRight(Ref* sender,Widget::TouchEventType controlEvent);
	void goLeft(Ref* sender,Widget::TouchEventType controlEvent);
	void jump(Ref* sender,Widget::TouchEventType controlEvent);
	void pause(Ref* sender,Widget::TouchEventType controlEvent);
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
	void changeHp(Ref* sender);
	CREATE_FUNC(HudLayer);


	Button* goRightBtn;
	Button* goLeftBtn;
	Button* pauseBtn;
	Button* jumpBtn;
	LoadingBar* hpBar;
	double hpValue;

};

