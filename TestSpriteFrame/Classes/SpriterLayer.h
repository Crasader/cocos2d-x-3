#ifndef SPRITER_LAYER_H
#define SPRITER_LAYER_H

#include "cocos2d.h"

USING_NS_CC;

class SpriterLayer : public CCLayer
{
public:
	virtual ~SpriterLayer();
	virtual bool init();
	CREATE_FUNC(SpriterLayer);
	
	static CCScene *createScene();

	CCSize size;

	void initSpriteOne();
	void initSpriteTwo();
	void initSpriteThree();
	void initSpriteFourth();

	void animationEnd();

	void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
	void update(float delta);

	CCPoint location;
};

#endif