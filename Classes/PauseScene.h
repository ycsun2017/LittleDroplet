#pragma once
#include "cocos2d.h"
#include "cocostudio\CocoStudio.h"
#include "ui/CocosGUI.h"
using namespace cocostudio;
using namespace ui;
USING_NS_CC;
class PauseScene : public Scene
{
public:
	PauseScene(void);
	virtual ~PauseScene(void);	
	void create(CCRenderTexture* sqr);
	void exit(Ref* sender,Widget::TouchEventType controlEvent);
	void hint(Ref* sender,Widget::TouchEventType controlEvent);

	CREATE_FUNC(PauseScene);

private:
	Button* exitBtn;
	Button* returnBtn;
	Button* hintBtn;
	Sprite* musicControl;
	Sprite* effectControl;
	CCRenderTexture* renderTexture;
};

