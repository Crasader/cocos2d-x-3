#include "LevelGeneratorHub.h"
#include "config.h"
#define FONT_SIZE 20

LevelGeneratorHub::LevelGeneratorHub()
{

}

LevelGeneratorHub::~LevelGeneratorHub()
{


}

bool LevelGeneratorHub::init()
{
	if(!CCLayer::init())
		return false;

	CCSprite *sprite = CCSprite::create("SpriteImages/ScoreBar.png");
	sprite->setPosition(ccp(250.0f, 305));
	addChild(sprite,0);

	sprite = CCSprite::create("SpriteImages/emptyBar.png");
	sprite->setPosition(ccp(700.0f, 305));
	addChild(sprite, 0);

	CCSize size = CCDirector::sharedDirector()->getWinSize();
	
	label = CCLabelTTF::create("0","Verdana-Bold",FONT_SIZE,CCSizeMake(50,50),CCTextAlignment::kCCTextAlignmentRight);
	label->setColor(ccc3(0,0,0));
	label->setVisible(true);

	lblScore = CCLabelTTF::create("000","Verdana-Bold",FONT_SIZE);
	lblScore->retain();
	lblScore ->setColor( ccc3(250,250, 250) );
	lblScore ->setPosition(ccp(190,305));
	addChild(lblScore ,0);

	lblEnemyScore = CCLabelTTF::create("0","Verdana", FONT_SIZE);
	lblEnemyScore ->retain();
	lblEnemyScore ->setColor( ccc3(250,250, 250) );
	lblEnemyScore ->setPosition(ccp(280,305));
	addChild(lblEnemyScore ,0);
	

	lblZombieScore = CCLabelTTF::create("0","Verdana", FONT_SIZE);
	lblZombieScore ->retain();
	lblZombieScore ->setColor( ccc3(250,250, 250) );
	lblZombieScore ->setPosition(ccp(340,305));
	addChild(lblZombieScore ,0);
	
	lblCarScore = CCLabelTTF::create("0","Verdana", FONT_SIZE);
	lblCarScore ->retain();
	lblCarScore ->setColor( ccc3(250,250, 250) );
	lblCarScore ->setPosition(ccp(400,305));
	addChild(lblCarScore ,0);

	lblTimer = CCLabelTTF::create("00:00","Verdana", FONT_SIZE);
	lblTimer ->retain();
	lblTimer ->setColor( ccc3(250,250, 250) );
	lblTimer ->setPosition(ccp(475,305));
	lblTimer->setVisible(false);
	addChild(lblTimer ,0);

	int margin = 10;

	label->setPosition(ccp(size.width - (label->getContentSize().width/2)-margin,
		label->getContentSize().height / 2 + margin));

	addChild(label);

	CCSprite *hbb = CCSprite::create("SpriteImages/heathbarborder.png");
	hbb->setPosition(ccp(size.width-300,size.height-13));
	addChild(hbb,3);

	CCSprite *hb = CCSprite::create("SpriteImages/healthbar.png");
	hb->setPosition(ccp(size.width-300,size.height-13));
	addChild(hb,2,1);

	setTouchEnabled(true);


	CCLabelTTF *gameStart = CCLabelTTF::create("Game Start", "Arial", FONT_SIZE);
	gameStart->setPosition(ccp(size.width/2,size.height/2));
	addChild(gameStart);

	CCFiniteTimeAction *labelAction = CCSpawn::createWithTwoActions(CCScaleBy::create(0.6f, 2), CCFadeOut::create(0.6f));
	//gameStart->runAction(labelAction);

	CCMenuItemImage *closeItem = CCMenuItemImage::create("SpriteImages/backbutton.png","SpriteImages/backbutton.png",
		this,menu_selector(LevelGeneratorHub::backCallback));
	closeItem->setPosition(ccp(size.width-120,size.height-15));

	CCMenu *closeMenu = CCMenu::create(closeItem,NULL);
	addChild(closeMenu,20,1);
	closeMenu->setPosition(CCPointZero);

	CCMenuItemImage *pauseItem = CCMenuItemImage::create("pause button.png","pause button.png",
		this,menu_selector(LevelGeneratorHub::pauseCallback));
	pauseItem->setPosition(ccp(780,50));

	CCMenu *pauseMenu = CCMenu::create(pauseItem,NULL);
	pauseMenu->setPosition(CCPointZero);
	addChild(pauseMenu,20,1);

	CCMenuItemImage *playItem = CCMenuItemImage::create("play button.png","play button.png", 
		this,menu_selector(LevelGeneratorHub::playCallback));
	playItem->setPosition(ccp(780,50));
	
	CCMenu *playMenu = CCMenu::create(playItem,NULL);
	playMenu->setPosition(CCPointZero);
	addChild(playMenu,20,1);

	pauseMenu->setVisible(true);
	playMenu->setVisible(false);

	setKeypadEnabled(true);

	return true;
}

void LevelGeneratorHub::backCallback(CCObject *sender)
{
#ifdef DEBUG
	PRINTF_LOG  
#endif
}

void LevelGeneratorHub::pauseCallback(CCObject *sender)
{
#ifdef DEBUG
	PRINTF_LOG  
#endif
}

void LevelGeneratorHub::playCallback(CCObject *sender)
{
#ifdef DEBUG
	PRINTF_LOG  
#endif
}