#include "SpriterLayer.h"

SpriterLayer::~SpriterLayer()
{

}

bool SpriterLayer::init()
{
	if(!CCLayer::init())
		return false;

	location.x = 30;
	location.y = 100;
	size = CCDirector::sharedDirector()->getWinSize();

	CCLayerColor *colorLayer = CCLayerColor::create(ccc4(150, 150, 150, 230),size.width,size.height);
	addChild(colorLayer);

	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("role.plist");
	
	initSpriteOne();

	initSpriteTwo();

	initSpriteThree();

	initSpriteFourth();


	setTouchEnabled(true);

	scheduleUpdate();
	

	return  true;
}

CCScene *SpriterLayer::createScene()
{
	CCScene *scene = NULL;

	scene = CCScene::create();

	SpriterLayer *layer= SpriterLayer::create();

	scene->addChild(layer);


	return scene;
}

void SpriterLayer::initSpriteOne()
{
	CCSprite  *sprite = CCSprite::createWithSpriteFrameName("Img_ZRun1.png");
	addChild(sprite);
	sprite->setPosition(ccp(100,size.height/2));

	CCArray *frameArray = CCArray::create();
	frameArray->retain();

	for (int i=1;i<7;i++)
	{
		CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("Img_ZRun%d.png",i)->getCString());
		frameArray->addObject(frame);
	}
	CCAnimation *animation = CCAnimation::createWithSpriteFrames(frameArray,0.1f);

	CCAnimate *animate = CCAnimate::create(animation);
	CCAction *action = CCRepeatForever::create(animate);

	sprite->runAction(action);
}

void SpriterLayer::initSpriteTwo()
{
	CCSprite *sprite = CCSprite::createWithSpriteFrameName("Img_Zhici1.png");
	addChild(sprite);
	sprite->setPosition(ccp(300,size.height/2));

	CCArray *frameArray = CCArray::create();
	frameArray->retain();

	for (int i=1;i<9;i++)
	{
		CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("Img_Zhici%d.png",i)->getCString());
		frameArray->addObject(frame);
	}

	CCAnimation *animation = CCAnimation::createWithSpriteFrames(frameArray,0.1f);
	CCAnimate *animate = CCAnimate::create(animation);

	CCAction *action = CCSequence::create(animate,CCCallFunc::create(this,callfunc_selector(SpriterLayer::animationEnd)),NULL);

	sprite->runAction(action);

}

void SpriterLayer::initSpriteThree()
{
	CCSprite *sprite = CCSprite::createWithSpriteFrameName("Img_Zhn1.png");
	addChild(sprite);
	sprite->setPosition(ccp(500,size.height/2));

	CCArray *frameArray = CCArray::create();
	frameArray->retain();

	for (int i=1;i<17;i++)
	{
		CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("Img_Zhn%d.png",i)->getCString());
		frameArray->addObject(frame);
	}

	CCAnimation *animation = CCAnimation::createWithSpriteFrames(frameArray,0.1f);
	CCAnimate *animate = CCAnimate::create(animation);

	CCAction *action = CCRepeatForever::create(animate);

	sprite->runAction(action);

}


void SpriterLayer::initSpriteFourth()
{
	CCSprite *sprite = CCSprite::createWithSpriteFrameName("Img_Zwlak1.png");
	addChild(sprite,0,1);

	sprite->setPosition(ccp(30,100));

	CCArray *frameArray = CCArray::create();
	frameArray->retain();

	for (int i=1;i<7;i++)
	{
		CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("Img_Zwlak%d.png",i)->getCString());
		frameArray->addObject(frame);
	}

	CCAnimation *animation = CCAnimation::createWithSpriteFrames(frameArray,0.1f);
	animation->setRestoreOriginalFrame(true);  //动画完成之后还原为第一帧
	CCAnimate *animate = CCAnimate::create(animation);

	CCAction *action = CCRepeatForever::create(animate);
	
	sprite->runAction(action);
}

void SpriterLayer::animationEnd()
{
	CCLog("animation finish");
}

void SpriterLayer::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{	
	CCTouch *touch = (CCTouch *)( pTouches->anyObject());

#ifdef DEBUG
	CCPoint point = touch->getLocation();
	CCLog("location x=%2.2f\t y=%2.2f\n",point.x,point.y);

	CCPoint viewPoint = touch->getLocationInView();
	CCLog("viewLocation x=%2.2f\t y=%2.2f\n",viewPoint.x,viewPoint.y);
#endif

	location = touch->getLocationInView();

}

void SpriterLayer::update(float delta)
{
	CCSprite *sprite = (CCSprite *)this->getChildByTag(1);

	if (sprite!=NULL)
	{
		if(sprite->getPositionX()>location.x)
		{
			sprite->setScaleX(-1);
		}
		else
		{
			sprite->setScaleX(1);
		}

		sprite->setPosition(ccp(location.x,100));
	}
}