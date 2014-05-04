#include<unistd.h>
#include "ThreadLayer.h"
#include "pthread.h"

static int num = 100;

static pthread_mutex_t mutex;

bool ThreadLayer::init()
{
	if(!CCLayerColor::initWithColor(ccc4(0,0,0,0)))
		return false;
	
	count = 0;

	pthread_t pthread;
	pthread_attr_t tattr;

	pthread_attr_init(&tattr);
	pthread_mutex_init(&mutex,NULL);

	pthread_attr_setdetachstate(&tattr,PTHREAD_CREATE_DETACHED);  //PTHREAD_CREATE_DETACHED分离线程。调用完成即销毁
	pthread_create(&pthread,&tattr,pthread_func1,this);

	pthread_t pthread2;
	pthread_create(&pthread2,NULL,pthread_func2,this);  

	CCTextureCache::sharedTextureCache()->addImageAsync("ui_text.png",this,callfuncO_selector(ThreadLayer::showSprite));

	size = CCDirector::sharedDirector()->getWinSize();

	bg = CCSprite::create("loadingBg.png");
	bg->setAnchorPoint(CCPointZero);
	bg->setPosition(CCPointZero);
	addChild(bg);

	progressBg = CCSprite::create("loadingProgress_Bg.png");
	progressBg->setAnchorPoint(CCPointZero);
	progressBg->setPosition(ccp(size.width/3-50,size.height/2-50));

	progress = CCProgressTimer::create(CCSprite::create("loadingProgress.png"));
	progress->setType(kCCProgressTimerTypeBar);
	progress->setMidpoint(ccp(0,0));
	progress->setBarChangeRate(ccp(1,0));
	progress->setAnchorPoint(CCPointZero);
	progress->setPosition(ccp(size.width/3-50,size.height/2-50));
	bg->addChild(progress,2);
	bg->addChild(progressBg,1);
	
	imageArray.push_back("login_bg.png");
	imageArray.push_back("login_bg.png");
	imageArray.push_back("login_bg.png");
	imageArray.push_back("login_bg.png");
	imageArray.push_back("login_bg.png");
	imageArray.push_back("login_bg.png");

	printf("%g\n",1/15);

	setProgress(0,0);
	
	CCNotificationCenter::sharedNotificationCenter()->addObserver(this,callfuncO_selector(ThreadLayer::test),"test",NULL);	

	return true;
}

CCScene * ThreadLayer::createScene()
{
	CCScene *scene = NULL;

	scene = CCScene::create();
	
	ThreadLayer *layer = ThreadLayer::create();

	scene->addChild(layer);

	return scene;
}

void * ThreadLayer::pthread_func1(void *arg)
{
	while(num >0)
	{
		pthread_mutex_lock(&mutex);
		num--;
		CCLog("pthread fun:%d", num);
		pthread_mutex_unlock(&mutex);
		sleep(1);
	}
	return  NULL;
}

void * ThreadLayer::pthread_func2(void *arg)
{
	while(num >0)
	{
		pthread_mutex_lock(&mutex);
		num--;
		CCLog("pthread fun2:%d", num);
		pthread_mutex_unlock(&mutex);
		sleep(1);
	}

	return  NULL;
}

void ThreadLayer::showSprite(CCObject *obj)
{

	CCLog("loading...\n");
	CCTexture2D *text_ui_text = (CCTexture2D *)obj;
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ui_text.plist",text_ui_text);
	
	CCSize size = CCDirector::sharedDirector()->getWinSize();

	CCSprite *raffle = CCSprite::createWithSpriteFrameName("raffle_b_friend.png");
	raffle->setPosition(ccp(size.width/2,20));
	addChild(raffle);
}

void ThreadLayer::setProgress(int percents,int max)
{
	if(imageArray.size() ==0 ||count==imageArray.size()-1)
	{
		return ;
	}
	else
	{
		count++;
	}

	CCTextureCache::sharedTextureCache()->addImageAsync(imageArray.at(count).c_str(),this,callfuncO_selector(ThreadLayer::setProgress));

	progress->stopAllActions();
	CCProgressTo *to2 = CCProgressTo::create(1,20*count);
	to2->setTag(20);
	
	CCCallFunc *func = CCCallFunc::create(this,callfunc_selector(ThreadLayer::loadingFinish));
	CCSequence *seq = CCSequence::create(to2,func,NULL);
	progress->runAction(seq);
	
}

void ThreadLayer::loadingFinish()
{
	if(count == imageArray.size()-1)
	{
		CCLog("finish\n");
		CCNotificationCenter::sharedNotificationCenter()->postNotification("test", this);
	}
}

void ThreadLayer::test(CCObject *obj)
{
	CCLog("**********************\n");
}
