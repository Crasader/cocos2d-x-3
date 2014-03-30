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
	
	//����һ��CClayer�Ķ�������Ϊlayer��ȡ�øö���ķ���ΪgetLayer
	CC_SYNTHESIZE_READONLY(CCLayer*,layer,Layer);
	/*չ���Ĵ�������
	protected: int nTest; 
	public: virtual nTest getTest(void) const { return nTest; } 
	public: virtual void setTest(int var){ nTest = var; }  
	*/
	CC_SYNTHESIZE(int, pt, PT);
	CC_SYNTHESIZE(int, lt, LT);
};


#endif