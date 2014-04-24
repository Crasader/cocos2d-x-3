#include "effect.h"

Effect *Effect::instanece = NULL;

Effect::Effect()
{
}

Effect::~Effect()
{
}

Effect* Effect::getSharedEffect()
{
	if(Effect::instanece == NULL)
	{
		Effect::instanece = new Effect();
	}

	return Effect::instanece;

}

void Effect::preLoad()
{
	//将爆炸的plist和图片加入到cache中
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("explosion.plist");

	//创建CCAnimation
	CCAnimation *boomAnimation = CCAnimation::create();
	boomAnimation->setDelayPerUnit(0.5f);
	boomAnimation->setLoops(1);

	int i =1;
	for(i=1;i<=35;i++)
	{
		char str[20];
		memset(str,'\0',20);
		sprintf(str,"explosion_%02d.png",i);

		CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str);
		boomAnimation->addSpriteFrame(pFrame);

	}

	CCAnimationCache::sharedAnimationCache()->addAnimation(boomAnimation,"boom");

}

void Effect::boom( CCNode *target,CCPoint point)
{
	CCSprite *sp = CCSprite::createWithSpriteFrameName("explosion_01.png");

	sp->addChild(sp,55);
	sp->setPosition(point);

	CCAnimation *boomAnimation = CCAnimationCache::sharedAnimationCache()->animationByName("boom");

	CCAnimate *anim = CCAnimate::create(boomAnimation);

	CCCallFunc *callback = CCCallFuncN::create(sp,callfuncN_selector(Effect::boom_callback));

	CCAction *actions = CCSequence::create(anim,callback,NULL);

	sp->runAction(actions);
}


void Effect::boom_callback(CCNode *pNode)
{
	pNode->removeFromParentAndCleanup(true);
}
