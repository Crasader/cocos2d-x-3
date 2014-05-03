#include "MenuLayer.h"
#include "config.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "SettingLayer.h"

using namespace CocosDenshion;

MenuLayer::MenuLayer()
{
	bool flag  = CCUserDefault::sharedUserDefault()->getBoolForKey("music_trigger");
	if(!flag)
	{
		SimpleAudioEngine::sharedEngine()->playBackgroundMusic("latin_industries.wav",true);
	}
}

MenuLayer::~MenuLayer()
{
}

bool MenuLayer::init()
{

	if(!CCLayer::init())
	{
		return false;
	}

	setBackgroundImage("background.png");

	CCMenuItemFont *playItem = CCMenuItemFont::create("Play",this,menu_selector(MenuLayer::menuCallbackPlay));

/*	CCActionInterval* color_action = CCTintBy::create(0.5f, 0, -255, -255);
	CCActionInterval* color_back = color_action->reverse();
	CCSequence* seq = CCSequence::create(color_action, color_back, NULL);
	playItem->runAction(CCRepeatForever::create(seq));*/

	CCMenuItemFont *settingItem = CCMenuItemFont::create("Setting",this,menu_selector(MenuLayer::menuCallbackSetting));
	CCMenuItemFont *quitItem = CCMenuItemFont::create("Quit",this,menu_selector(MenuLayer::menuCallbackQuit));

	CCMenu *menu = CCMenu::create(playItem,settingItem,quitItem,NULL);

	addChild(menu);
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	menu->setPosition(ccp(size.width/2,size.height/2));
	menu->alignItemsVertically();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	//  CCLayer::setIsKeypadEnabled(true);
	setKeypadEnabled(true);	
#endif
	


	return true;
}

CCScene* MenuLayer::menuScene = NULL;

CCScene *MenuLayer::createScene()
{

	if(menuScene == NULL)
	{
		menuScene = CCScene::create();
		MenuLayer *menuLayer = MenuLayer::create();
		menuScene->addChild(menuLayer);
	}

	return menuScene;

}

void MenuLayer::setBackgroundImage(const char *image)
{
#ifdef DEBUG
	CCLog("*************%s\n",image);
#endif
	
	CCSprite *back = CCSprite::create(image);
//	CCSize size = CCDirector::sharedDirector()->getWinSize();
	back->setAnchorPoint(ccp(0,0));
//	back->setPosition(ccp(size.width/2,size.height/2));
	
	addChild(back);
}

void MenuLayer::menuCallbackPlay(CCObject *sender)
{
#ifdef DEBUG
	CCLog("********************Play");
#endif

	CCDirector::sharedDirector()->pushScene(CCTransitionFade::create(0.5f, GameScene::create()));

}

void MenuLayer::menuCallbackSetting(CCObject *sender)
{
	CCDirector::sharedDirector()->pushScene(CCTransitionFade::create(0.5f,SettingLayer::createScene()));
}

void MenuLayer::menuCallbackQuit(CCObject *sender)
{
	exit(0);
}


void MenuLayer::keyBackClicked()
{
	exit(0);
}
