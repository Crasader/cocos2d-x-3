#include "HelloWorldScene.h"
#include "Box2D/Box2D.h"

USING_NS_CC;


#define DEBUG

class BodyDef {
public:
    BodyDef() {}
//			: fixtures(NULL) {}

    ~BodyDef() {

    }

//		FixtureDef *fixtures;
    CCPoint anchorPoint;
};


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

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label

    CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Arial", 24);

    // position the label on the center of the screen
    pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - pLabel->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(pLabel, 1);

    // add "HelloWorld" splash screen"
    CCSprite* pSprite = CCSprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);


    //testDictionary();
    testDictionary();

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


void HelloWorld::testDictionary(int a)
{
    CCLog("******************************\n");
    const char * testPath = "/opt/cocos/cocos2d-x-2.2.1/projects/TestDict/Resources/testarray.plist" ;
    const char * fullPath = CCFileUtils::sharedFileUtils()->fullPathFromRelativeFile("testarray.plist",testPath);

    CCDictionary *plistDic = CCDictionary::createWithContentsOfFile(fullPath);

    CCDictionary *levelDic = dynamic_cast<CCDictionary *>(plistDic->objectForKey("level1"));
    if(levelDic != NULL)
    {
        CCLog("*****************success\n");
    }

    CCArray *array = static_cast<CCArray *>(levelDic->objectForKey("bg_far_scene"));

    if(array !=NULL)
    {
        CCLog("Get Array Success\n");
        CCObject *obj;
        CCARRAY_FOREACH(array,obj)
        {
            CCDictionary *topDict = static_cast<CCDictionary *>(obj);
            if(topDict != NULL)
            {
                int density = static_cast<CCString *>(topDict->objectForKey("density"))->intValue();
                CCLog("density=%d\n",density);

                CCArray *arrayList = static_cast<CCArray *>(topDict->objectForKey("polygons"));
                CCObject *obj;
                CCARRAY_FOREACH(arrayList,obj)
                {
                    CCArray *tmpArray = static_cast<CCArray *>(obj);
                    if(tmpArray!=NULL)
                    {
                        CCObject *obj = NULL;
                        CCARRAY_FOREACH(tmpArray,obj)
                        {
                            CCLog("%s\n",static_cast<CCString *>(obj)->getCString());
                        }
                    }
                }

            }
        }

    }
}

void HelloWorld::testDictionary()
{
    const char * testPath = "/opt/cocos/cocos2d-x-2.2.1/projects/TestDict/Resources/BodyPlist.plist" ;
    const char * fullPath = CCFileUtils::sharedFileUtils()->fullPathFromRelativeFile("BodyPlist.plist",testPath);

    CCDictionary *plistDic = CCDictionary::createWithContentsOfFile(fullPath);

    CCDictionary *metaDic = dynamic_cast<CCDictionary *>(plistDic->objectForKey("metadata"));
    int format = dynamic_cast<CCString *>(metaDic->objectForKey("format"))->intValue();
    float ptmRatio = dynamic_cast<CCString *>(metaDic->objectForKey("ptm_ratio"))->floatValue();
#ifdef DEBUG
    CCLog("%d\t%2.2f\n",format,ptmRatio);
#endif

    CCDictionary *bodyDic = dynamic_cast<CCDictionary *>(plistDic->objectForKey("bodies"));

    CCDictElement *element;
    CCDICT_FOREACH(bodyDic,element)
    {
        CCDictionary *test = dynamic_cast<CCDictionary *>(bodyDic->objectForKey("Head"));
        CCPoint point = CCPointFromString(test->valueForKey("anchorpoint")->getCString());

#ifdef DEBUG
        CCLog("%2.2f\t%2.2f\n",point.x,point.y);
#endif

        CCArray * fixturesList = static_cast<CCArray *>(test->objectForKey("fixtures"));

        if(fixturesList !=NULL)
        {
            CCObject *obj;
            CCARRAY_FOREACH(fixturesList,obj)
            {
                if(obj !=NULL)
                {
                    CCLog("success\n");
                    CCDictionary *itemDict = static_cast<CCDictionary *>(obj);

                    if(itemDict!=NULL)
                    {
                        int filter_categoryBits = dynamic_cast<CCString *>(itemDict->objectForKey("filter_categoryBits"))->intValue();
                        int filter_maskBits = dynamic_cast<CCString *>(itemDict->objectForKey("filter_maskBits"))->intValue();
                        int filter_groupIndex = dynamic_cast<CCString *>(itemDict->objectForKey("filter_groupIndex"))->intValue();
                        float friction = dynamic_cast<CCString *>(itemDict->objectForKey("friction"))->floatValue();
                        float density =dynamic_cast<CCString *>(itemDict->objectForKey("density"))->floatValue();
                        float restitution =dynamic_cast<CCString *>(itemDict->objectForKey("restitution"))->floatValue();
                        int isSensor = dynamic_cast<CCString *>(itemDict->objectForKey("isSensor"))->intValue();

                        const char *fixture_type = dynamic_cast<CCString *>(itemDict->objectForKey("fixture_type"))->getCString();

#ifdef DEBUG
                        CCLog("%d\t%d\t%d\t%2.2f\t%2.2f\t%2.2f\t%d\n",filter_categoryBits,filter_maskBits,filter_groupIndex,
                              friction,density,restitution,isSensor);
#endif

                        if(strcmp(fixture_type,"POLYGON") == 0)
                        {
#ifdef DEBUG
                            CCLog("fixture_type = %s\n",fixture_type);
#endif

#if 1
                            CCArray * arrayList = static_cast<CCArray *>(itemDict->objectForKey("polygons"));

                            if(arrayList!=NULL)
                            {
#ifdef DEBUG
                                CCLog("get arrayList success\n");
#endif
#if 1
                                CCObject *obj = NULL;
                                CCARRAY_FOREACH(arrayList,obj)
                                {
                                    CCArray *array = static_cast<CCArray *>(obj);

                                    if(array !=NULL)
                                    {
                                        CCObject *tmp;
                                        CCARRAY_FOREACH(array,tmp)
                                        {

                                            CCPoint point  = CCPointFromString(static_cast<CCString *>(tmp)->getCString());
                                            CCLog("%2.2f\t%2.2f\n",point.x,point.y);
                                        }
                                    }
                                }
#endif
                            }
#endif

                        }
                        else if(strcmp(fixture_type,"CIRCLE") == 0)
                        {
#ifdef DEBUG
                            CCLog("fixture_type = %s\n",fixture_type);
#endif
                        }
                        else
                        {
                            CCLog("error\n");
                        }

                        CCArray *polygonsList = static_cast<CCArray *>(itemDict->objectForKey("polygons"));

                        if(polygonsList!=NULL)
                        {
                            CCLog("success\n");
                        }

                    }
                    else
                    {
                        CCLog("error\n");
                    }

                }
                else
                {
                    CCLog("error\n");
                }
            }


        }
        else
        {
            CCLog("error\n");
        }
    }

}

