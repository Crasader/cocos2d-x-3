#include "MenuLayer.h"
#include "../config.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

MenuLayer::MenuLayer()
{
}

MenuLayer::~MenuLayer()
{
}

bool MenuLayer::init()
{
	if(!CCLayer::init())
		return false;
	
	CCSize size = CCDirector::sharedDirector()->getWinSize();

	CCSprite *backImg = CCSprite::create("SpriteImages/bgemptyb.png");
	backImg->setAnchorPoint(ccp(0.5,0.5));
	backImg->setPosition(ccp(size.width/2,size.height/2));
	addChild(backImg);

	CCSprite *gameNode  =CCSprite::create("SpriteImages/Gamemode.png");
	gameNode->setAnchorPoint(ccp(0.5,0.5));
	gameNode->setPosition(ccp(size.width/2,size.height-50));
	addChild(gameNode);

	CCMenuItemImage *level1 = CCMenuItemImage::create("SpriteImages/TimeMode.png","SpriteImages/TimeMode2.png",
			this,menu_selector(MenuLayer::level1Callback));
	CCMenuItemImage *level2 = CCMenuItemImage::create("SpriteImages/EndlessMode.png","SpriteImages/EndlessMode2.png",
			this,menu_selector(MenuLayer::level2Callback));

	CCMenuItemImage *level3 = CCMenuItemImage::create("SpriteImages/SurvivalMode.png","SpriteImages/SurvivalMode2.png",
			this,menu_selector(MenuLayer::level3Callback));

	CCMenu *menu = CCMenu::create(level1,level2,level3,NULL);
	menu->alignItemsHorizontally();
	menu->alignItemsHorizontallyWithPadding(35);

	addChild(menu);



	return true;
}

CCScene *MenuLayer::createScene()
{
	CCScene *scene = NULL;

	scene = CCScene::create();

	MenuLayer *menuLayer = MenuLayer::create();
	scene->addChild(menuLayer);

	return scene;

}

void MenuLayer::level1Callback(CCObject *sender)
{
#ifdef DEBUG
//	PRINTF_LOG;
#endif
	SimpleAudioEngine::sharedEngine()->playEffect("Sound/buttonclick.mp3");

}

void MenuLayer::level2Callback(CCObject *sender)
{
	SimpleAudioEngine::sharedEngine()->playEffect("Sound/buttonclick.mp3");
}

void MenuLayer::level3Callback(CCObject *sender)
{
	SimpleAudioEngine::sharedEngine()->playEffect("Sound/buttonclick.mp3");
}
