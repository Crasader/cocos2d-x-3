#ifndef MENU_LAYER_H
#define MENU_LAYER_H

#include "cocos2d.h"

USING_NS_CC;


class MenuLayer : public CCLayer
{
	public:
		MenuLayer();
		~MenuLayer();

		CREATE_FUNC(MenuLayer);

		virtual bool init();

		void setBackgroundImage(const char *image);
		static CCScene *menuScene ;

		static CCScene *createScene();

		void menuCallbackPlay(CCObject *sender);
		void menuCallbackSetting(CCObject *sender);
		void menuCallbackQuit(CCObject *sender);

		virtual void keyBackClicked();

};


#endif
