#ifndef  LEVEL_GENERATOR_HUB_H
#define  LEVEL_GENERATOR_HUB_H

#include "cocos2d.h"

USING_NS_CC;

class  LevelGeneratorHub : public CCLayer
{
public:
	LevelGeneratorHub();
	~LevelGeneratorHub();

	virtual bool init();

	CREATE_FUNC(LevelGeneratorHub);

	CCLabelTTF *label;
	CCLabelTTF *lblTimer;

	void backCallback(CCObject *sender);
	void pauseCallback(CCObject *sender);
	void playCallback(CCObject *sender);

private:

	CCLabelTTF* lblScore;
	CCLabelTTF* lblEnemyScore;
	CCLabelTTF* lblZombieScore;
	CCLabelTTF* lblCarScore;
	CCLabelTTF* lblTruckScore;
	CCLabelTTF* lblHeliScore;
};

#endif