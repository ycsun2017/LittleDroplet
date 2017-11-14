#include "Litter.h"
#include "cocos2d.h"
#include "Bin.h"
USING_NS_CC;
Litter::Litter(){
	alive = true;
	color = ((int)(CCRANDOM_0_1()*100)) % 4; 
	origin = Point(0,0);
}

Litter::~Litter(){

}

bool Litter::init(){
	return true;
}

void Litter::set(int color,int i){

	Sprite* s = NULL;
	this->color = color;
	char name[50];
	memset(name,0,50);

	switch (color){
	case BLUE:
		sprintf(name,"litters/recyclable/%01d.png",i);
		s = Sprite::create(name);
		break;
	case RED:
		sprintf(name,"litters/harmful/%01d.png",i);
		s = Sprite::create(name);
		break;
	case GREEN:
		sprintf(name,"litters/kitchen/%01d.png",i);
		s = Sprite::create(name);
		break;
	case YELLOW:
		sprintf(name,"litters/other/%01d.png",i);
		s = Sprite::create(name);
		break;
	}

	bindSprite(s);
	
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [&](Touch* touch, Event* event){
		if(getBoundingBox().containsPoint(touch->getLocation())){
			origin = getPosition();
			return true;
		}
		else 
			return false;
	};
	listener->onTouchMoved = [&](Touch* touch, Event* event){
		{
			setPosition(touch->getLocation());
		}
	};
	listener->onTouchEnded = [&](Touch* touch, Event* event){
			for(auto bin: getBoundingBin()){
				if(collide(bin)){
					if(this->color == bin->color){
						bin->speedDown();
						hide();
						break;
					}
					else{
						hide();
						bin->angry();
						bin->speedUp();
						setPosition(origin);
					}
				}
				else
					continue;
			}
			setPosition(origin);
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

}

//void Litter::show(){
//	if (getSprite() != NULL){
//		setVisible(true);
//		alive = true;
//	}
//}

void Litter::hide(){
	if (getSprite() != NULL){
		setVisible(false);
		//reset();
		alive = false;
	}
	//delete sprite
}

/*
void Litter::reset(){
	if (getSprite() != NULL){
		setPosition(Point(800 + CCRANDOM_0_1() * 2000, 200 - CCRANDOM_0_1() * 100));//·¶Î§´ýÐÞ¸Ä
	}
}*/

bool Litter::isAlive(){
	return alive;
}

bool Litter::collide(Bin* bin){
	Rect rect = bin->getBoundingBox();

	Point litterPos = getPosition();

	return rect.containsPoint(litterPos);
}

void Litter::bindBin(Vector<Bin*> binArr){
		boundBin = binArr;
}

Vector<Bin*> Litter::getBoundingBin(){
	return boundBin;
}