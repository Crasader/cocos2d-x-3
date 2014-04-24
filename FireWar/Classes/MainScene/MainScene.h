#ifndef MAIN_SCENE_H
#define MAIN_SCENE_H

#include "cocos2d.h"

USING_NS_CC;

class MainLayer : public CCLayer
{
	public:
		MainLayer();
		~MainLayer();

		virtual bool init();

		static CCScene * createScene();

		CREATE_FUNC(MainLayer);

		void startCallback(CCObject *psender);
};


#endif
