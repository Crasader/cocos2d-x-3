#ifndef INTRO_LAYER_2_H
#define INTRO_LAYER_2_H

#include "cocos2d.h"


USING_NS_CC;

class IntroLayer2 : public CCLayer
{
public:
    IntroLayer2();
    ~IntroLayer2();

    virtual bool init();

    static CCScene *createScene();

    CREATE_FUNC(IntroLayer2);

    void startGame();

};

#endif