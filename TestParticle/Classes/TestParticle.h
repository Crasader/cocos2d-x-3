#ifndef TEST_PARTICLE
#define TEST_PARTICLE

#include "cocos2d.h"

USING_NS_CC;

class TestParticle : public CCLayer
{
public:
	TestParticle();
	~TestParticle();
	virtual bool init();

	CREATE_FUNC(TestParticle);
	static CCScene *createScene();

	CCSize size;
	void initSmoke();
	void initFirework();
	void initFire();
	void initSun();
	void initGalaxy();
	void initFlower();
	void initBigFlower();
	void initRotFlower();
	void initMeteor();
	void initSpiral();
	void initExplosion();
	void initSnow();
	void initRain();

};


#endif