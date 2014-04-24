#include "warriorlayer.h"

WarriorLayer::WarriorLayer()
{
	warrior = NULL;
}

WarriorLayer::~WarriorLayer()
{
}

bool WarriorLayer::init()
{
	bool sRect = false;

	do
	{
		CC_BREAK_IF(!BaserLayer::init());
		setViews();
		sRect = true;

	}while(0);

	return sRect;

}

void WarriorLayer::setViews()
{

	/**
	 *创建飞机
	 */
	warrior = CCSprite::create("ship01.png",CCRectMake(60,0,60,43));

	warrior->setPosition(ccp(getWinSize().width/2,getWinSize().height/2));
	this->addChild(warrior);


	/**
	 *创建动画
	 */
	CCAnimation *animation = CCAnimation::create();
	animation->setDelayPerUnit(0.1f);

	animation->addSpriteFrame(CCSpriteFrame::create("ship01.png", CCRectMake(60,0,60,43)));
	animation->addSpriteFrame(CCSpriteFrame::create("ship01.png", CCRectMake(0,0,60,43)));

	CCAnimate *animate = CCAnimate::create(animation);

	warrior->runAction(CCRepeatForever::create(animate));

	this->setTouchEnabled(true);
}

bool WarriorLayer::ccTouchBegan(CCTouch *pTouch,CCEvent *event)
{
	CCMoveTo *moveTo =  CCMoveTo::create(0.35f,pTouch->getLocation());
	
	warrior->runAction(moveTo);

	return true;
}

void WarriorLayer::registerWithTouchDispatcher(void)
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,INT_MIN,true);
}

CCPoint  WarriorLayer::getWarriorPostion()
{
	return warrior->getPosition();
}

CCSize WarriorLayer::getFlySize()
{
	return warrior->getContentSize();
}

BulletLayer::BulletLayer()
{
	mBulletNode = NULL;
	bulletArray = NULL;
}

BulletLayer::~BulletLayer()
{
}

bool BulletLayer::init()
{
	if(!BaserLayer::init())
		return false;

	setViews();
	return true;
}

void BulletLayer::setViews()
{
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("bullet.plist","bullet.png");

	mBulletNode  = CCSpriteBatchNode::create("bullet.png");

	ccBlendFunc cb = {GL_SRC_ALPHA,GL_NONE};

	mBulletNode->setBlendFunc(cb);

	this->addChild(mBulletNode);

	bulletArray = CCArray::create();
	bulletArray->retain();

//	this->schedule(schedule_selector(BulletLayer::addBullet),0.8f);
	this->schedule(schedule_selector(BulletLayer::moveAllBullet),0.05f);
}

void BulletLayer::addBullet(const CCPoint startPoint, CCSize flySize)
{
	CCSprite *bulletSprite = CCSprite::createWithSpriteFrameName("W1.png");
	bulletSprite->setPosition(ccp(startPoint.x-flySize.width/4,
				startPoint.y+flySize.height/2));

	CCSprite *bulletSprite2 = CCSprite::createWithSpriteFrameName("W1.png");
	bulletSprite2->setPosition(ccp(startPoint.x+flySize.width/4,
				startPoint.y+flySize.height/2));



	bulletArray->addObject(bulletSprite);
	bulletArray->addObject(bulletSprite2);

	mBulletNode->addChild(bulletSprite);
	mBulletNode->addChild(bulletSprite2);

}

/*
void BulletLayer::addBullet(float t)
{
	CCSprite *bulletSprite = CCSprite::createWithSpriteFrameName("W1.png");

	CCSize size = getWinSize();

	bulletSprite->setPosition(ccp(size.width/2,size.height/2));
	bulletArray->addObject(bulletSprite);

	mBulletNode->addChild(bulletSprite);

}

*/
void BulletLayer::moveAllBullet(float t)
{
	CCSize size = getWinSize();

	CCObject *obj = NULL;

	CCARRAY_FOREACH(bulletArray,obj)
	{
		CCSprite *sp = (CCSprite *)obj;
		sp->setPositionY(sp->getPositionY() +10);
		if(sp->getPositionY()>size.height)
		{
			mBulletNode->removeChild(sp,true);
			bulletArray->removeObject(sp);
		}
	}
}
