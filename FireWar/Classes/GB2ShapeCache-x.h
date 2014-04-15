#ifndef GB2_SHAPE_CACHE_X_H
#define GB2_SHAPE_CACHE_X_H

#include "cocos2d.h"

class BodyDef;
class b2Body;

namespace cocos2d {
class GB2ShapeCache {
public:
    // Static interface
    static GB2ShapeCache* sharedGB2ShapeCache(void);

public:
    bool init();
    //void addShapesWithFile(const std::string &plist);
    //void addShapesWithFile(const std::string &plist,int flag);
    void addShapesWithFile(const char *plist);
    void addFixturesToBody(b2Body *body, const std::string &shape,bool  isCollied);
    cocos2d::CCPoint anchorPointForShape(const std::string &shape);
    void reset();
    float getPtmRatio() {
        return ptmRatio;
    }
    ~GB2ShapeCache() {}

private:
    std::map<std::string, BodyDef *> shapeObjects;
    GB2ShapeCache(void) {}
    float ptmRatio;
};
}

#endif