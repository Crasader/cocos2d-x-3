#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "CocoStudio/GUI/System/CocosGUI.h"

USING_NS_CC;
using namespace cocos2d::extension;
using namespace cocos2d::extension;
using namespace ui;
class HelloWorld : public cocos2d::CCLayer
{
public:
	virtual ~HelloWorld();
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);
	CCArmature *armature ;
	void initControlMenu();
	CCSize size;

	void buttonCallback(CCObject *sender);
	void button1Callback(CCObject *sender);
	void button2Callback(CCObject *sender);
	void button3Callback(CCObject *sender);

};

#endif // __HELLOWORLD_SCENE_H__
