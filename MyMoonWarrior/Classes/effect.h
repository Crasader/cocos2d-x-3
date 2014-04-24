#ifndef _EFFECT_H
#define _EFFECT_H

#include "cocos2d.h"

USING_NS_CC;

class Effect
{
	public:
	Effect();
	~Effect();
	static Effect *getSharedEffect();
	static Effect *instanece;

	void preLoad();

	void boom(CCNode *target,CCPoint point);

	void boom_callback(CCNode *pNode);
};


#endif
