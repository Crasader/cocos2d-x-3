#include "enemymodel.h"

EnemyModel::EnemyModel(Monster monster,CCPoint targetPoint)
{
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile( "Monster.plist", "Monster.png");



		switch(monster)
		{
		case monster1:
			{
				mSprite = CCSprite::createWithSpriteFrameName("Monster1.png");
				mAction = CCMoveTo::create(1.0f,targetPoint);

		  	}
	  		break;
		case monster2:
			{	
				mSprite = CCSprite::createWithSpriteFrameName("Monster1.png");
				mAction = CCMoveTo::create(1.0f,targetPoint);
		  	}
	  		break;
		case monster3:
			{						
				mSprite = CCSprite::createWithSpriteFrameName("Monster1.png");
				mAction = CCMoveTo::create(1.0f,targetPoint);
		  	}
	  		break;
		case monster4:
			{				
				mSprite = CCSprite::createWithSpriteFrameName("Monster1.png");
				mAction = CCMoveTo::create(1.0f,targetPoint);
		  	}
	  		break;
		case monster5:
			{						
				mSprite = CCSprite::createWithSpriteFrameName("Monster1.png");
				mAction = CCMoveTo::create(1.0f,targetPoint);
		  	}
	  		break;
		case monster6:
			{	
				mSprite = CCSprite::createWithSpriteFrameName("Monster1.png");
				mAction = CCMoveTo::create(1.0f,targetPoint);
		  	}
	  		break;
		default:
			{
				mSprite = CCSprite::createWithSpriteFrameName("Monster1.png");
				mAction = CCMoveTo::create(1.0f,targetPoint);
			}
			break;
	}
}

EnemyModel::~EnemyModel()
{
}

bool EnemyModel::init()
{
	bulletArray = CCArray::create();
	bulletArray->retain();

//	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile( "Monster.plist", "Monster.png");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("bullet.plist","bullet.png");

	enemyBatchNode = CCSpriteBatchNode::create("bullet.png");
	
	ccBlendFunc cb = {GL_SRC0_ALPHA,GL_ONE};
	enemyBatchNode->setBlendFunc(cb);

	this->addChild(enemyBatchNode);

	mSprite->setPosition(CCPointZero);

	this->addChild(mSprite);
	this->runAction(mAction);

	this->schedule(schedule_selector(EnemyModel::addBullet),0.1f);
	this->schedule(schedule_selector(EnemyModel::moveBullet),0.015f);

	return true;
}

EnemyModel* EnemyModel::getEnemy(Monster monster,CCPoint targetPoint)
{
	EnemyModel* model = new EnemyModel( monster,targetPoint );
	
	if( model && model->init()){
		model->autorelease();
		return  model;
	}

	CC_SAFE_DELETE( model );
	return NULL;
}

void EnemyModel::addBullet(float f)
{
/*	CCSprite *bulletSprite = CCSprite::createWithSpriteFrameName("W1.png");
  	CCSize size = CCDirector::sharedDirector()->getWinSize();

 	bulletSprite->setPosition(ccp(size.width/2,size.height/2));
	bulletArray->addObject(bulletSprite);
	enemyBatchNode->addChild(bulletSprite);*/

	 
   	CCSprite* sp = CCSprite::createWithSpriteFrameName( "W1.png" );
	sp->setPosition(  mSprite->getPosition() );
	enemyBatchNode ->addChild( sp );
	bulletArray->addObject( sp );



}

void EnemyModel::moveBullet(float t)
{
//	CCSize size =CCDirector::sharedDirector()->getWinSize();
	CCObject *obj = NULL;

	CCARRAY_FOREACH(bulletArray,obj)
	{
		CCSprite *sp = (CCSprite *)obj;
		sp->setPositionY(sp->getPositionY() -10);
		if(sp->getPositionY() <= -200)
		{
			enemyBatchNode->removeChild(sp,true);
			bulletArray->removeObject(sp);
		}
	}

}

EnemyManager::EnemyManager()
{
	enemyArray = CCArray::create();
	enemyArray->retain();
}

EnemyManager::~EnemyManager()
{
	CC_SAFE_DELETE_ARRAY(enemyArray);
}

bool EnemyManager::init()
{
	if(!BaserLayer::init())
	{
		return false;
	}

	setViews();

	return true;
}

void EnemyManager::setViews()
{

	
	Monster monster = {monster1};

//	EnemyModel *enemyModel = EnemyModel::getEnemy(monster,ccp(getWinSize().width/2,getWinSize().height/2*0.75));
	EnemyModel *enemyModel = EnemyModel::getEnemy(monster,ccp(getWinSize().width /2 , getWinSize().height * .75));

	enemyArray->addObject(enemyModel);

	this->addChild(enemyModel,1);
	//enemyModel->setPosition( ccp( getWinSize().width /2 , getWinSize().height * .75) );
	enemyModel->setPosition( ccp( 0,0) );
}

void EnemyManager::addEnemy(float t)
{
}

CCArray *EnemyManager::getEnemyArray()
{
	return enemyArray;
}

