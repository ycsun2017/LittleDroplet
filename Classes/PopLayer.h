#pragma once

#include "cocos2d.h"
#include "cocostudio\CocoStudio.h"
#include "ui/CocosGUI.h"
using namespace cocostudio;
using namespace ui;
USING_NS_CC;

class PopLayer :
	public Layer
{
public:
	PopLayer(void);
	virtual ~PopLayer(void);
	bool init();
	void initWithCsb(int num);
	void onClick(Ref* sender,Widget::TouchEventType controlEvent);
	CREATE_FUNC(PopLayer);
private:
	Button* m_button;
};

