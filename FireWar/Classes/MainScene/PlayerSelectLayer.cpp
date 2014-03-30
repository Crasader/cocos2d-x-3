#include "PlayerSelectLayer.h"
#include "LevelScene.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

PlayerSeleceLayer::PlayerSeleceLayer()
{


}

PlayerSeleceLayer::~PlayerSeleceLayer()
{

}

bool PlayerSeleceLayer::init()
{
	if(!CCLayer::init())
		return false;

	CCSize size = CCDirector::sharedDirector()->getWinSize();

	CCSprite *pSprite = CCSprite::create("SpriteImages/bgEmpty.png");
	addChild(pSprite);
	pSprite->setPosition(ccp(size.width/2,size.height/2));

	pSprite = CCSprite::create("SpriteImages/playerselector.png");
	addChild(pSprite);
	pSprite->setPosition(ccp(size.width/2,size.height-pSprite->getContentSize().height));

	CCMenuItemImage *level1 = CCMenuItemImage::create("PlayerType/BlackCommando.png","PlayerType/BlackCommando2.png",
		this,menu_selector(PlayerSeleceLayer::playerSelectOne));

	CCMenuItemImage *level2 = CCMenuItemImage::create("PlayerType/GoldenCommando.png","PlayerType/GoldenCommando2.png",
		this,menu_selector(PlayerSeleceLayer::playerSelectSecond));
	
	CCMenuItemImage *level3 = CCMenuItemImage::create("PlayerType/GreenCommando.png","PlayerType/GreenCommando2.png",
		this,menu_selector(PlayerSeleceLayer::playerSelectThrid));

	CCMenu *menu = CCMenu::create(level1,level2,level3,NULL);
	menu->alignItemsHorizontally();
	//menu->alignItemsHorizontallyWithPadding(50);
	addChild(menu);

	SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Sound/Menu.mp3");

	return true;
}

CCScene *PlayerSeleceLayer::createScene()
{
	CCScene *scene = NULL;
	scene = CCScene::create();

	PlayerSeleceLayer *playerSeleceLayer = PlayerSeleceLayer::create();

	scene->addChild(playerSeleceLayer);
	return scene;

}

void PlayerSeleceLayer::playerSelectOne(CCObject *sender)
{
	SimpleAudioEngine::sharedEngine()->playEffect("Sound/buttonclick.mp3");

	LevelScene *levelScene = LevelScene::create();
	levelScene->setPlayerType(1,1);

	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.0f,levelScene));
}
void PlayerSeleceLayer::playerSelectSecond(CCObject *sender)
{
	SimpleAudioEngine::sharedEngine()->playEffect("Sound/buttonclick.mp3");
}

void PlayerSeleceLayer::playerSelectThrid(CCObject *sender)
{
	SimpleAudioEngine::sharedEngine()->playEffect("Sound/buttonclick.mp3");
}