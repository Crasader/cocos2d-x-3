#ifndef SNEAKY_BUTTON_H
#define SNEAKY_BUTTON_H

#include "cocos2d.h"

USING_NS_CC;

class SneakyButton : public CCNode,public CCTargetedTouchDelegate
{
public:
    CCPoint center;
    float radiusSq;

    cocos2d::CCRect bounds;

    CC_SYNTHESIZE(bool, status, Status);
    CC_SYNTHESIZE_READONLY(bool, active, IsActive);
    CC_SYNTHESIZE_READONLY(bool, value, Value);
    CC_SYNTHESIZE(bool, isHoldable, IsHoldable);
    CC_SYNTHESIZE(bool, isToggleable, IsToggleable);
    CC_SYNTHESIZE(float, rateLimit, RateLimit);

    CC_SYNTHESIZE_READONLY(float, radius, Radius);

    //Public methods
    virtual void onEnterTransitionDidFinish();
    virtual void onExit();
    bool initWithRect(cocos2d::CCRect rect);
    void limiter(float delta);
    void setRadius(float r);
    virtual bool ccTouchBegan(CCTouch *touch, cocos2d::CCEvent *event);
    virtual void ccTouchMoved(CCTouch *touch, cocos2d::CCEvent *event);
    virtual void ccTouchEnded(CCTouch *touch, cocos2d::CCEvent *event);
    virtual void ccTouchCancelled(CCTouch *touch, cocos2d::CCEvent *event);

};

#endif