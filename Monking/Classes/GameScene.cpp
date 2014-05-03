#include "GameScene.h"

GameScene::GameScene()
{
	gameLayer = NULL;
	hubLayer = NULL;
}

GameScene::~GameScene()
{
}

bool GameScene::init()
{
	
	if(!CCScene::init())
		return false;

	gameLayer = GameLayer::create();
	this->addChild(gameLayer);

	hubLayer = HubLayer::create();
	this->addChild(hubLayer);

	gameLayer->setHubLayer(hubLayer);

//	this->isKeypadEnabled(true);

	return true;
}

