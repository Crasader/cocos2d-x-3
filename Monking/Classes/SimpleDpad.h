#ifndef SIMPLE_DPAD_H
#define SIMPLE_DPAD_H

#include "cocos2d.h"

USING_NS_CC;

class SimpleDpad;


class SimpleDelegate
{
public:
	virtual void didChangeDirectorTo(SimpleDpad *simpleDpad,CCPoint position) = 0; 
	virtual void isHoldingDirector(SimpleDpad *simpleDpad,CCPoint position) = 0;
	virtual void simpleDpadTouchEnd(SimpleDpad *simpleDpad) =0;
};

class SimpleDpad : public CCSprite,public CCTargetedTouchDelegate
{
public:
	SimpleDpad();
	~SimpleDpad();

	//virtual bool init();

	//CREATE_FUNC(SimpleDpad);

	static SimpleDpad *dpadWithFile(CCString *fileName,float r);
#ifdef INSTANCE
	static SimpleDpad *simpleDpad;
#endif

	bool initWithFile(CCString *fileName,float r);

	void onEnterTransitionDidFinish();
	void onExit();
	void update(float dt);
	

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);

	void updateDirectionForLocation(CCPoint location);

	SimpleDelegate *delegate;

	bool isHeld;

	float radius;
	CCPoint director;
};

#endif