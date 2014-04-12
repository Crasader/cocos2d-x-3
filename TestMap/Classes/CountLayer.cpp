#include "CountLayer.h"
#include "MenuLayer.h"

bool CountLayer::init()
{
	if(!CCLayer::init())
		return false;

	count = 0;
	
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		this,
		menu_selector(CountLayer::closeCallback));

	pCloseItem->setPosition(ccp(size.width-25,size.height-25));

	// create menu, it's an autorelease object
	CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu, 1);

	label = CCLabelTTF::create("0", "Verdana-Bold", 20.0, CCSizeMake(50,25), kCCTextAlignmentRight);
	label->setColor(ccc3(0,0,0));
	label->setPosition(ccp(size.width-75,size.height-25));
	addChild(label);

	timeLabel = CCLabelTTF::create("00:00", "Verdana-Bold", 20.0, CCSizeMake(50,25), kCCTextAlignmentRight);
	timeLabel->setColor(ccc3(0,0,0));
	timeLabel->setPosition(ccp(size.width-100,size.height-25));
	addChild(timeLabel);

	schedule(schedule_selector(CountLayer::updateTime),1.0f);

	return true;
}

void CountLayer::countChange(int count)
{
	char buf[10];
	sprintf(buf,"%d",count);
	label->setString(buf);
	watermelonCount = count;
}

void CountLayer::closeCallback(CCObject *psender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
	CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
#endif
}

void CountLayer::updateTime(float dt)
{
	if(count >=3600)
		count = 0;
	count++;

	if(count>=180 && watermelonCount <=10)
	{
		unschedule(schedule_selector(CountLayer::updateTime));
		CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5f,MenuLayer::createScene()));
	}


	char buf[64];
	sprintf(buf,"%02d:%02d",count/60,count%60);

	timeLabel->setString(buf);

}