#pragma once

#include "cocos2d.h"
#include "cocostudio\CocoStudio.h"
#include "ui/CocosGUI.h"
using namespace cocostudio;
using namespace ui;
USING_NS_CC;
class PopScene :
	public Scene
{
public:
	PopScene(void);
	virtual ~PopScene(void);
	void initWithCsb(char name[],CCRenderTexture* sqr );
	void initWithSprite(char name[],CCRenderTexture* sqr);
	void onClickBtn(Ref* sender,Widget::TouchEventType controlEvent);
	void assignScene(Scene* scene, bool replace, bool push);
	void exit();
	void changeScene();

	CREATE_FUNC(PopScene);

private:
	Button* exitBtn;
	bool replaceScene;
	bool pushScene;
	Scene* newScene;
};

