#ifndef ABOUT_LAYER_H
#define ABOUT_LAYER_H

#include "cocos2d.h"
#include "BaserLayer.h"

USING_NS_CC;

class AboutLayer : public BaserLayer
{
	public:
		AboutLayer();
		~AboutLayer();

		virtual bool init();

		static CCScene* scene();

		CREATE_FUNC(AboutLayer);

		void setViews();

		void backCallback(CCObject *sender ); 
};

#endif
