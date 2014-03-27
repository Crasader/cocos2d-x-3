#ifndef MENU_LAYER_H
#define MENU_LAYER_H

#include "cocos2d.h"

USING_NS_CC;

class MenuLayer: public CCLayer
{
public:
	MenuLayer();
	~MenuLayer();

	static CCScene *createScene();

	virtual bool init();

	CREATE_FUNC(MenuLayer);


	void level1Callback(CCObject *sender);
	void level2Callback(CCObject *sender);
	void level3Callback(CCObject *sender);
};

#endif
