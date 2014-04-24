#ifndef SNEAKY_BUTTON_SKINNED_BASE_H
#define SNEAKY_BUTTON_SKINNED_BASE_H

#include "cocos2d.h"
#include "SneakyButton.h"

USING_NS_CC;

class SneakyButtonSkinnedBase : public CCLayer
{
public:
    CC_SYNTHESIZE_READONLY(CCSprite *, defaultSprite, DefaultSprite);
    CC_SYNTHESIZE_READONLY(CCSprite *, activatedSprite, ActivatedSprite);
    CC_SYNTHESIZE_READONLY(CCSprite *, disabledSprite, DisabledSprite);
    CC_SYNTHESIZE_READONLY(CCSprite *, pressSprite, PressSprite);

    CC_SYNTHESIZE_READONLY(SneakyButton *, button, Button); //Not sure about this

    //Public methods
    CREATE_FUNC(SneakyButtonSkinnedBase);
    virtual ~SneakyButtonSkinnedBase();
    bool init();
    void watchSelf(float t);
    void setContentSize(CCSize s);
    void setDefaultSprite(CCSprite *aSprite);
    void setActivatedSprite(CCSprite *aSprite);
    void setDisabledSprite(CCSprite *aSprite);
    void setPressSprite(CCSprite *aSprite);
    void setButton(SneakyButton *aButton);
};

#endif