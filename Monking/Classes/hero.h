#ifndef HERO_H
#define HERO_H

#include "cocos2d.h"
#include "ActionSprite.h"

class HeroSprite : public ActionSprite
{
public:
	HeroSprite();
	~HeroSprite();

	virtual bool init();

	CREATE_FUNC(HeroSprite);
	
};

#endif