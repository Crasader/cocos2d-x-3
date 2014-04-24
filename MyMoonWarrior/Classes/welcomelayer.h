#ifndef WELCOME_LAYER_H
#define WELCOME_LAYER_H

#include "cocos2d.h"
#include "BaserLayer.h"

USING_NS_CC;

class WelcomeLayer : public BaserLayer
{
	public:
		WelcomeLayer();
		~WelcomeLayer();

		virtual bool init();
	
		virtual void onEnter();

		static CCScene* scene();

		CREATE_FUNC(WelcomeLayer);

		void setViews();

		void startGameCallback(CCObject *sender ); 
		void aboutGameCallback(CCObject *sender );
		void optionGameCallback(CCObject *sender );
};

#endif
