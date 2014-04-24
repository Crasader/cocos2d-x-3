#ifndef _BASER_LAYER_H
#define _BASER_LAYER_H
#include "cocos2d.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

using namespace CocosDenshion;

class BaserLayer : public CCLayer
{
	public:
		BaserLayer();
		~BaserLayer();

	virtual bool init();

	CCSize getWinSize();

	CREATE_FUNC(BaserLayer);

	void setBackGroundImage(CCSprite *back);
	void setBackGroundImage(const char* image);
};

#endif
