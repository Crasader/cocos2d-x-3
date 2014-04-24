#include "MenuLayer.h"
#include "HelloWorldScene.h"

bool MenuLayer::init()
{
	if(!CCLayer::init())
		return false;

	CCLabelTTF *tipLabel = CCLabelTTF::create("You Lost", "Verdana-Bold", 28.0, CCSizeMake(200,25),  kCCTextAlignmentCenter);
	CCMenuItemLabel *tipItem = CCMenuItemLabel::create(tipLabel,this,NULL);

	CCLabelTTF *label = CCLabelTTF::create("ReSet", "Verdana-Bold", 28.0, CCSizeMake(200,25),  kCCTextAlignmentCenter);
	CCMenuItemLabel *resetItem = CCMenuItemLabel::create(label,this,menu_selector(MenuLayer::resetCallback));

	CCLabelTTF *quitLabel = CCLabelTTF::create("Quit", "Verdana-Bold", 28.0, CCSizeMake(200,25),  kCCTextAlignmentCenter);
	CCMenuItemLabel *quitItem = CCMenuItemLabel::create(quitLabel,this,menu_selector(MenuLayer::quitCallback));

	CCMenu *menu = CCMenu::create(tipItem,resetItem,quitItem,NULL);
	addChild(menu);
	menu->alignItemsVertically();
	menu->alignItemsVerticallyWithPadding(20);

	CCSize size = CCDirector::sharedDirector()->getWinSize();
	menu->setPosition(ccp(size.width/2,size.height/2));

	return true;
}

CCScene *MenuLayer::createScene()
{
	CCScene *scene = NULL;

	scene = CCScene::create();
	if(scene !=NULL)
	{
		MenuLayer *menuLayer = MenuLayer::create();
		scene->addChild(menuLayer);
		return scene;
	}
	else
	{
		return NULL;
	}
}

void MenuLayer::resetCallback(CCObject *sender)
{
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5f,HelloWorld::scene()));
}

void MenuLayer::quitCallback(CCObject *sender)
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