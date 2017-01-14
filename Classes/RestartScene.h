#pragma once

#include "cocos2d.h"
#include "cocostudio\CocoStudio.h"
#include "ui/CocosGUI.h"
using namespace cocostudio;
using namespace ui;
USING_NS_CC;

class RestartScene :
	public Scene
{
public:
	RestartScene(void);
	virtual ~RestartScene(void);
	void create(CCRenderTexture* sqr);
	void onClickBtn(Ref* sender,Widget::TouchEventType controlEvent);
	CREATE_FUNC(RestartScene);
};

