#include "HelloWorldScene.h"

HelloWorld::~HelloWorld()
{
	alert->release();
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

	uiLayer = UILayer::create();
	addChild(uiLayer);

	widget = static_cast<Layout*>(GUIReader::shareReader()->widgetFromJsonFile("UITest.json"));
	uiLayer->addWidget(widget);

	uiLayer->setPosition(ccp(150,100));

	CCSize widgetSize = widget->getSize();


	//自己添加控件
	alert = UILabel::create();
	alert->setText("Layout");
	alert->setFontName("Marker Felt");
	alert->setFontSize(30);
	alert->setColor(ccc3(159, 168, 176));
	alert->setAnchorPoint(ccp(0.5,0.5));
	alert->setPosition(ccp(widgetSize.width/2,widgetSize.height/2));
	alert->retain();	
	uiLayer->addWidget(alert);


	UIButton *button = UIButton::create();
	button->setTouchEnabled(true);
	button->loadTextures("button.png", "button1.png", "");
	button->setPosition(ccp(40, widgetSize.height-40));

	uiLayer->addWidget(button);

	//从布局文件获取按钮
	Label *back = static_cast<Label*>(UIHelper::seekWidgetByName(widget, "back"));
	if(back != NULL)
	{
		back->addTouchEventListener(this,toucheventselector(HelloWorld::backCallback));
	}

	Button *left = static_cast<Button*>(UIHelper::seekWidgetByName(widget,"left_Button"));
	if(left!=NULL)
	{
		left->addTouchEventListener(this,toucheventselector(HelloWorld::leftCallback));
	}

	Button *middle = static_cast<Button*>(UIHelper::seekWidgetByName(widget,"middle_Button"));
	if(middle!=NULL)
	{
		middle->addTouchEventListener(this,toucheventselector(HelloWorld::middleCallback));
	}

	Button *right = static_cast<Button *>(UIHelper::seekWidgetByName(widget,"right_Button"));
	if(right!=NULL)
	{
		right->addTouchEventListener(this,toucheventselector(HelloWorld::rightCallback));
	}

    return true;
}


void HelloWorld::menuCloseCallback(CCObject* pSender)
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

void HelloWorld::backCallback(CCObject *obj,TouchEventType type)
{
	switch(type)
	{
		case TOUCH_EVENT_ENDED:
		{
			CCLog("back\n");
			alert->setText("Back");
		}
		break;
		default:
		break;
	}
}

void HelloWorld::leftCallback(CCObject *obj,TouchEventType type)
{
	switch(type)
	{
		case TOUCH_EVENT_ENDED:
		{
			CCLog("left\n");
			alert->setText("Left");
		}
		break;
		default:
		break;
	}
}

void HelloWorld::middleCallback(CCObject *obj,TouchEventType type)
{
	switch(type)
	{
		case TOUCH_EVENT_ENDED:
		{
			CCLog("middle\n");
			alert->setText("Middle");
		}
		break;
		default:
		break;
	}
}

void HelloWorld::rightCallback(CCObject *obj,TouchEventType type)
{
	switch(type)
	{
		case TOUCH_EVENT_ENDED:
		{
			CCLog("right\n");
			alert->setText("Right");
		}
		break;
		default:
		break;
	}
}
