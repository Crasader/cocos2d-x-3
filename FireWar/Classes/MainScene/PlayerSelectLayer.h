#ifndef PLAYER_SELECT_LAYER_H
#define PLAYER_SELECT_LAYER_H

#include "cocos2d.h"

USING_NS_CC;

class PlayerSeleceLayer : public CCLayer
{
public:
	PlayerSeleceLayer();
	~PlayerSeleceLayer();

	static CCScene *createScene() ;

	virtual bool init();

	CREATE_FUNC(PlayerSeleceLayer);

	void playerSelectOne(CCObject *sender);
	void playerSelectSecond(CCObject *sender);
	void playerSelectThrid(CCObject *sender);
};

#endif