#ifndef _OPTION_LAYER_H
#define _OPTION_LAYER_H

#include "BaserLayer.h"


USING_NS_CC;

class OptionLayer : public BaserLayer
{
	public:
		OptionLayer();
		~OptionLayer();

		virtual bool init();

		CREATE_FUNC(OptionLayer);

		static CCScene *scene();

		void setViews();

		void music_triggerCallback(CCObject *obj);
		void backCallback(CCObject *obj);
};

#endif
