void GB2ShapeCache::addShapesWithFile(const std::string &plist) {
	//const char *fullName = CCFileUtils::fullPathFromRelativePath(plist.c_str());
	const char *fullName = CCFileUtils::sharedFileUtils()->fullPathFromRelativeFile(plist.c_str());
	//ObjectDict *dict = CCFileUtils::dictionaryWithContentsOfFile(fullName);
	CCDictionary *dict =CCDictionary::createWithContentsOfFile(fullName);

/*	//CCFileUtils::sharedFileUtils()->createCCDictionaryWithContentsOfFile(fullName);
	CCAssert(dict != NULL, "Shape-file not found"); // not triggered - cocos2dx delivers empty dict if non was found
    CCAssert(dict->count() != 0, "plist file empty or not existing");
	*/

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
}