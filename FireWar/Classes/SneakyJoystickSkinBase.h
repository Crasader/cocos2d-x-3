#ifndef SNEAKY_JOY_STICK_SKIN_BASE_H
#define SNEAKY_JOY_STICK_SKIN_BASE_H

#include "cocos2d.h"
#include "SneakyJoystick.h"

USING_NS_CC;

class SneakyJoystickSkinBase : public CCLayer
{
public:
    SneakyJoystickSkinBase();
    ~SneakyJoystickSkinBase();

    virtual bool init();
    CREATE_FUNC(SneakyJoystickSkinBase);

    CC_SYNTHESIZE_READONLY(cocos2d::CCSprite *, backgroundSprite, BackgroundSprite);
    CC_SYNTHESIZE_READONLY(cocos2d::CCSprite *, thumbSprite, ThumbSprite);
    CC_SYNTHESIZE_READONLY(SneakyJoystick *, joystick, Joystick);

    void updatePositions(float t);
    void setContentSize(CCSize s);
    void setBackgroundSprite(CCSprite *aSprite);
    void setThumbSprite(CCSprite *aSprite);
    void setJoystick(SneakyJoystick *aJoystick);
};

#endif