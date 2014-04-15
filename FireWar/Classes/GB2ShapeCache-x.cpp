#include "GB2ShapeCache-x.h"
#include "Box2D/Box2D.h"
#include "cocoa/CCNS.h"

using namespace cocos2d;

/**
 * Internal class to hold the fixtures
 */
class FixtureDef {
public:
    FixtureDef()
            : next(NULL) {}

    ~FixtureDef() {
        delete next;
        delete fixture.shape;
    }

    FixtureDef *next;
    b2FixtureDef fixture;
    int callbackData;
};

class BodyDef {
public:
    BodyDef()
            : fixtures(NULL) {}

    ~BodyDef() {
        if (fixtures)
            delete fixtures;
    }

    FixtureDef *fixtures;
    CCPoint anchorPoint;
};

static GB2ShapeCache *_sharedGB2ShapeCache = NULL;

GB2ShapeCache* GB2ShapeCache::sharedGB2ShapeCache(void) {
    if (!_sharedGB2ShapeCache) {
        _sharedGB2ShapeCache = new GB2ShapeCache();
        _sharedGB2ShapeCache->init();
    }

    return _sharedGB2ShapeCache;
}

bool GB2ShapeCache::init() {
    return true;
}

void GB2ShapeCache::reset() {
    std::map<std::string, BodyDef *>::iterator iter;
    for (iter = shapeObjects.begin() ; iter != shapeObjects.end() ; ++iter) {
        delete iter->second;
    }
    shapeObjects.clear();
}

void GB2ShapeCache::addFixturesToBody(b2Body *body, const std::string &shape,bool  isCollied) {
    std::map<std::string, BodyDef *>::iterator pos = shapeObjects.find(shape);
    assert(pos != shapeObjects.end());

    BodyDef *so = (*pos).second;

    FixtureDef *fix = so->fixtures;

    while (fix) {
        if (isCollied)
            fix->fixture.userData = (void*)1;
        body->CreateFixture(&fix->fixture);
        fix = fix->next;
    }
}

cocos2d::CCPoint GB2ShapeCache::anchorPointForShape(const std::string &shape) {
    std::map<std::string, BodyDef *>::iterator pos = shapeObjects.find(shape);
    assert(pos != shapeObjects.end());

    BodyDef *bd = (*pos).second;
    return bd->anchorPoint;
}

//typedef CCDictionary<std::string, CCObject*> ObjectDict;
//typedef CCDictionary<char*,CCObject*> ObjectDict;

/*
void GB2ShapeCache::addShapesWithFile(const std::string &plist) {
	//const char *fullName = CCFileUtils::fullPathFromRelativePath(plist.c_str());
	const char *fullName = CCFileUtils::sharedFileUtils()->fullPathFromRelativeFile(plist.c_str());
	//ObjectDict *dict = CCFileUtils::dictionaryWithContentsOfFile(fullName);
	CCDictionary *dict =CCDictionary::createWithContentsOfFile(fullName);

	//CCFileUtils::sharedFileUtils()->createCCDictionaryWithContentsOfFile(fullName);
	CCAssert(dict != NULL, "Shape-file not found"); // not triggered - cocos2dx delivers empty dict if non was found
    CCAssert(dict->count() != 0, "plist file empty or not existing");


	ObjectDict *metadataDict = (ObjectDict *)dict->objectForKey("metadata");
    int format = static_cast<CCString *>(metadataDict->objectForKey("format"))->toInt();
    ptmRatio = static_cast<CCString *>(metadataDict->objectForKey("ptm_ratio"))->toFloat();
	CCAssert(format == 1, "Format not supported");

	//int format = (CCDictElement *)dict->objectForKey("metadata");

	ObjectDict *bodyDict = (ObjectDict *)dict->objectForKey("bodies");

    b2Vec2 vertices[b2_maxPolygonVertices];

	ObjectDict::CCObjectMapIter iter;

	bodyDict->begin();
	std::string bodyName;
	ObjectDict *bodyData;
	while ((bodyData = (ObjectDict *)bodyDict->next(&bodyName))) {
		BodyDef *bodyDef = new BodyDef();
		bodyDef->anchorPoint = CCPointFromString(static_cast<CCString *>(bodyData->objectForKey("anchorpoint"))->toStdString().c_str());

		CCMutableArray<ObjectDict *> *fixtureList = (CCMutableArray<ObjectDict *> *)(bodyData->objectForKey("fixtures"));
        FixtureDef **nextFixtureDef = &(bodyDef->fixtures);

		CCMutableArray<ObjectDict *>::CCMutableArrayIterator iter;
		for (iter = fixtureList->begin(); iter != fixtureList->end(); ++iter) {
            b2FixtureDef basicData;
            ObjectDict *fixtureData = *iter;

            basicData.filter.categoryBits = static_cast<CCString *>(fixtureData->objectForKey("filter_categoryBits"))->toInt();
            basicData.filter.maskBits = static_cast<CCString *>(fixtureData->objectForKey("filter_maskBits"))->toInt();
            basicData.filter.groupIndex = static_cast<CCString *>(fixtureData->objectForKey("filter_groupIndex"))->toInt();
            basicData.friction = static_cast<CCString *>(fixtureData->objectForKey("friction"))->toFloat();
            basicData.density = static_cast<CCString *>(fixtureData->objectForKey("density"))->toFloat();
            basicData.restitution = static_cast<CCString *>(fixtureData->objectForKey("restitution"))->toFloat();
            basicData.isSensor = (bool)static_cast<CCString *>(fixtureData->objectForKey("isSensor"))->toInt();

			CCString *cb = static_cast<CCString *>(fixtureData->objectForKey("userdataCbValue"));

            int callbackData = 0;

			if (cb)
				callbackData = cb->toInt();

			std::string fixtureType = static_cast<CCString *>(fixtureData->objectForKey("fixture_type"))->toStdString();

			if (fixtureType == "POLYGON") {
				CCMutableArray<ObjectDict *> *polygonsArray = (CCMutableArray<ObjectDict *> *)(fixtureData->objectForKey("polygons"));
				CCMutableArray<ObjectDict *>::CCMutableArrayIterator iter;

				for (iter = polygonsArray->begin(); iter != polygonsArray->end(); ++iter) {
                    FixtureDef *fix = new FixtureDef();
                    fix->fixture = basicData; // copy basic data
                    fix->callbackData = callbackData;

                    b2PolygonShape *polyshape = new b2PolygonShape();
                    int vindex = 0;

					CCMutableArray<CCString *> *polygonArray = (CCMutableArray<CCString *> *)(*iter);

                    assert(polygonArray->count() <= b2_maxPolygonVertices);

					CCMutableArray<CCString *>::CCMutableArrayIterator piter;

					for (piter = polygonArray->begin(); piter != polygonArray->end(); ++piter) {
                        CCPoint offset = CCPointFromString((*piter)->toStdString().c_str());
                        vertices[vindex].x = (offset.x / ptmRatio) ;
                        vertices[vindex].y = (offset.y / ptmRatio) ;
                        vindex++;
                    }

                    polyshape->Set(vertices, vindex);
                    fix->fixture.shape = polyshape;

                    // create a list
                    *nextFixtureDef = fix;
                    nextFixtureDef = &(fix->next);
				}

			} else if (fixtureType == "CIRCLE") {
				FixtureDef *fix = new FixtureDef();
                fix->fixture = basicData; // copy basic data
                fix->callbackData = callbackData;

                ObjectDict *circleData = (ObjectDict *)fixtureData->objectForKey("circle");

                b2CircleShape *circleShape = new b2CircleShape();

                circleShape->m_radius = static_cast<CCString *>(circleData->objectForKey("radius"))->toFloat() / ptmRatio;
				CCPoint p = CCPointFromString(static_cast<CCString *>(circleData->objectForKey("position"))->toStdString().c_str());
                circleShape->m_p = b2Vec2(p.x / ptmRatio, p.y / ptmRatio);
                fix->fixture.shape = circleShape;

                // create a list
                *nextFixtureDef = fix;
                nextFixtureDef = &(fix->next);

			} else {
				CCAssert(0, "Unknown fixtureType");
			}

			// add the body element to the hash
			shapeObjects[bodyName] = bodyDef;
		}
	}
}*/


void GB2ShapeCache::addShapesWithFile(const char *plist)
{
    CCDictionary *plistDict = CCDictionary::createWithContentsOfFile(plist);
    CCAssert(plistDict !=NULL,"shape file not found");

    if (plistDict !=NULL)
    {
        CCLog("success\n");
    }

    CCDictionary *metaDict =static_cast<CCDictionary *>(plistDict->objectForKey("metadata"));
    CCAssert(metaDict !=NULL,"error");

    int format = dynamic_cast<CCString *>(metaDict->objectForKey("format"))->intValue();
    float ptmRatio = dynamic_cast<CCString *>(metaDict->objectForKey("ptm_ratio"))->floatValue();

#ifdef DEBUG
    CCLog("%d\t%2.2f\n",format,ptmRatio);
#endif

    b2Vec2 vertices[b2_maxPolygonVertices];

    CCDictionary *bodyDict = dynamic_cast<CCDictionary *>(plistDict->objectForKey("bodies"));
    if (bodyDict !=NULL)
    {
        CCLog("success\n");
        CCDictElement *element;

        std::string bodyName;
        CCDICT_FOREACH(bodyDict,element)
        {
            const char *name = element->getStrKey();
            bodyName.append(name);
            CCDictionary *itemDict = static_cast<CCDictionary *>(element->getObject());
            if (itemDict !=NULL)
            {
                BodyDef *bodyDef = new BodyDef();
                bodyDef->anchorPoint = CCPointFromString(itemDict->valueForKey("anchorpoint")->getCString());
                FixtureDef **nextFixtureDef = &(bodyDef->fixtures);

                CCArray *itemArray = static_cast<CCArray *>(itemDict->objectForKey("fixtures"));

                CCObject *obj;
                CCARRAY_FOREACH(itemArray,obj)
                {
                    b2FixtureDef basicData;
                    CCDictionary *item = static_cast<CCDictionary *>(obj);
                    basicData.filter.categoryBits = static_cast<CCString *>(item->objectForKey("filter_categoryBits"))->intValue();
                    basicData.filter.maskBits = static_cast<CCString *>(item->objectForKey("filter_maskBits"))->intValue();
                    basicData.filter.groupIndex = static_cast<CCString *>(item->objectForKey("filter_groupIndex"))->intValue();
                    basicData.friction = static_cast<CCString *>(item->objectForKey("friction"))->floatValue();
                    basicData.density = static_cast<CCString *>(item->objectForKey("density"))->floatValue();
                    basicData.restitution = static_cast<CCString *>(item->objectForKey("restitution"))->floatValue();
                    basicData.isSensor = (bool)static_cast<CCString *>(item->objectForKey("isSensor"))->intValue();

                    CCString *cb = static_cast<CCString *>(item->objectForKey("userdataCbValue"));

                    int callbackData = 0;

                    if (cb)
                        callbackData = cb->intValue();

                    const char *fixtureType = static_cast<CCString *>(item->objectForKey("fixture_type"))->getCString();

                    if (strcmp(fixtureType,"POLYGON") == 0)
                    {
                        CCArray *itemArray  = static_cast<CCArray *>(item->objectForKey("polygons"));
                        CCObject *obj;

                        CCARRAY_FOREACH(itemArray,obj)
                        {
                            FixtureDef *fix = new FixtureDef();
                            fix->fixture = basicData; // copy basic data
                            fix->callbackData = callbackData;

                            b2PolygonShape *polyshape = new b2PolygonShape();
                            int vindex = 0;

                            CCArray *array = static_cast<CCArray *>(obj);

                            CCObject *objItem;

                            CCARRAY_FOREACH(array,objItem)
                            {
                                CCPoint offset = CCPointFromString(static_cast<CCString *>(objItem)->getCString());
                                vertices[vindex].x = (offset.x / ptmRatio) ;
                                vertices[vindex].y = (offset.y / ptmRatio) ;
                                vindex++;
                            }

                            polyshape->Set(vertices, vindex);
                            fix->fixture.shape = polyshape;

                            // create a list
                            *nextFixtureDef = fix;
                            nextFixtureDef = &(fix->next);
                        }
                    }
                    else if (strcmp(fixtureType,"CIRCLE")==0)
                    {
                        /*FixtureDef *fix = new FixtureDef();
                        fix->fixture = basicData; // copy basic data
                        fix->callbackData = callbackData;

                        ObjectDict *circleData = (ObjectDict *)fixtureData->objectForKey("circle");

                        b2CircleShape *circleShape = new b2CircleShape();

                        circleShape->m_radius = static_cast<CCString *>(circleData->objectForKey("radius"))->toFloat() / ptmRatio;
                        CCPoint p = CCPointFromString(static_cast<CCString *>(circleData->objectForKey("position"))->toStdString().c_str());
                        circleShape->m_p = b2Vec2(p.x / ptmRatio, p.y / ptmRatio);
                        fix->fixture.shape = circleShape;

                        // create a list
                        *nextFixtureDef = fix;
                        nextFixtureDef = &(fix->next);*/

                    }
                    else
                    {
                        CCLog("error\n");
                    }
                    std::cout<<"********************"<<bodyName<<endl;
                    shapeObjects[bodyName] = bodyDef;
                }
            }
        }
    }

}