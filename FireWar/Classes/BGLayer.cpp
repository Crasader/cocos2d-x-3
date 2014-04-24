#include "BGLayer.h"

CCScene *BGLayer::createScene()
{
    CCScene *scene = NULL;
    scene = CCScene::create();

    BGLayer *bgLayer = BGLayer::create();
    scene->addChild(scene);

    return scene;
}

bool BGLayer::init()
{
    bool bRet = false;
    do
    {
        CC_BREAK_IF(! CCLayer::init());
        CCSize size = CCDirector::sharedDirector()->getWinSize();

        CCSprite* pSprite = CCSprite::create("Background1/Mountain.jpeg");
        CC_BREAK_IF(!pSprite);

        pSprite->setAnchorPoint(ccp(0,0));
        pSprite->setPosition(ccp(0, size.height/2));
        this->addChild(pSprite, 0);


        CCSprite* pSprite2 = CCSprite::create("Background1/Mountain2.jpeg");
        CC_BREAK_IF(! pSprite2);
        pSprite2->setAnchorPoint(ccp(0,0));
        pSprite2->setPosition(ccp(size.width/2-1, size.height/2));
        this->addChild(pSprite2, 0);

        CCSprite* pSprite3 = CCSprite::create("Background1/Mountain.jpeg");
        CC_BREAK_IF(! pSprite3);
        //x=x+size.width;
        pSprite3->setAnchorPoint(ccp(0,0));
        pSprite3->setPosition(ccp(size.width-2, size.height/2));
        this->addChild(pSprite3, 0);

        CCSprite* pSprite4 = CCSprite::create("Background1/Mountain2.jpeg");
        CC_BREAK_IF(! pSprite4);
        pSprite4->setAnchorPoint(ccp(0,0));
        pSprite4->setPosition(ccp((size.width/2)*3-3, size.height/2));
        this->addChild(pSprite4, 0);

        CCSprite* pSprite42 = CCSprite::create("Background1/Mountain.jpeg");
        CC_BREAK_IF(! pSprite42);
        pSprite42->setAnchorPoint(ccp(0,0));
        pSprite42->setPosition(ccp((size.width*2)-4, size.height/2));
        this->addChild(pSprite42, 0);

        CCSprite* pSpritebg = CCSprite::create("Background1/bg.png");
        CC_BREAK_IF(! pSpritebg);
        pSpritebg->setAnchorPoint(ccp(0,0));
        pSpritebg->setPosition(ccp(0, -40));
        this->addChild(pSpritebg, 0);

        CCSprite* pSprite2bg = CCSprite::create("Background1/bg2.png");
        CC_BREAK_IF(! pSprite2bg);
        pSprite2bg->setAnchorPoint(ccp(0,0));
        pSprite2bg->setPosition(ccp((size.width/2)-1, -40));
        this->addChild(pSprite2bg, 0);

        CCSprite* pSprite3bg = CCSprite::create("Background1/bg.png");
        CC_BREAK_IF(! pSprite3bg);
        pSprite3bg->setAnchorPoint(ccp(0,0));
        pSprite3bg->setPosition(ccp(size.width-2, -40));
        this->addChild(pSprite3bg, 0);

        CCSprite* pSprite4bg = CCSprite::create("Background1/bg2.png");
        CC_BREAK_IF(! pSprite4bg);
        pSprite4bg->setAnchorPoint(ccp(0,0));
        pSprite4bg->setPosition(ccp((size.width/2)*3-3, -40));
        this->addChild(pSprite4bg, 0);


        CCSprite* pSprite3bg2 = CCSprite::create("Background1/bg.png");
        CC_BREAK_IF(! pSprite3bg2);
        pSprite3bg2->setAnchorPoint(ccp(0,0));
        pSprite3bg2->setPosition(ccp(size.width*2-4, -40));
        this->addChild(pSprite3bg2, 0);

        CCSprite* pSpritetent = CCSprite::create("Background1/bunker.png");
        CC_BREAK_IF(! pSpritetent);
        pSpritetent->setAnchorPoint(ccp(0,0));
        pSpritetent->setPosition(ccp(-20, size.height/3));
        this->addChild(pSpritetent, 1);

        CCSprite* pSprite2tent = CCSprite::create("Background1/bluetent4.png");
        CC_BREAK_IF(! pSprite2tent);
        pSprite2tent->setAnchorPoint(ccp(0,0));
        pSprite2tent->setPosition(ccp((size.width/2)-60, 60));
        this->addChild(pSprite2tent, 1);


        CCSprite* pSprite3tent = CCSprite::create("Background1/bluetent2tone.png");
        CC_BREAK_IF(! pSprite3tent);
        pSprite3tent->setAnchorPoint(ccp(0,0));
        pSprite3tent->setPosition(ccp(size.width, 60));
        this->addChild(pSprite3tent, 1);

        CCSprite* pSprite4tent = CCSprite::create("Background1/greytent2.png");
        CC_BREAK_IF(! pSprite4tent);
        pSprite4tent->setAnchorPoint(ccp(0,0));
        pSprite4tent->setPosition(ccp((size.width/2)*3, 60));

        CCSprite* jeep = CCSprite::create("Background1/jeep2.png");
        CC_BREAK_IF(! jeep);
        jeep->setAnchorPoint(ccp(0,0));
        jeep->setPosition(ccp(size.width*2-190, size.height/3));
        this->addChild(jeep, 0);

        CCSprite* bunker = CCSprite::create("Background1/bunker.png");
        CC_BREAK_IF(! bunker);
        bunker->setAnchorPoint(ccp(0,0));
        bunker->setPosition(ccp((size.width/2)*3, size.height/3));
        this->addChild(bunker, 1);

        CCSprite* fence  = CCSprite::create("Background1/fence.png");
        CC_BREAK_IF(! fence);
        fence->setAnchorPoint(ccp(0,0));
        fence->setPosition(ccp(size.width/4, size.height/3));
        this->addChild(fence, 3);

        CCSprite* fence2  = CCSprite::create("Background1/fence.png");
        CC_BREAK_IF(! fence2);
        fence2->setAnchorPoint(ccp(0,0));
        fence2->setPosition(ccp(size.width/4+100, size.height/3+10));
        this->addChild(fence2, 3);


        CCSprite* fence3  = CCSprite::create("Background1/fence.png");
        CC_BREAK_IF(! fence3);
        fence3->setAnchorPoint(ccp(0,0));
        fence3->setPosition(ccp((size.width/2)+200, size.height/3-20));
        this->addChild(fence3, 3);

        CCSprite* fire2 = CCSprite::create("Background1/fire1.png");
        CC_BREAK_IF(!fire2);
        fire2->setAnchorPoint(ccp(0,0));
        fire2->setPosition(ccp((size.width/2)+300,size.height/3-60));
        this->addChild(fire2, 9);

        /************************************************************************/
        /* Á£×ÓÏµÍ³                                                              */
        /************************************************************************/
        CCParticleSystem*	m_emitter2;

        m_emitter2 = CCParticleSmoke::create();
        m_emitter2->retain();
        this->addChild(m_emitter2, 10);
        m_emitter2->setStartSize(20.0f);
        m_emitter2->setSpeed(30.0f);
        m_emitter2->setTexture( CCTextureCache::sharedTextureCache()->addImage("Background1/fire.png") );//.pvr"];

        m_emitter2->setPosition( CCPointMake((size.width/2)+350,size.height/3));

        CCSprite* fire = CCSprite::create("Background1/fire1.png");
        CC_BREAK_IF(!fire);
        fire->setAnchorPoint(ccp(0,0));
        fire->setPosition(ccp((size.width/4)-50,size.height/3-60));
        this->addChild(fire, 9);

        CCParticleSystem*	m_emitter;
        CCSprite*m_background;
        m_emitter = CCParticleSmoke::create();
        m_emitter->retain();
        this->addChild(m_emitter, 10);
        m_emitter->setStartSize(20.0f);
        m_emitter->setSpeed(30.0f);
        m_emitter->setTexture( CCTextureCache::sharedTextureCache()->addImage("Background1/fire.png") );

        m_emitter->setPosition( CCPointMake(size.width/4,size.height/3));


        CCSprite* pSprite0tree = CCSprite::create("Background1/tree1.png");
        CC_BREAK_IF(! pSprite0tree);
        pSprite0tree->setAnchorPoint(ccp(0,0));
        pSprite0tree->setPosition(ccp(40, size.height/3-10));
        this->addChild(pSprite0tree, 3);

        CCSprite* pSpritetree = CCSprite::create("Background1/bushytree.png");
        CC_BREAK_IF(! pSpritetree);

        pSpritetree->setAnchorPoint(ccp(0,0));
        pSpritetree->setPosition(ccp(size.width/4, size.height/3));
        this->addChild(pSpritetree, 2);


        CCSprite* pSprite2tree = CCSprite::create("Background1/tree1.png");
        CC_BREAK_IF(! pSprite2tree);
        pSprite2tree->setAnchorPoint(ccp(0,0));

        pSprite2tree->setPosition(ccp((size.width/2)+100, size.height/2-40));

        this->addChild(pSprite2tree, 0);

        CCSprite* pSprite3tree = CCSprite::create("Background1/treetilt.png");
        CC_BREAK_IF(! pSprite3tree);
        pSprite3tree->setAnchorPoint(ccp(0,0));
        pSprite3tree->setPosition(ccp(size.width+50, size.height/3));
        this->addChild(pSprite3tree, 0);


        CCSprite* pSprite31tree = CCSprite::create("Background1/treetilt.png");
        CC_BREAK_IF(! pSprite31tree);
        pSprite31tree->setAnchorPoint(ccp(0,0));
        pSprite31tree->setPosition(ccp((size.width/2)*3-70, size.height/3));
        this->addChild(pSprite31tree, 0);

        CCSprite* pSprite4tree = CCSprite::create("Background1/tree1.png");
        CC_BREAK_IF(! pSprite4tree);
        pSprite4tree->setAnchorPoint(ccp(0,0));
        pSprite4tree->setPosition(ccp((size.width/2)*3-40, size.height/3));
        this->addChild(pSprite4tree, 1);


        CCSprite* pSprite41tree = CCSprite::create("Background1/treetilt.png");
        CC_BREAK_IF(! pSprite41tree);
        pSprite41tree->setAnchorPoint(ccp(0,0));
        pSprite41tree->setPosition(ccp(size.width*2-70, size.height/3));
        this->addChild(pSprite41tree, 1);

        CCSprite* pSprite5tree = CCSprite::create("Background1/tree1.png");
        CC_BREAK_IF(! pSprite5tree);
        pSprite5tree->setAnchorPoint(ccp(0,0));
        pSprite5tree->setPosition(ccp(size.width*2-40, size.height/3));
        this->addChild(pSprite5tree, 0);
        this->setTouchEnabled(true);

        bRet = true;
    } while (0);

    return bRet;
}

void BGLayer::menuCloseCallback(CCObject* pSender)
{


}

void BGLayer::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{


}
