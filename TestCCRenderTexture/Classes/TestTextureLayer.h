#ifndef  TEST_TEXTURE_H
#define  TEST_TEXTURE_H

#include "cocos2d.h"


USING_NS_CC;


class TestTextureLayer : public CCLayer
{
	public:
		virtual ~TestTextureLayer();

		virtual bool init();
		
		CREATE_FUNC(TestTextureLayer);

		static CCScene *createScene();

};

#endif
