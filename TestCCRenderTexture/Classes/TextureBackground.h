#ifndef TEXTURE_BACKGROUND_H
#define TEXTURE_BACKGROUND_H

#include "cocos2d.h"

USING_NS_CC;


class TextureBackground : public CCLayer
{
protected:
    CCSprite *_background;
    CCSprite *_background2;
    CCSprite *_grass;

public:
    CREATE_FUNC(TextureBackground);

    TextureBackground() : _background(NULL) {};

    virtual bool init();
    ~TextureBackground();

    CCSprite* spriteWithColor(ccColor4F bgColor, float textureSize);
    CCSprite* spriteWithColor2(ccColor4F bgColor, float width, float height);

    ccColor4F randomBrightColor();
    void genBackground();

    virtual void menuCloseCallback(CCObject* pSender);

    virtual void ccTouchesBegan(CCSet* touches, CCEvent* event);


};

#endif