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
	void initWithSelect(char name[],CCRenderTexture* sqr );
	void initWithSprite(char name[],CCRenderTexture* sqr);
	void initWithDialogs(char name[],int num, CCRenderTexture* sqr);
	void initRestart(CCRenderTexture* sqr );
	void onClickBtn(Ref* sender,Widget::TouchEventType controlEvent);
	void onRestartBtn(Ref* sender,Widget::TouchEventType controlEvent);
	void onClickYes(Ref* sender,Widget::TouchEventType controlEvent);
	void onClickNo(Ref* sender,Widget::TouchEventType controlEvent);
	void assignScene(Scene* scene, bool replace, bool push);
	void exit();
	void changeScene();

	CREATE_FUNC(PopScene);

private:
	Button* exitBtn;
	Button* yesBtn;
	Button* noBtn;
	bool replaceScene;
	bool pushScene;
	Scene* newScene;
	int digNum;
};

