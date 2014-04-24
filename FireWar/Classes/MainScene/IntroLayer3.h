#ifndef INTRO_LAYER_H
#define INTRO_LAYER_H

#include "cocos2d.h"


USING_NS_CC;

class IntroLayer3 : public CCLayer
{
public:
	IntroLayer3();
	~IntroLayer3();

	virtual bool init();

	static CCScene *createScene();

	CREATE_FUNC(IntroLayer3);

	void startGame();

};

#endif