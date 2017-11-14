#ifndef  _APP_DELEGATE_H_
#define  _APP_DELEGATE_H_

#include "cocos2d.h"

/**
@brief    The cocos2d Application.

The reason for implement as private inheritance is to hide some interface call by Director.
*/
class  AppDelegate : private cocos2d::Application
{
public:
    AppDelegate();
    virtual ~AppDelegate();

    virtual void initGLContextAttrs();

    /**
    @brief    Implement Director and Scene init code here.
    @return true    Initialize success, app continue.
    @return false   Initialize failed, app terminate.
    */
    virtual bool applicationDidFinishLaunching();

    /**
    @brief  The function be called when the application enter background
    @param  the pointer of the application
    */
    virtual void applicationDidEnterBackground();

    /**
    @brief  The function be called when the application enter foreground
    @param  the pointer of the application
    */
    virtual void applicationWillEnterForeground();
	bool getRightState();
	void setRightState(bool state);
	bool getLeftState();
	void setLeftState(bool state);

	bool getMusicState();
	void setMusicState(bool state);
	bool getEffectState();
	void setEffectState(bool state);
	int getLevel();
	void setLevel(int level);
	int getSparNum();
	void setSparNum(int num);

private:
	bool _right_button_isPressed;
	bool _left_button_isPressed;
	bool _music_switch;
	bool _effect_switch;
	int _level;
	int _sparNum;
};

#endif // _APP_DELEGATE_H_

