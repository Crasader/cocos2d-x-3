#ifndef SNEAK_JOY_STICK_H
#define SNEAK_JOY_STICK_H

#include "cocos2d.h"

USING_NS_CC;

class SneakyJoystick : public CCNode ,public CCTargetedTouchDelegate
{
public:
    float joystickRadiusSq;
    float thumbRadiusSq;
    float deadRadiusSq;

    CC_SYNTHESIZE_READONLY(cocos2d::CCPoint, stickPosition, StickPosition);
    CC_SYNTHESIZE_READONLY(float, degrees, Degrees);
    CC_SYNTHESIZE_READONLY(cocos2d::CCPoint, velocity, Velocity);
    CC_SYNTHESIZE(bool, autoCenter, AutoCenter);
    CC_SYNTHESIZE_READONLY(bool, isDPad, IsDPad);
    CC_SYNTHESIZE(bool, hasDeadzone, HasDeadzone);
    CC_SYNTHESIZE(int, numberOfDirections, NumberOfDirections);

    CC_SYNTHESIZE_READONLY(float, joystickRadius, JoystickRadius);
    CC_SYNTHESIZE_READONLY(float, thumbRadius, ThumbRadius);
    CC_SYNTHESIZE_READONLY(float, deadRadius, DeadRadius);

    virtual ~SneakyJoystick();

    bool initWithRect(CCRect rect);
    virtual void onEnterTransitionDidFinish();
    virtual void onExit();
    void setIsDPad(bool b);
    void setJoystickRadius(float r);
    void setThumbRadius(float r);
    void setDeadRadius(float r);

    virtual bool ccTouchBegan(CCTouch *touch, CCEvent *event);
    virtual void ccTouchMoved(CCTouch *touch, CCEvent *event);
    virtual void ccTouchEnded(CCTouch *touch, CCEvent *event);
    virtual void ccTouchCancelled(CCTouch *touch,CCEvent *event);

private:
    void updateVelocity(cocos2d::CCPoint point);
    void setTouchRadius();

};



#endif