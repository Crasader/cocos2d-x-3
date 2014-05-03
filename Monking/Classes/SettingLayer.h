#ifndef SETTING_LAYER_H
#define SETTING_LAYER_H

#include "cocos2d.h"

USING_NS_CC;

class SettingLayer : public  CCLayer
{
	public:
		SettingLayer();
		~SettingLayer();

		virtual bool init();

		CREATE_FUNC(SettingLayer);

		static CCScene *settingScene;
		static CCScene *createScene();

		void menuCallbackToggle(CCObject *sender);
		void menuCallbackEffectToggle(CCObject *sender);
		void menuCallbackBack(CCObject *sender);

		void keyBackClicked();
};


#endif
