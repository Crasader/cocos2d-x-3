#include "HelloWorldScene.h"


USING_NS_CC;

CCScene* HelloWorld::scene()
{
    CCScene *scene = CCScene::create();

    HelloWorld *layer = HelloWorld::create();

    scene->addChild(layer);

    return scene;
}

bool HelloWorld::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }

    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                      "CloseNormal.png",
                                      "CloseSelected.png",
                                      this,
                                      menu_selector(HelloWorld::menuCloseCallback));

    pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));

    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);

    CCSize size = CCDirector::sharedDirector()->getWinSize();

#if 0
    CCLayerColor *colorLayer = CCLayerColor::create(ccc4(0,80,80,255));
    addChild(colorLayer);

    CCSprite *spr_premulti = CCSprite::create("Ball.png");
    spr_premulti->setPosition(ccp(16,48));

    CCSprite *spr_nonpremulti = CCSprite::create("Ball.png");
    spr_nonpremulti->setPosition(ccp(16,16));


    CCRenderTexture *rend = CCRenderTexture::create(32, 64, kCCTexture2DPixelFormat_RGBA8888);

    if (rend == NULL)
        exit(0);

    rend->begin();
    spr_premulti->visit();
    spr_nonpremulti->visit();
    rend->end();

    addChild(spr_nonpremulti);
    addChild(spr_premulti);
    addChild(rend);
#endif

	scheduleUpdate();

    return true;
}


void HelloWorld::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
    CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}


CCSprite *HelloWorld::spriteWithColor(ccColor4F bgColor, float textureWidth, float textureHeight)
{
    CCRenderTexture *rt = CCRenderTexture::create(textureWidth,textureHeight);

    rt->beginWithClear(bgColor.r, bgColor.g, bgColor.b, bgColor.a);

    this->setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionColor));

    CC_NODE_DRAW_SETUP();

    // 3: Draw into the texture
    float gradientAlpha = 0.7f;
    CCPoint vertices[4];
    ccColor4F colors[4];
    int nVertices = 0;

    /**
      *矩形的四个顶点(0,0) (1,0) ,(0,1) ,(1,1)
      *
      */

    vertices[nVertices] = CCPointMake(0, 0);
    colors[nVertices++] = ccc4f(0, 0, 0, 0);
    vertices[nVertices] = CCPointMake(textureWidth, 0);
    colors[nVertices++] = ccc4f(0, 0, 0, 0);
    vertices[nVertices] = CCPointMake(0, textureHeight);
    colors[nVertices++] = ccc4f(0, 0, 0, gradientAlpha);
    vertices[nVertices] = CCPointMake(textureWidth, textureHeight);
    colors[nVertices++] = ccc4f(0, 0, 0, gradientAlpha);

    ccGLEnableVertexAttribs(kCCVertexAttribFlag_Position | kCCVertexAttribFlag_Color);

    glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, vertices);
    glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_FLOAT, GL_FALSE, 0, colors);
    glBlendFunc(CC_BLEND_SRC, CC_BLEND_DST);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, (GLsizei)nVertices);

	nVertices = 0;

	vertices[nVertices] = ccp(0, 0);
	colors[nVertices++] = ccc4f(0, 0, 0, 0);

	vertices[nVertices] = ccp(textureWidth, 0);
	colors[nVertices++] = ccc4f(0, 0, 0, 0);

	vertices[nVertices] = ccp(0, textureHeight);
	colors[nVertices++] = ccc4f(0, 0, 0, gradientAlpha);

	vertices[nVertices] = ccp(textureWidth, textureHeight);
	colors[nVertices++] = ccc4f(0, 0, 0, gradientAlpha);

	glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, vertices);
	glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_FLOAT, GL_TRUE, 0, colors);
	glBlendFunc(CC_BLEND_SRC, CC_BLEND_DST);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, (GLsizei)nVertices);

	// Layer 3: top highlight
	float borderHeight = textureHeight / 16;
	float borderAlpha = 0.3f;
	nVertices = 0;

	vertices[nVertices] = ccp(0, 0);
	colors[nVertices++] = ccc4f(1, 1, 1, borderAlpha);

	vertices[nVertices] = ccp(textureWidth, 0);
	colors[nVertices++] = ccc4f(1, 1, 1, borderAlpha);

	vertices[nVertices] = ccp(0, borderHeight);
	colors[nVertices++] = ccc4f(0, 0, 0, 0);

	vertices[nVertices] = ccp(textureWidth, borderHeight);
	colors[nVertices++] = ccc4f(0, 0, 0, 0);

	glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, vertices);
	glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_FLOAT, GL_TRUE, 0, colors);
	glBlendFunc(CC_BLEND_SRC, CC_BLEND_DST);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, (GLsizei)nVertices);


    CCSprite *noise = CCSprite::create("Noise.png");
    ccBlendFunc blendFunc = {GL_DST_COLOR, GL_ZERO};
    noise->setBlendFunc(blendFunc);
    noise->setPosition(ccp(textureWidth / 2, textureHeight / 2));
    noise->visit();

    rt->end();


    return CCSprite::createWithTexture(rt->getSprite()->getTexture());

}


CCSprite *HelloWorld::spriteWithColor(ccColor4F c1, ccColor4F c2, float textureWidth, float textureHeight, int nStripes)
{
    CCRenderTexture *rt = CCRenderTexture::create(textureWidth, textureHeight);

    // 2: Call CCRenderTexture:begin
    rt->beginWithClear(c1.r, c1.g, c1.b, c1.a);

    // 3: Draw into the texture
    this->setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionColor));
    CC_NODE_DRAW_SETUP();

    // Layer 1: Stripes
    CCPoint *vertices = new CCPoint[nStripes * 6];
    ccColor4F *colors = new ccColor4F[nStripes * 6];

    int nVertices = 0;
    float x1 = -textureHeight;
    float x2;
    float y1 = textureHeight;
    float y2 = 0;
    float dx = textureWidth / nStripes * 2;
    float stripeWidth = dx / 2;
    for (int i = 0; i < nStripes; ++i)
    {
        x2  = x1 + textureHeight;

        vertices[nVertices] = ccp(x1, y1);
        colors[nVertices++] = ccc4f(c2.r, c2.g, c2.b, c2.a);

        vertices[nVertices] = ccp(x1 + stripeWidth, y1);
        colors[nVertices++] = ccc4f(c2.r, c2.g, c2.b, c2.a);

        vertices[nVertices] = ccp(x2, y2);
        colors[nVertices++] = ccc4f(c2.r, c2.g, c2.b, c2.a);

        vertices[nVertices] = vertices[nVertices - 2];
        colors[nVertices++] = ccc4f(c2.r, c2.g, c2.b, c2.a);

        vertices[nVertices] = vertices[nVertices - 2];
        colors[nVertices++] = ccc4f(c2.r, c2.g, c2.b, c2.a);

        vertices[nVertices] = ccp(x2 + stripeWidth, y2);
        colors[nVertices++] = ccc4f(c2.r, c2.g, c2.b, c2.a);
        x1 += dx;
    }

    ccGLEnableVertexAttribs(kCCVertexAttribFlag_Position | kCCVertexAttribFlag_Color);
    glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, vertices);
    glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_FLOAT, GL_TRUE, 0, colors);
    glDrawArrays(GL_TRIANGLES, 0, (GLsizei)nVertices);

    CC_SAFE_DELETE_ARRAY(vertices);
    CC_SAFE_DELETE_ARRAY(colors);

    // Layer 4: Noise
    CCSprite *noise = CCSprite::create("Noise.png");
    ccBlendFunc blendFunc = {GL_DST_COLOR, GL_ZERO};
    noise->setBlendFunc(blendFunc);
    noise->setPosition(ccp(textureWidth / 2, textureHeight / 2));
    noise->visit();

    // 4: Call CCRenderTexture:end
    rt->end();

    // 5: Create a new Sprite from the texture
    return CCSprite::createWithTexture(rt->getSprite()->getTexture());
}



ccColor4F HelloWorld::randomBrightColor()
{
    while (true)
    {
        float requiredBrightness = 192;
        ccColor4B randomColor = ccc4(rand() % 255,
                                     rand() % 255,
                                     rand() % 255,
                                     255);

        if (randomColor.r > requiredBrightness ||
                randomColor.g > requiredBrightness ||
                randomColor.b > requiredBrightness)
        {
            return ccc4FFromccc4B(randomColor);
        }

    }
}


void HelloWorld::genBackground()
{

    if (background)
    {
        background->removeFromParentAndCleanup(true);
    }

    ccColor4F bgColor = this->randomBrightColor();
    background = this->spriteWithColor(bgColor, 512,512);

    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    background->setPosition(ccp(winSize.width / 2, winSize.height / 2));
    this->addChild(background, -1);
}

void HelloWorld::genBackground(int flag)
{
	if(background)
	{
		background->removeFromParentAndCleanup(true);		
	}

	ccColor4F bgColor = this->randomBrightColor();
	
	ccColor4F color2 = this->randomBrightColor();
	
	//_background = this->spriteWithColor(bgColor, 512, 512);
	
	int nStripes = ((rand() % 4) + 1) * 2;	
	background = this->spriteWithColor(bgColor, color2, 512, 512, nStripes);

//	this->setScale(0.5f);

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	
	background->setPosition(ccp(winSize.width / 2, winSize.height / 2));	

	ccTexParams tp = {GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT};
	background->getTexture()->setTexParameters(&tp);
	this->addChild(background);
}

void HelloWorld::onEnter()
{
    CCLayer::onEnter();
    this->genBackground(0);
    this->setTouchEnabled(true);
}

void HelloWorld::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
    this->genBackground(0);
}


void HelloWorld::update(float dt)
{
	float PIXELS_PER_SECOND = 100;
	static float offset = 0;	
	offset += PIXELS_PER_SECOND * dt;

	CCSize textureSize = background->getTextureRect().size;
	background->setTextureRect(CCRectMake(offset, 0, textureSize.width, textureSize.height));
}



