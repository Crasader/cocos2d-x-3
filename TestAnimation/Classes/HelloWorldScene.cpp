#include "HelloWorldScene.h"


HelloWorld::~HelloWorld()
{
	armature->release();
}

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	size = CCDirector::sharedDirector()->getWinSize();


    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(HelloWorld::menuCloseCallback));
    
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);

	initControlMenu();

	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("hero/HEROXM~10.png","hero/HEROXM~10.plist","hero/Hero.ExportJson");
	armature = CCArmature::create("Hero");
	armature->retain();
    //armature->getAnimation()->play("attack");

	armature->setScale(1.0);
	armature->setPosition(ccp(visibleSize.width*0.45, 100));

	addChild(armature);

    return true;
}


void HelloWorld::menuCloseCallback(CCObject* pSender)
{
	cocos2d::extension::CCArmatureDataManager::purge();
	cocos2d::extension::ActionManager::shareManager()->purge();
	cocos2d::extension::SceneReader::sharedSceneReader()->purge();
	cocos2d::extension::GUIReader::shareReader()->purge();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}

void HelloWorld::initControlMenu()
{
	CCMenuItemImage *item = CCMenuItemImage::create("button.png","button.png","button.png",this,menu_selector(HelloWorld::buttonCallback));
	CCMenuItemImage *item1 = CCMenuItemImage::create("button1.png","button1.png","button1.png",this,menu_selector(HelloWorld::button1Callback));
	CCMenuItemImage *item2 = CCMenuItemImage::create("button2.png","button2.png","button2.png",this,menu_selector(HelloWorld::button2Callback));
	CCMenuItemImage *item3 = CCMenuItemImage::create("button3.png","button3.png","button3.png",this,menu_selector(HelloWorld::button3Callback));

	CCMenu *menu = CCMenu::create(item,item1,item2,item3,NULL);
	menu->alignItemsHorizontally();
	menu->alignItemsHorizontallyWithPadding(30);
	addChild(menu);

	menu->setPosition(ccp(size.width/2,size.height-100));
}

void HelloWorld::buttonCallback(CCObject *sender)
{
	CCLog("******************");
	armature->getAnimation()->stop();
	armature->getAnimation()->play("run");
}

void HelloWorld::button1Callback(CCObject *sender)
{
	armature->getAnimation()->stop();
	armature->getAnimation()->play("attack");
}

void HelloWorld::button2Callback(CCObject *sender)
{
	armature->getAnimation()->stop();
	armature->getAnimation()->play("smitten");
}

void HelloWorld::button3Callback(CCObject *sender)
{
	armature->getAnimation()->stop();
	armature->getAnimation()->play("death");
}