#ifndef LEVEL_SCENE_H
#define LEVEL_SCENE_H

#include "cocos2d.h"

USING_NS_CC;

class LevelScene : public CCScene
{
public:
	LevelScene();
	~LevelScene();


	CREATE_FUNC(LevelScene);
	virtual bool init();
	void setPlayerType(int type ,int level);
	
	//定义一个CClayer的对象，名字为layer，取得该对象的方法为getLayer
	CC_SYNTHESIZE_READONLY(CCLayer*,layer,Layer);
	/*展开的代码如下
	protected: int nTest; 
	public: virtual nTest getTest(void) const { return nTest; } 
	public: virtual void setTest(int var){ nTest = var; }  
	*/
	CC_SYNTHESIZE(int, pt, PT);
	CC_SYNTHESIZE(int, lt, LT);
};


#endif