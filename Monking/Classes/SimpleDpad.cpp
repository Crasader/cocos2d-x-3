#include "SimpleDpad.h"

#ifdef INSTANCE
SimpleDpad *SimpleDpad::simpleDpad = NULL;
#endif


SimpleDpad::SimpleDpad()
{
	this->delegate = NULL;
}

SimpleDpad::~SimpleDpad()
{

}


SimpleDpad *SimpleDpad::dpadWithFile(CCString *fileName,float r)
{
	
#ifdef INSTANCE
	if(SimpleDpad::simpleDpad == NULL)
	{
		simpleDpad = new SimpleDpad();
	}
	return simpleDpad;
#else
	SimpleDpad *simpleDpad = new SimpleDpad();

	if(simpleDpad&&simpleDpad->initWithFile(fileName,r))
	{	
		return simpleDpad;
	}
	else
	{
		delete simpleDpad;
		simpleDpad = NULL;

		return NULL;
	}
#endif
}

bool SimpleDpad::initWithFile(CCString *fileName,float r)
{
	if(!CCSprite::initWithFile(fileName->getCString()))
	{
		return false;
	}
	else
	{
		this->radius = r;
		this->director = CCPointZero;
		this->isHeld = false;
		this->scheduleUpdate();
		return true;
	}
}

void SimpleDpad::onEnterTransitionDidFinish()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,0,true); //注册单点触摸回调函数
	CCLOG("********************************");
}

void SimpleDpad::onExit()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

void SimpleDpad::update(float dt)
{
	if(this->isHeld)
	{
		if(delegate !=NULL)
		{
			this->delegate->isHoldingDirector(this,director);
		}
	}
}



bool SimpleDpad::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	//求两点间距离的平方
	float distanceSQ = ccpDistanceSQ(pTouch->getLocation(),this->getPosition());  
	
	if(distanceSQ <= radius* radius)
	{
		this->updateDirectionForLocation(pTouch->getLocation());
		isHeld = true;
		
		return true;
	}

	return false;
}

void SimpleDpad::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	this->updateDirectionForLocation(pTouch->getLocation());
}

void SimpleDpad::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	this->director = CCPointZero;
	isHeld = false;
	if(delegate !=NULL)
	{
		this->delegate->simpleDpadTouchEnd(this);
	}
	
}

void SimpleDpad::updateDirectionForLocation(CCPoint location)
{
	//float radians = ccpToAngle(cc location,this->getPosition()); //求弧度值
	float radians = ccpToAngle(ccpSub(location,this->getPosition()));
	float degrees = -1*CC_RADIANS_TO_DEGREES(radians);  //求角度值


	CCLOG("**********************%f",degrees);

	if(degrees >= -22.5 && degrees<=22.5)
	{
		this->director= ccp(1,0);
	}
	else if(degrees>22.5&&degrees<67.5)
	{
		this->director=ccp(1,-1);
	}
	else if(degrees>=67.5&&degrees<=112.5){
		this->director=ccp(0,-1);
	}
	else if(degrees>112.5&&degrees<157.5){
		this->director=ccp(-1,-1);
	}
	else if(degrees>=157.5 || degrees<=-157.5){
		this->director=ccp(-1,0);
	}
	else if(degrees<-22.5&&degrees>-67.5){
		this->director=ccp(1,1);
	}
	else if(degrees<=-67.5&&degrees>=-112.5){
		this->director=ccp(0,1);
	}
	else if(degrees<-112.5&&degrees>-157.5){
		this->director=ccp(-1,1);
	}

	if(delegate !=NULL)
	{
		this->delegate->didChangeDirectorTo(this,this->director);
	}
	
}
