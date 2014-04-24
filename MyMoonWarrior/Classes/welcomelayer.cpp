#include "welcomelayer.h"
#include "aboutlayer.h"
#include "optionlayer.h"

WelcomeLayer::WelcomeLayer()
{
}

WelcomeLayer::~WelcomeLayer()
{
}

/**
 *初始化方法
 */
bool WelcomeLayer::init()
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

/**
 *初始化控件
 */
void WelcomeLayer::setViews()
{
	/**
	 *设置背景
	 */
	setBackGroundImage("loading.png");

	CCSprite *logo = CCSprite::create("logo.png");
	logo->setAnchorPoint(ccp(0.5,1.0));
	logo->setPosition(ccp(getWinSize().width/2,getWinSize().height-20));
	this->addChild(logo);


	/**
	 *创建menu
	 */
	CCSprite *startGameNormal = CCSprite::create("menu.png",CCRectMake(0,0,126,33));
	CCSprite *startGamePress = CCSprite::create("menu.png",CCRectMake(0,33,126,33));
	CCSprite *startGameDisable = CCSprite::create("menu.png",CCRectMake(0,66,126,33));

	CCMenuItemSprite *startGmae = CCMenuItemSprite::create(startGameNormal,startGamePress,startGameDisable,this,
			menu_selector(WelcomeLayer::startGameCallback));

	CCSprite *aboutGameNormal = CCSprite::create("menu.png",CCRectMake(252,0,126,33));
	CCSprite *aboutGamePress = CCSprite::create("menu.png",CCRectMake(252,33,126,33));
	CCSprite *aboutGameDisable = CCSprite::create("menu.png",CCRectMake(252,66,126,33));

	CCMenuItemSprite *aboutGmae = CCMenuItemSprite::create(aboutGameNormal,aboutGamePress,aboutGameDisable,this,
			menu_selector(WelcomeLayer::aboutGameCallback));

	CCSprite *optionGameNormal = CCSprite::create("menu.png",CCRectMake(126,0,126,33));
	CCSprite *optionGamePress = CCSprite::create("menu.png",CCRectMake(126,33,126,33));
	CCSprite *optionGameDisable = CCSprite::create("menu.png",CCRectMake(126,66,126,33));

	CCMenuItemSprite *optionGmae = CCMenuItemSprite::create(optionGameNormal,optionGamePress,optionGameDisable,this,
			menu_selector(WelcomeLayer::optionGameCallback));

	CCMenu *menu = CCMenu::create(startGmae,optionGmae,aboutGmae,NULL);
	menu->setPosition(ccp(getWinSize().width/2,getWinSize().height/2));
	menu->alignItemsVerticallyWithPadding(10);

	this->addChild(menu);
}

CCScene * WelcomeLayer::scene()
{
	CCScene *scene = NULL;

	do
	{
		scene = CCScene::create();
		CC_BREAK_IF(!scene);

		WelcomeLayer *layer = WelcomeLayer::create();
		CC_BREAK_IF(!layer);

		scene->addChild(layer);

	}while(0);

	return scene;
}

void WelcomeLayer::startGameCallback(CCObject *sender )
{
	CCLog("stratGame");
}

void WelcomeLayer::aboutGameCallback(CCObject *sender )
{
	CCLog("aboutGame");

	CCDirector::sharedDirector()->pushScene(CCTransitionFade::create(0.5f, AboutLayer::scene() ));
}


void WelcomeLayer::optionGameCallback(CCObject *sender )
{
	CCLog("optionGame");
	CCDirector::sharedDirector()->pushScene(CCTransitionFade::create(0.5f, OptionLayer::scene() ));
}

/**
 *重写onEnter方法，调用父类的onEnter方法
 */
void WelcomeLayer::onEnter()
{
	CCLayer::onEnter();

	CCLog("onEnter");
	/**
	 *加入背景音乐
	 */
	
	bool flag =	CCUserDefault::sharedUserDefault()->getBoolForKey("music_trigger");

	if(!flag)
	{
		if(!SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying())
		{
			SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Music/mainMainMusic.mp3",true);
		}
	}
	else
	{
		SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
	}
}
