#include "HubLayer.h"
#include "GameScene.h"
#include "config.h"
#include "MenuLayer.h"

HubLayer::HubLayer()
{

}

HubLayer::~HubLayer()
{

}

bool HubLayer::init()
{
	if(!CCLayer::init())
	{
		return false;
	}

	simpleDpad = SimpleDpad::dpadWithFile(CCString::create("pd_dpad.png"),64);
	simpleDpad->setPosition(ccp(64,64));
	simpleDpad->setOpacity(100);

	this->addChild(simpleDpad);

//	CCSprite *back = CCSprite::create("back.png");

/*	CCSize size = CCDirector::sharedDirector()->getWinSize();

	CCMenuItemImage *back = CCMenuItemImage::create("back.png","back.png",this,menu_selector(HubLayer::menuCallbackBack));

	CCMenu *menu = CCMenu::create(back,NULL);
	menu->setPosition(ccp(size.width-20,50));

	addChild(menu);
*/

	this->scheduleUpdate();

	return true;
}

void HubLayer::update(float delta)
{
	if((GameScene *) this->getParent() == NULL)
	{
		return ;
	}
	else
	{
		this->unscheduleUpdate();

		this->simpleDpad->delegate = ((GameScene *)this->getParent())->gameLayer;
	}
}

/*
void HubLayer::menuCallbackBack(CCObject *sender)
{
#ifdef DEBUG
	CCLog("******************************back\n");
#endif

	CCDirector::sharedDirector()->pushScene(CCTransitionFade::create(0.5f, MenuLayer::createScene()));
}
*/
