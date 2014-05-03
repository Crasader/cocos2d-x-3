#include "Robot.h"


USING_NS_CC;

Robot::Robot(void)
{
	nextDecisionTime = 0;
}


Robot::~Robot(void)
{
}

bool Robot::init()
{
	if(!ActionSprite::init()){
		return false;
	}

	if(!ActionSprite::initWithSpriteFrameName("robot_idle_00.png")){
		return false;
	}

	int i;

	CCArray* idleFrames=CCArray::createWithCapacity(5);
	for(i=0;i<5;i++){
		CCSpriteFrame* frame=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("robot_idle_%02d.png",i)->getCString());
		idleFrames->addObject(frame);
	}
	CCAnimation* idleAnimation=CCAnimation::createWithSpriteFrames(idleFrames,0.1f);
	this->idleAction=CCRepeatForever::create(CCAnimate::create(idleAnimation));
	this->idleAction->retain();

	CCArray* attackFrames=CCArray::createWithCapacity(5);
	for(i=0;i<5;i++){
		CCSpriteFrame* frame=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("robot_attack_%02d.png",i)->getCString());
		attackFrames->addObject(frame);
	}
	CCAnimation* attackAnimation=CCAnimation::createWithSpriteFrames(attackFrames,0.05f);
	this->attackAction=CCSequence::create(CCAnimate::create(attackAnimation),CCCallFunc::create(this,callfunc_selector(Robot::idle)),NULL);
	this->attackAction->retain();

	CCArray* walkFrames=CCArray::createWithCapacity(6);
	for(i=0;i<6;i++){
		CCSpriteFrame* frame=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("robot_walk_%02d.png",i)->getCString());
		walkFrames->addObject(frame);
	}
	CCAnimation* walkAnimation=CCAnimation::createWithSpriteFrames(walkFrames,0.1f);
	this->walkAction=CCRepeatForever::create(CCAnimate::create(walkAnimation));
	this->walkAction->retain();

	CCArray* hurtFrames=CCArray::createWithCapacity(3);
	for(i=0;i<3;i++){
		CCSpriteFrame* frame=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("robot_hurt_%02d.png",i)->getCString());
		hurtFrames->addObject(frame);
	}
	CCAnimation* hurtAnimation=CCAnimation::createWithSpriteFrames(hurtFrames,0.1f);
	this->hurtAction=CCSequence::create(CCAnimate::create(hurtAnimation),CCCallFunc::create(this,callfunc_selector(Robot::idle)),NULL);
	this->hurtAction->retain();


	CCArray* deadFrames=CCArray::createWithCapacity(5);
	for(i=0;i<5;i++){
		CCSpriteFrame* frame=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("robot_knockout_%02d.png",i)->getCString());
		deadFrames->addObject(frame);
	}
	CCAnimation* deadAnimation=CCAnimation::createWithSpriteFrames(deadFrames,0.1f);
	this->deadAction=CCSequence::create(CCAnimate::create(deadAnimation),CCBlink::create(2.0,10.0),NULL);  
	this->deadAction->retain();


	this->walkSpeed=80;
	this->centerToBottom=39;
	this->centerToSlide =29;
	this->hitPoints=100;
	this->danage =10; 

	
	hitBox = this->createBoundBoxWithOrigin(ccp(-this->centerToSlide,-centerToBottom),CCSizeMake(centerToSlide*2,centerToBottom*2));
	attackBox = this->createBoundBoxWithOrigin(ccp(centerToSlide,-5),CCSizeMake(25,20));



	return true;
}