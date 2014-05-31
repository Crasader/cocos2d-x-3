#ifndef APP_UTIL_H
#define APP_UTIL_H

#include "cocos2d.h"
#include "support/tinyxml2/tinyxml2.h"
#include <vector>

#include "rapidxml.hpp"
#include "rapidxml_iterators.hpp"
#include "rapidxml_print.hpp"
#include "rapidxml_utils.hpp"

USING_NS_CC;

using namespace std;

class AppUtil 
{
public:
	AppUtil();
	static AppUtil *getInstance();
	static AppUtil *appUtils;
	void readChinesValue();
	void readMonsterData();
	void writeXml();
	void parseXml();

	void writeXmlWithRapid();
	void readXmlWithRapid();
private:
	map<string,string> m_mapChinesString;
	map<string,string> m_mapEnglishString;
};

#endif