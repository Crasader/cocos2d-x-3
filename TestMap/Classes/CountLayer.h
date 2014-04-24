#ifndef COUNT_LAYER_H
#define COUNT_LAYER_H

#include "cocos2d.h"

USING_NS_CC;

class CountLayer : public CCLayer
{
public :
	virtual bool init();
	CREATE_FUNC(CountLayer);
	CCLabelTTF *label;
	//CCLabelBMFont *timeLabel;
	CCLabelTTF *timeLabel;
	void countChange(int  count);
	void closeCallback(CCObject *psender);
	void updateTime(float dt);
	int count;
	int watermelonCount;

};

#endif