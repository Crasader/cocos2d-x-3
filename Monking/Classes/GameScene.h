#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#include "cocos2d.h"
#include "GameLayer.h"
#include "HubLayer.h"

USING_NS_CC;

class GameScene : public CCScene
{

public:
	GameScene(void);
	virtual ~GameScene(void);

	virtual bool init();

	CREATE_FUNC(GameScene);

	GameLayer *gameLayer;
	HubLayer *hubLayer;
};


#endif

