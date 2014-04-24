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

BUG 1����ͼ��ÿ��ͼ��֮����һЩϸ�ܵļ�����ر��ǳ����ƶ�ʱ�������ԣ�����Ϸ��ͼ�Ŵ󣬿��Ժ����Կ������ϸ��
���������ͨ������ccConfo.h�е�CC_FIX_ARTIFACTS_BY_STRECHING_TEXEL���������
��  #define CC_FIX_ARTIFACTS_BY_STRECHING_TEXEL 0  
��Ϊ #define CC_FIX_ARTIFACTS_BY_STRECHING_TEXEL 1
ccConfig.hλ�ã�/cocos2dx/include/ccConfig.h
�������ԭ���ǽ���ͼ�����÷�Χ�ĳ�99%����������ı��εķ�Χ��СһȦ

BUG2: �����������������е�ͼ�ᶶ��
������������ǿ���ͨ����TiledMap��ÿ��ͼ��������������Ч��������������
����������£�
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