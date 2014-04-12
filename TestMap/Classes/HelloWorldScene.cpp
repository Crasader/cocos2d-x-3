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
	//convertToNodeSpace�������ǰ�OpenGL������ת����CCLayer�����ꡣ  
	CCPoint touchPosition = this->convertTouchToNodeSpace(pTouch);  
	//��ȡ������CCLayer�ϵ�����  
	CCPoint playerPos = player->getPosition();  

	//�ô�����������ȥ��������꣬��������Ҫ�ƶ��ķ����Լ��ƶ�һ��λ�ã����ǳ�֮Ϊ�ƶ������  
	CCPoint diff = ccpSub(touchPosition, playerPos);  

	//���ƶ�������x�������y�����ʱ������ֻ�ƶ�x�ᣬ��֮���ƶ�y��  
	if (abs(diff.x) > abs(diff.y))  
	{  
		//���ƶ�������x����0ʱ ���������ƶ��������������x�����һ����Ƭ��ͼ�Ŀ�ȡ�  
		if (diff.x > 0)  
		{  
			//getTileSize().width��ȡһ����Ƭ��ͼ�Ŀ��  
			playerPos.x += map->getTileSize().width-2;  
		}  
		else  
		{  
			//���ƶ�������xС��0ʱ ���������ƶ��������������x���ȥһ����Ƭ��ͼ�Ŀ�ȡ�  
			//getTileSize().width��ȡһ����Ƭ��ͼ�Ŀ��  
			playerPos.x -= map->getTileSize().width+2;  
		}  
	}  
	else  
	{  
		//���ƶ�������y����0ʱ ���������ƶ��������������y�����һ����Ƭ��ͼ�ĸ߶ȡ�  
		if (diff.y > 0)  
		{  
			//getTileSize().height��ȡһ����Ƭ��ͼ�ĸ߶�  
			playerPos.y += map->getTileSize().height;  
		}  
		else  
		{  
			//���ƶ�������yС��0ʱ ���������ƶ��������������x���ȥһ����Ƭ��ͼ�ĸ߶ȡ�  
			//getTileSize().height��ȡһ����Ƭ��ͼ�ĸ߶�  
			playerPos.y -= map->getTileSize().height;  
		}  
	}  
	//��������Ƭ��ͼ�������� ���У�_tileMap->getTileSize().width�õ�������Ƭ��ͼÿһ����Ƭ�Ŀ�ȣ�  
	//_tileMap->getMapSize().width�õ�������Ƭ��ͼ�����ɶ��ٸ���Ƭ���  
	float mapWidth = map->getTileSize().width * map->getMapSize().width;  

	//��������Ƭ��ͼ������߶� ���У�_tileMap->getTileSize().height�õ�������Ƭ��ͼÿһ����Ƭ�ĸ߶ȣ�  
	//_tileMap->getMapSize().height�õ�������Ƭ��ͼ�����ɶ��ٸ���Ƭ���  
	float mapHeight = map->getMapSize().height * map->getTileSize().height;  

	//��������жϵ���˼��ֻ����������������Ƭ��ͼ�вŶ����������������������  
	//���������ֻ����С����Ƭ��ͼ�������Ⱥ͸߶��Լ�Ҫ����0�� �����ڵ�ͼ��  
	if (playerPos.x < mapWidth && playerPos.y < mapHeight && playerPos.x >= 0 && playerPos.y >= 0)  
	{  
		this->setPlayerPosition(playerPos);  
	}  
	//����������괫���ͼ����ƶ��ķ������Ա��������ƶ��ķ���  
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
	//�������Ŀ�ĵ������y������ת������Ƭ��ͼ�е�y�������
	int y = ((map->getMapSize().height * map->getTileSize().height) - position.y) / map->getTileSize().height;
	return ccp(x, y);
}