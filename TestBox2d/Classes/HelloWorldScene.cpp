#include "HelloWorldScene.h"

USING_NS_CC;

HelloWorld::~HelloWorld()
{
	delete world;
	body = NULL;
	world = NULL;
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

	ball = CCSprite::create("Ball.png");
	addChild(ball);
	
	setAccelerometerEnabled(true);

	CCSize size = CCDirector::sharedDirector()->getWinSize();

	ball->setPosition(ccp(size.width/2,size.height/2));

	b2Vec2 gravity = b2Vec2(0.0f,-30.0f);

	world = new b2World(gravity);

	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0,0);
	b2Body *groundBody = world->CreateBody(&groundBodyDef);
	b2EdgeShape groundEdge;
	b2FixtureDef boxShapeDef;
	boxShapeDef.shape = &groundEdge;
	groundEdge.Set(b2Vec2(0,0), b2Vec2(size.width/PTM_RATIO, 0));
	groundBody->CreateFixture(&boxShapeDef);
	groundEdge.Set(b2Vec2(0,0), b2Vec2(0, size.height/PTM_RATIO));
	groundBody->CreateFixture(&boxShapeDef);
	groundEdge.Set(b2Vec2(0, size.height/PTM_RATIO), 
		b2Vec2(size.width/PTM_RATIO, size.height/PTM_RATIO));
	groundBody->CreateFixture(&boxShapeDef);
	groundEdge.Set(b2Vec2(size.width/PTM_RATIO, 
		size.height/PTM_RATIO), b2Vec2(size.width/PTM_RATIO, 0));
	groundBody->CreateFixture(&boxShapeDef);

	b2BodyDef ballBodyDef;
	ballBodyDef.type = b2_dynamicBody;
	ballBodyDef.position.Set(100/PTM_RATIO, 100/PTM_RATIO);
	ballBodyDef.userData = ball;
	body = world->CreateBody(&ballBodyDef);

	b2CircleShape circle;
	circle.m_radius = 26.0/PTM_RATIO;

	b2FixtureDef ballShapeDef;
	ballShapeDef.shape = &circle;
	ballShapeDef.density = 1.0f;  //设置物体的密度
	ballShapeDef.friction = 0.2f; //设置物体的摩擦系数
	ballShapeDef.restitution = 0.8f;
	body->CreateFixture(&ballShapeDef);


	schedule(schedule_selector(HelloWorld::tick),0.1f);

 
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

void HelloWorld::tick(float dt)
{
	world->Step(dt, 10, 10);
	for(b2Body *b = world->GetBodyList(); b; b=b->GetNext()) {    
		if (b->GetUserData() != NULL) {
			CCSprite *ballData = (CCSprite *)b->GetUserData();
		/*	ballData.position = ccp(b->GetPosition().x * PTM_RATIO,
				b->GetPosition().y * PTM_RATIO);
			ballData.rotation = -1 * CC_RADIANS_TO_DEGREES(b->GetAngle());*/

			ballData->setPosition(ccp(b->GetPosition().x * PTM_RATIO,b->GetPosition().y * PTM_RATIO));
			ballData->setRotation(-1 * CC_RADIANS_TO_DEGREES(b->GetAngle()));
		}        
	}
}