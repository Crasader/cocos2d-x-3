#include "aboutlayer.h"
#include "welcomelayer.h"

AboutLayer::AboutLayer()
{
}

AboutLayer::~AboutLayer()
{
}

/**
 *初始化方法
 */
bool AboutLayer::init()
{
	bool sRect = false;

	do
	{
		CC_BREAK_IF(!BaserLayer::init());

		setViews();

		sRect = true;

	}while(0);

	return sRect;
}

void AboutLayer::setViews()
{
	setBackGroundImage("loading.png");

	CCSprite *title = CCSprite::create("menuTitle.png",CCRectMake(0,38,138,30));
	title->setAnchorPoint(ccp(0.5,1));
	title->setPosition(ccp(getWinSize().width/2,getWinSize().height-20));

	this->addChild(title);

	CCLabelBMFont *des = CCLabelBMFont::create("this Gmae is recorded by Study","arial-14.fnt");
	des->setPosition(ccp(getWinSize().width/2,getWinSize().height/2));

	this->addChild(des);

	CCLabelBMFont *back = CCLabelBMFont::create("back","arial-14.fnt");

	back->setScale(1.25f);
	CCMenuItemLabel *backLable =  CCMenuItemLabel::create(back,this,menu_selector(AboutLayer::backCallback));
	backLable->setAnchorPoint(ccp(0.5,1));
	backLable->setPosition(ccp(getWinSize().width/2,30));

	CCMenu *menu = CCMenu::create(backLable,NULL);
	menu->setPosition(CCPointZero);

	this->addChild(menu);


}

CCScene * AboutLayer::scene()
{
	CCScene *scene = NULL;

	do
	{
		scene = CCScene::create();
		CC_BREAK_IF(!scene);

		AboutLayer *layer = AboutLayer::create();
		CC_BREAK_IF(!layer);

		scene->addChild(layer);

	}while(0);

	return scene;
}

void AboutLayer::backCallback(CCObject *sender )
{
	CCLog("stratGame");

	CCDirector::sharedDirector()->pushScene(CCTransitionFade::create(0.5f, WelcomeLayer::scene() ));

}


