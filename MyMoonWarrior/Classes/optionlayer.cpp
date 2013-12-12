#include "optionlayer.h"
#include "welcomelayer.h"

OptionLayer::OptionLayer()
{
}

OptionLayer::~OptionLayer()
{
}

CCScene * OptionLayer::scene()
{
	CCScene *scene = NULL;

	do
	{
		scene = CCScene::create();
		CC_BREAK_IF(!scene);

		OptionLayer *layer = OptionLayer::create();
		CC_BREAK_IF(!layer);
		scene->addChild(layer);

	}while(0);

	return scene;

}

bool OptionLayer::init()
{
	bool sRect = false;

	do
	{
		CC_BREAK_IF(!BaserLayer::init());
		sRect = true;

		setViews();

	}while(0);

	return sRect;
}

void OptionLayer::setViews()
{
	setBackGroundImage("loading.png");	

	CCSprite *title = CCSprite::create("menuTitle.png",CCRectMake(0,0,135,35));
	title->setAnchorPoint(ccp(0.5,1));
	title->setPosition(ccp(getWinSize().width/2,getWinSize().height-20));

	this->addChild(title);

	CCMenuItemToggle *music_trigger = CCMenuItemToggle::createWithTarget(this,menu_selector(OptionLayer::music_triggerCallback),
			CCMenuItemFont::create("Music : On"),CCMenuItemFont::create("Music : Off"),NULL);
	
	music_trigger->setPosition(ccp(getWinSize().width/2,getWinSize().height/2));


	if(SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying())
	{
		music_trigger->setSelectedIndex(1);
	}
	else
	{
		music_trigger->setSelectedIndex(0);
	}

	//menu->setPosition(ccp(getWinSize().width/2,getWinSize().height/2));

	CCLabelBMFont *back = CCLabelBMFont::create("back","arial-14.fnt");

	back->setScale(1.25f);
	CCMenuItemLabel *backLable =  CCMenuItemLabel::create(back,this,menu_selector(OptionLayer::backCallback));
	backLable->setAnchorPoint(ccp(0.5,1));
	backLable->setPosition(ccp(getWinSize().width/2,50));

	CCMenu *menu = CCMenu::create(music_trigger,backLable,NULL);
	menu->setPosition(CCPointZero);

	this->addChild(menu);
}

void OptionLayer::backCallback(CCObject *obj)
{
	CCDirector::sharedDirector()->pushScene(CCTransitionFade::create(0.5f, WelcomeLayer::scene() ));
}

void OptionLayer::music_triggerCallback(CCObject *obj)
{

	if(SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying())
	{
		//		music_trigger->setSelectedIndex(2);
		SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
		CCUserDefault::sharedUserDefault()->setBoolForKey("music_trigger",true);
	}
	else
	{
		SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
		CCUserDefault::sharedUserDefault()->setBoolForKey("music_trigger",false);
	}

}
