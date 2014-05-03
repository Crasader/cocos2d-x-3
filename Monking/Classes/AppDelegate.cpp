#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "GameScene.h"
#include "config.h"
#include "MenuLayer.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

using namespace CocosDenshion;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

    pDirector->setOpenGLView(pEGLView);

	/*
//	CCSize frameSize = CCEGLView::sharedOpenGLView()->getWinSize();
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	// 设置 LsSize 固定值
	// CCSize lsSize = CCSizeMake(480, 320);
	CCLog("winSize = \t%f\t%f\n",winSize.width,winSize.height);
	CCSize frameSize =  CCEGLView::sharedOpenGLView()->getFrameSize();
	CCLog("frameSize = \t%f\t%f\n",frameSize.width,frameSize.height);
*/

	CCSize frameSize = CCEGLView::sharedOpenGLView()->getFrameSize();
	// 设置 LsSize 固定值
	CCSize lsSize = CCSizeMake(480, 320);
	  
  	float scaleX = (float) frameSize.width / lsSize.width;
	float scaleY = (float) frameSize.height / lsSize.height;

	//   // 定义 scale 变量

	float scale = 0.0f; // MAX(scaleX, scaleY);
	if (scaleX > scaleY) {
		//       // 如果是 X 方向偏大，那么 scaleX 需要除以一个放大系数，放大系数可以由枞方向获取，
		//           // 因为此时 FrameSize 和 LsSize 的上下边是重叠的
		scale = scaleX / (frameSize.height / (float) lsSize.height);
	} else {
		scale = scaleY / (frameSize.width / (float) lsSize.width);
	}

	CCLog("x: %f; y: %f; scale: %f", scaleX, scaleY, scale);

	// 根据 LsSize 和屏幕宽高比动态设定 WinSize
	CCEGLView::sharedOpenGLView()->setDesignResolutionSize(lsSize.width * scale,
			lsSize.height * scale, kResolutionNoBorder);

	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("latin_industries.wav");
	//SimpleAudioEngine::sharedEngine()->playBackgroundMusic("latin_industries.wav");
	SimpleAudioEngine::sharedEngine()->preloadEffect("pd_hit0.wav");
	SimpleAudioEngine::sharedEngine()->preloadEffect("pd_hit1.wav");
	SimpleAudioEngine::sharedEngine()->preloadEffect("pd_herodeath.wav");
	SimpleAudioEngine::sharedEngine()->preloadEffect("pd_botdeath.wav");



	CCScene *pScene = MenuLayer::createScene();

    // run
    pDirector->runWithScene(pScene);



    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->stopAnimation();

#ifdef DEBUG
	CCLOG("******************************1\n");

	CCDirector::sharedDirector()->pause();

	if(SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying())
	{
		SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
	}

#endif


    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();

#ifdef DEBUG
	CCLOG("******************************2\n");

	CCDirector::sharedDirector()->resume();
	if(!SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying())
	{
		SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
	}


#endif

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
