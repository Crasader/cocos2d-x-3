#ifndef MENU_LAYER_H
#define MENU_LAYER_H

#include "cocos2d.h"

USING_NS_CC;

class MenuLayer : public CCLayer
{
public:
	virtual bool init();
	CREATE_FUNC(MenuLayer);
	static CCScene *createScene();
	void resetCallback(CCObject *sender);
	void quitCallback(CCObject *sender);
};

#endif