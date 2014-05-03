#ifndef HUB_LAYER
#define HUB_LAYER

#include "cocos2d.h"
#include "SimpleDpad.h"

USING_NS_CC;

class HubLayer : public CCLayer
{
public:
	HubLayer();
	~HubLayer();

	CREATE_FUNC(HubLayer);

	SimpleDpad *simpleDpad ;

	virtual bool init();

//	void menuCallbackBack(CCObject *sender);

	void update(float delta);
};

#endif
