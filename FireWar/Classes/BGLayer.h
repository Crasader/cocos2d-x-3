#ifndef BG_LAYER_H
#define BG_LAYER_H

#include "cocos2d.h"

USING_NS_CC;

class BGLayer : public  CCLayer
{
    virtual bool init();


    static CCScene* createScene();


    virtual void menuCloseCallback(CCObject* pSender);

    CREATE_FUNC(BGLayer);
    virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
};

#endif