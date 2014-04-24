#include "IntroLayer2.h"
#include "PlayerSelectLayer.h"

IntroLayer2::IntroLayer2()
{

}

IntroLayer2::~IntroLayer2()
{

}

CCScene *IntroLayer2::createScene()
{
    CCScene *scene = NULL;

    scene = CCScene::create();
    IntroLayer2 *layer = IntroLayer2::create();
    scene->addChild(layer);

    return scene;
}

bool IntroLayer2::init()
{
    if (!CCLayer::init())
        return false;

    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Menus/Intro/Intro2.plist");

    CCSprite *firstFrame = CCSprite::create("Menus/Intro/bgIntro21.png");
    this->addChild(firstFrame);

    CCSize size = CCDirector::sharedDirector()->getWinSize();

    firstFrame->setPosition(ccp(size.width/2,size.height/2));

    CCArray *frameArray = CCArray::create();
    frameArray->retain();

    for (int i =1; i<4; i++)
    {
        CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(
                                   CCString::createWithFormat("bgIntro2%d.png",i)->getCString()
                               );

        frameArray->addObject(frame);
    }

    CCAnimation *animation = CCAnimation::createWithSpriteFrames(frameArray,1.0f);
    CCAnimate *animate = CCAnimate::create(animation);

    CCAction *loopAction = CCSequence::create(animate,CCCallFunc::create(this,callfunc_selector(IntroLayer2::startGame)),NULL);
    loopAction->retain();

    firstFrame->runAction(loopAction);

    return true;
}

void IntroLayer2::startGame()
{
    CCLOG("**********************************start\n");

    //CCDirector::sharedDirector()->replaceScene(CCTransitionFadeDown::create(1.0f,PlayerSeleceLayer::createScene()));
    CCDirector::sharedDirector()->replaceScene(CCTransitionProgressInOut::create(0.5f,PlayerSeleceLayer::createScene()));
}
