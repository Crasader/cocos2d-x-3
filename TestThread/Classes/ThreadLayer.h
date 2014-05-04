#ifndef THREAD_LAYER_H
#define THREAD_LAYER_H

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

using namespace std;

class ThreadLayer : public CCLayerColor
{
	public:
		static CCScene *createScene();
		virtual bool  init();
		CREATE_FUNC(ThreadLayer);

		static void * pthread_func1(void *arg);
		static void * pthread_func2(void *arg);
		void showSprite(CCObject *obj);

		CCSize size;

		CCSprite *bg;
		CCSprite *progressBg;
		CCProgressTimer *progress;
		void setProgress(int percents,int max);
		vector<string> imageArray;
		int count ;
		void loadingFinish();
		void test(cocos2d::CCObject *obj);
};

#endif
