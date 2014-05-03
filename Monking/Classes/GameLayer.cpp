#include "GameLayer.h"
#include "Robot.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "config.h"
#include "MenuLayer.h"

using namespace CocosDenshion;

/*
#define frandom (float)random()/UINT64_C(0x100000000)
#define frandom_range(low,high) ((high-low)*frandom)+low
*/

#ifndef INT64_C
#define INT64_C(c) (c ## LL)
#define UINT64_C(c) (c ## ULL)
#endif

#define random_range(low, high) (rand() % (high - low + 1)) + low
#define frandom (float)rand() / UINT64_C(0x100000000)
#define frandom_range(low, high) ((high - low) * frandom) + low

GameLayer::GameLayer()
{
	this->heroSprite = NULL;
	tiled = NULL;
	robotArray = NULL;
	hubLayer = NULL;
	//heroSprite->autorelease();
}

GameLayer::~GameLayer()
{
}

bool GameLayer::init()
{
	if(!CCLayer::init())
		return false;

/*	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("latin_industries.wav");
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic("latin_industries.wav");
	SimpleAudioEngine::sharedEngine()->preloadEffect("pd_hit0.wav");
	SimpleAudioEngine::sharedEngine()->preloadEffect("pd_hit1.wav");
	SimpleAudioEngine::sharedEngine()->preloadEffect("pd_herodeath.wav");
	SimpleAudioEngine::sharedEngine()->preloadEffect("pd_botdeath.wav");
*/

	this->initTiledMap();

	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("pd_sprites.plist");

	actor = CCSpriteBatchNode::create("pd_sprites.pvr.ccz");
	actor->getTexture()->setAliasTexParameters();

	this->addChild(actor);

	initHero();
	initRobot();

	this->setTouchEnabled(true);
	this->scheduleUpdate();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//	CCLayer::setIsKeypadEnabled(true);
	setKeypadEnabled(true);
#endif
	
	return true;
}

void GameLayer::setHubLayer(HubLayer *layer)
{
	this->hubLayer =layer ;
}


void GameLayer::initTiledMap()
{
	tiled = CCTMXTiledMap::create("pd_tilemap.tmx");

	CCObject *obj = NULL;

	CCARRAY_FOREACH(tiled->getChildren(),obj)
	{
		CCTMXLayer *child = (CCTMXLayer *)obj;

		child->getTexture()->setAliasTexParameters();
	} 

	this->addChild(tiled);
}

void GameLayer::initHero()
{
	this->heroSprite = HeroSprite::create();
	this->actor->addChild(heroSprite);

	heroSprite->setPosition(ccp(this->heroSprite->centerToSlide,80));

	heroSprite->desritePoint = heroSprite->getPosition();

	heroSprite->idle();
}

void GameLayer::initRobot()
{
	robotArray = CCArray::create();
	robotArray->retain();
	
	for (int i=0;i<25;i++)
	{
		Robot *robot = Robot::create();
		actor->addChild(robot);
		robotArray->addObject(robot);

		CCSize winSize=CCDirector::sharedDirector()->getWinSize();
		int minX=winSize.width+robot->centerToSlide ;
		int maxX=this->tiled->getMapSize().width*this->tiled->getTileSize().width-robot->centerToSlide;
		int minY=robot->centerToBottom;
		int maxY=3*this->tiled->getTileSize().height+robot->centerToBottom;
		robot->setScaleX(-1);
		robot->setPosition(ccp((rand()%(maxX-minX+1))+minX,(rand()%(maxY-minY+1))+minY));
		robot->desritePoint=robot->getPosition();
		robot->idle();

	} 

}



void GameLayer::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
	this->heroSprite->attack();

	CCObject *obj;
	CCARRAY_FOREACH(this->robotArray,obj)
	{
		Robot *robot = (Robot *)obj; 

		if(robot->actionState != ACTION_DEAD)
		{
			if(fabsf(this->heroSprite->getPositionY() -robot->getPositionY()) <10)
			{
				if(this->heroSprite->attackBox.actual.intersectsRect(robot->hitBox.actual))
				{
					robot->hurtWithDanage(this->heroSprite->danage);
				}
			}
		}
	}

}

void GameLayer::registerWithTouchDispatcher(void)
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate(this,0);  //注册多点触摸
}

 void GameLayer::didChangeDirectorTo(SimpleDpad *simpleDpad,CCPoint position)
 {
	heroSprite->walkWithDirection(position);
 }

 void GameLayer::isHoldingDirector(SimpleDpad *simpleDpad,CCPoint position)
 {
	 heroSprite->walkWithDirection(position);
 }
void GameLayer::simpleDpadTouchEnd(SimpleDpad *simpleDpad)
{
	if(heroSprite->actionState ==  ACTION_WALK)
	{
		heroSprite->idle();
	}
}

void GameLayer::update(float delta)
{
	heroSprite->updateDesiredPosition(delta);

	float posx = MIN(this->tiled->getMapSize().width*this->tiled->getTileSize().width -heroSprite->centerToSlide,
		MAX(heroSprite->centerToSlide,heroSprite->desritePoint.x));

	float posy = MIN(3*this->tiled->getTileSize().height+this->heroSprite->centerToBottom,
		MAX(heroSprite->centerToSlide,heroSprite->desritePoint.y));

	heroSprite->setPosition(ccp(posx,posy));

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	int x = MAX(heroSprite->getPositionX(),winSize.width/2);
	int y = MAX(heroSprite->getPositionY(),winSize.height/2);

	//砖块的个数X砖块的宽度
	x = MIN(x,(this->tiled->getMapSize().width*this->tiled->getTileSize().width)-winSize.width/2);
	y = MIN(y,(this->tiled->getMapSize().height*this->tiled->getTileSize().height)-winSize.height/2); 

	CCPoint actualPointion = ccp(x,y);
	CCPoint centerOfView = ccp(winSize.width/2,winSize.height/2);
	CCPoint viewPoint = ccpSub(centerOfView,actualPointion);

	this->setPosition(viewPoint);

	CCObject *obj = NULL;

	CCARRAY_FOREACH(this->actor->getChildren(),obj)
	{
		this->actor->reorderChild((CCNode *)obj,1000-((ActionSprite*)obj)->getPositionY());
	}

	updateRobot(delta);

	obj = NULL;

	CCARRAY_FOREACH(robotArray,obj)
	{
		Robot *robot = (Robot*) obj;

		float posx = MIN(this->tiled->getMapSize().width*this->tiled->getTileSize().width -robot->centerToSlide,
			MAX(robot->centerToSlide,robot->desritePoint.x));

		float posy = MIN(3*this->tiled->getTileSize().height+robot->centerToBottom,
			MAX(robot->centerToSlide,robot->desritePoint.y));

		robot->setPosition(ccp(posx,posy));

	}
}

float getCurrentTime()
{
	timeval time ;
	gettimeofday(&time,NULL);

	unsigned long millises = time.tv_sec*1000+time.tv_usec/1000;

	return millises;
}

void GameLayer::updateRobot(float dt)
{
	int alive = 0;
	int distanceSQ; //两点之间距离的平方
	int randomChoice = 0;

	CCSize size = CCDirector::sharedDirector()->getWinSize();


	CCObject *obj = NULL;


	CCARRAY_FOREACH(this->robotArray,obj)
	{
		Robot *robot =  (Robot *)obj;

		robot->updateDesiredPosition(dt);

		if(robot->actionState != ACTION_DEAD)
		{
			alive+=1;

			if(getCurrentTime() > robot->nextDecisionTime)
			{
				distanceSQ = ccpDistanceSQ(robot->getPosition(),this->heroSprite->getPosition());

				if(distanceSQ <=50*50)
				{
					robot->nextDecisionTime = getCurrentTime() + frandom_range(0.1,0.5);
					randomChoice = random_range(0,1);

					if(randomChoice == 0)   //机器人执行攻击动作
					{
						if(this->heroSprite->getPositionX() > robot->getPositionX())
						{
							robot->setScaleX(1.0f);
						}
						else
						{
							robot->setScaleX(-1.0f);
						}

						robot->nextDecisionTime=robot->nextDecisionTime+frandom_range(0.1,0.5)*2000;
						robot->attack();

						if(fabsf(this->heroSprite->getPositionY()-robot->getPositionY())<10){
							if(heroSprite->hitBox.actual.intersectsRect(robot->attackBox.actual)){
								heroSprite->hurtWithDanage(robot->danage);

								if(heroSprite->actionState ==  ACTION_DEAD && !hubLayer->getChildByTag(1))
								{
									gameOver();
								}

							}
						}

					}else
					{
						robot->idle();
					}
				}else if(distanceSQ <= size.width*size.width)
				{
					robot->nextDecisionTime = getCurrentTime()+frandom_range(0.5,1.0)*1000;
					randomChoice=random_range(0,2);

					if(randomChoice == 0)
					{
						CCPoint moveDirection=ccpNormalize(ccpSub(heroSprite->getPosition(),robot->getPosition())); 

						robot->walkWithDirection(moveDirection);
						robot->updateDesiredPosition(dt*20);
					}else 
					{
						robot->idle();
					}

				}
			}
		}
	}

	if(alive==0 && !hubLayer->getChildByTag(1) )
	{
		gameOver();
	}
}

void GameLayer::gameOver()
{
	CCLabelTTF *label = CCLabelTTF::create("Reset","Arial",40);

	CCMenuItemLabel *resetItem = CCMenuItemLabel::create(label,this,menu_selector(GameLayer::gameReset));

	CCMenu *menu = CCMenu::create(resetItem,NULL);

	CCSize size = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint point = CCDirector::sharedDirector()->getVisibleOrigin();

	menu->setPosition(ccp(point.x+size.width/2,point.y+size.height/2));
	menu->setTag(1);
	
	GameScene *scene = (GameScene *) this->getParent();

	if(scene !=NULL)
	{
		CCLOG("test-------------------");
		scene->hubLayer->addChild(menu);
	}
}

void GameLayer::gameReset()
{

}

void GameLayer::gameReset(CCObject *psend)
{
	CCDirector::sharedDirector()->replaceScene(GameScene::create());
}

void GameLayer::keyBackClicked()
{

#ifdef DEBUG
	CCLOG("*****************************back\n");
#endif

/*	CCDirector::sharedDirector()->pause();

	if(SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying())
	{
		    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
	}*/

//	exit(0);
	CCDirector::sharedDirector()->pushScene(CCTransitionFade::create(0.5f, MenuLayer::createScene()));
}

void GameLayer::keyMenuClicked()
{
	CCLOG("*****************************menu\n");
}
