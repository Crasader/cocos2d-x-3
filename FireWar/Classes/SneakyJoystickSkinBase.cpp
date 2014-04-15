#include "SneakyJoystickSkinBase.h"

SneakyJoystickSkinBase::SneakyJoystickSkinBase()
{
    backgroundSprite = NULL;
    thumbSprite = NULL;
}

SneakyJoystickSkinBase::~SneakyJoystickSkinBase()
{
    if (backgroundSprite)
    {
        backgroundSprite->release();
        backgroundSprite = NULL;
    }
    if (thumbSprite)
    {
        thumbSprite->release();
        thumbSprite = NULL;
    }

    if (joystick)
    {
        joystick->release();
        joystick = NULL;
    }
}

bool SneakyJoystickSkinBase::init()
{
    bool pRet = false;
    if (CCLayer::init()) {
        this->backgroundSprite = NULL;

        this->thumbSprite = NULL;

        this->joystick = NULL;

        this->schedule(schedule_selector(SneakyJoystickSkinBase::updatePositions));
        pRet = true;
    }
    return pRet;
}

void SneakyJoystickSkinBase::updatePositions(float t)
{
    if (joystick && thumbSprite)
        thumbSprite->setPosition(joystick->getStickPosition());
}

void SneakyJoystickSkinBase::setContentSize(CCSize s)
{
    CCLayer::setContentSize(s);
    backgroundSprite->setContentSize(s);
}

void SneakyJoystickSkinBase::setBackgroundSprite(CCSprite *aSprite)
{
    CCLOG("**************************add1\n");
    if (backgroundSprite) {
        if (backgroundSprite->getParent())
            backgroundSprite->getParent()->removeChild(backgroundSprite, true);
        backgroundSprite->release();
    }
    aSprite->retain();
    backgroundSprite = aSprite;
    if (aSprite) {

        CCLOG("**************************add2\n");
        this->addChild(backgroundSprite, 0);

        this->setContentSize(backgroundSprite->getContentSize());
    }
}

void SneakyJoystickSkinBase::setThumbSprite(CCSprite *aSprite)
{
    if (thumbSprite) {
        if (thumbSprite->getParent())
            thumbSprite->getParent()->removeChild(thumbSprite, true);
        thumbSprite->release();
    }
    aSprite->retain();
    thumbSprite = aSprite;
    if (aSprite) {
        this->addChild(thumbSprite, 1);

        //joystick->setThumbRadius(thumbSprite->getContentSize().width/2);
    }
}

void SneakyJoystickSkinBase::setJoystick(SneakyJoystick *aJoystick)
{
    if (joystick) {
        if (joystick->getParent())
            joystick->getParent()->removeChild(joystick, true);
        joystick->release();
    }
    aJoystick->retain();
    joystick = aJoystick;
    if (aJoystick) {
        this->addChild(aJoystick, 2);
        if (thumbSprite)
            joystick->setThumbRadius(thumbSprite->getContentSize().width/2);
        else
            joystick->setThumbRadius(0);

        if (backgroundSprite)
            joystick->setJoystickRadius(backgroundSprite->getContentSize().width/2);
    }
}

