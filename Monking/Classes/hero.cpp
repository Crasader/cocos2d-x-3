#include "hero.h"

HeroSprite::HeroSprite()
{
}

HeroSprite::~HeroSprite()
{

}

bool HeroSprite::init()
{
	if(!HeroSprite::initWithSpriteFrameName("hero_idle_00.png"))
		return false;

	/*空闲动作*/
	CCArray *idleArray = CCArray::create();
	idleArray->retain();
	
	for (int i=0;i<6;i++)
	{
		CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(
			CCString::createWithFormat("hero_idle_%02d.png",i)->getCString());
	
		idleArray->addObject(frame);
	}

	CCAnimation *idleAnimation = CCAnimation::createWithSpriteFrames(idleArray,0.3f);
	this->idleAction = CCRepeatForever::create(CCAnimate::create(idleAnimation));
	idleAction->retain();

	/*攻击动作*/
	CCArray *attackArray = CCArray::create();
	attackArray->retain();

	for (int i=0;i<3;i++)
	{
		CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(
			CCString::createWithFormat("hero_attack_00_%02d.png",i)->getCString());

		attackArray->addObject(frame);
	}

	CCAnimation *attackAnimation = CCAnimation::createWithSpriteFrames(attackArray,0.1f);
	this->attackAction = CCSequence::create(CCAnimate::create(attackAnimation),
		CCCallFunc::create(this,callfunc_selector(ActionSprite::idle)),NULL);
	attackAction->retain();

	/*行走动作*/
	CCArray *walkArray = CCArray::create();
	walkArray->retain();

	for(int i= 0;i<8;i++)
	{
		CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(
			CCString::createWithFormat("hero_walk_%02d.png",i)->getCString());

		walkArray->addObject(frame);
	}

	CCAnimation *walkAnimation = CCAnimation::createWithSpriteFrames(walkArray,0.1f);
	walkAction = CCRepeatForever::create(CCAnimate::create(walkAnimation));
	walkAction->retain();

	/**
	*受伤动作
	*/

	CCArray *hurtArray = CCArray::create();
	hurtArray->retain();

	for (int i=0;i<3;i++)
	{
		CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(
			CCString::createWithFormat("hero_hurt_%02d.png",i)->getCString());

		hurtArray->addObject(frame);
	}

	CCAnimation *hurtAnimation = CCAnimation::createWithSpriteFrames(hurtArray,0.1f);
	this->hurtAction = CCSequence::create(CCAnimate::create(hurtAnimation),
		CCCallFunc::create(this,callfunc_selector(ActionSprite::idle)),NULL);
	hurtAction->retain();


	/*死亡动作*/

	CCArray *deadArray = CCArray::create();
	deadArray->retain();

	for (int i=0;i<5;i++)
	{
		CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(
			CCString::createWithFormat("hero_knockout_%02d.png",i)->getCString());

		deadArray->addObject(frame);
	}

	CCAnimation *deadAnimation = CCAnimation::createWithSpriteFrames(deadArray,0.1f);
	this->deadAction = CCSequence::create(CCAnimate::create(deadAnimation),
		CCBlink::create(2.0,10.0),NULL);
	deadAction->retain();


	this->centerToBottom = 39.0f;
	this->centerToSlide = 29.0f;
	this->hitPoints = 100;
	this->danage = 20;
	this->walkSpeed = 80;

	hitBox = this->createBoundBoxWithOrigin(ccp(-this->centerToSlide,-centerToBottom),CCSizeMake(centerToSlide*2,centerToBottom*2));
	attackBox = this->createBoundBoxWithOrigin(ccp(centerToSlide,-10),CCSizeMake(20,20));

	return true;

}