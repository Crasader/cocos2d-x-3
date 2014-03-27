#include "MainScene.h"
#include "../config.h"
#include "SimpleAudioEngine.h"
#include "MenuLayer.h"


using namespace  CocosDenshion;


MainLayer::MainLayer()
{
}

MainLayer::~MainLayer()
{
}


CCScene *MainLayer::createScene()
{
	CCScene *scene = NULL;

	scene = CCScene::create();

	MainLayer *mainLayer = MainLayer::create();

	scene->addChild(mainLayer);

	return scene;
}

bool MainLayer::init()
{

	if(!CCLayer::init())
		return false;

	CCSize size = CCDirector::sharedDirector()->getWinSize();

	CCSprite *backSprite = CCSprite::create("SpriteImages/bgMainMenu.png");
	backSprite->setAnchorPoint(ccp(0.5,0.5));

	backSprite->setPosition(ccp(size.width/2,size.height/2));
	addChild(backSprite);

	
	CCMenuItemImage *item = CCMenuItemImage::create("SpriteImages/StartGame.png","SpriteImages/StartGame2.png",this,menu_selector(MainLayer::startCallback));

	CCMenu *menu = CCMenu::create(item,NULL);

	addChild(menu);


	return true;
}

void MainLayer::startCallback(CCObject *psender)
{
#ifndef DEBUG
	PRINTF_LOG;
#endif
	//CircusMusic.mp3
	SimpleAudioEngine::sharedEngine()->playEffect("Sound/buttonclick.mp3");

	CCDirector::sharedDirector()->setDepthTest(true);
	CCDirector::sharedDirector()->replaceScene(CCTransitionPageTurn::create(0.5f,MenuLayer::createScene(),false));

}
