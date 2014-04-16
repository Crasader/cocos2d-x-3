#include "TestTextureLayer.h"
#include "TextureBackground.h"

TestTextureLayer::~TestTextureLayer()
{

}

bool TestTextureLayer::init()
{
	if(!CCLayer::init())
		return false;

	TextureBackground *tex =TextureBackground::create();
	this->addChild(tex,1);

	return true;
}

CCScene *TestTextureLayer::createScene()
{
	CCScene *scene = NULL;

	scene  =CCScene::create();

	TestTextureLayer *layer = TestTextureLayer::create();

	scene->addChild(layer);

	return scene;

}
