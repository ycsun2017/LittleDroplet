#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "StartScene.h"
USING_NS_CC;

AppDelegate::AppDelegate() {
	_music_switch = true;
	_effect_switch = true;
	_right_button_isPressed = false;
	_left_button_isPressed = false;
	_level = 0;
	_sparNum = 0;
}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

// If you want to use packages manager to install more packages, 
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::create("Little Droplet");
        director->setOpenGLView(glview);
    }
	glview->setDesignResolutionSize(960, 640, ResolutionPolicy::FIXED_HEIGHT);
    // turn on display FPS
    director->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    register_all_packages();

    // create a scene. it's an autorelease object
    auto scene = StartScene::create();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}

bool AppDelegate::getRightState()
{
	return _right_button_isPressed;
}
void AppDelegate::setRightState(bool state)
{
	_right_button_isPressed = state;
}
bool AppDelegate::getLeftState()
{
	return _left_button_isPressed;
}
void AppDelegate::setLeftState(bool state)
{
	_left_button_isPressed = state;
}
bool AppDelegate::getMusicState()
{
	return _music_switch;
}
void AppDelegate::setMusicState(bool state)
{
	_music_switch = state;
}
bool AppDelegate::getEffectState()
{
	return _effect_switch;
}
void AppDelegate::setEffectState(bool state)
{
	_effect_switch = state;
}
int AppDelegate::getLevel()
{
	return _level;
}
void AppDelegate::setLevel(int level)
{
	_level = level;
}
int AppDelegate::getSparNum()
{
	return _sparNum;
}
void AppDelegate::setSparNum(int num)
{
	_sparNum = num;
}