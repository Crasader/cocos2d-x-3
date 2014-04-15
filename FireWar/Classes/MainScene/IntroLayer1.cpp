#include "IntroLayer1.h"
#include "PlayerSelectLayer.h"

IntroLayer1::IntroLayer1()
{

}

IntroLayer1::~IntroLayer1()
{

}

CCScene *IntroLayer1::createScene()
{
    CCScene *scene = NULL;

    scene = CCScene::create();
    IntroLayer1 *layer = IntroLayer1::create();
    scene->addChild(layer);

    return scene;
}

bool IntroLayer1::init()
{
    if (!CCLayer::init())
        return false;

    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Menus/Intro/Intro0.plist");

    CCSprite *firstFrame = CCSprite::create("Menus/Intro/bgIntro1.png");
    this->addChild(firstFrame);

    CCSize size = CCDirector::sharedDirector()->getWinSize();

    firstFrame->setPosition(ccp(size.width/2,size.height/2));

    CCArray *frameArray = CCArray::create();
    frameArray->retain();

    for (int i =1; i<4; i++)
    {
        CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(
                                   CCString::createWithFormat("bgIntro%d.png",i)->getCString()
                               );

        frameArray->addObject(frame);
    }

    CCAnimation *animation = CCAnimation::createWithSpriteFrames(frameArray,1.0f);
    CCAnimate *animate = CCAnimate::create(animation);

    CCAction *loopAction = CCSequence::create(animate,CCCallFunc::create(this,callfunc_selector(IntroLayer1::startGame)),NULL);
    loopAction->retain();

    firstFrame->runAction(loopAction);

    return true;
}

void IntroLayer1::startGame()
{
    CCLOG("**********************************start\n");

    //CCDirector::sharedDirector()->replaceScene(CCTransitionFadeDown::create(1.0f,PlayerSeleceLayer::createScene()));
    CCDirector::sharedDirector()->replaceScene(CCTransitionProgressInOut::create(0.5f,PlayerSeleceLayer::createScene()));
}
