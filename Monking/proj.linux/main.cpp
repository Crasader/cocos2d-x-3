#include "../Classes/AppDelegate.h"
#include "cocos2d.h"
#include "CCEGLView.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string>

USING_NS_CC;

int main(int argc, char **argv)
{
    // create the application instance
    AppDelegate app;
/*
    CCSize frameSize = CCEGLView::sharedOpenGLView()->getFrameSize();
    // 设置 LsSize 固定值
    CCSize lsSize = CCSizeMake(480, 320);
 
	CCLog("%f\t%f\t",frameSize.width,frameSize.height);

    float scaleX = (float) frameSize.width / lsSize.width;
    float scaleY = (float) frameSize.height / lsSize.height;
    
    // 定义 scale 变量
    float scale = 0.0f; // MAX(scaleX, scaleY);
    if (scaleX > scaleY) {
        // 如果是 X 方向偏大，那么 scaleX 需要除以一个放大系数，放大系数可以由枞方向获取，
        // 因为此时 FrameSize 和 LsSize 的上下边是重叠的
        scale = scaleX / (frameSize.height / (float) lsSize.height);
    } else {
        scale = scaleY / (frameSize.width / (float) lsSize.width);
    }
    
    CCLog("x: %f; y: %f; scale: %f", scaleX, scaleY, scale);
    
    // 根据 LsSize 和屏幕宽高比动态设定 WinSize
    CCEGLView::sharedOpenGLView()->setDesignResolutionSize(lsSize.width * scale,
                                                           lsSize.height * scale, kResolutionNoBorder);
*/

    CCEGLView* eglView = CCEGLView::sharedOpenGLView();
//    eglView->setFrameSize(800, 325);
//	eglView->setDesignResolutionSize(800,480,kResolutionShowAll);

	eglView->setFrameSize(480,320);
    return CCApplication::sharedApplication()->run();
}
