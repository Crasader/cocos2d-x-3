#include "ActionSprite.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

ActionSprite::ActionSprite()
{
	this->actionState = ACTION_NONE;
}

ActionSprite::~ActionSprite()
{

}

bool ActionSprite::init()
{
	if(this->actionState!=ACTION_NONE){
		this->stopAllActions();
		this->runAction(this->idleAction);

		this->actionState= ACTION_IDLE;
		this->velocity =CCPointZero;
	}

	return true;
}

void ActionSprite::idle()
{
	if(this->actionState != ACTION_IDLE)
	{
		this->stopAllActions();
		this->runAction(this->idleAction);

		this->actionState = ACTION_IDLE;
		this->velocity = CCPointZero;
	}
}

void ActionSprite::attack()
{
	if(this->actionState ==  ACTION_IDLE || actionState == ACTION_ATTACK || actionState == ACTION_WALK)
	{
		this->stopAllActions();
		this->actionState = ACTION_ATTACK;
		this->runAction(this->attackAction);
	}
}

void ActionSprite::walkWithDirection(CCPoint point)
{
	if(actionState == ACTION_IDLE)
	{
		this->stopAllActions();
		this->runAction(this->walkAction);
		this->actionState = ACTION_WALK;
	}

	if(actionState == ACTION_WALK)
	{
		velocity = ccp(point.x*walkSpeed,point.y*walkSpeed);

		if(this->velocity.x >=0)
		{
			this->setScaleX(1.0);  /*调整人物左右方向*/
		}
		else
		{
			this->setScaleX(-1.0);
		}
	}

}

void ActionSprite::hurtWithDanage(float danage)
{
	bool flag = CCUserDefault::sharedUserDefault()->getBoolForKey("music_trigger");
	if(!flag)
	{
		SimpleAudioEngine::sharedEngine()->playEffect("pd_hit0.wav");
	}

	if(this->actionState != ACTION_DEAD )
	{
		this->stopAllActions();
		actionState = ACTION_HURT;

		this->runAction(hurtAction);

		hitPoints-=danage;

		if(hitPoints <=0)
		{
			this->dead();
		}
	}
}
void ActionSprite::dead()
{
	stopAllActions();
	this->runAction(deadAction);
	actionState = ACTION_DEAD;
	hitPoints = 0;
}


void ActionSprite::updateDesiredPosition(float dt)
{
	if(actionState ==  ACTION_WALK)
	{
		desritePoint = ccpAdd(this->getPosition(),ccpMult(velocity,dt));
	}

}

BoundBox ActionSprite::createBoundBoxWithOrigin(CCPoint origin,CCSize size)
{
	BoundBox boundBox;

	boundBox.original.origin = origin;
	boundBox.original.size = size;

	boundBox.actual.origin = ccpAdd(this->getPosition(),ccp(boundBox.original.origin.x,boundBox.original.origin.y));
	boundBox.actual.size = size;

	return boundBox;

}

void ActionSprite::tranfromBoxes()
{
	hitBox.actual.origin = ccpAdd(this->getPosition(),ccp(hitBox.original.origin.x,hitBox.original.origin.y));

	attackBox.actual.origin=ccpAdd(this->getPosition(),ccp(attackBox.original.origin.x+(this->getScaleX()==-1?(-attackBox.original.size.width-hitBox.original.size.width):0),attackBox.original.origin.y));
}

void ActionSprite::setPosition(CCPoint pos)
{
	CCSprite::setPosition(pos);
	tranfromBoxes();
}
