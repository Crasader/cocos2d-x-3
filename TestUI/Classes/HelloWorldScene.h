#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "CocoStudio/GUI/System/CocosGUI.h"

USING_NS_CC;

using namespace cocos2d::extension;
using namespace ui;


class HelloWorld : public cocos2d::CCLayer
{
public:
	virtual ~HelloWorld();
    virtual bool init();  

    static cocos2d::CCScene* scene();
    
    void menuCloseCallback(CCObject* pSender);
    
    CREATE_FUNC(HelloWorld);
	
	UILayer *uiLayer;
	Layout *widget;
	UILabel* alert;

	CCSize size;

	void backCallback(CCObject *obj,TouchEventType type);
	void leftCallback(CCObject *obj,TouchEventType type);
	void middleCallback(CCObject *obj,TouchEventType type);
	void rightCallback(CCObject *obj,TouchEventType type);
};

#endif // __HELLOWORLD_SCENE_H__
