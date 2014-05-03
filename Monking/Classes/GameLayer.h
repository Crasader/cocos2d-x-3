#ifndef GAME_LAYER_H
#define GAME_LAYER_H

#include "cocos2d.h"
#include "hero.h"
#include "SimpleDpad.h"
#include "HubLayer.h"

USING_NS_CC;

class GameLayer : public CCLayer , public SimpleDelegate
{
public:
	GameLayer();
	~GameLayer();

	virtual bool init();
	virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
	void registerWithTouchDispatcher(void);

	virtual void didChangeDirectorTo(SimpleDpad *simpleDpad,CCPoint position) ; 
	virtual void isHoldingDirector(SimpleDpad *simpleDpad,CCPoint position) ;
	virtual void simpleDpadTouchEnd(SimpleDpad *simpleDpad) ;

	void initTiledMap();

	CREATE_FUNC(GameLayer);

	CCSpriteBatchNode *actor;

	HeroSprite *heroSprite;

	void initHero();
	void initRobot();
	void updateRobot(float dt);   //实现机器人抉择方法
//	float getCurrentTime();

	void gameOver();
	void gameReset();
	void gameReset(CCObject *psend);


	CCArray  *robotArray;

	void update(float delta);

	CCTMXTiledMap *tiled;

	void setHubLayer(HubLayer *layer);
	HubLayer *hubLayer;

	virtual void keyBackClicked();
	virtual void keyMenuClicked();
};

#endif
