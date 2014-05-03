#include "SettingLayer.h"
#include "MenuLayer.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

CCScene *SettingLayer::settingScene = NULL;

SettingLayer::SettingLayer()
{
}

SettingLayer::~SettingLayer()
{
}

bool SettingLayer::init()
{
	if(!CCLayer::init())
	{
		return false;
	}

	CCSprite *sp = CCSprite::create("settingbackground.png");

	sp->setAnchorPoint(ccp(0,0));
	addChild(sp);

	CCMenuItemToggle *backgroundMusic = CCMenuItemToggle::createWithTarget(this,
			menu_selector(SettingLayer::menuCallbackToggle),
			CCMenuItemFont::create("Music Off"),
			CCMenuItemFont::create("Music On"),
			NULL);

	CCMenuItemToggle *effectMusic =  CCMenuItemToggle::createWithTarget(this,
			menu_selector(SettingLayer::menuCallbackEffectToggle),
			CCMenuItemFont::create("Effect Off"),
			CCMenuItemFont::create("Effect On"),
			NULL);

//	CCMenuItemFont *back = CCMenuItemFont::create("Back",this,menu_selector(SettingLayer::menuCallbackBack));

	CCMenu *menu = CCMenu::create();

	menu->addChild(backgroundMusic);
	menu->addChild(effectMusic);
//	menu->addChild(back);

	menu->alignItemsVertically();

	addChild(menu);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	setKeypadEnabled(true);
#endif


	return true;
}

CCScene *SettingLayer::createScene()
{
	if(settingScene == NULL)
	{
		settingScene = CCScene::create();

		SettingLayer *settingLayer = SettingLayer::create();

		settingScene->addChild(settingLayer);
	}

	return settingScene;

}

void SettingLayer::menuCallbackToggle(CCObject *sender)
{
	bool flag = CCUserDefault::sharedUserDefault()->getBoolForKey("music_trigger");
	if(!flag)
	{
		CCUserDefault::sharedUserDefault()->setBoolForKey("music_trigger", true);
		CCLog("******************1\n");

		if(SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying())
		{
			SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
		}

	}
	else
	{
		CCUserDefault::sharedUserDefault()->setBoolForKey("music_trigger", false);
		CCLog("*****************2\n");

		SimpleAudioEngine::sharedEngine()->playBackgroundMusic("latin_industries.wav",true);
	}

}

void SettingLayer::menuCallbackEffectToggle(CCObject *sender)
{
	bool flag = CCUserDefault::sharedUserDefault()->getBoolForKey("effect");
	if(!flag)
	{
		CCUserDefault::sharedUserDefault()->setBoolForKey("effect", true);
	}
	else
	{   
		CCUserDefault::sharedUserDefault()->setBoolForKey("effect", false);
	}   
}

void SettingLayer::menuCallbackBack(CCObject *sender)
{
	CCDirector::sharedDirector()->pushScene(CCTransitionFade::create(0.5f,MenuLayer::createScene()));
}

void SettingLayer::keyBackClicked()
{
	CCDirector::sharedDirector()->pushScene(CCTransitionFade::create(0.5f,MenuLayer::createScene()));
}
