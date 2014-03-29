#include "IntroLayer3.h"

IntroLayer3::IntroLayer3()
{


}

IntroLayer3::~IntroLayer3()
{


}

CCScene *IntroLayer3::createScene()
{
	CCScene *scene = NULL;

	scene = CCScene::create();

	IntroLayer3 *layer = IntroLayer3::create();
	scene->addChild(layer);

	return scene;

}

bool IntroLayer3::init()
{
	if(!CCLayer::init())
		return false;

	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Menus/Intro/Intro.plist");

	//CCSpriteFrame *firstFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("bgIntro31.png");

	CCSprite *firstFrame = CCSprite::create("Menus/Intro/bgIntro31.png");
	this->addChild(firstFrame);

	CCSize size = CCDirector::sharedDirector()->getWinSize();

	firstFrame->setPosition(ccp(size.width/2,size.height/2));

	CCArray *frameArray = CCArray::create();
	frameArray->retain();

	for(int i =1;i<4;i++)
	{
		CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(
			CCString::createWithFormat("bgIntro3%d.png",i)->getCString()
			);

		frameArray->addObject(frame);
	}

	CCAnimation *animation = CCAnimation::createWithSpriteFrames(frameArray,1.0f);
	CCAnimate *animate = CCAnimate::create(animation);

	CCAction *loopAction = CCSequence::create(animate,CCCallFunc::create(this,callfunc_selector(IntroLayer3::startGame)),NULL);
	loopAction->retain();

	firstFrame->runAction(loopAction);

	//firstFrame->runAction()


	return true;
}

void IntroLayer3::startGame()
{
	CCLOG("**********************************start\n");
}
