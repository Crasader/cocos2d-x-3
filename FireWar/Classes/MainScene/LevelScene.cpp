#include "LevelScene.h"
#include "LevelGeneratorHub.h"

int lp=1;
int levelT=1;

LevelScene::LevelScene()
{
	layer = NULL;
}

LevelScene::~LevelScene()
{
	if(layer)
	{
		layer->release();
		layer = NULL;
	}

}

bool LevelScene::init()
{
	if(!CCScene::init())
		return false;

	return true;
}

void LevelScene::setPlayerType(int type ,int level)
{
	pt=type;
	lp=type;
	levelT=level;
	lt=level;

	LevelGeneratorHub *levelGeneratorHub = LevelGeneratorHub::create();

	this->addChild(levelGeneratorHub,5);
}