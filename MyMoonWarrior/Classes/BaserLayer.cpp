#include "BaserLayer.h"

BaserLayer::BaserLayer()
{
}

BaserLayer::~BaserLayer()
{
}

bool BaserLayer::init()
{
	bool sRect = false;

	do
	{
		CC_BREAK_IF(!CCLayer::init());

		sRect = true;
	}while(0);

	return sRect;
}


CCSize  BaserLayer::getWinSize()
{
	return CCDirector::sharedDirector()->getWinSize();
}

void BaserLayer::setBackGroundImage(CCSprite *back)
{
	back->setPosition(ccp(getWinSize().width/2,getWinSize().height/2));
}

void BaserLayer::setBackGroundImage(const char *image)
{

	CCSprite *sp = CCSprite::create(image);
	sp->setPosition(ccp(getWinSize().width/2,getWinSize().height/2));
	this->addChild(sp);
}
