#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "CountLayer.h"

USING_NS_CC;
using namespace CocosDenshion;


HelloWorld::HelloWorld()
{
	map = NULL;
	player = NULL;
	count = 0;
}

HelloWorld::~HelloWorld()
{
}


CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

	CountLayer *countLayer = CountLayer::create();


    // add layer as a child to scene
    scene->addChild(layer);
	scene->addChild(countLayer,1,1);
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
   /* CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(HelloWorld::menuCloseCallback));
    
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);*/

	map = CCTMXTiledMap::create("SecondMap.tmx");
	addChild(map);

	/*
	this->setForeground(map->layerNamed("Foreground"));
	foreground->setVisible(false);*/

	foreground = map->layerNamed("Foreground");

	if(foreground == NULL)
	{
		CCLog("************************\n");
	}

	//foreground->setVisible(false);

	mapLayer = map->layerNamed("Meta");
	mapLayer->setVisible(false);



	if(mapLayer == NULL)
	{
		CCLog("******************error\n");
	}

	CCTMXObjectGroup *objects = map->objectGroupNamed("object");
	CCAssert(objects != NULL, "Objects' object group not found");

	CCDictionary *testPoint = objects->objectNamed("player");

	int x = testPoint->valueForKey("x")->intValue();
	int y = testPoint->valueForKey("y")->intValue();

	CCLog("%d\t%d\n",x,y);

	player = CCSprite::create("Player.png");
	addChild(player);
	player->setPosition(ccp(x,y));

	setViewpointCenter(player->getPosition());

	this->setTouchEnabled(true);

//	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("TileMap.wav");
	SimpleAudioEngine::sharedEngine()->preloadEffect("hit.wav");
	SimpleAudioEngine::sharedEngine()->preloadEffect("move.wav");
	SimpleAudioEngine::sharedEngine()->preloadEffect("pickup.wav");

	SimpleAudioEngine::sharedEngine()->playBackgroundMusic("TileMap.wav",true);

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


void HelloWorld::setViewpointCenter(CCPoint point)
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();   
	int x = MAX(point.x, winSize.width / 2);  
	int y = MAX(point.y, winSize.height / 2);  
  
	int mapWidth =map->getMapSize().width *map->getTileSize().width;  

	int mapHeight =map->getMapSize().height *map->getTileSize().height;  

	x = MIN(x, mapWidth- winSize.width / 2);  
	y = MIN(y, mapHeight - winSize.height / 2);  

	CCPoint actualPoint = ccp(x, y);  

	CCPoint viewCenterPoint = ccp(winSize.width / 2,winSize.height / 2);  

	CCPoint viewPoint = ccpSub(viewCenterPoint, actualPoint);  
	this->setPosition(viewPoint); 
}

bool HelloWorld::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	return true;
}

void HelloWorld::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	//convertToNodeSpace函数就是把OpenGL的坐标转换成CCLayer的坐标。  
	CCPoint touchPosition = this->convertTouchToNodeSpace(pTouch);  
	//获取任务在CCLayer上的坐标  
	CCPoint playerPos = player->getPosition();  

	//让触摸点的坐标减去人物的坐标，等于人物要移动的方向以及移动一个位置，我们称之为移动坐标点  
	CCPoint diff = ccpSub(touchPosition, playerPos);  

	//当移动坐标点的x坐标大于y坐标点时，我们只移动x轴，反之则移动y轴  
	if (abs(diff.x) > abs(diff.y))  
	{  
		//当移动坐标点的x大于0时 我们向右移动即让人物的坐标x轴加上一个瓦片地图的宽度。  
		if (diff.x > 0)  
		{  
			//getTileSize().width获取一个瓦片地图的宽度  
			playerPos.x += map->getTileSize().width-2;  
		}  
		else  
		{  
			//当移动坐标点的x小于0时 我们向右移动即让人物的坐标x轴减去一个瓦片地图的宽度。  
			//getTileSize().width获取一个瓦片地图的宽度  
			playerPos.x -= map->getTileSize().width+2;  
		}  
	}  
	else  
	{  
		//当移动坐标点的y大于0时 我们向右移动即让人物的坐标y轴加上一个瓦片地图的高度。  
		if (diff.y > 0)  
		{  
			//getTileSize().height获取一个瓦片地图的高度  
			playerPos.y += map->getTileSize().height;  
		}  
		else  
		{  
			//当移动坐标点的y小于0时 我们向右移动即让人物的坐标x轴减去一个瓦片地图的高度。  
			//getTileSize().height获取一个瓦片地图的高度  
			playerPos.y -= map->getTileSize().height;  
		}  
	}  
	//求出这个瓦片地图的整体宽度 其中，_tileMap->getTileSize().width得到的是瓦片地图每一个瓦片的宽度，  
	//_tileMap->getMapSize().width得到的是瓦片地图横向由多少个瓦片组成  
	float mapWidth = map->getTileSize().width * map->getMapSize().width;  

	//求出这个瓦片地图的整体高度 其中，_tileMap->getTileSize().height得到的是瓦片地图每一个瓦片的高度，  
	//_tileMap->getMapSize().height得到的是瓦片地图纵向由多少个瓦片组成  
	float mapHeight = map->getMapSize().height * map->getTileSize().height;  

	//以下这个判断的意思：只有人物的坐标点在瓦片地图中才对人物的坐标点进行重新设置  
	//任务的坐标只有在小于瓦片地图的整体宽度和高度以及要大于0点 ，才在地图中  
	if (playerPos.x < mapWidth && playerPos.y < mapHeight && playerPos.x >= 0 && playerPos.y >= 0)  
	{  
		this->setPlayerPosition(playerPos);  
	}  
	//将人物的坐标传入地图相对移动的方法，以便计算相对移动的方向。  
	this->setViewpointCenter(player->getPosition());  
}

void HelloWorld::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,0,true);
}

void HelloWorld::setPlayerPosition(CCPoint position)
{
	SimpleAudioEngine::sharedEngine()->playEffect("move.wav");

	CCPoint tileCoord = this->tileCoordForPosition(position);

	int tileGid = mapLayer->tileGIDAt(tileCoord);
	
	if (tileGid)
	{
		
		CCDictionary *properties = map->propertiesForGID(tileGid);
		CCLog("%d\n",tileGid);

		if (properties)
		{
			const CCString *collision = properties->valueForKey("Collidable");
			CCLog("%s\n",collision->getCString());

			if (collision && collision->compare("true") ==0)
			{
				SimpleAudioEngine::sharedEngine()->playEffect("hit.wav");
				return;
			}           
		}

		const CCString *collectable = properties->valueForKey("Collectable");
		if (collectable && collectable->compare("true") ==0)
		{
			count+=1;
			SimpleAudioEngine::sharedEngine()->playEffect("pickup.wav");

			CountLayer *countLayer =(CountLayer *) this->getParent()->getChildByTag(1);

			if(countLayer!=NULL)
			{
				countLayer->countChange(count);
			}
			else
			{
				CCLog("*************error\n");
			}

			mapLayer->removeTileAt(tileCoord);
			foreground->removeTileAt(tileCoord);
		}

	}
	player->setPosition(position);


	//player->setPosition(position);
}
CCPoint HelloWorld::tileCoordForPosition(CCPoint position)
{
	int x = position.x / map->getTileSize().width;
	//将人物的目的的坐标的y轴坐标转换成瓦片地图中的y轴的坐标
	int y = ((map->getMapSize().height * map->getTileSize().height) - position.y) / map->getTileSize().height;
	return ccp(x, y);
}