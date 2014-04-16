#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;


class HelloWorld : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);

	CCSprite *spriteWithColor(ccColor4F bgColor, float textureWidth, float textureHeight);
	CCSprite *spriteWithColor(ccColor4F c1,ccColor4F c2,float textureWidth,float textureHeight,int nStripes);
	CCSprite *background;

	ccColor4F randomBrightColor();

	void genBackground();
	void genBackground(int flag);

	void update(float dt);

	virtual void onEnter();
	void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
};

#endif // __HELLOWORLD_SCENE_H__
