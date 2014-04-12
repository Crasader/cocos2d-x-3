#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class HelloWorld : public cocos2d::CCLayer
{
public:
	HelloWorld();
	virtual ~HelloWorld();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);

	CCTMXTiledMap *map;
	CCSprite *player;
	CCSprite *waterMelon1;
	CCSprite *waterMelon2;
	CCSprite *waterMelon3;
	CCTMXLayer *mapLayer;
	CCTMXLayer *foreground;
//	CC_SYNTHESIZE_RETAIN(CCTMXLayer*, foreground, Foreground);
	void setViewpointCenter(CCPoint point);

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	void registerWithTouchDispatcher();
	void setPlayerPosition(CCPoint position);
	CCPoint tileCoordForPosition(CCPoint position);

	int count;

};

#endif // __HELLOWORLD_SCENE_H__


/*

BUG 1：地图的每个图块之间有一些细密的间隔，特别是场景移动时更加明显，将游戏截图放大，可以很明显看到这个细线
解决方案：通过设置ccConfo.h中的CC_FIX_ARTIFACTS_BY_STRECHING_TEXEL宏来解决。
将  #define CC_FIX_ARTIFACTS_BY_STRECHING_TEXEL 0  
改为 #define CC_FIX_ARTIFACTS_BY_STRECHING_TEXEL 1
ccConfig.h位置：/cocos2dx/include/ccConfig.h
解决大致原理是将贴图的适用范围改成99%，将纹理的四边形的范围缩小一圈

BUG2: 场景发生滚动过程中地图会抖动
解决方案：我们可以通过给TiledMap的每个图层的纹理开启抗锯齿效果来解决这个问题
具体代码如下：
CCArray *pChildrenArray = map->getChildren();
CCSpriteBatchNode *child = NULL;
CCObject *pObject = NULL;
CCARRAY_FOREACH(pChildrenArray,pObject){
child = (CCSpriteBatchNode *)pObject;
if(!child)
break;
child->getTexture()->setAntiAliasTexParameters();
}


*/