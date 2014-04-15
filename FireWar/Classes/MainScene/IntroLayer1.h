#ifndef INTRO_LAYER_1_H
#define INTRO_LAYER_1_H

#include "cocos2d.h"


USING_NS_CC;

class IntroLayer1 : public CCLayer
{
public:
    IntroLayer1();
    ~IntroLayer1();

    virtual bool init();

    static CCScene *createScene();

    CREATE_FUNC(IntroLayer1);

    void startGame();

};

#endif