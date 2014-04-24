#include "gamelayer.h"

GameLayer::GameLayer()
{
	mWarrior = NULL;
	bulletManager = NULL;
}

GameLayer::~GameLayer()
{
}

bool GameLayer::init()
{
	bool sRect = false;

	do
	{
		CC_BREAK_IF(!BaserLayer::init());

		setViews();

		sRect = true;

	}while(0);

	return sRect;
}

CCScene *GameLayer::scene()
{
	CCScene *scene = NULL;

	do
	{

		scene = CCScene::create();
		CC_BREAK_IF(!scene);

		GameLayer  *layer = GameLayer::create();

		CC_BREAK_IF(!layer);

		scene->addChild(layer);

	}while(0);

	return scene;

}

void GameLayer::setViews()
{
	do
	{
		CCSprite *bg1 = CCSprite::create("bg01.jpg");
		CCSprite *bg2 = CCSprite::create("bg01.jpg");

		bg1->setAnchorPoint(CCPointZero);
		bg2->setAnchorPoint(CCPointZero);

		bg1->setPosition(CCPointZero);
		bg2->setPosition(ccp(0,576));

		this->addChild(bg1,0,11);
		this->addChild(bg2,0,12);

		//调用滚动背景
		this->schedule(schedule_selector(GameLayer::background_scroll),0.1f);

		//加入分数
		ScoreLayer *scoreLayer = ScoreLayer::create();
		scoreLayer->setAnchorPoint(ccp(0,1));
		scoreLayer->setPosition(ccp(10,getWinSize().height-40));

		this->addChild(scoreLayer);

		//加入时间
		TimeLayer *timeLayer = TimeLayer::create();
		timeLayer->setAnchorPoint(ccp(0,1));
		timeLayer->setPosition(ccp(getWinSize().width-120,getWinSize().height-40));

		this->addChild(timeLayer);

		//创建暂停/恢复按钮
		CCMenuItemImage *menuImage = CCMenuItemImage::create("pause.png","pause.png",this,menu_selector(GameLayer::pause_game));
		 menuImage->setPosition(ccp(getWinSize().width -menuImage->getContentSize().width-160 ,
					 menuImage->getContentSize().height-230));
//		menuImage->setPosition(ccp(0,0));
		menuImage->setAnchorPoint(ccp(0,1));

		CCMenu *menu = CCMenu::create(menuImage,NULL);
		
		this->addChild(menu,1,156);

		//加入pauselayer
		PauseLayer *pauseLayer = PauseLayer::create();
		pauseLayer->setPosition(CCPointZero);
		pauseLayer->setVisible(false);
		this->addChild(pauseLayer,10,10);

		mWarrior = WarriorLayer::create();
		this->addChild(mWarrior,1);

		/*
		 *加入子弹管理类
		 */
		bulletManager = BulletLayer::create();
		this->addChild(bulletManager,1);

		this->schedule(schedule_selector(GameLayer::warrior_add_new_bullet),0.2f);

	}while(0);

}

void GameLayer::background_scroll(float t)
{
	CCSprite *bg1 =(CCSprite *) getChildByTag(11);
	CCSprite *bg2 =(CCSprite *) getChildByTag(12);

	bg1->setPositionY(bg1->getPositionY() -10);
	bg2->setPositionY(bg1->getPositionY()+576);

	if(bg2->getPositionY() <=0)
	{
		bg1->setPositionY(0);
	}
}

void GameLayer::pause_game(CCObject *obj)
{
	getChildByTag(10)->setVisible(true);

	CCDirector::sharedDirector()->pause();

	CCMenu *menu = (CCMenu *)getChildByTag(156);

	menu->setEnabled(true);

	if(SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying())
	{
		SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();	
	}

}

void GameLayer::warrior_add_new_bullet(float t)
{
	bulletManager->addBullet(mWarrior->getWarriorPostion(),mWarrior->getFlySize());
}

ScoreLayer::ScoreLayer()
{
}

ScoreLayer::~ScoreLayer()
{
}

bool ScoreLayer::init()
{
	bool sRect = false;

	do
	{
		CC_BREAK_IF(!BaserLayer::init());

		setViews();

		sRect = true;

	}while(0);

	return sRect;
}

void ScoreLayer::setViews()
{
	do
	{
		CCLabelBMFont *scoreFont = CCLabelBMFont::create("Score : 20","arial-14.fnt");
		scoreFont->setAnchorPoint(CCPointZero);
		scoreFont->setPosition(CCPointZero);
		scoreFont->setScale(1.5f);
		this->addChild(scoreFont);
		
	}while(0);

}

TimeLayer::TimeLayer()
{
	count = 0;
}

TimeLayer::~TimeLayer()
{
}

bool TimeLayer::init()
{
	bool sRect = false;

	do
	{
		CC_BREAK_IF(!BaserLayer::init());

		setViews();

		sRect = true;

	}while(0);

	return sRect;
}

void TimeLayer::setViews()
{
	do
	{
		CCLabelBMFont *timeFont = CCLabelBMFont::create("Time : 0 ","arial-14.fnt");
		timeFont->setAnchorPoint(CCPointZero);
		timeFont->setPosition(CCPointZero);
		timeFont->setScale(1.5f);
		this->addChild(timeFont,0,15);
		
		this->schedule(schedule_selector(TimeLayer::time_count),1.0f);

	}while(0);

}

void TimeLayer::time_count(float t)
{
	CCLabelBMFont *timeFont =(CCLabelBMFont *) getChildByTag(15);
	
	char buf[32];
	sprintf(buf,"Time : %d",count);

	timeFont->setString(buf);

	count +=1;
}

PauseLayer::PauseLayer()
{
}

PauseLayer::~PauseLayer()
{
}

bool PauseLayer::init()
{
	bool sRect = false;

	do
	{
		CC_BREAK_IF(!CCLayerColor::initWithColor(ccc4(0,0,0,50)));

		setViews();

		sRect = true;

	}while(0);

	return sRect;
}

void PauseLayer::setViews()
{
	do
	{
		/*
		CCLabelBMFont *timeFont = CCLabelBMFont::create("Time : 0 ","arial-14.fnt");
		timeFont->setAnchorPoint(CCPointZero);
		timeFont->setPosition(CCPointZero);
		timeFont->setScale(1.5f);
		this->addChild(timeFont,0,15);
		
		this->schedule(schedule_selector(TimeLayer::time_count),1.0f);*/

		CCSize size = CCDirector::sharedDirector()->getWinSize();
		CCMenuItemImage *menuImage = CCMenuItemImage::create("play.png","pause.png",this,menu_selector(PauseLayer::play_stats));
		menuImage->setPosition(ccp(size.width/2,size.height/2));

		CCMenu *menu = CCMenu::create(menuImage,NULL);
		menu->setPosition(CCPointZero);
		this->addChild(menu);


	}while(0);

}

void PauseLayer::play_stats(CCObject *obj)
{
	 //this->removeFromParentAndCleanup( true );

	/*getChildByTag(10)->setVisible(true);

	CCMenu *menu = (CCMenu *)getChildByTag(156);

	menu->setEnabled(false);
	CCDirector::sharedDirector()->resume();*/

	CCLayer *parentLayer = (GameLayer *)getParent();


	PauseLayer *pauseLayer = (PauseLayer *) parentLayer->getChildByTag(10);
	pauseLayer->setVisible(false);

	CCMenu *menu = (CCMenu *)parentLayer->getChildByTag(156);
	menu->setEnabled(true);

	CCDirector::sharedDirector()->resume();
	SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();

}
