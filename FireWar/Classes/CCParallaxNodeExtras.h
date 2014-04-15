#ifndef CCPARALLAX_NODE_EXTRAS_H
#define CCPARALLAX_NODE_EXTRAS_H

#include "cocos2d.h"

USING_NS_CC;

class CCParallaxNodeExtras : public CCParallaxNode {

public :
    CCParallaxNodeExtras() ;
    static CCParallaxNodeExtras * node() ;
    void incrementOffset(CCPoint offset,CCNode* node) ;
} ;

#endif