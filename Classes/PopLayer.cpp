#include "PopLayer.h"


PopLayer::PopLayer(void)
{
	m_button = NULL;
}


PopLayer::~PopLayer(void)
{
}

bool PopLayer::init()
{
	/*Node* hint = CSLoader::createNode("Layer.csb");
	this->addChild(hint);
		
	m_button = static_cast<Button*>(hint->getChildByName("Button_1"));

	m_button->addTouchEventListener(CC_CALLBACK_2(PopLayer::onClick,this));	*/
	return true;
}

void PopLayer::initWithCsb(int num)
{
	/*char name[10];
	memset(name,0,10);
	sprintf(name,"Layer%01d.csb",num);
	log(name);*/
	Node* hint = CSLoader::createNode("Layer1.csb");
	this->addChild(hint);
		
	m_button = static_cast<Button*>(hint->getChildByName("exitButton"));

	m_button->addTouchEventListener(CC_CALLBACK_2(PopLayer::onClick,this));	
}

void PopLayer::onClick(Ref* sender,Widget::TouchEventType controlEvent)
{
	if(controlEvent == cocos2d::ui::Widget::TouchEventType::BEGAN)
	{
		//µã»÷°´Å¥·µ»Ø
		NotificationCenter::getInstance()->postNotification("remove");
	}
}