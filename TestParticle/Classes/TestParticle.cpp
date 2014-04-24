#include "TestParticle.h"

TestParticle::TestParticle()
{

}

TestParticle::~TestParticle()
{

}

bool TestParticle::init()
{
	if(! CCLayer::init())
		return false;
	size = CCDirector::sharedDirector()->getWinSize();

	initSmoke();	
	initFirework();
	initFire();
	initSun();
	initGalaxy();
	initFlower();
	initFlower();
	initBigFlower();
	initRotFlower();
	initMeteor();
	initSpiral();
	initExplosion();
	initSnow();

	return true;
}

CCScene *TestParticle::createScene()
{
	CCScene *scene = NULL;

	scene = CCScene::create();

	TestParticle *layer = TestParticle::create();
	scene->addChild(layer);

	return scene;
}

void TestParticle::initSmoke()
{
	CCParticleSystem *emitter = CCParticleSmoke::create();
	emitter->retain();
	this->addChild(emitter, 10);
	emitter->setStartSize(20.0f);
	//emitter->setTotalParticles(300);
	emitter->setSpeed(150.0f); //设置速度
	emitter->setTexture( CCTextureCache::sharedTextureCache()->addImage("fire.png") ); //设置图片
	//emitter->setDuration(5.0f); //设置时间
	emitter->setPosition(ccp(size.width/6,size.height-150)); //设置初始位置
	emitter->release();

}

void TestParticle::initFirework()
{
	CCParticleSystem *emitter = CCParticleFireworks::create();
	emitter->retain();
	addChild(emitter,10);
	emitter->setStartSize(20.0f);
	emitter->setSpeed(150.0f);
	emitter->setTexture(CCTextureCache::sharedTextureCache()->addImage("stars.png"));
	//emitter->setDuration(5.0f);
	emitter->setPosition(ccp(size.width/6*2,size.height-150));
	emitter->release();

}

void TestParticle::initFire()
{
	CCParticleSystem *emitter = CCParticleFire::create();
	emitter->retain();
	addChild(emitter,10);
	emitter->setStartSize(30.0f);
	emitter->setSpeed(150.0f);
	emitter->setTexture(CCTextureCache::sharedTextureCache()->addImage("fire.png"));
	emitter->setPosition(ccp(size.width/6*3,size.height-150));
	emitter->release();
}

void TestParticle::initSun()
{
	CCParticleSystem *emitter = CCParticleSun::create();
	emitter->retain();
	addChild(emitter,10);
	emitter->setStartSize(20.f);
	emitter->setSpeed(50.f);
	emitter->setTexture(CCTextureCache::sharedTextureCache()->addImage("fire.png"));
	emitter->setPosition(ccp(size.width/6*4,size.height-85));
	emitter->release();
}

void TestParticle::initGalaxy()
{
	CCParticleSystem *emitter = CCParticleGalaxy::create();
	emitter->retain();
	addChild(emitter,10);
	emitter->setStartSize(20.f);
	emitter->setSpeed(50.f);
	emitter->setTexture(CCTextureCache::sharedTextureCache()->addImage("fire.png"));
	emitter->setPosition(ccp(size.width/6*5,size.height-85));
	emitter->release();
}

void TestParticle::initFlower()
{
	CCParticleSystem *emitter = CCParticleFlower::create();
	emitter->retain();
	addChild(emitter,10);
//	emitter->setStartSize(20.f);
	emitter->setSpeed(100.f);
	emitter->setTexture(CCTextureCache::sharedTextureCache()->addImage("stars.png"));
	emitter->setPosition(ccp(size.width/6*1,size.height-250));
	emitter->release();
}

/************************************************************************/
/* 放射式粒子                                                                     */
/************************************************************************/
void TestParticle::initBigFlower()
{
	CCParticleSystem *emitter = new CCParticleSystemQuad();
	addChild(emitter);

	emitter->initWithTotalParticles(50);

	emitter->setTexture( CCTextureCache::sharedTextureCache()->addImage("stars.png") );

	emitter->setDuration(-1);

	// gravity
	emitter->setGravity(CCPointZero);

	// angle
	emitter->setAngle(90);
	emitter->setAngleVar(360);

	// speed of particles
	emitter->setSpeed(160);
	emitter->setSpeedVar(20);

	// radial
	emitter->setRadialAccel(-120);
	emitter->setRadialAccelVar(0);

	// tagential
	emitter->setTangentialAccel(30);
	emitter->setTangentialAccelVar(0);

	// emitter position
	emitter->setPosition( ccp(160,240) );
	emitter->setPosVar(CCPointZero);

	// life of particles
	emitter->setLife(4);
	emitter->setLifeVar(1);

	// spin of particles
	emitter->setStartSpin(0);
	emitter->setStartSizeVar(0);
	emitter->setEndSpin(0);
	emitter->setEndSpinVar(0);

	// color of particles
	ccColor4F startColor = {0.5f, 0.5f, 0.5f, 1.0f};
	emitter->setStartColor(startColor);

	ccColor4F startColorVar = {0.5f, 0.5f, 0.5f, 1.0f};
	emitter->setStartColorVar(startColorVar);

	ccColor4F endColor = {0.1f, 0.1f, 0.1f, 0.2f};
	emitter->setEndColor(endColor);

	ccColor4F endColorVar = {0.1f, 0.1f, 0.1f, 0.2f};
	emitter->setEndColorVar(endColorVar);

	// size, in pixels
	emitter->setStartSize(80.0f);
	emitter->setStartSizeVar(40.0f);
	emitter->setEndSize(kParticleStartSizeEqualToEndSize);

	// emits per second
	emitter->setEmissionRate(emitter->getTotalParticles()/emitter->getLife());

	// additive
	emitter->setBlendAdditive(true);

	emitter->setPosition(ccp(size.width/6*3,size.height-250));
	emitter->release();
}

void TestParticle::initRotFlower()
{
	CCParticleSystem *emitter = new CCParticleSystemQuad();
	emitter->initWithTotalParticles(300);
	//emitter->autorelease();
	addChild(emitter);
	////emitter->release();    // win32 : Remove this line
	emitter->setTexture( CCTextureCache::sharedTextureCache()->addImage("stars2.png"));

	// duration
	emitter->setDuration(-1);

	// gravity
	emitter->setGravity(CCPointZero);

	// angle
	emitter->setAngle(90);
	emitter->setAngleVar(360);

	emitter->setSpeed(160);
	emitter->setSpeedVar(20);

	// radial
	emitter->setRadialAccel(-120);
	emitter->setRadialAccelVar(0);

	// tagential
	emitter->setTangentialAccel(30);
	emitter->setTangentialAccelVar(0);

	// emitter position
	emitter->setPosition( ccp(160,240) );
	emitter->setPosVar(CCPointZero);

	// life of particles
	emitter->setLife(3);
	emitter->setLifeVar(1);

	// spin of particles
	emitter->setStartSpin(0);
	emitter->setStartSpinVar(0);
	emitter->setEndSpin(0);
	emitter->setEndSpinVar(2000);

	ccColor4F startColor = {0.5f, 0.5f, 0.5f, 1.0f};
	emitter->setStartColor(startColor);

	ccColor4F startColorVar = {0.5f, 0.5f, 0.5f, 1.0f};
	emitter->setStartColorVar(startColorVar);

	ccColor4F endColor = {0.1f, 0.1f, 0.1f, 0.2f};
	emitter->setEndColor(endColor);

	ccColor4F endColorVar = {0.1f, 0.1f, 0.1f, 0.2f};
	emitter->setEndColorVar(endColorVar);

	// size, in pixels
	emitter->setStartSize(30.0f);
	emitter->setStartSizeVar(00.0f);
	emitter->setEndSize(kParticleStartSizeEqualToEndSize);

	// emits per second
	emitter->setEmissionRate(emitter->getTotalParticles()/emitter->getLife());

	// additive
	emitter->setBlendAdditive(false);

	emitter->setPosition(ccp(size.width/6*5,size.height-250));
	emitter->release();

}

void TestParticle::initMeteor()
{
	CCParticleSystem *emitter = CCParticleMeteor::create();
	emitter->retain();

	addChild(emitter,10);
	emitter->setTexture(CCTextureCache::sharedTextureCache()->addImage("fire.png"));
	
	emitter->setPosition(ccp(100,50));
	emitter->release();
}

void TestParticle::initSpiral()
{
	CCParticleSystem *emitter = CCParticleSpiral::create();
	emitter->retain();

	addChild(emitter,10);
	emitter->setTexture(CCTextureCache::sharedTextureCache()->addImage("fire.png"));

	emitter->setPosition(ccp(250,50));
	emitter->release();
}

void TestParticle::initExplosion()
{
	CCParticleSystem *emitter = CCParticleExplosion::create();
	emitter->retain();
	addChild(emitter, 10);

	emitter->setTexture( CCTextureCache::sharedTextureCache()->addImage("stars.png") );

	emitter->setAutoRemoveOnFinish(true);

	emitter->setPosition(ccp(400,50));
	emitter->release();
}

void TestParticle::initSnow()
{
	CCParticleSystem *emitter = CCParticleSnow::create();
	emitter->retain();
	addChild(emitter, 10);

	CCPoint p = emitter->getPosition();
	emitter->setPosition( ccp( p.x, p.y-110) );
	emitter->setLife(3);
	emitter->setLifeVar(1);

	// gravity
	emitter->setGravity(ccp(0,-10));

	// speed of particles
	emitter->setSpeed(130);
	emitter->setSpeedVar(30);


	ccColor4F startColor = emitter->getStartColor();
	startColor.r = 0.9f;
	startColor.g = 0.9f;
	startColor.b = 0.9f;
	emitter->setStartColor(startColor);

	ccColor4F startColorVar = emitter->getStartColorVar();
	startColorVar.b = 0.1f;
	emitter->setStartColorVar(startColorVar);

	emitter->setEmissionRate(emitter->getTotalParticles()/emitter->getLife());

	emitter->setTexture( CCTextureCache::sharedTextureCache()->addImage("snow.png"));

	emitter->setPosition(ccp(0,480));
	emitter->release();
}

void TestParticle::initRain()
{
	CCParticleSystem *emitter = CCParticleRain::create();
	emitter->retain();
	addChild(emitter, 10);

	CCPoint p = emitter->getPosition();
	emitter->setPosition( ccp( p.x, p.y-100) );
	emitter->setLife(4);

	emitter->setTexture( CCTextureCache::sharedTextureCache()->addImage("fire.png") );
	emitter->setPosition(ccp(400,50));

	emitter->release();

}